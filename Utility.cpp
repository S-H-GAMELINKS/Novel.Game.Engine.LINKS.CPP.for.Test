// Utility Source

#include "DxLib.h"
#include "ConstantExpressionVariable.h"
#include "GameMenu.h"
#include "SaveData.h"
#include "ConfigMenu.h"
#include "Skip_Auto.h"
#include "BackLog.h"
#include <string>
#include <thread>
#include <chrono>

//ゲームタイトル名
extern const char* GameTitle;

extern int Sp, Cp;	// 参照する文字列番号と文字列中の文字ポインタ

//終了フラグ
extern int EndFlag;

//各種素材ハンドル
extern std::int32_t BackGroundHandle, CharacterHandle, BackGroundMusicHandle, SoundEffectHandle;

//文字列描画位置
extern int DrawPointX, DrawPointY;

//tempデータ
extern int EndFlagTemp, SpTemp;

extern ConfigData_t ConfigData;

namespace {

	//処理停止時間計算関数
	auto WaitTimeCalc(const int var) noexcept {
		return var * var;
	}

	//ゲーム画面再描画処理
	void DrawGameScreenAgain() noexcept {
		Sp = SpTemp;
		Cp = 0;
		DrawPointX = 0;
		DrawPointY = 0;
		DxLib::PlaySoundMem(BackGroundMusicHandle, DX_PLAYTYPE_LOOP);
		DxLib::DrawGraph(0, 0, BackGroundHandle, TRUE);
		DxLib::DrawGraph(150, 130, CharacterHandle, TRUE);
	}
}

//メッセージボックス(Yes or No)
int MessageBoxYesNo(LPCTSTR lpText) noexcept
{
	return MessageBox(
		DxLib::GetMainWindowHandle(),
		lpText,
		GameTitle,
		MB_YESNO
	);
}

//メッセージボックス(OK)
int MessageBoxOk(LPCTSTR lpText) noexcept
{
	return MessageBox(
		DxLib::GetMainWindowHandle(),
		lpText,
		GameTitle,
		MB_OK
	);
}

//画面クリア処理関数
void ScreenClear() noexcept {
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	SetDrawScreen(DX_SCREEN_FRONT);
}

//ゲーム終了確認ウインドウ
void GameEndMessageBox() noexcept {

		if (IDYES == MessageBoxYesNo("終了しますか？"))
			EndFlag = 99;

		if (EndFlag != 99 && EndFlag != 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitTimeCalc(WaitKeyTaskTime) / WaitGameTime));
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
}

//スクリーンショット取得関数
void ScreenShotGet() noexcept {
	if (IDYES == MessageBoxYesNo("スクリーンショットを取得しますか？")) {
		static std::int32_t ScreenShotCount;
		std::string FileName = "DATA/SCREENSHOT/SCREENSHOT";
		FileName += std::to_string(ScreenShotCount + 1);
		FileName += ".png";

		DxLib::SaveDrawScreenToPNG(0, 0, 640, 480, FileName.c_str());
		ScreenShotCount++;
	}
}

namespace {

	//セーブデータ関連
	void SaveData(const int Num) {
		SpTemp = Sp;
		SaveDataLoop(Num);
		DrawGameScreenAgain();
	}

	//スキップ・オート関係
	void SkipAndAuto(const int Num, const int EndFlag) {
		SpTemp = Sp;
		SkipAndAutoTask(Num, EndFlag);
		DrawGameScreenAgain();
	}

	//バックログ関係
	void BackLog() {
		SpTemp = Sp;
		BackLogLoop();
		DrawGameScreenAgain();
	}

	//コンフィグ関係
	void Config() {
		SpTemp = Sp;
		ConfigMenuLoop();
		DrawGameScreenAgain();
	}

	//タイトルへ戻る
	void BackToTitle() {
		if (IDYES == MessageBoxYesNo("タイトル画面に戻りますか？")) {
			DxLib::ClearDrawScreen();
			EndFlag = 0;
			Sp = 0;
			Cp = 0;
			DrawPointX = 0;
			DrawPointY = 0;
			BackGroundHandle = 0;
			CharacterHandle = 0;
			BackGroundMusicHandle = 0;
			SoundEffectHandle = 0;
		}
		else
			DrawGameScreenAgain();
	}

	//クイックセーブ
	void QuickSave() {
		SpTemp = Sp;
		QuickSaveDataSave();
		DrawGameScreenAgain();
	}

	//スクリーンショット
	void ScreenShot() {
		ScreenShotGet();
		Cp = 0;
		DrawPointX = 0;
		DrawPointY = 0;
		DxLib::PlaySoundMem(BackGroundMusicHandle, DX_PLAYTYPE_LOOP);
		DxLib::DrawGraph(0, 0, BackGroundHandle, TRUE);
		DxLib::DrawGraph(150, 130, CharacterHandle, TRUE);
	}

	//ゲームメニュー
	void GameMenu() {
		SaveDataScreenShotGet();
		DxLib::StopSoundMem(BackGroundMusicHandle);
		DxLib::StopSoundMem(SoundEffectHandle);
		EndFlagTemp = EndFlag;
		SpTemp = Sp;
		EndFlag = 17;
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitTimeCalc(WaitKeyTaskTime) / WaitGameTime));
	}
}

//各種ショートカットキー
void ShortCutKey() noexcept {

	if (DxLib::CheckHitKey(KEY_INPUT_F1) == 1)
		SaveData(1);

	if (DxLib::CheckHitKey(KEY_INPUT_F2) == 1)
		SaveData(2);

	if (DxLib::CheckHitKey(KEY_INPUT_F3) == 1)
		SaveData(3);

	if (DxLib::CheckHitKey(KEY_INPUT_F4) == 1)
		SkipAndAuto(3, EndFlag);

	if (DxLib::CheckHitKey(KEY_INPUT_F5) == 1)
		SkipAndAuto(1, EndFlag);

	if (DxLib::CheckHitKey(KEY_INPUT_F6) == 1)
		SkipAndAuto(2, EndFlag);

	if (DxLib::CheckHitKey(KEY_INPUT_F7) == 1)
		SkipAndAuto(0, EndFlag);

	if (DxLib::CheckHitKey(KEY_INPUT_F8) == 1)
		BackLog();

	if (DxLib::CheckHitKey(KEY_INPUT_F9) == 1)
		Config();

	if (DxLib::CheckHitKey(KEY_INPUT_F10) == 1)
		BackToTitle();

	if (DxLib::CheckHitKey(KEY_INPUT_F11) == 1)
		QuickSave();

	if (DxLib::CheckHitKey(KEY_INPUT_F12) == 1)
		ScreenShot();

	if (DxLib::CheckHitKey(KEY_INPUT_BACK) == 1 || (DxLib::GetMouseInput() == MOUSE_INPUT_RIGHT))
		GameMenu();

	//ゲーム終了確認ウインドウ
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		GameEndMessageBox();
}

//タイトルムービー処理
void TitleMoviePlay() noexcept {
	PlayMovie("DATA/MOVIE/OP.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
	ScreenClear();
}