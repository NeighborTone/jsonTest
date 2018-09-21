#include "JsonRead.hpp"

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
		//‘å•ª–³—‚â‚è‚ ‚Æ‚Å’¼‚·
		sex = json.GetParameter<std::string>("Player", "data", 0);
		age = json.GetParameter<std::string>("Player", "data", 1);
		job = json.GetParameter<std::string>("Player", "data", 2);
		//”z—ñ‚Ìæ“¾
		json.GetArrayParameter<std::string>("Player", "data", data ,std::size(data));
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
//¦JSON‚É‚ÍƒRƒƒ“ƒg•¶‚Í‚È‚¢
int main()
{
	Player player;
	player.Show();
	system("pause");
}