#ifndef __MyHid_H__
#define __MyHid_H__
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <queue>
#include "hidapi.h"
#include <stdint.h>

// hid句柄数量
#define HANDLE_COUNT 2

class MyHid
{
public:
	MyHid();
	MyHid(unsigned short, unsigned short);
	~MyHid(){ Close(); }
public:// read write search ...
	bool Search();                                        // 搜索指定的设备
	bool SendCmd(uint8_t* buf, int len, int iface = 0);   // 发送命令1
	int Read(uint8_t** buf,int len, int iface = 0);       // 读handle1
	void Close();                                         // 关闭句柄
	bool Open();                                          // 搜索指定的hid并打开
public:// get set
	void SetDevNum(unsigned short vid, unsigned short pid){ vid_ = vid; pid_ = pid; }   // 设置设备号
	void GetDevNum(unsigned short &vid, unsigned short &pid){ vid = vid_; pid = pid_; } // 获得设备号
	void SetBlock(int b);                                                               // 设置阻塞
public:// static mathod
	static void Exit();                                   // 退出hid
public:
	bool isOpen_;
	bool isInit_;
	unsigned short vid_;
	unsigned short pid_;
private:
	static bool isExit_;
	uint8_t buf_read1_[65];                // handle1的读缓存
	uint8_t buf_read2_[65];                // handle2的都缓存
	hid_device *handle_[HANDLE_COUNT];     // 当前存储的设备句柄
};


#endif