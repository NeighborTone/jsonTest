#include "JsonRead.hpp"

//¦JSON‚É‚ÍƒRƒƒ“ƒg•¶‚Í‚È‚¢
int main()
{
	JsonRead json;
	json.Load("test.json");
	std::cout << json.GetParameter<number>("Player", "hp");
	system("pause");
}