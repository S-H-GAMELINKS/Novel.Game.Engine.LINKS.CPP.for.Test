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

			//背景画像読込関数
			BackGround = MaterialLoad(BackGround, "DATA/BACKGROUND", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//立ち絵画像読込関数
			Character = MaterialLoad(Character, "DATA/CHARACTER", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//BGM読込関数
			BackGroundMusic = MaterialLoad(BackGroundMusic, "DATA/BACKGROUNDMUSIC", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//SE読込関数
			SoundEffect = MaterialLoad(SoundEffect, "DATA/SOUNDEFFECT", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//動画読込関数
			Movie = MaterialLoad(Movie, "DATA/MOVIE", [](const std::string& Path) {return std::move(Path); });

			//イメージエフェクト読込関数
			ImageEffect = MaterialLoad(ImageEffect, "DATA/IMAGEEFFECT", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });
		}

		TEST_METHOD(ReturnKeyFunc) {

			std::int32_t CursorPosY = TitleMenuPosY;
			
			//タイトルメニューのキー操作
			CursorPosY = KeyState::KeyMoveTemplate(CursorPosY, TitleMenuPosY, TitleMenuExitPosY, CursorMove, ConfigData.MouseAndKeyFlag);

			//コンフィグ画面キー操作
			CursorPosY = KeyState::KeyMoveTemplate(CursorPosY, GameMenuBasePosY, GameMenuBasePosY * 7, CursorMove, ConfigData.MouseAndKeyFlag);

			//ゲームメニューキー操作
			CursorPosY = KeyState::KeyMoveTemplate(CursorPosY, GameMenuBasePosY, GameMenuBasePosY * 12, CursorMove, ConfigData.MouseAndKeyFlag);

			//選択肢キー操作
			CursorPosY = KeyState::KeyMoveTemplate(CursorPosY, ChoicePosY[0], ChoicePosY[1], CursorMove, ConfigData.MouseAndKeyFlag);

			//セーブデータメニューキー操作
			CursorPosY = KeyState::KeyMoveTemplate(SaveDataBasePosY, SaveDataBasePosY, SaveDataPosButtom, SaveDataCursorMove, ConfigData.MouseAndKeyFlag);
		}

		TEST_METHOD(ReturnMouceFunc) {

			std::int32_t CursorPosY = TitleMenuPosY;

			//タイトルメニューのマウス操作
			CursorPosY = MouseState::MouseMoveTemplate(CursorPosY, TitleMenuPosY, CursorMove, 6, ConfigData.MouseAndKeyFlag);

			//コンフィグ画面マウス操作
			CursorPosY = MouseState::MouseMoveTemplate(CursorPosY, GameMenuBasePosY, CursorMove, 7, ConfigData.MouseAndKeyFlag);

			//ゲームメニューのマウス操作
			CursorPosY = MouseState::MouseMoveTemplate(CursorPosY, GameMenuBasePosY, CursorMove, 12, ConfigData.MouseAndKeyFlag);

			//選択肢マウス操作
			CursorPosY = MouseState::MouseMoveTemplate(CursorPosY, (ChoicePosY[1] - CursorMove), CursorMove, 2, ConfigData.MouseAndKeyFlag);

			//セーブデータメニューマウス操作
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

			//背景画像読込関数
			BackGround = MaterialLoad(BackGround, "DATA/BACKGROUND", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//立ち絵画像読込関数
			Character = MaterialLoad(Character, "DATA/CHARACTER", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//BGM読込関数
			BackGroundMusic = MaterialLoad(BackGroundMusic, "DATA/BACKGROUNDMUSIC", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//SE読込関数
			SoundEffect = MaterialLoad(SoundEffect, "DATA/SOUNDEFFECT", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//動画読込関数
			Movie = MaterialLoad(Movie, "DATA/MOVIE", [](const std::string& Path) {return std::move(Path); });

			//イメージエフェクト読込関数
			ImageEffect = MaterialLoad(ImageEffect, "DATA/IMAGEEFFECT", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			ScriptTagTaskManager(Script, BackGround, Character, BackGroundMusic, SoundEffect, Movie, ImageEffect);
		}

		TEST_METHOD(ContinueSaveTest) {

			int EndFlag = 1;

			//クイックセーブ処理
			ContinueSaveDataSave(EndFlag);
		}
	};
}