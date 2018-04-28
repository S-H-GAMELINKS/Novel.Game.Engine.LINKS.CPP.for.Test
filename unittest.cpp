#include "stdafx.h"
#include "CppUnitTest.h"
#include "Material_Manager.h"
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
			std::int32_t GameTitleGraph;

			//�w�i�摜�Ǎ��֐�
			BackGround = MaterialLoad(BackGround, "DATA/BACKGROUND/BG", ".png", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//�����G�摜�Ǎ��֐�
			Character = MaterialLoad(Character, "DATA/CHARACTER/CHAR", ".png", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });

			//BGM�Ǎ��֐�
			BackGroundMusic = MaterialLoad(BackGroundMusic, "DATA/BACKGROUNDMUSIC/BGM", ".ogg", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//SE�Ǎ��֐�
			SoundEffect = MaterialLoad(SoundEffect, "DATA/SOUNDEFFECT/SE", ".ogg", [](const std::string& Path) {return DxLib::LoadSoundMem(Path.c_str()); });

			//����Ǎ��֐�
			Movie = MaterialLoad(Movie, "DATA/MOVIE/MOVIE", ".wmv", [](const std::string& Path) {return std::move(Path); });

			//�C���[�W�G�t�F�N�g�Ǎ��֐�
			ImageEffect = MaterialLoad(ImageEffect, "DATA/IMAGEEFFECT/IE", ".png", [](const std::string& Path) {return DxLib::LoadGraph(Path.c_str()); });
		}
	};
}