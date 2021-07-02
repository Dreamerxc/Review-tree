##### 一，C++常量折叠问题

```
const int a = 10;
int *p = (int*)&a;
*p = 20;
cout<<a<<endl;
cout<<*p<<endl;
cout<<&a<<endl;
cout<<p<<endl;
```

![image-20200802144428769](C:\Users\谯保林\AppData\Roaming\Typora\typora-user-images\image-20200802144428769.png)

可以看出，*p指向的就是a的地址，但是为什么输出结果不一样了，原因就是C++的常量折叠问题。

C++常量折叠问题：指const变量（即常量）值**放在编译器的符号表中**，计算时编译器直接从表中取值，省去了访问内存的时间，从而达到了优化。

##### 二，C++访问属性问题

```
class X
{
int a;
void fun1();
public:
void fun2();
};
X objX;
```

C++类默认为私有属性

objx.fun1()调用错误，fun1为私有，无法通过对象调用

objx.fun2()调用正确，fun2为共有，可以通过对象调用

##### 三，sizeof()是一个整型表达式

1，sizeof()是一个操作符，在编译阶段就被整型代替，所以也是一个整型表达式。

2，strlen是函数调用，在运行阶段就被整型代替。