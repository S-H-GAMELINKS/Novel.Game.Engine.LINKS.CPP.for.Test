
#include "DxLib.h"
#include "ConstantExpressionVariable.h"
#include "ConfigMenu.h"
#include <cstdint>
#include <thread>
#include <chrono>

extern ConfigData_t ConfigData;

namespace KeyState {

	//�L�[���씻��̃e���v���[�g
	std::int32_t KeyMoveTemplate(std::int32_t CursorPosY, std::int32_t TopPosY, std::int32_t ButtomPosY, std::int32_t Move, std::int32_t Flag) {
		if (Flag == 0) {
			if (DxLib::CheckHitKey(KEY_INPUT_DOWN) == 1)
				CursorPosY = (ButtomPosY == CursorPosY) ? TopPosY : CursorPosY + Move;

			if (DxLib::CheckHitKey(KEY_INPUT_UP) == 1)
				CursorPosY = (TopPosY == CursorPosY) ? ButtomPosY : CursorPosY - Move;

			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}

		return CursorPosY;
	}
}

namespace MouseState {

	std::int32_t MousePosY, MousePosX;

	//�^�C�g�����j���[�̃}�E�X����
	std::int32_t GameTitleMenuMouseMove(std::int32_t CursorPosY) noexcept {

		DxLib::GetMousePoint(&MousePosX, &MousePosY);

		if (ConfigData.MouseAndKeyFlag == 1) {
			CursorPosY = (MousePosY <= 329) ? TitleMenuPosY
				: (MousePosY <= (TitleMenuPosY + CursorMove * 2) - 1) ? TitleMenuPosY + CursorMove
				: (MousePosY <= (TitleMenuPosY + CursorMove * 3) - 1) ? TitleMenuPosY + CursorMove * 2
				: (MousePosY <= (TitleMenuPosY + CursorMove * 4) - 1) ? TitleMenuPosY + CursorMove * 3
				: (MousePosY <= TitleMenuExitPosY - 1) ? TitleMenuPosY + CursorMove * 4
				: TitleMenuExitPosY;
		}

		return CursorPosY;
	}

	//�R���t�B�O��ʃ}�E�X����
	std::int32_t ConfigMenuMouseMove(std::int32_t ConfigCursorPosY) noexcept {

		DxLib::GetMousePoint(&MousePosX, &MousePosY);

		if (ConfigData.MouseAndKeyFlag == 1) {
			ConfigCursorPosY = (MousePosY <= (GameMenuBasePosY * 2) - 1) ? GameMenuBasePosY
				: (MousePosY <= (GameMenuBasePosY * 3) - 1) ? GameMenuBasePosY * 2
				: (MousePosY <= (GameMenuBasePosY * 4) - 1) ? GameMenuBasePosY * 3
				: (MousePosY <= (GameMenuBasePosY * 5) - 1) ? GameMenuBasePosY * 4
				: (MousePosY <= (GameMenuBasePosY * 6) - 1) ? GameMenuBasePosY * 5
				: (MousePosY <= (GameMenuBasePosY * 7) - 1) ? GameMenuBasePosY * 6
				: GameMenuBasePosY * 7;
		}

		return ConfigCursorPosY;
	}

	//�Q�[�����j���[�̃}�E�X����
	std::int32_t GameMenuMouseMove(std::int32_t GameMenuCursorPosY) noexcept {

		DxLib::GetMousePoint(&MousePosX, &MousePosY);

		if (ConfigData.MouseAndKeyFlag == 1) {
			GameMenuCursorPosY = (MousePosY <= (GameMenuBasePosY * 2) - 1) ? GameMenuBasePosY
				: (MousePosY <= (GameMenuBasePosY * 3) - 1) ? (GameMenuBasePosY * 2)
				: (MousePosY <= (GameMenuBasePosY * 4) - 1) ? (GameMenuBasePosY * 3)
				: (MousePosY <= (GameMenuBasePosY * 5) - 1) ? (GameMenuBasePosY * 4)
				: (MousePosY <= (GameMenuBasePosY * 6) - 1) ? (GameMenuBasePosY * 5)
				: (MousePosY <= (GameMenuBasePosY * 7) - 1) ? (GameMenuBasePosY * 6)
				: (MousePosY <= (GameMenuBasePosY * 8) - 1) ? (GameMenuBasePosY * 7)
				: (MousePosY <= (GameMenuBasePosY * 9) - 1) ? (GameMenuBasePosY * 8)
				: (MousePosY <= (GameMenuBasePosY * 10) - 1) ? (GameMenuBasePosY * 9)
				: (MousePosY <= (GameMenuBasePosY * 11) - 1) ? (GameMenuBasePosY * 10)
				: (MousePosY <= (GameMenuBasePosY * 12) - 1) ? (GameMenuBasePosY * 11)
				: (GameMenuBasePosY * 12);
		}

		return GameMenuCursorPosY;
	}

	//�I�����}�E�X����
	std::int32_t ChoiceMouseMove(std::int32_t ChoiceCursorPosY) noexcept {

		DxLib::GetMousePoint(&MousePosX, &MousePosY);

		if (ConfigData.MouseAndKeyFlag == 1) {
			ChoiceCursorPosY = (MousePosY <= (ChoicePosY[1] - 1)) ? ChoicePosY[0] : ChoicePosY[1];
		}

		return ChoiceCursorPosY;
	}

	//�Z�[�u�f�[�^���j���[�}�E�X����
	std::int32_t SaveDataMenuMouseMove(std::int32_t SaveDataMenuPosY) noexcept {

		DxLib::GetMousePoint(&MousePosX, &MousePosY);

		if (ConfigData.MouseAndKeyFlag == 1) {
			SaveDataMenuPosY = (MousePosY <= (SaveDataBasePosY * 2) - 1) ? SaveDataBasePosY
				: (MousePosY <= (SaveDataBasePosY * 3) - 1) ? SaveDataBasePosY * 2
				: (MousePosY <= (SaveDataBasePosY * 4) - 1) ? SaveDataBasePosY * 3
				: SaveDataPosButtom;
		}

		return SaveDataMenuPosY;
	}
}

namespace MouseAndKey {

	//�}�E�X���L�[�m�F�i�E�j
	bool CheckMouseAndKeyRight() {
		return (ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RIGHT) == 1) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_RIGHT)) ? true : false;
	}

	//�}�E�X���L�[�m�F�i���j
	bool CheckMouseAndKeyLeft() {
		return (ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_LEFT) == 1) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT)) ? true : false;
	}

	//�}�E�X���L�[�m�F�i����j
	bool CheckMouseAndKeyEnter() {
		return (ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1) ||  ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT) ? true : false;
	}
}