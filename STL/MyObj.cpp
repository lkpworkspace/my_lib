#include "MyObj.h"
#include "MyEvent.h"

MyObj::MyObj()
{
	MyEvent::Start();
	MyEvent::AddEvent(this);
}

MyObj::~MyObj()
{

}