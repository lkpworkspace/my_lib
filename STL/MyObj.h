#ifndef __MyObj_H__
#define __MyObj_H__

class MyObj
{
public:
	MyObj();
	~MyObj();
	virtual void Run() = 0;  // ���ܽ�����������ʱ
private:
	friend class MyEvent;
};

#endif