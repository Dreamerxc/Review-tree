### C++重载，隐藏，覆盖（重写）

#### 一，C++重载

C++允许在同一作用域中的某个函数和运算符指定多个定义，分为运算符重载和函数重载。重载声明是指一个与之前在该作用域具有相同名称的声明

##### 1，函数重载

​		在同一个作用域，可以声明多个功能相似的同名函数，这些同名函数根据形式参数（参数个数，参数类型，有无const限定等）的不同，在预编译阶段其实已经转换为独一无二的函数名，所以函数调用时才不会发生错误。

```
class add
{
	int add_data(int x,int y)
	{
		return x+y;
	}
	int add_data(int x,double y)
	{
		return x + (int)y;
	}
	int add_data(int x,int y) const
	{
		return x+y;
	}
}
```

##### 2,运算符重载

​		重载运算符和重载函数思想是一样的，只是有运算符重载的特殊形式（函数名由operator和要重载的符号名构成），你可以对大部分C++内置类型进行重载。

比如经典的复数类：

```
class complex
{
	complex(double r = 0.0,double i = 0.0):real(r),imag(i){}
	complex operator+ (const complex& other)
	{
		return complex(real+other.real,imag+other.imag);
	}
	complex operator- (const complex& other)
	{
		return complex(real-other.real,imag-other.imag);
	}
	
private:
	double real;
	double imag;
}
```

#### 二，C++隐藏

​		隐藏是指派生类的函数屏蔽了其同名的基类函数

##### 1，如果派生类的函数与基类的函数同名，但是参数不同，此时，无论有无virtual,基类的函数将被隐藏。

```
class testA
{
public:
	virtual void print(double x)
	{
		cout << "调用基类函数"<<endl;
	}
};

class testB :public testA
{
public:
	void print(int x)
	{
		cout << "调用派生类函数"<<endl;
	}
};

int main()
{
	testB b;
	testB* p = &b;
	p->print(1);
	p->print(1.1);
}
```

运行结果：

调用派生类函数1

调用派生类函数1

解析：因为派生类同名函数print(int x)与基类函数参数类型不同，此时不管是否是虚函数，基类的print函数都会被隐藏，所以，尽管p->print(1.1)的实参是double类型，但是此时基类的print函数已经被隐藏，所以只能通过先进行强制类型转换，然后调用派生类的函数。

##### 2，如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual关键字。

```
class testA
{
public:
	void print(int x)
	{
		cout << "调用基类函数"<<x<<endl;
	}
};

class testB :public testA
{
public:
	void print(int x)   //如果派生类没有这个函数，就会调用基类的函数，所以称为隐藏
	{
		cout << "调用派生类函数"<<x<<endl; 
	}
};

int main()
{
	testB b;
	testB* p = &b;
	p->print(1);
	p->print(1.1);
}
```

运行结果：

调用派生类函数1

调用派生类函数1

解析：基类的print()函数已经被隐藏，只能调用派生类中的函数。

#### 三，C++覆盖

​		覆盖是指派生类函数覆盖基类函数，主要有以下特征：

（1）不同的范围（分别位于派生类与基类）；
（2）函数名字相同；
（3）参数相同；
（4）基类函数必须有virtual关键字。

```
class testA
{
public:
	virtual void print(int x)
	{
		cout << "调用基类函数"<<x<<endl;
	}
};

class testB :public testA
{
public:
	void print(int x)
	{
		cout << "调用派生类函数"<<x<<endl;
	}
};

int main()
{
	testB b;
	testA* p = &b;    //用基类指针指向派生类，用来使用多态
	p->print(1);
	p->print(1.1);
}
```

运行结果：

调用派生类函数1

调用派生类函数1

##### 覆盖的使用常常和多态进行联系，也常常称为重写。