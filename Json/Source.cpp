#include "JsonRead.hpp"

//※JSONにはコメント文はない
int main()
{
	JsonRead json;
	json.Load("test.json");
	std::cout << json.GetParameter<number>("Player", "hp");
	system("pause");
}