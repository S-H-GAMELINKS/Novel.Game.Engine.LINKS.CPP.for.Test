#include "stdafx.h"
#include "CppUnitTest.h"
#include "Material_Manager.h"
#include "MouseAndKeyState.hpp"
#include "BackLog.hpp"
#include "ConfigMenu.hpp"
#include "GameMenu.hpp"
#include "Choice.hpp"
#include "ScriptTask_Manager.h"
#include "SaveData.h"
#include <iostream>
#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern ConfigData_t ConfigData;

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
			CursorPosY = KeyState::KeyMoveTemplate(CursorPosY, TitleMenuPosY, TitleMenuExitPosY, CursorMove, ConfigData.MouseAndKeyFlag);

			//�R���t�B�O��ʃL�[����
			CursorPosY = KeyState::KeyMoveTemplate(CursorPosY, GameMenuBasePosY, GameMenuBasePosY * 7, CursorMove, ConfigData.MouseAndKeyFlag);

			//�Q�[�����j���[�L�[����
			CursorPosY = KeyState::KeyMoveTemplate(CursorPosY, GameMenuBasePosY, GameMenuBasePosY * 12, CursorMove, ConfigData.MouseAndKeyFlag);

			//�I�����L�[����
			CursorPosY = KeyState::KeyMoveTemplate(CursorPosY, ChoicePosY[0], ChoicePosY[1], CursorMove, ConfigData.MouseAndKeyFlag);

			//�Z�[�u�f�[�^���j���[�L�[����
			CursorPosY = KeyState::KeyMoveTemplate(SaveDataBasePosY, SaveDataBasePosY, SaveDataPosButtom, SaveDataCursorMove, ConfigData.MouseAndKeyFlag);
		}

		TEST_METHOD(ReturnMouceFunc) {

			std::int32_t CursorPosY = TitleMenuPosY;

			//�^�C�g�����j���[�̃}�E�X����
			CursorPosY = MouseState::MouseMoveTemplate(CursorPosY, TitleMenuPosY, CursorMove, 6, ConfigData.MouseAndKeyFlag);

			//�R���t�B�O��ʃ}�E�X����
			CursorPosY = MouseState::MouseMoveTemplate(CursorPosY, GameMenuBasePosY, CursorMove, 7, ConfigData.MouseAndKeyFlag);

			//�Q�[�����j���[�̃}�E�X����
			CursorPosY = MouseState::MouseMoveTemplate(CursorPosY, GameMenuBasePosY, CursorMove, 12, ConfigData.MouseAndKeyFlag);

			//�I�����}�E�X����
			CursorPosY = MouseState::MouseMoveTemplate(CursorPosY, (ChoicePosY[1] - CursorMove), CursorMove, 2, ConfigData.MouseAndKeyFlag);

			//�Z�[�u�f�[�^���j���[�}�E�X����
			CursorPosY = MouseState::MouseMoveTemplate(SaveDataBasePosY, SaveDataBasePosY, SaveDataBasePosY, 4, ConfigData.MouseAndKeyFlag);
		}

		TEST_METHOD(BackLogGetTest) {

			for (std::int32_t i = 0; i < MaterialMax; i++)
				BackLogGet();
		}

		TEST_METHOD(ChoiceSelectTest) {

			std::int32_t EndFlag = 1;
			std::int32_t RouteNumber = 1;

			ChoiceSelect(RouteNumber);

		}

		TEST_METHOD(ConfigMenuLoadTest) {

			ConfigLoad();

		}

		TEST_METHOD(ConfigSaveTest) {

			ConfigSave();
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

		TEST_METHOD(ContinueSaveTest) {

			int EndFlag = 1;

			//�N�C�b�N�Z�[�u����
			ContinueSaveDataSave(EndFlag);
		}
	};
}