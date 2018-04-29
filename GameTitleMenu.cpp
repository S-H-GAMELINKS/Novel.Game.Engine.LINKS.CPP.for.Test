// Game Title Menu Source 
#include "DxLib.h"
#include "ConstantExpressionVariable.h"
#include "Utility.h"
#include "SaveData.h"
#include "ConfigMenu.h"
#include "MouseAndKeyState.hpp"
#include <thread>
#include <chrono>

//�I���t���O
extern int EndFlag;

//�^�C�g�����
extern std::int32_t GameTitleGraph;

extern ConfigData_t ConfigData;

namespace {

	//�^�C�g�����j���[�̕`��֐�
	void GameTitleMenuDraw(std::int32_t CursorPosY) noexcept {

		const char* TitleMenuItem[] = { "Start", "Load", "Config", "QuickLoad", "Continue", "Exit" };

		DxLib::DrawGraph(0, 0, GameTitleGraph, TRUE);

		//�J�[�\���̕`��
		DxLib::DrawString(TitleMenuCursorPosX, CursorPosY, "��", Color);

		//�e���j���[�`��
		for (std::int32_t i = 0; i < 6; i++)
			DxLib::DrawString(TitleMenuPosX, TitleMenuPosY + 30 * i, TitleMenuItem[i], Color);
	}

	//�^�C�g�����j���[�̍��ڑI���֐�
	void GameTitleMenuChoice(const std::int32_t& CursorPosY) noexcept {

		if ((ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && CursorPosY == TitleMenuPosY) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT) && CursorPosY == TitleMenuPosY))
			EndFlag = 1;

		if ((ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && CursorPosY == TitleMenuLoadPosY) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT) && CursorPosY == TitleMenuLoadPosY))
			SaveDataLoop(2);

		if ((ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && CursorPosY == TitleMenuConfigPosY) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT) && CursorPosY == TitleMenuConfigPosY))
			ConfigMenuLoop();

		if ((ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && CursorPosY == TitleMenuQuickLoadPosY) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT) && CursorPosY == TitleMenuQuickLoadPosY))
			QuickSaveDataLoad();

		if ((ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && CursorPosY == TitleMenuContinuePosY) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT) && CursorPosY == TitleMenuContinuePosY))
			ContinueSaveDataLoad();

		if ((ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && CursorPosY == TitleMenuExitPosY) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT) && CursorPosY == TitleMenuExitPosY))
			GameEndMessageBox();
	}
}

//�^�C�g�����j���[�̃��[�v�֐�
void GameTitleMenuLoop(std::int32_t& CursorPosY) noexcept {

	while (EndFlag == 0) {
		ScreenClear();
		GameTitleMenuDraw(CursorPosY);
		CursorPosY = KeyState::GameTitleMenuKeyMove(CursorPosY);
		MouseState::GameTitleMenuMouseMove(CursorPosY);
		GameTitleMenuChoice(CursorPosY);

		//�Q�[���I���m�F�E�C���h�E
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			GameEndMessageBox();
	}
}
