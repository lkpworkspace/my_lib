#include "MyHid.h"
#include <qdebug.h>

bool MyHid::SearchOpen()
{
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
		qDebug() << cur_dev_->path;
		if (!handle_) {
			qDebug() << "unable to open device";
			return false;
		}
	}
	hid_free_enumeration(devs_);
	return true;
}

bool MyHid::SendCmd1()
{
	int res = -1;
	uint8_t buf[65];
	buf[0] = 0x01;
	buf[1] = 0x11;
	buf[2] = 0x11;
	buf[3] = 0x11;
	
	for (int i = 0; i < 5; ++i)
	{
		if (handle_[i])
		{
			qDebug() << "[send cmd] : send1" << endl;
			int res = hid_write(handle_[i], buf, 33);
			qDebug() << "[send cmd] : send2 res = " << res;
			if (res <= 0)
				continue;
			else
				return true;
		}
	}
	return false;
}
