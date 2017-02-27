#ifndef __MyHelp_H__
#define __MyHelp_H__
#include <cstdlib>
#include <string>
#include <vector>
#include <stdint.h>

class MyHelp
{
public:
	// 字符串转数字
	static int ToInt(const char *str);
	static float ToFloat(const char *str);
	static double ToDouble(const char* str);
	static long double ToLDouble(const char* str);
	static long ToLong(const char* str, int base);
	static long long ToLLong(const char* str, int base);
	static unsigned long ToULong(const char* str, int base);
	static unsigned long long ToULLong(const char* str, int base);
	// 数字转字符串
	static std::string ToStr(int num, int base);
	static std::string ToStr(long num, int base);
	static std::string ToStr(unsigned long num, int base);
	// 分割字符串
	static std::vector<std::string> SplitStr(std::string str, char split);
	// 获得当前时间
	static std::string GetCurTime();
	// 校验和
	static uint8_t CheckSum(uint8_t* buf, int len);
	// min : include; max : exclude
	static uint8_t RandomNum(int min, int max); // 生成一字节的随机数
	// 将一个buf中的16进制数转换成字符串的16进制数
	static std::string ToMutlStr(uint8_t* buf, int len);
};
#endif