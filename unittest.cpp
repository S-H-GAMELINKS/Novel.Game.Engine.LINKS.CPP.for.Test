#include "stdafx.h"
#include "CppUnitTest.h"
#include "Material_Manager.h"
#include "MouseAndKeyState.hpp"
#include "BackLog.h"
#include "ConfigMenu.h"
#include "GameMenu.h"
#include "Choice.h"
#include "ScriptTask_Manager.h"
#include <iostream>
#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(LoadScriptFile)
		{
			std::vector<std::string> Script;

			for (int i = 0; i < 16; i++) {
				Script = ScriptRead(i);

				if (Script.empty())
					std::cout << "Enpty!" << std::endl;
			}
		}

		TEST_METHOD(LoadMaterial)
		{
			std::vector<int> BackGround, Character, BackGroundMusic, SoundEffect, ImageEffect;
			std::vector<std::string> Movie;

			//�w�i�摜�Ǎ��֐�
			BackGround = MaterialLoad(BackGround, "DATA/BACKGROUND", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//�����G�摜�Ǎ��֐�
			Character = MaterialLoad(Character, "DATA/CHARACTER", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//BGM�Ǎ��֐�
			BackGroundMusic = MaterialLoad(BackGroundMusic, "DATA/BACKGROUNDMUSIC", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//SE�Ǎ��֐�
			SoundEffect = MaterialLoad(SoundEffect, "DATA/SOUNDEFFECT", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//����Ǎ��֐�
			Movie = MaterialLoad(Movie, "DATA/MOVIE", [](const std::string& Path) {return std::move(Path); });

			//�C���[�W�G�t�F�N�g�Ǎ��֐�
			ImageEffect = MaterialLoad(ImageEffect, "DATA/IMAGEEFFECT", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });
		}

		TEST_METHOD(ReturnKeyFunc) {

			std::int32_t CursorPosY = TitleMenuPosY;
			
			//�^�C�g�����j���[�̃L�[����
			CursorPosY = KeyState::GameTitleMenuKeyMove(CursorPosY);

			//�R���t�B�O��ʃL�[����
			CursorPosY = KeyState::ConfigMenuKeyMove(CursorPosY);

			//�Q�[�����j���[�L�[����
			CursorPosY = KeyState::GameMenuKeyMove(CursorPosY);

			//�I�����L�[����
			CursorPosY = KeyState::ChoiceKeyMove(CursorPosY);

			//�Z�[�u�f�[�^���j���[�L�[����
			CursorPosY = KeyState::SaveDataMenuKeyMove(CursorPosY);
		}

		TEST_METHOD(ReturnMouceFunc) {

			std::int32_t CursorPosY = TitleMenuPosY;

			//�^�C�g�����j���[�̃}�E�X����
			CursorPosY = MouseState::GameTitleMenuMouseMove(CursorPosY);

			//�R���t�B�O��ʃ}�E�X����
			CursorPosY = MouseState::ConfigMenuMouseMove(CursorPosY);

			//�Q�[�����j���[�̃}�E�X����
			CursorPosY = MouseState::GameMenuMouseMove(CursorPosY);

			//�I�����}�E�X����
			CursorPosY = MouseState::ChoiceMouseMove(CursorPosY);

			//�Z�[�u�f�[�^���j���[�}�E�X����
			CursorPosY = MouseState::SaveDataMenuMouseMove(CursorPosY);
		}

		TEST_METHOD(BackLogLoopTest) {

			for (std::int32_t i = 0; i < MaterialMax; i++)
				BackLogGet();

			BackLogLoop();
		}

		TEST_METHOD(ChoiceSelectTest) {

			std::int32_t EndFlag = 1;
			std::int32_t RouteNumber = 1;

			ChoiceSelect(RouteNumber);

		}

		TEST_METHOD(ConfigMenuLoopTest) {

			ConfigMenuLoop();

		}

		TEST_METHOD(GameMenuLoopTest) {

			GameMenuLoop();
		}

		TEST_METHOD(ScriptTaskManagerTest) {

			std::int32_t Sp = 0, Cp = 0;

			std::vector<std::string> Script;

			Script = ScriptRead(1);

			std::vector<int> BackGround, Character, BackGroundMusic, SoundEffect, ImageEffect;
			std::vector<std::string> Movie;

			//�w�i�摜�Ǎ��֐�
			BackGround = MaterialLoad(BackGround, "DATA/BACKGROUND", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//�����G�摜�Ǎ��֐�
			Character = MaterialLoad(Character, "DATA/CHARACTER", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//BGM�Ǎ��֐�
			BackGroundMusic = MaterialLoad(BackGroundMusic, "DATA/BACKGROUNDMUSIC", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//SE�Ǎ��֐�
			SoundEffect = MaterialLoad(SoundEffect, "DATA/SOUNDEFFECT", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//����Ǎ��֐�
			Movie = MaterialLoad(Movie, "DATA/MOVIE", [](const std::string& Path) {return std::move(Path); });

			//�C���[�W�G�t�F�N�g�Ǎ��֐�
			ImageEffect = MaterialLoad(ImageEffect, "DATA/IMAGEEFFECT", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			ScriptTagTaskManager(Script, BackGround, Character, BackGroundMusic, SoundEffect, Movie, ImageEffect);
		}
	};
}