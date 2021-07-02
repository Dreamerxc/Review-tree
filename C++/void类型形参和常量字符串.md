##### 一，形参为void *类型

观察以下程序：

```
void test(void *data) {
    unsigned int value = *((unsigned int*)data);
    printf("%u", value);
}
using namespace std;
int main() {
    unsigned int value = 10;
    test(&value);
    return 0;
}

```

 unsigned int value = *((unsigned int*)data); 原因分析如下：

参数是void \*类型，所以没有指定读多少字节，所以要用指针类型(unsigned int\*)类型强制转化为知道要读几个字节的int指针，然后再用*从开始地址，读取unsigned int个字节出来！

##### 二，对于for(;;);

```
for(int i = 0;i<10;i++);
```

对于上述for循环，只是没有循环体而已，在内部仍然循环了10次，不是1次。

##### 三，常量字符串

```
#include<iostream>
using namespace std;

int main()
{
	char p[] = { "hello" };
	char* q = "hello";
	cout <<( p == "hello") << endl;   //输出0
	cout << (q == "hello" )<< endl;   //输出1
	return 0;
}
```

1，char p[] = { "hello" }; ：p指向了一段（新开辟的）长度为6字节的内存区域，存储的值是“hello”的拷贝（也就是说不是原来的常量字符串）。

2，char* q = "hello";  ：p存的是常量字符串“hello”的地址。

3，p == "hello"和q == "hello"比较的是两者之间的地址，不是内容，比较字符串中内容应该用strcmp()函数。