#include "MyJson.h"
#include <iostream>
#include <fstream>

MyJson::MyJson(char* filename)
	:isOpen_(false),
	isOk_(false),
	filename_(filename)
{
	// 打开文件
	std::ifstream file(filename);
	// 解析文件
	ParseFile(file);
	// 关闭文件
	isOpen_ = false;
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

//std::string MyJson::GetString(std::string key)
//{
//	if (isOk_)
//		return root_[key].asString();
//	return NULL;
//}
//int MyJson::GetInt(std::string key)
//{
//	if (isOk_)
//		return (int)root_[key].asInt();
//	return -1;
//}

void MyJson::Close()
{
	isOk_ = false;
	root_.clear();
}

// 写入文件
bool MyJson::Write()
{
	std::ofstream file(filename_);
	//std::string str = writer_.write(root_);
	//file << str;
	file << root_.toStyledString();
	file.close();
	return true;
}