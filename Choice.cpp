// Choice Source

#include "DxLib.h"
#include "ConstantExpressionVariable.h"
#include "Utility.h"
#include "BackLog.h"
#include "ConfigMenu.h"
#include "MouseAndKeyState.hpp"
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

extern int EndFlag;

//�e��f�ރn���h��
extern std::int32_t BackGroundHandle;
extern std::int32_t CharacterHandle;

extern ConfigData_t ConfigData;

//�I�����p�ϐ�
static std::string Choice[2];
const char* ChoiceScript[][2] = {
	{ "DATA/STR/CHOICE/A.txt", "DATA/STR/CHOICE/B.txt" },
	{ "DATA/STR/CHOICE/C.txt", "DATA/STR/CHOICE/D.txt" },
	{ "DATA/STR/CHOICE/E.txt", "DATA/STR/CHOICE/F.txt" },
	{ "DATA/STR/CHOICE/G.txt", "DATA/STR/CHOICE/H.txt" },
	{ "DATA/STR/CHOICE/I.txt", "DATA/STR/CHOICE/J.txt" },
	{ "DATA/STR/CHOICE/K.txt", "DATA/STR/CHOICE/L.txt" },
	{ "DATA/STR/CHOICE/M.txt", "DATA/STR/CHOICE/N.txt" }
};

namespace {

	//�I�����`��֐�
	void DrawChoice(std::int32_t& ChoiceCursorPosY) noexcept {

		DxLib::DrawGraph(0, 0, BackGroundHandle, TRUE);
		DxLib::DrawGraph(150, 130, CharacterHandle, TRUE);

		//�J�[�\���̕`��
		DxLib::DrawString(ChoicePosX, ChoiceCursorPosY, "��", Color);

		for (auto&& i : { 0, 1 })
			DxLib::DrawString(ChoicePosX + CursorMove, ChoicePosY[i], Choice[i].c_str(), Color);
	}

	//�I�����Ǎ��֐�
	void ChoiceRead() noexcept {
		if (1 <= EndFlag && EndFlag <= 7) {
			for (std::size_t i : {0, 1}) {
				std::ifstream File(ChoiceScript[EndFlag - 1][i], std::ios_base::in);
				std::getline(File, Choice[i]);
			}
		}
	}

	//�I����(��)�I��������
	void ChoiceSelectUp() noexcept {
		if (1 <= EndFlag && EndFlag <= 7) {
			BackLogGet();
			EndFlag *= 2;
		}
	}

	//�I����(��)�I��������
	void ChoiceSelectDown() noexcept {
		if (1 <= EndFlag && EndFlag <= 7) {
			BackLogGet();
			EndFlag = EndFlag * 2 + 1;
		}
	}

	//�I�����̑I�����ꂽ�����`�F�b�N
	void ChoiceSelectCheck(std::int32_t &ChoiceCursorPosY) noexcept {

		if ((ChoiceCursorPosY == ChoicePosY[0] && ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1) || (ChoiceCursorPosY == ChoicePosY[0] && ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT))) {
			ChoiceSelectUp();
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}

		if ((ChoiceCursorPosY == ChoicePosY[1] && ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1) || (ChoiceCursorPosY == ChoicePosY[1] && ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT))) {
			ChoiceSelectDown();
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}
	}
}

//�I���������֐�
void ChoiceSelect(int RoutteNumber) noexcept {

	ChoiceRead();

	std::int32_t ChoiceCursorPosY = ChoicePosY[0];

	while (EndFlag == RoutteNumber) {
		DrawChoice(ChoiceCursorPosY);
		ChoiceCursorPosY = KeyState::ChoiceKeyMove(ChoiceCursorPosY);
		MouseState::ChoiceMouseMove(ChoiceCursorPosY);
		ChoiceSelectCheck(ChoiceCursorPosY);
		ScreenClear();
		ShortCutKey();

		//�Q�[���I���m�F�E�C���h�E
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			GameEndMessageBox();
	}

}
