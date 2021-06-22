#### 一，C++memset用法

memset函数原型：void *memset(void *buffer,int c,int count)

buffer : 为指针或是数组

c : 赋给buffer的值

count : 赋值buffer中的位数

##### 1，memset是以字节为单位，初始化内存块

```
char data[10];
memset(data,65,sizeof(data));
//A A A A A A A A A A 
```

为每个字节赋值65（即'A'）

```
int data[10];
memset(data,1,sizeof(data));
//16843009  （ 00000001  00000001  00000001  00000001）
```

memset是为每一个字节赋值的，所有为int类型赋值时，它的四个字节全部赋值为00000001，读取时读取四个字节，就变成以上结果。

##### 2，当结构体包含指针时

```
struct test
{
	int x;
	int *p;
};
test demo;
demo.p = new int[10];
memset(&demo,0,sizeof(demo));
```

以上程序并不会初始化int数组，而且只会把分配过的p指针本身设置为0，造成内存泄漏。

##### 3，当结构体或类的本身或基类中存在虚函数时，需要谨慎使用memset函数

```
class Base
{
	public:
		virtual void reset(){}
};
class test:public Base
{
	public:
		int data[10];
};
test demo;
memset(&demo,0,sizeof(demo));
Base* p = &demo;
......
Base * q = dynamic_cast<Base*>(p);
```

程序运行到dynamic_cast时发生异常。原因其实也很容易发现，我们的目的是为了初始化数据结构MyParameters里的data和buf，正常来说需要初始化的内存空间是sizeof(int) * 3 * 2 = 24字节，但是使用memset直接初始化MyParameters类型的数据结构时，sizeof(my_pars)却是28字节，因为为了实现多态机制，C++对有虚函数的对象会包含一个指向虚函数表(V-Table)的指针，当使用memset时，会把该虚函数表的指针也初始化为0，而dynamic_cast也使用RTTI技术，运行时会使用到V-Table，可此时由于与V-Table的链接已经被破坏，导致程序发生异常。

#### 二，C++/C中struct区别

1，C++语言将struct当成类来处理的，所以C++的struct可以包含C++类的所有东西，例如构造函数，析构函数，友元等，C++的struct和C++类唯一不同就是struct成员默认的是public， C++默认private。

2，C语言struct不是类，不可以有函数，也不能使用类的特征例如public等关键字 ，也不可以有static关键字。









