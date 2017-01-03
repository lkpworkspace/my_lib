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

class MyHid
{
public:
	MyHid()
	{
		isOpen_ = false;
		isInit_ = false;
		vid_ = 0x0485;
		pid_ = 0x00a8;
		for (int i = 0; i < 5; ++i)
		{
			handle_[i] = nullptr;
		}
		devs_ = cur_dev_ = nullptr;
	}
	~MyHid(){}
public:
	bool isOpen_;
	bool isInit_;
	unsigned short vid_;
	unsigned short pid_;
	// search ,open and sendcmd
	bool SearchOpenSendCmd()
	{
		if (SearchOpen())
		{
			if (SendCmd1())
			{
				return true;
			}
		}
		return false;
	}
	bool SearchOpen();
	bool SendCmd1();
private:
	hid_device *handle_[5];             // 当前存储的设备句柄
	struct hid_device_info *devs_;      // 设备链表
	struct hid_device_info *cur_dev_;   // 当前使用的设备
};


#endif