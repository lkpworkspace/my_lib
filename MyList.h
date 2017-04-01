#ifndef MY_LIST_HPP
#define MY_LIST_HPP
/*
 *  demo:
 *      双向循环链表
 *   #include <iostream>
 *   #include "MyList.h"
 *
 *   using namespace std;
 *   using namespace my_master
 *
 *   int main()
 *   {
 *       MyList<int> list;
 *       list.AddHead(10);
 *       list.AddHead(11);
 *       list.AddHead(12);
 *       cout << "list Count = " << list.Count() << endl;
 *
 *       for(int i = 0; i < list.Count(); ++i)
 *       {
 *           cout << list.GetData(i) << endl;
 *       }
 *
 *       list.DelWithIndex(0);
 *       list.DelHead();
 *       list.DelTail();
 *
 *       for(int i = 0; i < list.Count(); ++i)
 *       {
 *           cout << list.GetData(i) << endl;
 *       }
 *       return 0;
 *   }
 */
namespace my_master {


template<typename T>
class MyNode_list
{
public:
    MyNode_list()
        :m_data(0),m_prev(NULL),m_next(NULL)
    {}
    MyNode_list(T data)
        :m_data(data),m_prev(NULL),m_next(NULL)
    {}
    MyNode_list<T>* m_prev;
    MyNode_list<T>* m_next;
    T GetData(){return m_data;}
    void SetData(T data){this->m_data = data;}
private:
    T m_data;
};

template<typename T>
class MyList
{
public:
    MyList(){__Init();}
    ~MyList(){Clear(true);}
    ////////////////////////////////////
    void AddHead(T data);//
    void AddTail(T data);//
    void DelWithIndex(int index,bool b = true);
    void Del(T data, bool b = true);
    ////////////////////////////////////
private:
    void AddHead(MyNode_list<T>* node);//
    void AddTail(MyNode_list<T>* node);//
    void Del(MyNode_list<T>* node,bool b = false);//
    void DelHead(bool b = false);//
    void DelTail(bool b = false);//
    void MoveHead(MyNode_list<T>* node);//
    void MoveTail(MyNode_list<T>* node);//
    void Append(MyList<T>* to, MyList<T>* from);
    ////////////////////////////////////
public:
    T GetData(int index);//
    int Count(){return m_count;}//
    bool IsEmpty(){return &m_root == m_root.m_next;}//
    void Clear(bool b = false);//
private:
    void __Init();// 初始化
    void __Add(MyNode_list<T>* prev, MyNode_list<T>* next, MyNode_list<T>* node);//
    void __Del(MyNode_list<T>* prev, MyNode_list<T>* next, bool b);//
    MyNode_list<T>* __GetDataWithIndex(int index);//
    MyNode_list<T>* __GetData(T data);//

    MyNode_list<T> m_root;// 链表头
    int m_count;// 链表数量
};

// 初始化函数
template<typename T>
void MyList<T>::__Init()
{
    m_root.m_prev = m_root.m_next = &m_root;
    m_count = 0;
    m_root.SetData(NULL);
}

// add 函数
template<typename T>
void MyList<T>::__Add(MyNode_list<T>* prev, MyNode_list<T>* next, MyNode_list<T>* node)
{
    if(!node) return;
    ++m_count;
    prev->m_next = node;
    node->m_prev = prev;
    node->m_next = next;
    next->m_prev = node;
}

template<typename T>
void MyList<T>::AddHead(MyNode_list<T>* node)
{
    __Add(&m_root,m_root.m_next,node);
}

template<typename T>
void MyList<T>::AddTail(MyNode_list<T> *node)
{
    __Add(m_root.m_prev,&m_root,node);
}

template<typename T>
void MyList<T>::AddTail(T data)
{
    AddTail(new MyNode_list<T>(data));
}

template<typename T>
void MyList<T>::AddHead(T data)
{
    AddHead(new MyNode_list<T>(data));
}

// del 函数
template<typename T>
void MyList<T>::__Del(MyNode_list<T> *prev, MyNode_list<T> *next,bool b)
{
    --m_count;
    if(b)
        delete prev->m_next;
    prev->m_next = next;
    next->m_prev = prev;
}

template<typename T>
void MyList<T>::Del(MyNode_list<T> *node,bool b)
{
    __Del(node->m_prev,node->m_next,b);
}

template<typename T>
void MyList<T>::DelHead(bool b)
{
    if(IsEmpty()) return;
    __Del(&m_root,m_root.m_next->m_next,b);
}

template<typename T>
void MyList<T>::DelTail(bool b)
{
    if(IsEmpty()) return;
    __Del(m_root.m_prev->m_prev,&m_root,b);
}

template<typename T>
void MyList<T>::DelWithIndex(int index,bool b)
{
    if(IsEmpty()) return;
    MyNode_list<T>* temp;

    temp = __GetDataWithIndex(index);
    if(temp)
        __Del(temp->m_prev,temp->m_next,b);
}

template<typename T>
void MyList<T>::Del(T data, bool b)
{
    if(IsEmpty()) return;
    MyNode_list<T>* temp;
    temp = __GetData(data);
    if(temp)
        __Del(temp->m_prev,temp->m_next,b);
}

// move append函数
template<typename T>
void MyList<T>::MoveHead(MyNode_list<T>* node)
{
    __Del(node->m_prev,node->m_next,false);
    AddHead(node);
}

template<typename T>
void MyList<T>::MoveTail(MyNode_list<T>* node)
{
    __Del(node->m_prev,node->m_next,false);
    AddTail(node);
}

template<typename T>
void MyList<T>::Append(MyList<T>* to, MyList<T>* from/*don't invoke*/)
{
    // ...
    //    if(from->IsEmpty()) return;

    //    MyList<T>* from_tail = from->__GetData(0);
    //    MyList<T>* from_head = from->__GetData(from->Count() - 1);

    //    to->__GetData(to->Count() - 1)->next = from_head;
    //    from_head->prev = to->prev;

    //    from_tail->next = to;
    //    to->prev = from_tail;

    //    my_list_init(from);
}

// get 函数
template<typename T>
MyNode_list<T>* MyList<T>::__GetDataWithIndex(int index)
{
    if(IsEmpty()) return NULL;
    if(index < 0 || index >= m_count) return NULL;

    MyNode_list<T>* temp = &m_root;
    int temp_index = -1;

    if(index >= m_count / 2)
    {// 使用倒序遍历
        temp_index = m_count;
        do{
            if(index != temp_index)
            {
                --temp_index;
                temp = temp->m_prev;
            }else
                return temp;
        }while(true);
    }else
    {// 使用正序遍历
        temp_index = -1;
        do{
            if(index != temp_index)
            {
                ++temp_index;
                temp = temp->m_next;
            }else
                return temp;
        }while(true);
    }
}

template<typename T>
MyNode_list<T>* MyList<T>::__GetData(T data)
{
    if(IsEmpty()) return NULL;
    MyNode_list<T>* temp = &m_root;
    do{
        temp = temp->m_next;
        if(temp->GetData() == data)
            return temp;
    }while(temp != &m_root);
    return NULL;
}

template<typename T>
T MyList<T>::GetData(int index)
{
    MyNode_list<T>* temp;
    if((temp = __GetDataWithIndex(index)) == NULL) return NULL;
    return temp->GetData();
}

// clear 函数
template<typename T>
void MyList<T>::Clear(bool b)
{
    while(!IsEmpty()){DelHead(b);}
    m_count = 0;
}

} // end namespace
#endif // MY_LIST_H


