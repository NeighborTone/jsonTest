#include "JsonRead.hpp"
#include <memory>
#include <new>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

class Player
{
private:
	int hp;
	int atk;
	bool isHuman;
	std::string name;
	std::string sex;
	std::string age;
	std::string job;
	std::string data[3];
public:
	Player()
	{
		JsonRead json;
		json.Load("test.json");
		name = json.GetParameter<std::string>("Player", "name");
		hp = static_cast<int>(json.GetParameter<number>("Player", "hp"));
		atk = static_cast<int>(json.GetParameter<number>("Player", "atk"));
		isHuman = json.GetParameter<bool>("Player", "human");
		//大分無理やりあとで直す
		sex = json.GetParameter<std::string>("Player", "data", 0);
		age = json.GetParameter<std::string>("Player", "data", 1);
		job = json.GetParameter<std::string>("Player", "data", 2);
		//配列の取得
		json.GetArrayParameter<std::string>("Player", "data", data, std::size(data));
	}
	void Show()
	{
		std::cout << "Name:" << name << std::endl;
		std::cout << "HP:" << hp << std::endl;
		std::cout << "ATK:" << atk << std::endl;
		std::cout << "isHuman:" << std::boolalpha << isHuman << std::endl;
		std::cout << "Sex:" << sex << std::endl;
		std::cout << "Age:" << age << std::endl;
		std::cout << "Job:" << job << std::endl;
		for (const auto& it : data)
		{
			std::cout << "Data:" << it << std::endl;
		}
	}
};
//※JSONにはコメント文はない
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Player player;
	//player.Show();

	//jsonオブジェクトにデータを追加する
	picojson::object obj;
	//配列用
	picojson::array datalist;
	for(int i = 0; i < 5; ++i)
		datalist.push_back(picojson::value(static_cast<double>(i)));
	//データの追加
	obj.insert(std::make_pair("Name", "Hoge"));
	obj.insert(std::make_pair("number", picojson::value(static_cast<double>(1))));
	obj.insert(std::make_pair("flag", picojson::value(static_cast<bool>(false))));
	obj.insert(std::make_pair("array", picojson::value(datalist)));
	//文字列にするためにvalueを使用
	picojson::value val(obj);
	std::string out = val.serialize();
	std::cout << "書き出し" << std::endl;
	//★★★★★★★★★ここで暗号化をしたい★★★★★★★★★★★★

	std::cout << out << std::endl;
	//書き出し
	std::ofstream outputfile("out.json");
	outputfile << out;
	outputfile.close();

	//JSONデータの読み込み。
	std::stringstream ss;
	std::ifstream ifs("out.json", std::ios::in);
	if (ifs.fail())
	{
		std::cerr << "failed to read out.json" << std::endl;
	}
	ss << ifs.rdbuf();
	ifs.close();
	//★★★★★★★★★ここで復元をしたい★★★★★★★★★★★★★★

	//JSONデータを解析する。
	picojson::value v;
	const std::string err = picojson::parse(v, ss);
	if (err.empty() == false)
	{
		std::cerr << err << std::endl;
	}
	std::cout << "読み込み" << std::endl;
	std::cout << v.serialize() << std::endl;
	system("pause");

}