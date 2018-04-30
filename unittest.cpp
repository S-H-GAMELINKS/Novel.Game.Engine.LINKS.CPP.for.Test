#include "stdafx.h"
#include "CppUnitTest.h"
#include "Material_Manager.h"
#include "MouseAndKeyState.hpp"
#include "BackLog.h"
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
			std::array<int, MaterialMax> BackGround, Character, BackGroundMusic, SoundEffect, ImageEffect;
			std::array<std::string, MaterialMax> Movie;

			//背景画像読込関数
			BackGround = MaterialLoad(BackGround, "DATA/BACKGROUND/BG", ".png", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//立ち絵画像読込関数
			Character = MaterialLoad(Character, "DATA/CHARACTER/CHAR", ".png", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//BGM読込関数
			BackGroundMusic = MaterialLoad(BackGroundMusic, "DATA/BACKGROUNDMUSIC/BGM", ".ogg", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//SE読込関数
			SoundEffect = MaterialLoad(SoundEffect, "DATA/SOUNDEFFECT/SE", ".ogg", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//動画読込関数
			Movie = MaterialLoad(Movie, "DATA/MOVIE/MOVIE", ".wmv", [](const std::string& Path) {return std::move(Path); });

			//イメージエフェクト読込関数
			ImageEffect = MaterialLoad(ImageEffect, "DATA/IMAGEEFFECT/IE", ".png", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });
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
	};
}