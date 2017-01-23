#include "MyJson.h"
#include <iostream>
#include <fstream>

//MyJson* MyJson::m_pInstance = nullptr;
//
//MyJson* MyJson::GetInstance()
//{
//	if (m_pInstance == nullptr)
//		m_pInstance = new MyJson("StepVR_Config.json");
//	return m_pInstance;
//}

MyJson::MyJson(const char* filename)
	:isOk_(false),
	filename_(filename)
{
	// 打开文件
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "open json file failed";
		exit(1);
	}
	// 解析文件
	ParseFile(file);
	if (!isOk_)
	{
		std::cout << "parse json file failed";
		exit(1);
	}
	// 关闭文件
	file.close();
}

MyJson::~MyJson()
{
	Close();
}


void MyJson::ParseFile(std::ifstream& stream)
{
	if (reader_.parse(stream, root_, false))
		isOk_ = true;
}

void MyJson::Close()
{
	isOk_ = false;
	root_.clear();
}

// 写入文件
bool MyJson::Write()
{
	std::ofstream file(filename_);            // 打开文件并写入json数据
	//std::string str = writer_.write(root_); // 写入没有换行的json文件
	//file << str;
	file << root_.toStyledString();           // 写入有换行的json文件
	file.close();
	return true;
}

std::string MyJson::GetContent()
{
	return root_.toStyledString();
}

////////////////////////////////////////get value
float MyJson::GetFloatValue(std::string name, std::string key)
{
	if (!root_[name][key].isNull())
	{
		isOk_ = true;
		return root_[name][key].asFloat();
	}
	isOk_ = false;
	return 0.0f;
}
double MyJson::GetDoubleValue(std::string name, std::string key)
{
	if (!root_[name][key].isNull() && root_[name][key].isDouble())
	{
		isOk_ = true;
		return root_[name][key].asDouble();
	}
	isOk_ = false;
	return 0.0;
}
int MyJson::GetIntValue(std::string name, std::string key)
{
	if (!root_[name][key].isNull() && root_[name][key].isInt())
	{
		isOk_ = true;
		return root_[name][key].asInt();
	}
	isOk_ = false;
	return 0;
}
std::string MyJson::GetStringValue(std::string name, std::string key)
{
	if (!root_[name][key].isNull())
	{
		isOk_ = true;
		return root_[name][key].asString();
	}
	isOk_ = false;
	return "";
}
bool MyJson::GetBoolValue(std::string name, std::string key)
{
	if (!root_[name][key].isNull() && root_[name][key].isBool())
	{
		isOk_ = true;
		return root_[name][key].asBool();
	}
	isOk_ = false;
	return false;
}

float MyJson::GetFloatValue(Json::Value& v)
{
	return v.asFloat();
}
double MyJson::GetDoubleValue(Json::Value& v)
{
	if (!v.isNull() && v.isDouble())
	{
		isOk_ = true;
		return v.asDouble();
	}
	isOk_ = false;
	return 0.0;
}
int MyJson::GetIntValue(Json::Value& v)
{
	if (!v.isNull() && v.isIntegral())
	{
		isOk_ = true;
		return v.asInt();
	}
	isOk_ = false;
	return 0;
}
std::string MyJson::GetStringValue(Json::Value& v)
{
	if (!v.isNull())
	{
		isOk_ = true;
		return v.asString();
	}
	isOk_ = false;
	return "";
}
bool MyJson::GetBoolValue(Json::Value& v)
{
	if (!v.isNull() && v.isBool())
	{
		isOk_ = true;
		return v.asBool();
	}
	isOk_ = false;
	return false;
}

float MyJson::GetFloatValue(std::string str)
{
	std::vector<std::string> vec = ParseString(str);
	return GetFloatValue(GetValue(vec));
}
double MyJson::GetDoubleValue(std::string str)
{
	std::vector<std::string> vec = ParseString(str);
	return GetDoubleValue(GetValue(vec));
}
int MyJson::GetIntValue(std::string str)
{
	std::vector<std::string> vec = ParseString(str);
	return GetIntValue(GetValue(vec));
}
std::string MyJson::GetStringValue(std::string str)
{
	std::vector<std::string> vec = ParseString(str);
	return GetStringValue(GetValue(vec));
}
bool MyJson::GetBoolValue(std::string str)
{
	std::vector<std::string> vec = ParseString(str);
	return GetBoolValue(GetValue(vec));
}
////////////////////////////////////////set value
void MyJson::SetFloatValue(std::string name, std::string key, float value)
{
	if (!root_[name][key].isNull())
		root_[name][key] = value;
}
void MyJson::SetDoubleValue(std::string name, std::string key, double value)
{
	if (!root_[name][key].isNull() && root_[name][key].isDouble())
	{
		isOk_ = true;
		root_[name][key] = value;
	}
	isOk_ = false;
}
void MyJson::SetIntValue(std::string name, std::string key, int value)
{
	if (!root_[name][key].isNull() && root_[name][key].isInt())
	{
		isOk_ = true;
		root_[name][key] = value;
	}
	isOk_ = false;
}
void MyJson::SetStringValue(std::string name, std::string key, std::string value)
{
	if (!root_[name][key].isNull() && root_[name][key].isString())
	{
		isOk_ = true;
		root_[name][key] = value;
	}
	isOk_ = false;

}
void MyJson::SetBoolValue(std::string name, std::string key, bool value)
{
	if (!root_[name][key].isNull() && root_[name][key].isBool())
	{
		isOk_ = true;
		root_[name][key] = value;
	}
	isOk_ = false;
}

//////////////////////////////////////////////////////////////////////辅助函数
std::vector<std::string> MyJson::ParseString(std::string str)
{
	int pos;
	std::vector<std::string> res;
	str += '.';
	int size = str.size();

	for (int i = 0; i < size; ++i)
	{
		pos = str.find('.', i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			res.push_back(s);
			i = pos;
		}
	}
	return res;
}

Json::Value MyJson::GetValue(std::vector<std::string> vec)
{
	switch (vec.size())
	{
	case 1:
		return root_[vec[0]];
		break;
	case 2:
		return root_[vec[0]][vec[1]];
		break;
	case 3:
		return root_[vec[0]][vec[1]][vec[2]];
		break;
	case 4:
		return root_[vec[0]][vec[1]][vec[2]][vec[3]];
		break;
	case 5:
		return root_[vec[0]][vec[1]][vec[2]][vec[3]][vec[4]];
		break;
	case 6:
		return root_[vec[0]][vec[1]][vec[2]][vec[3]][vec[4]][vec[5]];
		break;
	case 7:
		return root_[vec[0]][vec[1]][vec[2]][vec[3]][vec[4]][vec[5]][vec[6]];
		break;
	case 8:
		return root_[vec[0]][vec[1]][vec[2]][vec[3]][vec[4]][vec[5]][vec[6]][vec[7]];
		break;
	case 9:
		return root_[vec[0]][vec[1]][vec[2]][vec[3]][vec[4]][vec[5]][vec[6]][vec[7]][vec[8]];
		break;
	case 10:
		return root_[vec[0]][vec[1]][vec[2]][vec[3]][vec[4]][vec[5]][vec[6]][vec[7]][vec[8]][vec[9]];
		break;
	default:
		break;
	}
	Json::Value v;
	return v;
}