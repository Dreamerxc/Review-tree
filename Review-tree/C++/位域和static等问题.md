##### 一，观察以下程序

```
struct st_t 
{
　　int status;
　　short *pdata;
　　char errstr[32];
};
```

```
st_t st[16];
char`*p = (char*)( st[2].errstr + 32 );
printf("%d", ( p - (char*)(st) ) );
```

答案： 120

解析：sizeof(st_t) = 40

​			st[2].errstr +32相当于 第四个结构体的首地址

​			求首地址到第四个首地址字节，共40*3 = 120

##### 二，C++结构体之位域

1，位域的定义

```
struct 位域结构名 
{

 位域列表（类型说明符 位域名：位域长度）

};
```

例如

```
struct data
{
	int x:1
	int y:2
	int z:3
};
struct data a;
//sizeof(a) = 4
```

[位域详解]: https://www.cnblogs.com/pure/archive/2013/04/22/3034818.html

##### 三，运算优先级问题

1<<3+2  = 1<<5 = 32

加号优先级比<<大，不要想当然。

##### 四，数组名为常量指针

```
int main()
{
	a[] = "abcd";
	a++;   //错误
}
```

数组名是一个指向数组首地址的常量指针，不能对齐进行++操作。

##### 五，static问题

观察以下从程序：

```
#include<iostream.h>
void f() {
    static int i=15;
    i++;
    cout<<"i="<<i<<endl;
}
void main(){
    for(int k=0;k<2;k++)
        f();
}
```

解析：第一次调用f()函数，打印 “16"

​			第二次调用f()函数，打印”17“

知识点：static修饰的变量为静态变量，他只初始化一次，当下次在遇到初始化该静态变量时，直接跳过该语句，所以第二次调用f()函数，会忽略初始化语句。