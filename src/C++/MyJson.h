#ifndef __MyJson_H__
#define __MyJson_H__
#include "json/json.h"
#include <string>
#include <vector>

//config.json(以下为json文件的内容)
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
//访问Json文件示例
//int main()
//{
//	MyJson json("config.json");
//	// 访问yyy对应的值
//	std::string str = json.GetStringValue("Algorithm.xxxx.yyy");
//  if(json.isOk_)
//      // 赋值给程序中的变量
//
//	// 写入文件
//	json.Write();
//
//  // 注： 获得浮点数时最好使用GetDoubleValue,而不要使用GetFloatValue
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
	// 获得根节点
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
	std::string filename_;     // json文件名
	Json::Reader reader_;      // 分析json的文件类
	Json::Value root_;         // json的根节点
	//Json::FastWriter writer_;
};

#endif