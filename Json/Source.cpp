#include "JsonRead.hpp"

struct Player
{
	int hp;
	int atk;
	bool isHuman;
	void Show()
	{
		std::cout << "HP:" << hp << std::endl;
		std::cout << "ATK:" << atk << std::endl;
		std::cout << "Human?:" << std::boolalpha << isHuman << std::endl;
	}
};
//¦JSON‚É‚ÍƒRƒƒ“ƒg•¶‚Í‚È‚¢
int main()
{
	Player player;
	JsonRead json;
	json.Load("test.json");
	player.hp = static_cast<int>(json.GetParameter<number>("Player", "hp"));
	player.atk = static_cast<int>(json.GetParameter<number>("Player", "atk"));
	player.isHuman = json.GetParameter<bool>("Player", "human");

	player.Show();
	system("pause");
}