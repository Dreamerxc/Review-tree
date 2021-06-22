##### 一，volatile关键字

​		volatile提醒编译器它**后面所定义的变量随时都有可能改变** ，因此**编译后的程序每次需要存储或读取这个变量的时候** ，都会直接从变量地址中读取数据。**如果没有volatile关键字，则编译器可能优化读取和存储，** 可能暂时使用寄存器中的值，如果这个变量由别的程序更新了的话，将出现不一致的现象。

一般说来，volatile用在如下的几个地方： 
(1) 中断服务程序中修改的供其它程序检测的变量需要加volatile； 
(2) 多任务环境下各任务间共享的标志应该加volatile； 
(3) 存储器映射的硬件寄存器通常也要加volatile说明，因为每次对它的读写都可能由不同意义；

##### 二，指向NULL的指针不能赋值

```
#include <stdio.h>
main()
{int
a[]={1,2,3,4,5,6,7,8,9,10,11,12},*p=a+5,*q=NULL;
 *q=*(p+5);
 
printf("%d %d\n",*p,*q);
}
```

解析：以上程序运行崩溃，如果q不是null，则上述程序正确。

知识点：

(1) p=NULL;指针的变化是 p指向了一个地址为0的内存，这就提醒别人不要对这个指针进行解引用的操作。NULL其实就是0x0。p=NULL后，p指向0x0这个地址。此处的地址，我们没有访问权限。

(2) 空指针指没有定位内存的指针，值为null（0），你使用new或者malloc申请了指针p，使用后delete或者free，你必须将指针值设置为null，否则，p将成为一个非法指针，后续代码如果使用到该指针有可能会造成系统崩溃（内存不可以读不可写），或者，破坏自身有效内存数据（释放后，又在申请作为别的用途，恰巧系统分配了同一块内存）

##### 三，重复释放指针问题

```
class A{
   int i;
};
class B{
   A *p;
public:
   B(){p=new A;}
   ~B(){delete p;}
};
void sayHello(B b){
}
int main(){
   B b;
   sayHello(b);
}
```

以上程序会发生程序崩溃

解析：这里的错误原因是编译器在生成default copy construction的时候使用的bitwise copy语义，也就是只是简单的浅拷贝。 ***上面被注释掉的程序就是编译器自动添加的部分。*** 从而导致在sayHello中向参数x传递值时，调用了bitwise copy的拷贝构造函数，使得x对象和b对象中的值完全一致，包括p指针的值，在x离开作用域（也就是sayHello函数结束），x发生析构，调用delete 销毁了指针p，同时在main函数结束的时候，析构b时又会调用一次delete删除指针p。

bitwise copy: 位逐次拷贝

改正：添加拷贝构造函数

```
B(constB& other)
{
	p = new A;   //构造新指针。
	*p = *(other.p);
}
```

##### 四，字符标准问题

C语言: char a = 'a'; sizeof(char) = 1 sizeof(a) = 1 sizeof('a') = 4 

C++语言: char a = 'a'; sizeof(char) = 1 sizeof(a) = 1 sizeof('a') = 1 

字符型变量是1字节这个没错，奇怪就奇怪在C语言认为'a'是4字节，而C++语言认为'a'是1字节。 

   

原因如下:  

 C99标准的规定，'a'叫做**整型字符常量**(integer   character constant)，被看成是int型，所以在32位机器上占4字节。

 ISO C++标准规定，'a'叫做**字符字面量**(character literal)，被看成是char型，所以占1字节



##### 五，引用不能是void类型

void类型没有分配内存，而引用必须是另一个固定内存变量的别名，所以不能指向void