// SaveData Source

#include "DxLib.h"
#include "ConstantExpressionVariable.h"
#include "Utility.h"
#include "ConfigMenu.h"
#include "MouseAndKeyState.hpp"
#include <string>
#include <thread>
#include <chrono>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

extern int Sp, Cp;	// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^

//�e��f�ރn���h��
extern std::int32_t BackGroundHandle, CharacterHandle, BackGroundMusicHandle, SoundEffectHandle;

//������`��ʒu
extern int DrawPointX, DrawPointY;

//�I���t���O
extern int EndFlag;

//temp�f�[�^
extern int EndFlagTemp, SpTemp;

extern ConfigData_t ConfigData;

namespace {

	//�e�핪��\���z��
	static constexpr const char* SaveTaskItem[] = { "�Z�[�u���܂����H", "���[�h���܂����H", "�폜���܂����H" };
	static constexpr const char* SaveTaskItemParticle[] = { "��", "��", "��" };

	//�Z�[�u�f�[�^�p�X�N���[���V���b�g�i�[�ϐ�
	std::int32_t SaveSnap[SaveDataSlotNum];

	//�Z�[�u�f�[�^���`��p�z��
	static constexpr const char* SaveDataName[] = { "�Z�[�u�f�[�^1", "�Z�[�u�f�[�^2", "�Z�[�u�f�[�^3" };

	//�ʏ�Z�[�u�f�[�^
	struct alignas(4) SaveData_t {
		std::int32_t EndFlag;    //EndFlag
		std::int32_t Sp;			//�s��
		std::int32_t Cp;			//�����ʒu
		std::int32_t Character;		//�����G���
		std::int32_t BackGround;			//�w�i�摜���
		std::int32_t BackGroundMusic;		//BGM���
	};

	//�Z�[�u�f�[�^�p�X�N���[���V���b�g�Ǎ��֐�
	void SaveDataSnapLoad() noexcept {
		std::string FilePath = "DATA/SAVE/SAVESNAP";
		std::string FileFormat = ".png";
		std::string FileName = "";

		for (std::int32_t i = 0; i < SaveDataSlotNum; i++) {

			FileName = (FilePath + std::to_string(i + 1) + FileFormat);

			SaveSnap[i] = DxLib::LoadGraph(FileName.c_str());
		}
	}

	//�Z�[�u�f�[�^ ���j���[�`��
	void SaveDataMenuDraw(std::int32_t& SaveDataMenuPosY) noexcept {

		//�X�N���[���V���b�g�`��
		for (std::int32_t i = 0; i < SaveDataSlotNum; i++)
			DxLib::DrawRotaGraph(SaveSnapDrawPosX, SaveDataBasePosY * (i + 1), 0.2f, 0, SaveSnap[i], TRUE);

		//�J�[�\���̕`��
		DxLib::DrawString(SaveDataBasePosX, SaveDataMenuPosY, "��", Color);

		//�Z�[�u�f�[�^���`��
		for (std::int32_t i = 0; i < SaveDataSlotNum; i++)
			DxLib::DrawString(SaveDataNamePosX, SaveDataBasePosY * (i + 1), SaveDataName[i], Color);

		DxLib::DrawString(SaveDataNamePosX - CursorMove, SaveDataBasePosY * 4, "�߂�", Color);
	}

	//�X�N���[���V���b�g���O�ύX
	void SaveDataScreenShotRename(const int& Num) noexcept {
		std::string FileName = "DATA/SAVE/SAVESNAP" + std::to_string(Num) + ".png";

		const fs::path path("DATA/SAVE/SAVESNSAPTEMP.png");
		const fs::path dest(FileName.c_str());

		fs::copy_file(path, dest, fs::copy_option::overwrite_if_exists);
	}

	//�Z�[�u�f�[�^���Z�[�u
	int SaveDataSave(const char* SaveDataPath, const char* Message, const int& Num, const int& SaveSlot) noexcept {

		if (IDYES == MessageBoxYesNo(Message)) {

			SaveData_t SaveData = { EndFlagTemp, SpTemp, 0, CharacterHandle, BackGroundHandle, BackGroundMusicHandle };

			FILE *Fp;

			fopen_s(&Fp, SaveDataPath, "wb");//�o�C�i���t�@�C�����J��
			if (nullptr == Fp) {//�G���[���N������nullptr��Ԃ�
				return 0;
			}

			fwrite(&SaveData, sizeof(SaveData), 1, Fp); // SaveData_t�\���̂̒��g���o��
			fclose(Fp);

			//�X�N���[���V���b�g�̖��O�ύX
			SaveDataScreenShotRename(SaveSlot);

			MessageBoxOk("�Z�[�u���܂����I");
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}
		return 0;
	}

	//�Z�[�u�f�[�^�����[�h
	int SaveDataLoad(const char* SaveDataPath, const char* Message) noexcept {

		if (IDYES == MessageBoxYesNo(Message)) {

			SaveData_t SaveData;

			FILE *Fp;

			fopen_s(&Fp, SaveDataPath, "rb");
			if (Fp == nullptr) {
				MessageBoxOk("�Z�[�u�f�[�^�����[�h�ł��܂���");
				return 0;
			}

			fread(&SaveData, sizeof(SaveData), 1, Fp);
			fclose(Fp);

			EndFlag = SaveData.EndFlag;
			Sp = SaveData.Sp;
			Cp = SaveData.Cp;
			CharacterHandle = SaveData.Character;
			BackGroundHandle = SaveData.BackGround;
			BackGroundMusicHandle = SaveData.BackGroundMusic;

			MessageBoxOk("���[�h���܂����I");
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));

			DrawPointX = 0;
			DrawPointY = 0;
			DxLib::PlaySoundMem(BackGroundMusicHandle, DX_PLAYTYPE_LOOP);
			DxLib::DrawGraph(0, 0, BackGroundHandle, TRUE);
			DxLib::DrawGraph(150, 130, CharacterHandle, TRUE);
		}
		return 0;
	}

	//�Z�[�u�f�[�^���f���[�g
	int SaveDataDelete(const char* SaveDataPath, const char* Message) noexcept {
		if (IDYES == MessageBoxYesNo(Message)) {
			std::remove(SaveDataPath);

			MessageBoxOk("�폜���܂����I");
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}
		return 0;
	}

	//�Z�[�u/���[�h/�f���[�g�؂�ւ��֐�
	void SaveDataTask(const int& Num, const char* SaveDataPath, const char* SaveDataName, std::int32_t& SaveFlag, const int& SaveSlot) noexcept {

		std::string Message = SaveDataName;
		Message += SaveTaskItemParticle[Num - 1];
		Message += SaveTaskItem[Num - 1];

		//�Z�[�u
		if (Num == 1)
			SaveFlag = SaveDataSave(SaveDataPath, Message.c_str(), Num, SaveSlot);

		//���[�h
		if (Num == 2)
			SaveFlag = SaveDataLoad(SaveDataPath, Message.c_str());

		//�f���[�g
		if (Num == 3)
			SaveFlag = SaveDataDelete(SaveDataPath, Message.c_str());
	}

	//�Z�[�u�f�[�^ ���j���[�I������
	void SaveDataMenuSelect(std::int32_t& SaveDataMenuPosY, const int& Num, std::int32_t& SaveFlag) noexcept {

		if (SaveDataMenuPosY == SaveDataBasePosY && MouseAndKey::CheckMouseAndKeyEnter()) {
			SaveDataTask(Num, "DATA/SAVE/SAVEDATA1.bat", "�Z�[�u�f�[�^�P", SaveFlag, 1);
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}


		if (SaveDataMenuPosY == SaveDataBasePosY * 2 && MouseAndKey::CheckMouseAndKeyEnter()) {
			SaveDataTask(Num, "DATA/SAVE/SAVEDATA2.bat", "�Z�[�u�f�[�^�Q", SaveFlag, 2);
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}


		if (SaveDataMenuPosY == SaveDataBasePosY * 3 && MouseAndKey::CheckMouseAndKeyEnter()) {
			SaveDataTask(Num, "DATA/SAVE/SAVEDATA3.bat", "�Z�[�u�f�[�^�R", SaveFlag, 3);
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}


		if (SaveDataMenuPosY == SaveDataBasePosY * 4 && MouseAndKey::CheckMouseAndKeyEnter()) {

			if (IDYES == MessageBoxYesNo("�߂�܂����H")){
				SaveFlag = 0;
				std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
		}
	}
}

//�Z�[�u�f�[�^(�Z�[�u/���[�h/�f���[�g)���[�v
void SaveDataLoop(const int& Num) noexcept {

	//�e�핪��\��
	if (IDYES == MessageBoxYesNo(SaveTaskItem[Num - 1])) {

		//�Z�[�u�f�[�^���[�v�p�t���O
		std::int32_t SaveFlag = 1;

		DxLib::ClearDrawScreen();
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));

		//�X�N���[���V���b�g�̓Ǎ�
		SaveDataSnapLoad();

		//�J�[�\���̏����ʒu
		std::int32_t SaveDataMenuPosY = SaveDataBasePosY;

		//�Z�[�u�f�[�^���[�v
		while (SaveFlag == 1) {
			ScreenClear();
			SaveDataMenuDraw(SaveDataMenuPosY);
			SaveDataMenuPosY = KeyState::SaveDataMenuKeyMove(SaveDataMenuPosY);
			SaveDataMenuPosY = MouseState::SaveDataMenuMouseMove(SaveDataMenuPosY);
			SaveDataMenuSelect(SaveDataMenuPosY, Num, SaveFlag);
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
}

//�Z�[�u�f�[�^���Z�[�u(Quick)
int QuickSaveDataSave() noexcept {

	if (IDYES == MessageBoxYesNo("�N�C�b�N�Z�[�u�����s���܂����H")) {

		SaveData_t SaveData = { EndFlag, SpTemp, 0, CharacterHandle, BackGroundHandle, BackGroundMusicHandle };

		FILE *Fp;

		fopen_s(&Fp, "DATA/SAVE/QuickSaveData.dat", "wb");//�o�C�i���t�@�C�����J��
		if (nullptr == Fp) {//�G���[���N������nullptr��Ԃ�
			return 0;
		}

		fwrite(&SaveData, sizeof(SaveData), 1, Fp); // SaveData_t�\���̂̒��g���o��
		fclose(Fp);

		MessageBoxOk("�Z�[�u���܂����I");
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
	}
	return 0;
}

//�Z�[�u�f�[�^�����[�h(Quick)
int QuickSaveDataLoad() noexcept {

	if (IDYES == MessageBoxYesNo("�N�C�b�N���[�h�����s���܂����H")) {

		SaveData_t SaveData;

		FILE *Fp;

		fopen_s(&Fp, "DATA/SAVE/QuickSaveData.dat", "rb");
		if (Fp == nullptr) {
			//MessageBoxOk(ErrorMessage);
			return 0;
		}

		fread(&SaveData, sizeof(SaveData), 1, Fp);
		fclose(Fp);

		EndFlag = SaveData.EndFlag;
		Sp = SaveData.Sp;
		Cp = SaveData.Cp;
		CharacterHandle = SaveData.Character;
		BackGroundHandle = SaveData.BackGround;
		BackGroundMusicHandle = SaveData.BackGroundMusic;

		MessageBoxOk("���[�h���܂����I");
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));

		DrawPointX = 0;
		DrawPointY = 0;
		DxLib::PlaySoundMem(BackGroundMusicHandle, DX_PLAYTYPE_LOOP);
		DxLib::DrawGraph(0, 0, BackGroundHandle, TRUE);
		DxLib::DrawGraph(150, 130, CharacterHandle, TRUE);
	}
	return 0;
}

//�Z�[�u�f�[�^���Z�[�u(Continue)
int ContinueSaveDataSave(const std::int32_t& RouteNum) noexcept {

	SaveData_t SaveData = { RouteNum, SpTemp, 0, CharacterHandle, BackGroundHandle, BackGroundMusicHandle };

	FILE *Fp;

	fopen_s(&Fp, "DATA/SAVE/ContinueSaveData.dat", "wb");//�o�C�i���t�@�C�����J��
	if (nullptr == Fp) {//�G���[���N������nullptr��Ԃ�
		return 0;
	}

	fwrite(&SaveData, sizeof(SaveData), 1, Fp); // SaveData_t�\���̂̒��g���o��
	fclose(Fp);

	return 0;
}

//�Z�[�u�f�[�^�����[�h(Continue)
int ContinueSaveDataLoad() noexcept {

	if (IDYES == MessageBoxYesNo("�O��v���C����������ĊJ���܂����H")) {

		SaveData_t SaveData;

		FILE *Fp;

		fopen_s(&Fp, "DATA/SAVE/QuickSaveData.dat", "rb");
		if (Fp == nullptr) {
			MessageBoxOk("���[�h�ł��܂���");
			return 0;
		}

		fread(&SaveData, sizeof(SaveData), 1, Fp);
		fclose(Fp);

		EndFlag = SaveData.EndFlag;
		Sp = SaveData.Sp;
		Cp = SaveData.Cp;
		CharacterHandle = SaveData.Character;
		BackGroundHandle = SaveData.BackGround;
		BackGroundMusicHandle = SaveData.BackGroundMusic;

		MessageBoxOk("���[�h���܂����I");
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));

		DrawPointX = 0;
		DrawPointY = 0;
		DxLib::PlaySoundMem(BackGroundMusicHandle, DX_PLAYTYPE_LOOP);
		DxLib::DrawGraph(0, 0, BackGroundHandle, TRUE);
		DxLib::DrawGraph(150, 130, CharacterHandle, TRUE);
	}
	return 0;
}

//�Z�[�u�f�[�^�p�X�N���[���V���b�g�擾
void SaveDataScreenShotGet() noexcept {
	DxLib::SaveDrawScreen(0, 0, 640, 480, "DATA/SAVE/SAVESNSAPTEMP.png");
}