##### 一，函数指针

```
int (*p)(float);
```

定义了一个返回值为int,参数类型为float的函数指针

```
int test(float a)
{
return (int)a;
}
p = test;    
//p = &test;     //两种赋值方式都可以
float x = 2.001;
int a1 = p(x);     //不推荐此种方式进行调用
int a2 = (*p)(x);
```

函数指针p指向test,通过p可以直接调用test()函数

##### 二，abstract修饰符

abstract修饰类：会使这个类成为一个抽象类，这个类将不能生成对象实例

abstract修饰方法：会使这个方法变为抽象方法，也就是只有声明而没有实现，需要子类继承实现