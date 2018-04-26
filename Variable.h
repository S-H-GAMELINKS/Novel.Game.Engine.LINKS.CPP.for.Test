// Variable Manage Source
#ifndef VALIABLE_H_
#define VALIABLE_H_

#include "ConstantExpressionVariable.h"
#include <vector>
#include <string>
#include <array>

//�Q�[���^�C�g��
extern const char* GameTitle = "�m�x���Q�[���G���W���uLINKS�v for C++";

int DrawPointX = 0, DrawPointY = 0;	// ������`��̈ʒu
int Sp = 0, Cp = 0;	// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^

int EndFlag = 0;	// �I���t���O

//�X�N���v�g�i�[�ϐ�
static std::vector<std::string> Script;

//�w�i�摜�i�[�ϐ�
static std::array<int, MaterialMax> BackGround;

//�����G�i�[�ϐ�
static std::array<int, MaterialMax> Character;

//BGM�i�[�ϐ�
static std::array<int, MaterialMax> BackGroundMusic;

//���ʉ��i�[�ϐ�
static std::array<int, MaterialMax> SoundEffect;

//����i�[�ϐ�
static std::array<std::string, MaterialMax> Movie;

//�C���[�W�G�t�F�N�g�i�[�ϐ�
static std::array<int, MaterialMax> ImageEffect;

//�e��f�ރn���h��
std::int32_t BackGroundHandle;
std::int32_t CharacterHandle;
std::int32_t BackGroundMusicHandle;
std::int32_t SoundEffectHandle;
std::int32_t ImageEffectHandle;

std::int32_t GameTitleGraph;

//��ʕϑJ�pTemp�ϐ�
int EndFlagTemp, SpTemp;

// ���ǃX�L�b�v/�X�L�b�v/�I�[�g�ϐ�
int SkipAndAutoFlag = 0;

#endif //VALIABLE_H_