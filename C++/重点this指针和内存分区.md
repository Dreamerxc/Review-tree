##### 一，数组指针与指针数组

1，int *a[10]:数组指针。

​			数组a中存放着10个int型指针。

2，int (*a)[10]:指针数组

​			a是一个指针，指向存放10个int型元素的数组。

##### 二，this指针

​		全局函数，静态函数都不能使用this指针。

原因：this指针指向当前调用对象，只是用于类的非静态成员函数。因为静态函数和全局函数没有当前对象，所以无this指针。

##### 三，linux内存分区

[转自]: https://blog.csdn.net/qq_40025335/article/details/94864826

##### 四，char是有符号还是无符号？

如何理解有符号char: char类型可以是负数，只是没有对应字符。

可能有符号，也可能没有符号。

- arm-linux-gcc 规定 char 为 unsigned char
- vc 编译器、x86上的 gcc 规定 char 为 signed char

所以，为了代码移植，一般不用char.