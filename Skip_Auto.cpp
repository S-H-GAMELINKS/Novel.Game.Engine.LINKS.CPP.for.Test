// Skip Auto Source

#include "DxLib.h"
#include "Utility.h"
#include "ConstantExpressionVariable.h"
#include <array>
#include <thread>
#include <chrono>

//�I���t���O
extern int EndFlag;

// ���ǃX�L�b�v/�X�L�b�v/�I�[�g�ϐ�
extern int SkipAndAutoFlag;

//���ǃX�L�b�v����p�ϐ�
std::array<std::int32_t, 15> SkipData;

//���ǃX�L�b�v
struct alignas(4) SkipData_t {
	std::int32_t LINKS;		//���C�����[�g�̊��Ǐ��
	std::int32_t A;			//A���[�g�̊��Ǐ��
	std::int32_t B;			//B���[�g�̊��Ǐ��
	std::int32_t C;			//C���[�g�̊��Ǐ��
	std::int32_t D;			//D���[�g�̊��Ǐ��
	std::int32_t E;			//E���[�g�̊��Ǐ��
	std::int32_t F;			//F���[�g�̊��Ǐ��
	std::int32_t G;			//G���[�g�̊��Ǐ��
	std::int32_t H;			//H���[�g�̊��Ǐ��
	std::int32_t I;			//I���[�g�̊��Ǐ��
	std::int32_t J;			//J���[�g�̊��Ǐ��
	std::int32_t K;			//K���[�g�̊��Ǐ��
	std::int32_t L;			//L���[�g�̊��Ǐ��
	std::int32_t M;			//M���[�g�̊��Ǐ��
	std::int32_t N;			//N���[�g�̊��Ǐ��
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
	fopen_s(&Fp, "DATA/SAVE/SKIP_READ.dat", "rb");
	if (nullptr == Fp) {
		return 0;
	}
	fread(&Data, sizeof(SkipData_t), 1, Fp);

	SkipData[0] = Data.LINKS;
	SkipData[1] = Data.A;
	SkipData[2] = Data.B;
	SkipData[3] = Data.C;
	SkipData[4] = Data.D;
	SkipData[5] = Data.E;
	SkipData[6] = Data.F;
	SkipData[7] = Data.G;
	SkipData[8] = Data.H;
	SkipData[9] = Data.I;
	SkipData[10] = Data.J;
	SkipData[11] = Data.K;
	SkipData[12] = Data.L;
	SkipData[13] = Data.M;
	SkipData[14] = Data.N;

	fclose(Fp);
	return 0;
}

//SKIP_READ SAVE�֐�
int SkipDataSave() noexcept {
	SkipData_t Data = {
		SkipData[0], SkipData[1], SkipData[2], SkipData[3], SkipData[4], SkipData[5],
		SkipData[6], SkipData[7], SkipData[8], SkipData[9], SkipData[10], SkipData[11],
		SkipData[12], SkipData[13], SkipData[14]
	};

	FILE *Fp;
	fopen_s(&Fp, "DATA/SAVE/SKIP_READ.dat", "wb");//�o�C�i���t�@�C�����J��
	if (nullptr == Fp) {//�G���[���N������nullptr��Ԃ�
		return 0;
	}
	fwrite(&Data, sizeof(SkipData_t), 1, Fp); // SkipData_t�\���̂̒��g���o��
	fclose(Fp);
	return 0;
}

// ���ǃX�L�b�v/�X�L�b�v/�I�[�g�؂�ւ��֐�
void SkipAndAutoTask(const std::int32_t& Num) noexcept {

	if (Num == 0) {
		if (IDYES == MessageBoxYesNo("�I�[�g/�X�L�b�v���~���܂����H")) {
			SkipAndAutoFlag = 0;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
	}

	if (Num == 1) {
		if (IDYES == MessageBoxYesNo("�X�L�b�v�����s���܂����H")) {
			SkipAndAutoFlag = 1;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
	}

	if (Num == 2) {
		if (IDYES == MessageBoxYesNo("�I�[�g�����s���܂����H")) {
			SkipAndAutoFlag = 2;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
	}

	if (Num == 3) {
		if (IDYES == MessageBoxYesNo("���ǃX�L�b�v�����s���܂����H")) {
			SkipDataCheck(EndFlag);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(WaitKeyTaskTime));
	}
}
