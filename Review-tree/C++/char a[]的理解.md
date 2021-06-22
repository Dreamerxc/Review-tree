##### char *a[]的理解

有如下程序：

```
int main()
{
	char* a[] = {"123","abc","456"}, ** p;
	p = a;
	printf("%s/n", *p);
	printf("%c",**p);
	return 0;
}
```

p = a : 此时a装换为指向数组首地址的指针，即char**类型，等价于&a[0]。

此时*p为char*类型指向“123”，等价于a[0]，实质是指向字符数组“123”的第一个字符，若再次解引用则为第一个字符本身。运行结果如下：

![image-20200625215554384](C:\Users\谯保林\AppData\Roaming\Typora\typora-user-images\image-20200625215554384.png)

程序进行变形：

```
#include <stdio.h>
void f(char** p) {
	*p += 1;   
}
int main()
{
	char* a[] = {"123","abc","456"}, ** p;
	p = a;
	f(p);
	printf("%s\r\n", *p);
	printf("%c", **p);
	return 0;
}
```

*p += 1 :此时指向"123"的第二个字符。运行结果如下：

![image-20200625215850504](C:\Users\谯保林\AppData\Roaming\Typora\typora-user-images\image-20200625215850504.png)

