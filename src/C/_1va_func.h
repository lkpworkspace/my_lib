


//示例代码1：可变参数函数的使用
#include <stdio.h>
#include <stdarg.h>
void simple_va_fun(int start, ...)
{
    va_list arg_ptr;
    int nArgValue =start;
    int nArgCout="0";  //可变参数的数目
    va_start(arg_ptr,start);  //以固定参数的地址为起点确定变参的内存起始地址。
    do
    {
        ++nArgCout;
        printf("the %d th arg: %d",nArgCout,nArgValue); //输出各参数的值
        nArgValue = va_arg(arg_ptr,int);  //得到下一个可变参数的值
    } while(nArgValue != -1);               
    return;
}

/*
main函数:
int main(int argc, char* argv[])
{
    simple_va_fun(100,-1);
    simple_va_fun(100,200,-1);
    return 0;
}
*/


////////////////////////////////////////////////////////////////////////////
//例如：
//	int printf( const char* format, ...);
//注：
//	这类函数必须有一个固定函数参数

//void va_start( va_list arg_ptr, prev_param );
//type va_arg( va_list arg_ptr, type );
//void va_end( va_list arg_ptr );

//这些宏定义在stdarg.h中,所以用到可变参数的程序应该包含这个头文件。
//⑵函数里首先定义一个va_list型的变量,这里是arg_ptr,这个变量是存储参数地址的指针.因为得到参数的地址之后，再结合参数的类型，才能得到参数的值。
//⑶然后用va_start宏初始化⑵中定义的变量arg_ptr,这个宏的第二个参数是可变参数列表的前一个参数,即最后一个固定参数。
//⑷然后依次用va_arg宏使arg_ptr返回可变参数的地址,得到这个地址之后，结合参数的类型，就可以得到参数的值。
//⑸设定结束条件，这里的条件就是判断参数值是否为-1。注意被调的函数在调用时是不知道可变参数的正确数目的，程序员必须自己在代码中指明结束条件。至于为什么它不会知道参数的数目，在看完这几个宏的内部实现机制后，自然就会明白。





