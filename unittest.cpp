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
			CursorPosY = KeyState::GameTitleMenuKeyMove(CursorPosY);

			//コンフィグ画面キー操作
			CursorPosY = KeyState::ConfigMenuKeyMove(CursorPosY);

			//ゲームメニューキー操作
			CursorPosY = KeyState::GameMenuKeyMove(CursorPosY);

			//選択肢キー操作
			CursorPosY = KeyState::ChoiceKeyMove(CursorPosY);

			//セーブデータメニューキー操作
			CursorPosY = KeyState::SaveDataMenuKeyMove(CursorPosY);
		}

		TEST_METHOD(ReturnMouceFunc) {

			std::int32_t CursorPosY = TitleMenuPosY;

			//タイトルメニューのマウス操作
			CursorPosY = MouseState::GameTitleMenuMouseMove(CursorPosY);

			//コンフィグ画面マウス操作
			CursorPosY = MouseState::ConfigMenuMouseMove(CursorPosY);

			//ゲームメニューのマウス操作
			CursorPosY = MouseState::GameMenuMouseMove(CursorPosY);

			//選択肢マウス操作
			CursorPosY = MouseState::ChoiceMouseMove(CursorPosY);

			//セーブデータメニューマウス操作
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
	};
}