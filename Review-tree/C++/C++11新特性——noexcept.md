#### C++11新特性——noexcept

##### 一，noexcept指定符

作用：指定函数是否抛出异常

##### 语法：

```
noexcept
noexcept(expression)
```

##### 举例：

```
void f() noexcept;   // 函数f()不抛出异常
void (*f)() noexcept(false);   // f是函数指针，指向的函数可能抛出异常
void g(void f() noexcept);    // g函数的形式参数，接收不抛出异常的函数指针
```



##### 二，noexcept运算符

作用：noexcept运算符在编译时检查，若表达式声明为不抛出异常则返回true

语法：

```
noexcept(expression)
```



解释：

1. noexcept 运算符不对 expression 求值
2. C++17起：若 expression的潜在异常集合为空则结果为true，否则为false
3. C++17前： 若 expression含有至少一个下列潜在求值的构造则结果为 false：



三，用于函数模板

​		noexcept 指定符和noexcept 运算符配合用于函数模板，以声明函数将对某些类型抛出异常，但不对其他类型抛出

```
template <class T>
void fun() noexcept(noexcept(T()))
{
    .....
}
```

