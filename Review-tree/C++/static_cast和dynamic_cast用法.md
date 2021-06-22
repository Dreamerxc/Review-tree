##### 一，static_cast用法

1，用于类层次结构中基类和派生类之间指针或引用的转换

（1）进行上行转换，把派生类的指针或引用转换成基类表示是可以的

（2）进行下行转换，把基类指针或引用转换为派生类表示时，由于没有动态类型检查，所以是不安全的

```
calss Base
{};
class Derived:public Base
{};
Base *pb = new Base();
Derived* pd = static_cast<Derived*>(pb);   //不能将static_cast用于基类向派生类的转换

Derived* pd = new Derived();
Base* pb = static_cast<Base*>(pd);  //可以进行转换
```

2，用于基本类型的转换

```na
char s = 's';
int a = static_cast<int>(s);
```

3，把空指针转换成目标类型的指针

4，把任何类型转换成void类型

```
int b = 1;
int* a = &b;
void* d = static_cast<void*>(a);

```

5,static_cast不能转换掉expression的const,volatile或者_unaligned属性

```
const int a = 10;
double b = static_cast<double>(a);  //编译错误，无法去除const属性
```

##### 二，dynamic_cast用法

1，dynamic_cast< type* >(e)
      type必须是一个类类型且必须是一个有效的指针
2，dynamic_cast< type& >(e)
      type必须是一个类类型且必须是一个左值
3，dynamic_cast< type&& >(e)
      type必须是一个类类型且必须是一个右值

e的类型必须符合以下三个条件中的任何一个：
1、e的类型是目标类型type的公有派生类
2、e的类型是目标type的共有基类
3、e的类型就是目标type的类型。

在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的；在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全。















