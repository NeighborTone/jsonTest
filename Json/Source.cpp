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
		//�啪������肠�ƂŒ���
		sex = json.GetParameter<std::string>("Player", "data", 0);
		age = json.GetParameter<std::string>("Player", "data", 1);
		job = json.GetParameter<std::string>("Player", "data", 2);
		//�z��̎擾
		//json.GetArrayParameter<std::string>("Player", "data", data ,std::size(data));
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
		//for (const auto& it : data)
	//	{
		//	std::cout << "Data:" << it << std::endl;
	//	}
	}
};
//��JSON�ɂ̓R�����g���͂Ȃ�
int main()
{
	//Player player;
	//player.Show();


	//json�I�u�W�F�N�g�Ƀf�[�^��ǉ�����
	picojson::object obj;
	//�z��p
	picojson::array datalist;
	for(int i = 0; i < 5; ++i)
		datalist.push_back(picojson::value(static_cast<double>(i)));
	//�f�[�^�̒ǉ�
	obj.insert(std::make_pair("Name", "Hoge"));
	obj.insert(std::make_pair("number", picojson::value(static_cast<double>(1))));
	obj.insert(std::make_pair("flag", picojson::value(static_cast<bool>(false))));
	obj.insert(std::make_pair("array", picojson::value(datalist)));
	//������ɂ��邽�߂�value���g�p
	picojson::value val(obj);
	std::string out = val.serialize();
	std::cout << out;
	//�����o��
	std::ofstream outputfile("out.json");
	outputfile << out;
	outputfile.close();
	system("pause");

}