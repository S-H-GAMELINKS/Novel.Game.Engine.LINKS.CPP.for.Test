//Script Tag Task Maneger Source
#define _SCL_SECURE_NO_WARNINGS 

#include "DxLib.h"
#include "ConstantExpressionVariable.h"
#include "Utility.h"
#include "Choice.h"
#include "ConfigMenu.h"
#include "BackLog.h"
#include "MouseAndKeyState.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include <thread>
#include <chrono>
#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;

extern int DrawPointX, DrawPointY;	// ������`��̈ʒu
extern int Sp, Cp;	// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^

//�I���t���O
extern int EndFlag;

//�e��f�ރn���h��
extern std::int32_t BackGroundHandle, CharacterHandle, BackGroundMusicHandle, SoundEffectHandle, ImageEffectHandle;

// ���ǃX�L�b�v/�X�L�b�v/�I�[�g�ϐ�
extern int SkipAndAutoFlag;

extern struct ConfigData_t ConfigData;

//�f�ޗp�G�C���A�X
template <class T>
using Material = std::vector<T>;

//�X�N���v�g�p�G�C���A�X
using Script = const std::vector<std::string>;

//�����G�폜���Q�[���I�[�o�[�p�G�C���A�X
using unique = std::unique_ptr<int>;

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

	//�������x�֐�
	void DrawSpeed(const int& Speed, const int& SpeedVolume) {
		std::this_thread::sleep_for(std::chrono::milliseconds(SpeedVolume * Speed / 100));
	}

	//������`�摬�x
	void DrawScriptSpeed() noexcept {
		switch (SkipAndAutoFlag) {
		case 0:
			DrawSpeed(StringSpeedAuto, ConfigData.ScriptDrawSpeedVolume);
			break;

		case 1:
			DrawSpeed(StringSpeedSkip, ConfigData.SkipSpeedVolumeCount);
			break;

		case 2:
			DrawSpeed(StringSpeedAuto, ConfigData.AutoSpeedVolume);
			break;
		}
	}

	//������`��֐�
	void DrawScript(Script& Script) noexcept {
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

	//�f�ޔԍ�����
	int MaterialNumCheck(const Script& Script, const char* Tag) {

		std::string str = Script[Sp];

		sregex rex = sregex::compile(Tag);
		smatch what;
		regex_search(str, what, rex);
		std::string text(what[1]);
		int n = std::stoi(text);

		return n - 1;

	}

	//�w�i�摜�`��֐�
	template <typename T, typename Func>
	void DrawImages(Script& Script, Material<T>& Material, Func&& DrawFunc, T& Handle, const char* Tag) noexcept {
		Cp++;
		Handle = Material[MaterialNumCheck(Script, Tag)];
		DrawFunc(Handle);
	}

	//�����G�폜�����֐�
	void RemoveCharacterGraph() noexcept {
		unique CharacterDummy = std::make_unique<int>(DxLib::DerivationGraph(CharacterPosX, CharacterPosY, CharacterGraphSizeWidth, CharacterGraphSizeHeight, BackGroundHandle));
		DxLib::DrawGraph(CharacterPosX, CharacterPosY, *CharacterDummy, true);
	}

	//�����G�`��֐�
	void DrawCharacter(Script& Script, Material<int>& Character) noexcept {
		Cp++;

		ScriptTask::RemoveCharacterGraph();

		CharacterHandle = Character[MaterialNumCheck(Script, "C(\\d+)")];
		DxLib::DrawGraph(CharacterPosX, CharacterPosY, CharacterHandle, TRUE);
	}

	//���ʃZ�b�g�֐�
	void ChangeSoundVolumne() {
		DxLib::ChangeVolumeSoundMem(255 * ConfigData.BackGroundMusicVolume / 100, BackGroundMusicHandle);
		DxLib::ChangeVolumeSoundMem(255 * ConfigData.SoundEffectVolume / 100, SoundEffectHandle);
	}

	//�����Đ��m�F�֐�
	void CheckSoundPlay(const int& Handle) {
		//BGM�Đ����̏ꍇ�́ABGM���~����
		if (DxLib::CheckSoundMem(Handle))
			DxLib::StopSoundMem(Handle);
	}

	//�����Đ��֐�
	template <typename T>
	void PlaySounds(Script& Script, Material<int>& Material, T& Handle, const T& PlayType, const char* Tag) noexcept {
		
		CheckSoundPlay(Handle);

		Cp++;
		Handle = Material[MaterialNumCheck(Script, Tag)];

		ChangeSoundVolumne();
		
		DxLib::PlaySoundMem(Handle, PlayType);
	}

	//����Đ��֐�
	void PlayMovie(Script& Script, Material<std::string>& Movie) noexcept {
		Cp++;
		DxLib::PlayMovie(Movie[MaterialNumCheck(Script, "V(\\d+)")].c_str(), 1, DX_MOVIEPLAYTYPE_BCANCEL);
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
	void Comment(Script& Script) noexcept {
		if (Script[Sp][Cp] == '/') {
			Cp = 0;
			Sp++;
		}
	}

	//�N���b�N�҂������֐�
	void ClickWait() noexcept {
		if (SkipAndAutoFlag == 0) {
			DxLib::WaitKey();
			if (MouseAndKey::CheckMouseAndKeyEnter())
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
		unique GameOverHandle = std::make_unique<std::int32_t>(DxLib::LoadGraph("DATA/BACKGROUND/GAMEOVER.png"));
		DxLib::DrawGraph(0, 0, *GameOverHandle, TRUE);
	}
}

//�X�N���v�g�^�O�����֐�
void ScriptTagTaskManager(Material<std::string>& Script, Material<int>& BackGround, Material<int>& Character, Material<int>& BackGroundMusic, Material<int>& SoundEffect, Material<std::string>& Movie, Material<int>& ImageEffect) noexcept {

	switch (Script[Sp][Cp])
	{
	case 'B':	//�w�i�摜�`��
		ScriptTask::DrawImages(Script, BackGround, [](int Handle) {DxLib::DrawGraph(0, 0, Handle, TRUE); }, BackGroundHandle, "B(\\d+)");
		break;

	case 'C':	//�����G�摜�`��
		ScriptTask::DrawCharacter(Script, Character);
		break;

	case 'M':	//BGM�Đ�
		ScriptTask::PlaySounds(Script, BackGroundMusic, BackGroundMusicHandle, DX_PLAYTYPE_LOOP, "M(\\d+)");
		break;

	case 'S':	//SE�Đ�
		ScriptTask::PlaySounds(Script, SoundEffect, SoundEffectHandle, DX_PLAYTYPE_BACK, "S(\\d+)");
		break;

	case 'V':	//����Đ�
		ScriptTask::PlayMovie(Script, Movie);
		break;

	case 'I':	//�C���[�W�G�t�F�N�g�`��
		ScriptTask::DrawImages(Script, ImageEffect, [](int Handle) { DxLib::DrawGraph(0, 0, Handle, TRUE); }, ImageEffectHandle, "I(\\d+)");
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