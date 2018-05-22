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

//�e��f�ފi�[�ϐ�
static std::vector<int> BackGround, Character, BackGroundMusic, SoundEffect, ImageEffect;
static std::vector<std::string> Movie;

//�e��f�ރn���h��
std::int32_t BackGroundHandle, CharacterHandle, BackGroundMusicHandle, SoundEffectHandle, ImageEffectHandle, GameTitleGraph;

//��ʕϑJ�pTemp�ϐ�
int EndFlagTemp, SpTemp;

// ���ǃX�L�b�v/�X�L�b�v/�I�[�g�ϐ�
int SkipAndAutoFlag = 0;

#endif //VALIABLE_H_