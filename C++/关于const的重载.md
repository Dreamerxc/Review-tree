#### 关于const的重载

```
int test(int);
```

以下三种情况和上述函数构成重载情况如下：

##### 1，const修饰在函数后面

```
int test(int) const;
```

结论：构成重载。

##### 常成员函数的const限定符用于修饰隐式第一形参this

##### this指针为一个指针常量，其原型为：

```
Type *const this;
```

##### 成员函数加上const修饰后,this的类型变为：

```
const Type *const this;
```

##### 此时this指针是一个指向常量的指针常量，实现了常成员函数内不能修改当前对象的数据成员的语言特性。此时就可以与其他重载函数区分开来，起到重载的作用。

```
注意：只有成员函数才可以加const限定符，因为成员函数才有this指针，普通函数不能在其后加const限定符。
```

[关于const重载调用问题](https://blog.csdn.net/yanlinwang/article/details/8113246)

##### 2，const修饰在函数前面

```
const int test(int);
```

结论：不能构成重载

##### const 加在函数前面，对于上述函数，此时只是声明该函数返回值类型为const int,不可以修改，然后函数重载与函数返回值是没有关系的。

##### 3，形参增加const属性

```
int test(const int);
```

结论：不能构成重载

