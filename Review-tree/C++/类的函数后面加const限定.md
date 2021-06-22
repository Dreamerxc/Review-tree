#### 一，类的函数后面加const限定

```
class test
{
	int a;
	public:
		void vconst(int) const;
}
```

对于test类，有以下vconst函数实现：

```
void test::vconst(int k) const
{
	k = a;
}
```

可以运行

```
void test::vconst(int k) const
{
	a = k;
}
```

错误，类的成员函数后面加const限定，表明在该函数中无法改变成员变量的值。

##### 原因：

**编译器会自动给每一个函数加一个this指针。在一个类的函数后面加上const后，就表明这个函数是不能改变类的成员变量的（加了mutable修饰的除外）。实际上，也就是对这个this指针加上了const修饰**

















