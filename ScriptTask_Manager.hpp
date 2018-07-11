#ifndef SCRIPT_TASK_MANAGER_CPP_
#define SCRIPT_TASK_MANAGER_CPP_

#include "ConstantExpressionVariable.h"
#include <vector>
#include <string>
#include <array>

//�e��f�ފi�[�ϐ�
template <typename T>
using Material = std::vector<T>;


//�X�N���v�g�^�O�����֐�
void ScriptTagTaskManager(Material<std::string>& Script, Material<int>& BackGround, Material<int>& Character, Material<int>& BackGroundMusic, Material<int>& SoundEffect, Material<std::string>& Movie, Material<int>& ImageEffect) noexcept;

#endif //SCRIPT_TASK_MANAGER_CPP_