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

//※JSONにはコメント文はない
int main()
{
	// JSONデータの読み込み。
	std::stringstream ss;
	std::ifstream ifs("test.json", std::ios::in);
	if (ifs.fail()) 
	{
		std::cerr << "failed to read test.json" << std::endl;
	}
	ss << ifs.rdbuf();
	ifs.close();

	// JSONデータを解析する。
	picojson::value v;	//この変数に内容がすべて入る
	const std::string err = picojson::parse(v, ss); //内容を取り込む
	if (err.empty() == false)
	{
		std::cerr << err << std::endl;
	}

	//パースされたデータを取得
	picojson::object& obj = v.get<picojson::object>()["Player"].get<picojson::object>();
	auto name = obj["name"].get<std::string>();
	std::cout << "name: " << name << std::endl;
	//jsonは数値はすべてdoubleで扱う
	//intやfloatだと未解決の外部シンボルとなる
	using number = double;
	auto hp = obj["hp"].get<number>();
	std::cout << "hp: " << static_cast<int>(hp) << std::endl;
	auto atk = obj["atk"].get<number>();
	std::cout << "atk: " << static_cast<float>(atk) << std::endl;
	auto isHuman = obj["human"].get<bool>();
	std::cout << "human: " << std::boolalpha << isHuman << std::endl;
	//配列の取得
	auto arr = obj["array"].get<picojson::array>();
	for (const auto& it : arr)
	{
		//配列の中身を取得する
		auto num = it.get<number>();
		std::cout << "array: " << num << std::endl;
	}

	system("pause");
}