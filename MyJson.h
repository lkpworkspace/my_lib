/*
	����ʹ��jsoncpp��
*/
#ifndef __MyJson_H__
#define __MyJson_H__
#include "json/json.h"
#include <string>

class MyJson
{
public:
	MyJson(char*);
	~MyJson();
	////////////////read
	// std::string GetString(std::string);
	// int GetInt(std::string);
	// ��ø��ڵ�
	Json::Value& Get() { return root_; }
	/////////////////////////////////////////////
	///////////////write to file
	bool Write();
	/////////////////////////////////////////////
	void Close();
private:
	void ParseFile(std::ifstream& stream);
private:
	std::string filename_;
	Json::Reader reader_;
	Json::Value root_;
	//Json::FastWriter writer_;
	bool isOpen_;
	bool isOk_;
};

// read example
// std::cout << json.Get()["framelen"].asInt();
// std::cout << json.Get()["drivers"][0]["plugin"].asString();

// config.json�ļ���
// {
//	 "framelen":28,
//	 	"VID" : "2700",
//		"PID" : "2000",
//	 	"drivers" : [{
//			"plugin": "com_osvr_Multiserver",
//			"driver" : "YEI_3Space_Sensor"
//		}]
// }

// write example
//	Json::Value arrayObj;   // ��������  
//	Json::Value new_item, new_item1;
//	new_item["date"] = "2011-11-11";
//	new_item1["time"] = "11:11:11";
//	arrayObj.append(new_item);  // ���������Ա  
//	arrayObj.append(new_item1); // ���������Ա  
//	json.get()["state"] = arrayObj;


// DEMO
//int main()
//{
//	MyJson json("config.json");
//
//	// read
//	std::cout << json.Get()["framelen"].asInt() << std::endl;
//	std::cout << json.Get()["PID"] << std::endl;
//
//	// write
//	Json::Value test;
//	test = "xxx";
//	json.Get()["test"] = test;
//
//	//print
//	std::cout << json.Get().toStyledString();
//
//	// write to file
//	json.Write();
//
//	std::cin.get();
//	return 0;
//}

#endif