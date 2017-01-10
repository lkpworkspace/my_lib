#ifndef __MyObj_H__
#define __MyObj_H__

class MyObj
{
public:
	MyObj();
	~MyObj();
	virtual void Run() = 0;  // 不能进行阻塞或延时
private:
	friend class MyEvent;
};

#endif