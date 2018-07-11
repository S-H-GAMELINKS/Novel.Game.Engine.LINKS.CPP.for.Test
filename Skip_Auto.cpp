// Skip Auto Source

#include "DxLib.h"
#include "Utility.hpp"
#include "ConstantExpressionVariable.hpp"
#include <array>
#include <thread>
#include <chrono>

//�I���t���O
extern int EndFlag;

//������`��ʒu
extern int DrawPointX, DrawPointY;

// ���ǃX�L�b�v/�X�L�b�v/�I�[�g�ϐ�
extern int SkipAndAutoFlag;

//���ǃX�L�b�v����p�ϐ�
std::array<std::int32_t, 15> SkipData;

//���ǃX�L�b�v
struct alignas(4) SkipData_t {
	std::array<std::int32_t, 15> SkipFlag;
};

//���ǃX�L�b�v�f�[�^��������
void SkipDataWrite(const std::int32_t& RouteNum) noexcept {
	SkipData[RouteNum - 1] = 1;
}

//���ǔ���
void SkipDataCheck(const std::int32_t& RouteNum) noexcept {
	if (SkipData[RouteNum - 1] == 1)
		SkipAndAutoFlag = 1;
	else
		SkipAndAutoFlag = 0;
}

//���ǃX�L�b�v�f�[�^�̓Ǎ�
int SkipDataLoad() noexcept {
	SkipData_t Data;

	FILE *Fp;
	fopen_s(&Fp, "DATA/SAVE/SKIP_READ.bat", "rb");
	if (nullptr == Fp) {
		return 0;
	}
	fread(&Data, sizeof(SkipData_t), 1, Fp);

	std::int32_t i = 0;

	for (auto&& d : Data.SkipFlag) {
		SkipData[i] = d;
		i++;
	}

	fclose(Fp);
	return 0;
}

//SKIP_READ SAVE�֐�
int SkipDataSave() noexcept {

	SkipData_t Data;

	std::int32_t i = 0;

	for (auto&& d : Data.SkipFlag) {
		d = SkipData[i];
		i++;
	}

	FILE *Fp;
	fopen_s(&Fp, "DATA/SAVE/SKIP_READ.bat", "wb");//�o�C�i���t�@�C�����J��
	if (nullptr == Fp) {//�G���[���N������nullptr��Ԃ�
		return 0;
	}
	fwrite(&Data, sizeof(SkipData_t), 1, Fp); // SkipData_t�\���̂̒��g���o��
	fclose(Fp);
	return 0;
}

// ���ǃX�L�b�v/�X�L�b�v/�I�[�g�؂�ւ��֐�
void SkipAndAutoTask(const std::int32_t& Num, const int Flag) noexcept {

	if (Num == 0) {
		if (IDYES == MessageBoxYesNo("�I�[�g/�X�L�b�v���~���܂����H"))
			SkipAndAutoFlag = 0;
	}

	if (Num == 1) {
		if (IDYES == MessageBoxYesNo("�X�L�b�v�����s���܂����H")) {
			SkipAndAutoFlag = 1;
		}
	}

	if (Num == 2) {
		if (IDYES == MessageBoxYesNo("�I�[�g�����s���܂����H")) {
			SkipAndAutoFlag = 2;
		}
	}

	if (Num == 3) {
		if (IDYES == MessageBoxYesNo("���ǃX�L�b�v�����s���܂����H")) {
			SkipDataCheck(EndFlag);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
	}

	EndFlag = Flag;
	DrawPointX = 0;
	DrawPointY = 0;
}
