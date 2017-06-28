#ifndef __MySerialPort_H__
#define __MySerialPort_H__

#include <windows.h>
#include <process.h>
#include <stdint.h>
#include <queue>
#include <string>
#include <sstream>
#include <devguid.h>
#include <SetupAPI.h>
#include <time.h>

#pragma comment(lib, "SetupAPI.lib")

// 存储串口名字和串口号
typedef struct _sComInfo_t
{
	std::string ComName;
	int comId;
	_sComInfo_t()
	{
		comId = -1;
	}
}sComInfo_t;

class MySerialPort
{
public:
	MySerialPort();
	~MySerialPort();
	bool OpenPort();
	bool OpenPort(int comNo);                            //打开串口
	bool ClosePort();                                    //关闭串口

	void SearchCom();                                    //搜索串口并保存在结构体中
	int SearchComNo(std::string comName);                //搜索指定名字的串口，若没搜到则返回0

	bool SendCmd(uint8_t *data_buf, int len);            //发数据
	UINT BytesToRead();                                  //判断读了多少个字节
	bool ReadChar(char &portData);                       //读数据

	bool IsOpen() { return port_ != INVALID_HANDLE_VALUE; }
	std::vector<sComInfo_t> cominfo_buf_;
private:
	int portNum_;
	HANDLE port_;
	CRITICAL_SECTION critical_section_;
};


#endif