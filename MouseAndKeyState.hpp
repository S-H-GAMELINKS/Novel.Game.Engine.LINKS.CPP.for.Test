#ifndef MOUSE_AND_KEY_STATE_
#define MOUSE_AND_KEY_STATE_

#include <cstdint>

namespace KeyState {

	//�L�[���씻��̃e���v���[�g
	std::int32_t KeyMoveTemplate(std::int32_t CursorPosY, std::int32_t TopPosY, std::int32_t ButtomPosY, std::int32_t Move, std::int32_t Flag);
}

namespace MouseState {

	//�}�E�X���씻��̃e���v���[�g
	std::int32_t MouseMoveTemplate(std::int32_t CursorPosY, std::int32_t TopPosY, std::int32_t Move, std::int32_t Num, std::int32_t Flag);
}

namespace MouseAndKey {

	//�}�E�X���L�[�m�F�i�E�j
	bool CheckMouseAndKeyRight();

	//�}�E�X���L�[�m�F�i���j
	bool CheckMouseAndKeyLeft();

	//�}�E�X���L�[�m�F�i����j
	bool CheckMouseAndKeyEnter();
}

#endif // !MOUSE_AND_KEY_STATE_