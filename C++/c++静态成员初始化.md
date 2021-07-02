##### 一，关于C++静态数据成员初始化

1，通常静态数据成员在类声明中声明,在包含类方法的文件中初始化.初始化时使用作用域操作符来指出静态成员所属的类。

```
#include<iostream>
using namespace std;
class test
{
public:
	static int sum = 0;
};
//int test::sum = 0;
int main()
{
	test x;
	cout << x.sum << endl;
	return 0;
}
```

运行如下：静态数据成员不能再类中初始化。

![image-20200702115842549](C:\Users\谯保林\AppData\Roaming\Typora\typora-user-images\image-20200702115842549.png)

正确程序如下：

```
#include<iostream>
using namespace std;
class test
{
public:
	static int sum;   //类中声明
};
int test::sum = 0;   //类外初始化
int main()
{
	test x;
	cout << x.sum << endl;
	return 0;
}
```

2，如果一定要在类内初始化静态成员变量，则需要满足以下条件：

（1）静态成员必须为字面值常量类型的constexpr。

（2）给静态成员提供的初始值，必须为常量表达式。

```
constexpr static int sum = 0;  //正确
```

```
static const int nameSize = 16;
static const char name[nameSize];   //正确
```

