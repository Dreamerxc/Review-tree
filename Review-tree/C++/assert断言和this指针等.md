##### 一，assert断言

```
#include "assert.h"
void assert(int expression)
```

assert的作用是现计算表达式 expression ，如果其值为假（即为0），那么它先向stderr打印一条出错信息,然后通过调用 abort 来终止程序运行。

在debug时，有assert断言保护，而在release时，没有assert断言

##### 二，reinter_cast<new_type>(expression)用法

- 从指针类型到一个足够大的整数类型
- 从整数类型或者枚举类型到指针类型
- 从一个指向函数的指针到另一个不同类型的指向函数的指针
- 从一个指向对象的指针到另一个不同类型的指向对象的指针
- 从一个指向类函数成员的指针到另一个指向不同类型的函数成员的指针
- 从一个指向类数据成员的指针到另一个指向不同类型的数据成员的指针

reinterpret_cast用在任意指针（或引用）类型之间的转换；以及指针与足够大的整数类型之间的转换；从整数类型（包括枚举类型）到指针类型，无视大小。一般不是很常用。

##### 三，this指针

```
myClass::~myClass(){
delete this;
this = NULL;
}
```

上述代码是错误，主要是因为this指针是指针常量，无法改变其指向。

```
Myclass *const this;    //指针常量
```













