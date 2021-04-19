#### STL学习笔记

- 配置器
  - allocator
    - allocate
    - deallocate
  - constructor
    - construct
    - destroy
- 迭代器
  - iterator
- 仿函数
  - functional
  - hash_functional
- 容器
  - vector
  - list
  - deque
  - map
  - set
  - unordered_map
  - unordered_set
  - basic_string
- 算法
  - 基本算法
  - 数值算法
  - set 算法
  - heap 算法
  - 其他算法
- 配接器
  - container adapters
    - stack
    - queue
    - priority_queue
  - iterator adapters
    - reverse_iterator



##### ptrdiff_t : ptrdiff_t是C/C++标准库中定义的一个与机器相关的[数据](https://baike.baidu.com/item/数据/5947370)类型。ptrdiff_t类型[变量](https://baike.baidu.com/item/变量/3956968)通常用来保存两个[指针](https://baike.baidu.com/item/指针/2878304)减法操作的结果,通常为 long int 类型。



![img](https://images2015.cnblogs.com/blog/779368/201509/779368-20150921091623319-1554443006.png)



如何理解：

```
template <class T>
struct has_iterator_cat
{
private:
  struct two { char a; char b; };
  template <class U> static two test(...);
  template <class U> static char test(typename U::iterator_category* = 0);
public:
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
```

https://cloud.tencent.com/developer/article/1582451

sizeof 在编译器就可以确定，所以上述代码意思是只有 含有 iterator_category的类，value 才会是true.





##### std::is_convertible：

```
std::is_convertible<From, To>::value` 为 `true`，否则为 `false
```

1. `From` 和 `To` 均为 `void` 类型（可含有 `cv` 限定）

2. `std::declval<From>()` 可隐式转换为 `To` 类型





当我们对动态数组调用std::copy的时候，实际上就是调用的memmove的C标准库，用memmove可以加快复制过程。

memcpy与memmove其实差不多，目的都是将N个字节的源内存地址的内容拷贝到目标内存地址中，但是，当源内存和目标内存存在重叠时，memcpy会出现错误，而memmove能正确地实施拷贝，但这也增加了一点点开销。memmove与memcpy不同的处理措施：

> 1. `当源内存的首地址等于目标内存的首地址时，不进行任何拷贝`
> 2. `当源内存的首地址大于目标内存的首地址时，实行正向拷贝`
> 3. `当源内存的首地址小于目标内存的首地址时，实行反向拷贝`





##### std::addressof : 获得对象的实际地址