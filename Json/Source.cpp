#include "JsonRead.hpp"

//��JSON�ɂ̓R�����g���͂Ȃ�
int main()
{
	JsonRead json;
	json.Load("test.json");
	std::cout << json.GetParameter<number>("Player", "hp");
	system("pause");
}