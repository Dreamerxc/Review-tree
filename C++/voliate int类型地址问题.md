##### 一，voliate int类型地址问题

```
int a = 10;
cout<<&a<<endl;   // 012FFE30(一个正常的地址）
volitate int b = 10;
cout<<&b<<endl;   //  输出为 1
```

&b的地址从结果来看是1，但是这不是变量b的地址，这里的b只是指bool变量true。

原因：cout<<没有重载& volitate，所以不能输出地址。

解决办法：

（1）可以使用printf()函数进行打印

（2）将volatile int\*类型强制转换为int\*型

```
volatile int m = 4;
int *n = const_cast<int*>(&m);;
*n = 3;
printf("%08x %d\n", &m ,m);
cout << &m << ' ' << m << endl;
cout << n << ' ' << *n << endl;
return 0;
```

![image-20200803085901382](C:\Users\谯保林\AppData\Roaming\Typora\typora-user-images\image-20200803085901382.png)

##### 二，宏定义与typedef

```
#define INT_PTR int*
typedef int* int_ptr;
INT_PTR a,b;
int_ptr c,d;
```

解析：

（1）#define为宏定义，在预编译时进行宏替换，进行替换后变为：

```
int* a,b;   //a是一个指针变量，b是一个整型变量
```

（2）typedef作用是给已存在的数据类型引入一个别名，是类型定义，所以c,d都是指针变量。