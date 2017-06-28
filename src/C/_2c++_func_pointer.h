/*
要引用C++中类的成员函数，就需要定义成员函数指针。
例如cocos中：
    typedef void (CCObject::*SEL_MenuHandler)(CCObject*)；
既然定义成员函数指针，那么要用这个指针变量来调用回调函数，还需不需要对象实例呢。毫无疑问，还是需要的。
所以还必须有一个回调对象，CCObject *m_pListener。
    例如：
    (m_pListener->*m_pSelector)(CCObject *param);
*/

//////////////////////////////////////////////////////////////////////////////////////
//实例：
// person类：
#ifndef __TestCallBack__Person__
#define __TestCallBack__Person__

#include <iostream>
#include <string>

using namespace std;

// 基类
class Person {

public:
    void name(string name);
};

// 定义基类的成员函数指针
typedef void (Person::*SEL_CallFun)(string str);


// 派生类
class Student : public Person{
private:
    string m_name;
    int m_age;

public:
    Student(string name, int age);
    ~Student();

    // 回调
    void callBack(string str);

    // say方法，要调用回调函数。
    void say();
protected:
    // 回调的执行者
    Person *m_pListen;

    // 回调函数指针
    SEL_CallFun m_pfnSelectior;
};


void Person::name(string name)
{
    cout<<name<<endl;
}

Student::Student(string name, int age)
{
    this->m_name = name;
    this->m_age = age;
}

Student::~Student()
{

}

void Student::say()
{
    cout<<"Hi this is a Student"<<endl;

    // 回调函数指针赋值。需要强转成 SEL_CallFun
    m_pfnSelectior = (SEL_CallFun)(&Student::callBack);

    // 回调的执行对象，传this
    m_pListen = this;

    // 调用回调，参数是个string
    (m_pListen->*m_pfnSelectior)(m_name);
}

// 成员函数，要回调的函数
void Student::callBack(string str)
{
    cout<<"My name is "
       << str<<endl
       << "age is "
       <<m_age<<endl;
}

// main
//    #include <iostream>
//    #include "Person.h"

//    int main(int argc, const char * argv[])
//    {

//    Student *a = new Student("Join",20);
//    a->say();
//    return 0;
//    }

// 结果
//    Hi this is a Student
//    My name is Join
//    age is 20

/////////////////////////////////////////////////////////////
/*
自己实现：
#include <iostream>
#include <string>

using namespace std;

// 基类
class Person
{
public:
    Person(){}
    ~Person(){}
    void test(string name)
    {
        cout << name << endl;
    }

};
typedef void (Person::*SEL_CallFunc)(string name);
// 子类
class Student:public Person
{
public:
    Student(string name,int age)
    {
        this->m_age = age;
        this->m_name = name;
    }

    void CallBack(string str)
    {
        cout<<"My name is "
            << str<<endl
            << "age is "
            <<m_age<<endl;
    }

    void Say()
    {
        cout << "Hi this is a Student" << endl;
        m_func = (SEL_CallFunc)(&Student::CallBack);
        m_pListen = this;
        (m_pListen->*m_func)(m_name);
    }
protected:
    Person *m_pListen;
    SEL_CallFunc m_func;
private:
    string m_name;
    int m_age;
};

//////////////////////////////////////////////////////////////
实现2：
class Person
{
public:

};

typedef void (Person::*SEL_CallFunc)(string name);

class Test:public Person
{
public:
    Test(string name)
    {
        this->m_name = name;
        p_listener = this;
        m_func = (SEL_CallFunc)(&Test::CallBack);
    }

    void Say()
    {
        (p_listener->*m_func)(m_name);
    }
    void CallBack(string name)
    {
        cout << name << endl;
    }
private:
    string m_name;
    SEL_CallFunc m_func;
    Person* p_listener;
};

int main()
{
    Test *t = new Test("lkp");
    t->Say();
    return 0;
}
*/
















