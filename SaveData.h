#ifndef SAVEDATA_H_
#define SAVEDATA_H_

#include <cstdint>

//�Z�[�u�f�[�^(�Z�[�u/���[�h/�f���[�g)���[�v
void SaveDataLoop(const int& Num) noexcept;

//�Z�[�u�f�[�^���Z�[�u(Quick)
int QuickSaveDataSave() noexcept;

//�Z�[�u�f�[�^�����[�h(Quick)
int QuickSaveDataLoad() noexcept;

//�Z�[�u�f�[�^���Z�[�u(Continue)
int ContinueSaveDataSave(const std::int32_t& RouteNum) noexcept;

//�Z�[�u�f�[�^�����[�h(Continue)
int ContinueSaveDataLoad() noexcept;

//�Z�[�u�f�[�^�p�X�N���[���V���b�g�擾
void SaveDataScreenShotGet() noexcept;

#endif // SAVEDATA_H_