#ifndef MATERIAL_MANAGER_CPP_
#define MATERIAL_MANAGER_CPP_

#include "ConstantExpressionVariable.h"
#include <vector>
#include <string>
#include <array>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace {

	//�e��f�ރt�@�C���m�F�֐�
	bool CheckMaterialExistence(const std::string& FilePath) noexcept {
		std::ifstream Material(FilePath, std::ios_base::in);
		return Material.is_open();
	}

	//�e��f�ރt�@�C���p�X����
	std::string MaterialPathCalc(const std::int32_t& i, const std::string& FilePath, const std::string& FileFormat) noexcept {
		std::ostringstream Num;

		Num << std::setfill('0') << std::setw(2) << i + 1;

		return (FilePath + Num.str() + FileFormat);
	}
}

//�e��f�ޓǍ��e���v���[�g�֐�
template <typename T, typename Func>
std::array<T, MaterialMax> MaterialLoad(std::array<T, MaterialMax>& Material, const std::string& FilePath, const std::string& FileFormat, Func&& Loader) noexcept {

	//�T�E���h�f�[�^�̓ǂݍ��݌`��
	DxLib::SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);

	for (std::int32_t i = 0; i < MaterialMax; i++) {
		if (CheckMaterialExistence(MaterialPathCalc(i, FilePath, FileFormat)))
			Material[i] = Loader(MaterialPathCalc(i, FilePath, FileFormat));
	}

	return Material;
}

//�X�N���v�g�Ǎ��֐�
void ScriptRead(std::vector<std::string>& Script, unsigned int EndFlag) noexcept;

#endif // MATERIAL_MANAGER_CPP_