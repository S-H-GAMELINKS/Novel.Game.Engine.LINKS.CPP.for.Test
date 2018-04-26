//Script Tag Task Maneger Source
#include "DxLib.h"
#include "ConstantExpressionVariable.h"
#include "Utility.h"
#include "Choice.h"
#include "ConfigMenu.h"
#include "BackLog.h"
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include <thread>
#include <chrono>

extern int DrawPointX, DrawPointY;	// ������`��̈ʒu
extern int Sp, Cp;	// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^

//�I���t���O
extern int EndFlag;

//�e��f�ރn���h��
extern std::int32_t BackGroundHandle;
extern std::int32_t CharacterHandle;
extern std::int32_t BackGroundMusicHandle;
extern std::int32_t SoundEffectHandle;
extern std::int32_t ImageEffectHandle;

// ���ǃX�L�b�v/�X�L�b�v/�I�[�g�ϐ�
extern int SkipAndAutoFlag;

extern struct ConfigData_t ConfigData;

namespace ScriptTask {

	char OneMojiBuf[3];	// �P�������ꎞ�L���z��

	// ���s�֐�
	void Kaigyou() noexcept {
		int TempGraph;

		// �`��s�ʒu���������
		DrawPointY++;

		// �`�����ŏ��ɖ߂�
		DrawPointX = 0;

		// ������ʂ���͂ݏo��Ȃ��ʂ��X�N���[��������
		if (DrawPointY * MojiSize + MojiSize > 480)
		{
			// �e���|�����O���t�B�b�N�̍쐬
			TempGraph = MakeGraph(640, 480);

			// ��ʂ̓��e���ہX�R�s�[����
			GetDrawScreenGraph(0, 0, 640, 480, TempGraph);

			// ��s����ɓ\��t����
			DrawGraph(0, -MojiSize, TempGraph, FALSE);

			// ��ԉ��̍s�̕��������Ŗ��߂�
			DrawBox(0, 480 - MojiSize, 640, 480, 0, TRUE);

			// �`��s�ʒu���������
			DrawPointY--;

			// �O���t�B�b�N���폜����
			DeleteGraph(TempGraph);
		}
	}

	//������`�摬�x
	void DrawScriptSpeed() noexcept {
		switch (SkipAndAutoFlag) {
		case 0:
			std::this_thread::sleep_for(std::chrono::milliseconds(StringSpeedAuto * ConfigData.ScriptDrawSpeedVolume / 100));
			break;

		case 1:
			std::this_thread::sleep_for(std::chrono::milliseconds(StringSpeedSkip * ConfigData.ScriptDrawSpeedVolume / 100));
			break;

		case 2:
			std::this_thread::sleep_for(std::chrono::milliseconds(StringSpeedAuto * ConfigData.ScriptDrawSpeedVolume / 100));
			break;
		}
	}

	//������`��֐�
	void DrawScript(const std::vector<std::string>& Script) noexcept {
		// �P�����������o��
		OneMojiBuf[0] = Script[Sp][Cp];
		OneMojiBuf[1] = Script[Sp][Cp + 1];
		OneMojiBuf[2] = '\0';

		// �P�����`��
		DrawString(DrawPointX * MojiSize, DrawPointY * MojiSize, OneMojiBuf, Color);

		// �Q�ƕ����ʒu���Q�o�C�g���߂�
		Cp += 2;

		// �J�[�\�����ꕶ�����i�߂�
		DrawPointX++;

		// �����҂�
		DrawScriptSpeed();
	}

	//�w�i�摜�`��֐�
	void DrawBackGround(const std::vector<std::string>& Script, const std::array<int, MaterialMax>& BackGround) noexcept {
		Cp++;
		BackGroundHandle = BackGround[(static_cast<int>(Script[Sp][Cp]) - 48) * 10 + (static_cast<int>(Script[Sp][Cp + 1]) - 48) - 1];
		DxLib::DrawGraph(0, 0, BackGroundHandle, TRUE);
	}

	//�����G�폜�����֐�
	void RemoveCharacterGraph() noexcept {
		std::unique_ptr<int> CharacterDummy = std::make_unique<int>(DxLib::DerivationGraph(CharacterPosX, CharacterPosY, CharacterGraphSizeWidth, CharacterGraphSizeHeight, BackGroundHandle));
		DxLib::DrawGraph(CharacterPosX, CharacterPosY, *CharacterDummy, true);
	}

	//�����G�`��֐�
	void DrawCharacter(const std::vector<std::string>& Script, const std::array<int, MaterialMax>& Character) noexcept {
		Cp++;

		ScriptTask::RemoveCharacterGraph();

		CharacterHandle = Character[(static_cast<int>(Script[Sp][Cp]) - 48) * 10 + (static_cast<int>(Script[Sp][Cp + 1]) - 48) - 1];
		DxLib::DrawGraph(CharacterPosX, CharacterPosY, CharacterHandle, TRUE);
	}

	//BGM�Đ��֐�
	void PlayBackGroundMusic(const std::vector<std::string>& Script, const std::array<int, MaterialMax>& BackGroundMusic) noexcept {

		DxLib::ChangeVolumeSoundMem(255 * ConfigData.BackGroundMusicVolume / 100, BackGroundMusicHandle);
		
		//BGM�Đ����̏ꍇ�́ABGM���~����
		if (DxLib::CheckSoundMem(BackGroundMusicHandle))
			DxLib::StopSoundMem(BackGroundMusicHandle);

		Cp++;
		BackGroundMusicHandle = BackGroundMusic[(static_cast<int>(Script[Sp][Cp]) - 48) * 10 + (static_cast<int>(Script[Sp][Cp + 1]) - 48) - 1];
		DxLib::PlaySoundMem(BackGroundMusicHandle, DX_PLAYTYPE_LOOP);
	}

	//���ʉ��Đ��֐�
	void PlaySoundEffect(const std::vector<std::string>& Script, const std::array<int, MaterialMax>& SoundEffect) noexcept {

		DxLib::ChangeVolumeSoundMem(255 * ConfigData.SoundEffectVolume / 100, SoundEffectHandle);

		//SE�Đ����̏ꍇ�́ASE���~����
		if (DxLib::CheckSoundMem(SoundEffectHandle))
			DxLib::StopSoundMem(SoundEffectHandle);

		Cp++;
		SoundEffectHandle = SoundEffect[(static_cast<int>(Script[Sp][Cp]) - 48) * 10 + (static_cast<int>(Script[Sp][Cp + 1]) - 48) - 1];
		DxLib::PlaySoundMem(SoundEffectHandle, DX_PLAYTYPE_BACK);
	}

	//����Đ��֐�
	template <typename T>
	void PlayMovie(const std::vector<T>& Script, std::array<T, MaterialMax> Movie) noexcept {
		Cp++;
		DxLib::PlayMovie(Movie[(static_cast<int>(Script[Sp][Cp]) - 48) * 10 + (static_cast<int>(Script[Sp][Cp + 1]) - 48) - 1].c_str(), 1, DX_MOVIEPLAYTYPE_BCANCEL);
	}

	//�C���[�W�G�t�F�N�g�`��֐�
	void DrawImageEffect(const std::vector<std::string>& Script, const std::array<int, MaterialMax>& ImageEffect) {
		Cp++;
		ImageEffectHandle = ImageEffect[(static_cast<int>(Script[Sp][Cp]) - 48) * 10 + (static_cast<int>(Script[Sp][Cp + 1]) - 48) - 1];
		DxLib::DrawGraph(0, 0, ImageEffectHandle, TRUE);
	}

	//��ʃN���A�����֐�
	void ClearScreen() noexcept {
		BackLogGet();
		ClearDrawScreen();
		BackGroundHandle = 0;
		CharacterHandle = 0;
		DrawPointY = 0;
		DrawPointX = 0;
	}

	//�R�����g�����֐�
	template <typename T>
	void Comment(const std::vector<T>& Script) noexcept {
		if (Script[Sp][Cp] == '/') {
			Cp = 0;
			Sp++;
		}
	}

	//�N���b�N�҂������֐�
	void ClickWait() noexcept {
		if (SkipAndAutoFlag == 0) {
			DxLib::WaitKey();
			if ((ConfigData.MouseAndKeyFlag == 0 && DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1) || (ConfigData.MouseAndKeyFlag == 1 && (DxLib::GetMouseInput() == MOUSE_INPUT_LEFT)))
				Cp++;
		}

		if (SkipAndAutoFlag == 1)
			Cp++;

		if (SkipAndAutoFlag == 2) {
			std::this_thread::sleep_for(std::chrono::milliseconds((StringSpeedAuto * StringSpeedWait * ConfigData.AutoSpeedVolume / 100)));
			Cp++;
		}

	}

	//�Q�[���I�[�o�[��ʂ̕`��
	void GameOverScreenDraw() {
		std::unique_ptr<std::int32_t> GameOverHandle = std::make_unique<std::int32_t>(DxLib::LoadGraph("DATA/BACKGROUND/GAMEOVER.png"));
		DxLib::DrawGraph(0, 0, *GameOverHandle, TRUE);
	}
}

//�X�N���v�g�^�O�����֐�
void ScriptTagTaskManager(const std::vector<std::string>& Script, const std::array<int, MaterialMax>& BackGround, const std::array<int, MaterialMax>& Character, const std::array<int, MaterialMax>& BackGroundMusic, const std::array<int, MaterialMax>& SoundEffect, const std::array<std::string, MaterialMax>& Movie, const std::array<int, MaterialMax>& ImageEffect) noexcept {

	switch (Script[Sp][Cp])
	{
	case 'B':	//�w�i�摜�`��
		ScriptTask::DrawBackGround(Script, BackGround);
		break;

	case 'C':	//�����G�摜�`��
		ScriptTask::DrawCharacter(Script, Character);
		break;

	case 'M':	//BGM�Đ�
		ScriptTask::PlayBackGroundMusic(Script, BackGroundMusic);
		break;

	case 'S':	//SE�Đ�
		ScriptTask::PlaySoundEffect(Script, SoundEffect);
		break;

	case 'V':	//����Đ�
		ScriptTask::PlayMovie(Script, Movie);
		break;

	case 'I':	//�C���[�W�G�t�F�N�g�`��
		ScriptTask::DrawImageEffect(Script, ImageEffect);
		break;

	case 'L':	//���s����
		ScriptTask::Kaigyou();
		Cp++;
		break;

	case 'P':	//�N���b�N�҂�
		ScriptTask::ClickWait();
		break;

	case 'R':	//��ʃN���A
		ScriptTask::ClearScreen();
		Cp++;
		break;

	case 'W': //�x������
		std::this_thread::sleep_for(std::chrono::seconds(WaitGameTime));
		Cp++;
		break;

	case 'G':	//�Q�[���I�[�o�[���
		ScriptTask::GameOverScreenDraw();
		Cp++;
		break;

	case 'F':	//�G���f�B���O���
		DxLib::PlayMovie("DATA/MOVIE/ENDING.wmv", 1, DX_MOVIEPLAYTYPE_NORMAL);
		Cp++;
		break;

	case 'O':	//BGM��~
		DxLib::StopSoundMem(BackGroundMusicHandle);
		Cp++;
		break;

	case 'Q':	//SE��~
		Cp++;
		DxLib::StopSoundMem(SoundEffectHandle);
		break;

	case 'D':	//�I����
		ChoiceSelect(EndFlag);
		break;

	case 'E':	//�Q�[���I��
		EndFlag = 99;
		Cp++;
		break;

	case '/':	//�R�����g
		Cp++;
		ScriptTask::Comment(Script);
		break;

	case '@':	//�����G����ʂ���폜
		ScriptTask::RemoveCharacterGraph();
		Cp++;
		break;

	case '#':	//�L�����N�^�[���`��
		Cp++;
		break;

	case ' ':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		Cp++;
		break;

	default:	// ���̑��̕���

		//������`��
		ScriptTask::DrawScript(Script);

		// ��ʂ���͂ݏo������s����
		if (DrawPointX * MojiSize + MojiSize > 640) ScriptTask::Kaigyou();

		break;
	}
}