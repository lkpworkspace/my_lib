#include "MyHid.h"
#include <iostream>

bool MyHid::isExit_ = true;

MyHid::MyHid()
{
	isOpen_ = false;
	isInit_ = false;
	vid_ = 0x0485;
	pid_ = 0x00a8;
	for (int i = 0; i < HANDLE_COUNT; ++i)
	{
		handle_[i] = nullptr;
	}
}

MyHid::MyHid(unsigned short vid, unsigned short pid)
	:vid_(vid),
	pid_(pid)
{
	isOpen_ = false;
	isInit_ = false;
	for (int i = 0; i < HANDLE_COUNT; ++i)
	{
		handle_[i] = nullptr;
	}
}

bool MyHid::Open()
{
	struct hid_device_info *devs_;
	struct hid_device_info *cur_dev_;
	devs_ = cur_dev_ = nullptr;

	if (!isInit_)
	{
		if (hid_init())
			return false;
		isInit_ = true;
	}
	devs_ = hid_enumerate(vid_, pid_);
	cur_dev_ = devs_;
	for (int i = 0; cur_dev_ != nullptr; ++i, cur_dev_ = cur_dev_->next)
	{
		handle_[i] = hid_open_path(cur_dev_->path);
		if (!handle_[i])
		{
			isOpen_ = false;
			return false;
		}	
	}
	//if (handle_[0] != nullptr || handle_[1] != nullptr)
		//isOpen_ = true;
	hid_free_enumeration(devs_);
	return true;
}

bool MyHid::SendCmd(uint8_t* buf, int len, int iface)
{
	if (!isOpen_)
		return false;
	if (handle_[iface])
	{
		int res = hid_write(handle_[iface], buf, len);
		if (res <= 0)
			return false;
		else
			return true;
	}
	return false;
}

int MyHid::Read(uint8_t** buf, int len, int iface)
{
	if (!isOpen_)
		return false;
	if (handle_[iface] == nullptr) return 0;
	memset(buf_read1_, 0, 65);
	int res = hid_read(handle_[iface], buf_read1_, len);
	*buf = buf_read1_;
	return res;
}

bool MyHid::Search()
{
	bool hasDev = false;
	struct hid_device_info *devs;

	if (!isInit_)
	{
		if (hid_init())
			return false;
		isInit_ = true;
	}
	if (!(devs = hid_enumerate(vid_, pid_)))
	{// 没有搜到该设备
		return false;
	}
	// 搜索到该设备，释放hid设备信息链表
	hid_free_enumeration(devs);
	return true;
}


void MyHid::Close()
{
	isInit_ = false;
	isOpen_ = false;
	for (int i = 0; i < HANDLE_COUNT; ++i)
	{
		if (handle_[i] != nullptr)
		{
			hid_close(handle_[i]);
			handle_[i] = nullptr;
		}
	}
}

// 1 不阻塞； 0 阻塞；
void MyHid::SetBlock(int b)
{
	for (int i = 0; i < HANDLE_COUNT; ++i)
	{
		if (handle_[i])
			hid_set_nonblocking(handle_[i], b);
	}
}

void MyHid::Exit()
{
	if (!isExit_)
	{
		hid_exit();
		isExit_ = true;
	}	
}