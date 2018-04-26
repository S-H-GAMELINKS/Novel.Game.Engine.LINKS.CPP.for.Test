#ifndef CONSTANT_EXPRESSION_VARIABLE_H_
#define CONSTANT_EXPRESSION_VARIABLE_H_

#include "DxLib.h"

//�e��f�ލő吔
constexpr int MaterialMax = 99;

// �����̃T�C�Y
constexpr int MojiSize = 21;

//�^�C�g�����j���[�ʒu
constexpr int TitleMenuPosY			 = 300;
constexpr int TitleMenuPosX			 = 430;
constexpr int TitleMenuLoadPosY		 = 330;
constexpr int TitleMenuConfigPosY	 = 360;
constexpr int TitleMenuQuickLoadPosY = 390;
constexpr int TitleMenuContinuePosY  = 420;
constexpr int TitleMenuExitPosY		 = 450;

//�^�C�g�����j���[�̃J�[�\���ʒu
constexpr int TitleMenuCursorPosX = 400;

//�I����
constexpr int ChoicePosX   = 100;
constexpr int ChoicePosY[] = { 200, 230 };

//�L�[�J�[�\���̈ړ���
constexpr int CursorMove = 30;

//�L�[������~����
constexpr int WaitKeyTaskTime = 70;

//�Q�[���v���C���̒x������
constexpr int WaitGameTime = 3;

//�Q�[�����j���[�ʒu�֌W
constexpr int GameMenuBasePosY = 30;

//�Z�[�u�E���[�h��ʊ֌W
constexpr int SaveDataSlotNum    = 3;
constexpr int SaveDataBasePosX   = 400;
constexpr int SaveDataBasePosY   = 100;
constexpr int SaveDataCursorMove = 100;
constexpr int SaveDataPosButtom  = SaveDataBasePosY + SaveDataCursorMove * SaveDataSlotNum;
constexpr int SaveSnapDrawPosX   = 150;
constexpr int SaveDataNamePosX   = 250;

//�����`�摬�x�֌W
constexpr int StringSpeedSkip = 10;
constexpr int StringSpeedAuto = 30;
constexpr int StringSpeedWait = 600;

//�����G�ʒu�֌W
constexpr int CharacterPosY = 130;
constexpr int CharacterPosX = 150;
constexpr int CharacterGraphSizeWidth  = 300;
constexpr int CharacterGraphSizeHeight = 400;

//�����Ȃǂ̐F
constexpr int Color = 0xFFFFFF;

#endif // CONSTANT_EXPRESSION_VARIABLE_H_