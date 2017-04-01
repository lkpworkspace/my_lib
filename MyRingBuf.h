#ifndef __MYRINGBUF_H__
#define __MYRINGBUF_H__
#include <malloc.h>

/*DEMO
#include <iostream>
#include "MyRingBuf.h"

int main(int argc, char *argv[])
{
    MyRingBuf<int> buf;
    buf.EnQueue(10);
    buf.EnQueue(20);
    std::cout << buf.GetLength();
    int a = 0;
    buf.DeQueue(a);
    std::cout << a << std::endl;
    buf.DeQueue(a);
    std::cout << a << std::endl;
    return 0;
}
*/

template<class T>
class MyRingBuf
{
public:
    MyRingBuf(int size = 10);
    int GetLength();
    bool EnQueue(T t);
    bool DeQueue(T& t);
private:
    typedef struct{
        T* base;
        int front;
        int rear;
    }SqQueue;
private:
    void InitQueue();
private:
    SqQueue m_queue;
    int m_maxSize;
};

template<class T>
MyRingBuf<T>::MyRingBuf(int size)
{
    m_maxSize = size;
    InitQueue();
}

template<class T>
void MyRingBuf<T>::InitQueue()
{
    m_queue.base = (T*)malloc(m_maxSize*sizeof(T));
    m_queue.front = m_queue.rear = 0;
}

template<class T>
int MyRingBuf<T>::GetLength()
{
    return (m_queue.rear - m_queue.front + m_maxSize) % m_maxSize;
}

template<class T>
bool MyRingBuf<T>::EnQueue(T t)
{
    if((m_queue.rear+1) % m_maxSize == m_queue.front) return false;
    m_queue.base[m_queue.rear] = t;
    m_queue.rear = (m_queue.rear + 1) % m_maxSize;
    return true;
}

template<class T>
bool MyRingBuf<T>::DeQueue(T& t)
{
    if(m_queue.front == m_queue.rear) return false;
    t = m_queue.base[m_queue.front];
    m_queue.front = (m_queue.front + 1) % m_maxSize;
    return true;
}
#endif // MYRINGBUF_H
