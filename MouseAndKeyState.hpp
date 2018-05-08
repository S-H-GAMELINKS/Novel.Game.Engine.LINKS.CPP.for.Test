#ifndef MOUSE_AND_KEY_STATE_
#define MOUSE_AND_KEY_STATE_

#include <cstdint>

namespace KeyState {

	//�^�C�g�����j���[�̃L�[����
	std::int32_t GameTitleMenuKeyMove(std::int32_t CursorPosY) noexcept;

	//�R���t�B�O��ʃL�[����
	std::int32_t ConfigMenuKeyMove(std::int32_t ConfigCursorPosY) noexcept;

	//�Q�[�����j���[�L�[����
	std::int32_t GameMenuKeyMove(std::int32_t GameMenuCursorPosY) noexcept;

	//�I�����L�[����
	std::int32_t ChoiceKeyMove(std::int32_t ChoiceCursorPosY) noexcept;

	//�Z�[�u�f�[�^���j���[�L�[����
	std::int32_t SaveDataMenuKeyMove(std::int32_t SaveDataMenuPosY) noexcept;
}

namespace MouseState {

	//�^�C�g�����j���[�̃}�E�X����
	std::int32_t GameTitleMenuMouseMove(std::int32_t CursorPosY) noexcept;

	//�R���t�B�O��ʃ}�E�X����
	std::int32_t ConfigMenuMouseMove(std::int32_t ConfigCursorPosY) noexcept;

	//�Q�[�����j���[�̃}�E�X����
	std::int32_t GameMenuMouseMove(std::int32_t GameMenuCursorPosY) noexcept;

	//�I�����}�E�X����
	std::int32_t ChoiceMouseMove(std::int32_t ChoiceCursorPosY) noexcept;

	//�Z�[�u�f�[�^���j���[�}�E�X����
	std::int32_t SaveDataMenuMouseMove(std::int32_t SaveDataMenuPosY) noexcept;
}

namespace MouseAndKey {

	//�}�E�X���L�[�m�F�i�E�j
	bool CheckMouseAndKeyRight();

	//�}�E�X���L�[�m�F�i���j
	bool CheckMouseAndKeyLeft();
}

#endif // !MOUSE_AND_KEY_STATE_