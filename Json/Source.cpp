#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


#include "picojson.h"

template <class T>
const T GetParameter(const std::string& name,
	picojson::object& jsonObj)
{
	return jsonObj[name].get<T>();
}

//��JSON�ɂ̓R�����g���͂Ȃ�
int main()
{
	// JSON�f�[�^�̓ǂݍ��݁B
	std::stringstream ss;
	std::ifstream ifs("test.json", std::ios::in);
	if (ifs.fail()) 
	{
		std::cerr << "failed to read test.json" << std::endl;
	}
	ss << ifs.rdbuf();
	ifs.close();

	// JSON�f�[�^����͂���B
	picojson::value v;	//���̕ϐ��ɓ��e�����ׂē���
	const std::string err = picojson::parse(v, ss); //���e����荞��
	if (err.empty() == false)
	{
		std::cerr << err << std::endl;
	}

	//�p�[�X���ꂽ�f�[�^���擾
	picojson::object& obj = v.get<picojson::object>()["Player"].get<picojson::object>();
	auto name = obj["name"].get<std::string>();
	std::cout << "name: " << name << std::endl;
	//json�͐��l�͂��ׂ�double�ň���
	//int��float���Ɩ������̊O���V���{���ƂȂ�
	using number = double;
	auto hp = obj["hp"].get<number>();
	std::cout << "hp: " << static_cast<int>(hp) << std::endl;
	auto atk = obj["atk"].get<number>();
	std::cout << "atk: " << static_cast<float>(atk) << std::endl;
	auto isHuman = obj["human"].get<bool>();
	std::cout << "human: " << std::boolalpha << isHuman << std::endl;
	//�z��̎擾
	auto arr = obj["array"].get<picojson::array>();
	for (const auto& it : arr)
	{
		//�z��̒��g���擾����
		auto num = it.get<number>();
		std::cout << "array: " << num << std::endl;
	}

	system("pause");
}