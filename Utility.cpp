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

//�Q�[���^�C�g����
extern const char* GameTitle;

extern int Sp, Cp;	// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^

//�I���t���O
extern int EndFlag;

//�e��f�ރn���h��
extern std::int32_t BackGroundHandle, CharacterHandle, BackGroundMusicHandle, SoundEffectHandle;

//������`��ʒu
extern int DrawPointX, DrawPointY;

//temp�f�[�^
extern int EndFlagTemp, SpTemp;

extern ConfigData_t ConfigData;

namespace {

	//������~���Ԍv�Z�֐�
	template <typename T>
	decltype(auto) WaitTimeCalc(const T var) noexcept {
		return var * var;
	}

	//�Q�[����ʍĕ`�揈��
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

//���b�Z�[�W�{�b�N�X(Yes or No)
int MessageBoxYesNo(LPCTSTR lpText) noexcept
{
	return MessageBox(
		DxLib::GetMainWindowHandle(),
		lpText,
		GameTitle,
		MB_YESNO
	);
}

//���b�Z�[�W�{�b�N�X(OK)
int MessageBoxOk(LPCTSTR lpText) noexcept
{
	return MessageBox(
		DxLib::GetMainWindowHandle(),
		lpText,
		GameTitle,
		MB_OK
	);
}

//��ʃN���A�����֐�
void ScreenClear() noexcept {
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	SetDrawScreen(DX_SCREEN_FRONT);
}

//�Q�[���I���m�F�E�C���h�E
void GameEndMessageBox() noexcept {

		if (IDYES == MessageBoxYesNo("�I�����܂����H"))
			EndFlag = 99;

		if (EndFlag != 99 && EndFlag != 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitTimeCalc(WaitKeyTaskTime) / WaitGameTime));
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
}

//�X�N���[���V���b�g�擾�֐�
void ScreenShotGet() noexcept {
	if (IDYES == MessageBoxYesNo("�X�N���[���V���b�g���擾���܂����H")) {
		static std::int32_t ScreenShotCount;
		std::string FileName = "DATA/SCREENSHOT/SCREENSHOT";
		FileName += std::to_string(ScreenShotCount + 1);
		FileName += ".png";

		DxLib::SaveDrawScreenToPNG(0, 0, 640, 480, FileName.c_str());
		ScreenShotCount++;
	}
}

namespace {

	//�Z�[�u�f�[�^�֘A
	void SaveData(const int Num) {
		SpTemp = Sp;
		SaveDataLoop(Num);
		DrawGameScreenAgain();
	}

	//�X�L�b�v�E�I�[�g�֌W
	void SkipAndAuto(const int Num) {
		SpTemp = Sp;
		SkipAndAutoTask(Num);
		DrawGameScreenAgain();
	}

	//�o�b�N���O�֌W
	void BackLog() {
		SpTemp = Sp;
		BackLogLoop();
		DrawGameScreenAgain();
	}

	//�R���t�B�O�֌W
	void Config() {
		SpTemp = Sp;
		ConfigMenuLoop();
		DrawGameScreenAgain();
	}

	//�^�C�g���֖߂�
	void BackToTitle() {
		if (IDYES == MessageBoxYesNo("�^�C�g����ʂɖ߂�܂����H")) {
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

	//�N�C�b�N�Z�[�u
	void QuickSave() {
		SpTemp = Sp;
		QuickSaveDataSave();
		DrawGameScreenAgain();
	}

	//�X�N���[���V���b�g
	void ScreenShot() {
		ScreenShotGet();
		Cp = 0;
		DrawPointX = 0;
		DrawPointY = 0;
		DxLib::PlaySoundMem(BackGroundMusicHandle, DX_PLAYTYPE_LOOP);
		DxLib::DrawGraph(0, 0, BackGroundHandle, TRUE);
		DxLib::DrawGraph(150, 130, CharacterHandle, TRUE);
	}

	//�Q�[�����j���[
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

//�e��V���[�g�J�b�g�L�[
void ShortCutKey() noexcept {

	if (DxLib::CheckHitKey(KEY_INPUT_F1) == 1)
		SaveData(1);

	if (DxLib::CheckHitKey(KEY_INPUT_F2) == 1)
		SaveData(2);

	if (DxLib::CheckHitKey(KEY_INPUT_F3) == 1)
		SaveData(3);

	if (DxLib::CheckHitKey(KEY_INPUT_F4) == 1)
		SkipAndAuto(3);

	if (DxLib::CheckHitKey(KEY_INPUT_F5) == 1)
		SkipAndAuto(1);

	if (DxLib::CheckHitKey(KEY_INPUT_F6) == 1)
		SkipAndAuto(2);

	if (DxLib::CheckHitKey(KEY_INPUT_F7) == 1)
		SkipAndAuto(0);

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

	//�Q�[���I���m�F�E�C���h�E
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		GameEndMessageBox();
}

//�^�C�g�����[�r�[����
void TitleMoviePlay() noexcept {
	PlayMovie("DATA/MOVIE/OP.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
	ScreenClear();
}