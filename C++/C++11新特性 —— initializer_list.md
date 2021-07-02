#### C++11新特性 —— initializer_list

过往，我们这样给vector赋值：

```
std::vector v;
v.push_back(1);
v.push_back(2);
v.push_back(3);
v.push_back(4);
```

​		有了 initializer_list特性后，C++11允许构造函数和其他函数把初始化列表当作参数，我们可以进行下面的初始化：

```
std::vector v = { 1, 2, 3, 4 };
```

​	

```
class MyNumber
{
public:
    MyNumber(const std::initializer_list<int> &v) {
        for (auto itm : v) {
            mVec.push_back(itm);
        }
    }

    void print() {
    for (auto itm : mVec) {
        std::cout << itm << " ";
    }
    }
private:
    std::vector<int> mVec;
};

int main()
{
    MyNumber m = { 1, 2, 3, 4 };
    m.print();  // 1 2 3 4

    return 0;
}
```

​	initializer_list对象中的元素永远是常量值，我们无法改变initializer_list对象中元素的值。并且，拷贝或赋值一个initializer_list对象不会拷贝列表中的元素，其实只是引用而已，原始列表和副本共享元素

