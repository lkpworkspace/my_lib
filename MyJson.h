#ifndef __MyJson_H__
#define __MyJson_H__
#include "json/json.h"
#include <string>
#include <vector>

//config.json(����Ϊjson�ļ�������)
//{
//    "Algorithm":
//    {
//         "some":"thing",
//         "okok":"nono",
//         "xxxx":{
//			  "yyy":123.456
//         }
//    },
//    "SDK":{
//        "framelen":28
//    }
//}
//����Json�ļ�ʾ��
//int main()
//{
//	MyJson json("config.json");
//	// ����yyy��Ӧ��ֵ
//	std::string str = json.GetStringValue("Algorithm.xxxx.yyy");
//  if(json.isOk_)
//      // ��ֵ�������еı���
//
//	// д���ļ�
//	json.Write();
//
//  // ע�� ��ø�����ʱ���ʹ��GetDoubleValue,����Ҫʹ��GetFloatValue
//}

class MyJson
{
public:
	MyJson(const char*);
	~MyJson();
	//////////////////////////////////////////////
	////////////////single instance
	//static MyJson* GetInstance();
	//////////////////////////////////////////////
	////////////////get value
	float GetFloatValue(std::string name, std::string key);
	double GetDoubleValue(std::string name, std::string key);
	int GetIntValue(std::string name, std::string key);
	std::string GetStringValue(std::string name, std::string key);
	bool GetBoolValue(std::string name, std::string key);

	float GetFloatValue(Json::Value&);
	double GetDoubleValue(Json::Value&);
	int GetIntValue(Json::Value&);
	std::string GetStringValue(Json::Value&);
	bool GetBoolValue(Json::Value&);

	float GetFloatValue(std::string);
	double GetDoubleValue(std::string);
	int GetIntValue(std::string);
	std::string GetStringValue(std::string);
	bool GetBoolValue(std::string);
	//////////////////////////////////////////////
	////////////////set value
	void SetFloatValue(std::string name, std::string key, float value);
	void SetDoubleValue(std::string name, std::string key, double value);
	void SetIntValue(std::string name, std::string key, int value);
	void SetStringValue(std::string name, std::string key, std::string value);
	void SetBoolValue(std::string name, std::string key, bool value);
	//////////////////////////////////////////////
	////////////////read
	// ��ø��ڵ�
	Json::Value& Get() { return root_; }
	/////////////////////////////////////////////
	///////////////write to file
	bool Write();
	/////////////////////////////////////////////
	///////////////print json
	std::string GetContent();
	////////////////////////////////////////////
	///////////////close Json
	void Close();
public:
	bool isOk_;
private:
	void ParseFile(std::ifstream& stream);
	std::vector<std::string> ParseString(std::string);
	Json::Value GetValue(std::vector<std::string> vec);
private:
	//static MyJson* m_pInstance;
	std::string filename_;     // json�ļ���
	Json::Reader reader_;      // ����json���ļ���
	Json::Value root_;         // json�ĸ��ڵ�
	//Json::FastWriter writer_;
};

#endif