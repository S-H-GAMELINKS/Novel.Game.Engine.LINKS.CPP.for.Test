
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

	//�}�E�X���씻��̃e���v���[�g
	std::int32_t MouseMoveTemplate(std::int32_t CursorPosY, std::int32_t TopPosY, std::int32_t Move, std::int32_t Num, std::int32_t Flag) {

		DxLib::GetMousePoint(&MousePosX, &MousePosY);

		if (Flag == 1) {
			for (std::int32_t i = 0; i < Num; i++) {
				if ((TopPosY + Move * i) <= MousePosY && MousePosY <= (TopPosY + Move * (i + 1) - 1))
					CursorPosY = TopPosY + Move * i;
			}
		}

		return CursorPosY;
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