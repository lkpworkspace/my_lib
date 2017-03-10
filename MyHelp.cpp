#include "MyHelp.h"
#include <chrono>

// �ַ���ת����
int MyHelp::ToInt(const char *str)
{
	return atoi(str);
}
float MyHelp::ToFloat(const char *str)
{
	char* pEnd; // (out)ָ������ĵط�,Ҳ���ǲ����������ĵط�(�������ո�tab��)
	return strtof(str,&pEnd);
}
double MyHelp::ToDouble(const char* str)
{
	char* pEnd;
	return strtod(str,&pEnd);
}
long double MyHelp::ToLDouble(const char* str)
{
	char* pEnd;
	return strtold(str, &pEnd);
}
long MyHelp::ToLong(const char* str, int base)
{
	char* pEnd;
	return strtol(str, &pEnd, base);
}
long long MyHelp::ToLLong(const char* str, int base)
{
	char* pEnd;
	return strtoll(str, &pEnd, base);
}
unsigned long MyHelp::ToULong(const char* str, int base)
{
	char* pEnd;
	return strtoul(str, &pEnd, base);
}
unsigned long long MyHelp::ToULLong(const char* str, int base)
{
	char* pEnd;
	return strtoull(str, &pEnd, base);
}

// ����ת�ַ���
std::string MyHelp::ToStr(int num, int base)
{// num Ϊ 10���Ƶ���
	char buf[20] = { 0 };
	itoa(num, buf, base);
	return std::string(buf);
}
std::string MyHelp::ToStr(long num, int base)
{// num Ϊ 10���Ƶ���
	char buf[20] = { 0 };
	ltoa(num, buf, base);
	return std::string(buf);
}
std::string MyHelp::ToStr(unsigned long num, int base)
{
	char buf[20] = { 0 };
	ultoa(num, buf, base);
	return std::string(buf);
}
// �ָ��ַ���
std::vector<std::string> MyHelp::SplitStr(std::string str, char split)
{
	int pos;
	std::vector<std::string> res;
	str += split;
	int size = str.size();

	for (int i = 0; i < size; ++i)
	{
		pos = str.find(split, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			res.push_back(s);
			i = pos;
		}
	}
	return res;
}
// ��ȡ��ǰʱ��
std::string MyHelp::GetCurTime()
{
	time_t now_time;
	char tmp[64] = { 0 };

	now_time = time(NULL);
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&now_time));
	return std::string(tmp);
}
//struct tm *localtime(const time_t *timer)����һ����tm�ṹ���Ļ���ʱ����Ϣ
//char* asctime(struct tm * ptr)�õ�����ʱ��(����ʱ��ת��ΪASCII��)
//char *ctime(const time_t *time)�õ�����ʱ��
//double difftime(time_t time2, time_t time1)�õ����λ���ʱ����λΪ��
//struct tm *gmtime(time_t *time)�õ��Խṹtm��ʾ��ʱ����Ϣ
//size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm *timeptr);
//���ݸ�ʽ�ַ��������ַ�����
//struct tm *localtime(const time_t *timer);
//ȡ�õ���ʱ�䣬localtime��ȡ�Ľ���ɽṹtm����
//���ص��ַ������������еĸ�ʽ������
//%a ���ڼ�����д��Eg : Tue
//%A ���ڼ���ȫ���� Eg : Tuesday
//%b �·����Ƶ���д��
//%B �·����Ƶ�ȫ����
//%c ���ض�����ʱ��ϼѱ�ʾ�ַ�����
//%d �����ֱ�ʾ���µĵڼ���(��ΧΪ 00 �� 31)������
//%H �� 24 Сʱ�����ֱ�ʾСʱ��(��ΧΪ 00 �� 23)��
//%I �� 12 Сʱ�����ֱ�ʾСʱ��(��ΧΪ 01 �� 12)��
//%j �����ֱ�ʾ����ȵĵڼ���(��ΧΪ 001 �� 366)��
//%m �·ݵ�����(��Χ�� 1 �� 12)��
//%M ���ӡ�
//%p �� ''AM'' �� ''PM'' ��ʾ���ض�ʱ�䡣
//%S ������
//%U ���ֱ�ʾΪ����ȵĵڼ��ܣ���һ�������ɵ�һ�����տ�ʼ��
//%W ���ֱ�ʾΪ����ȵĵڼ��ܣ���һ�������ɵ�һ����һ��ʼ��
//%w �����ֱ�ʾ���ܵĵڼ���(0 Ϊ����)��
//%x ����ʱ������ڱ�ʾ����
//%X �������ڵ�ʱ���ʾ���� Eg : 15 : 26 : 30
//% y ��λ���ֱ�ʾ���(��Χ�� 00 �� 99)��
//%Y ������������ֱ�ʾ������λ���� Eg : 2008
//% Z(%z) ʱ����������д��Eg : �й���׼ʱ��
//%% % �ַ���
std::time_t MyHelp::GetTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	return tmp.count();
}

uint8_t MyHelp::CheckSum(uint8_t* buf, int len)
{
	uint8_t checksum = 0x00;
	for (int i = 0; i < len - 1; ++i)
	{
		checksum += buf[i];
	}
	return checksum;
}

// min : include; max : exclude
uint8_t MyHelp::RandomNum(int min, int max) // ����һ�ֽڵ������
{
	uint8_t temp = 0x00;

	if (max < min) return 0x00;
	temp = rand() % (max - min) + min;
	return temp;
}
std::string MyHelp::ToMutlStr(uint8_t* buf, int len)
{
	std::string temp;
	uint8_t *temp_buf1 = new uint8_t[len * 2];
	char temp_buf2[4] = { 0 };
	int j = 0;

	temp += "  ";
	memset(temp_buf1, 0, len * 2);
	for (int i = 0; i < len * 2; i += 2)
	{
		temp_buf1[i] = buf[j++];
		sprintf(temp_buf2, "%x", temp_buf1[i]);
		if (temp_buf1[i] <= 0x0f)
		{
			temp += '0';
			temp += temp_buf2;
		}
		else
		{
			temp += temp_buf2;
		}
		temp += " ";
		memset(temp_buf2, 0, 4);
	}
	delete temp_buf1;
	return temp;
}

