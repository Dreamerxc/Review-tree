##### 一，const 与 “*” 用法

口诀：左定值，右定向

const 在*左边不能改变字符常量的值

```
char *const p = "hello";
p[1] = 'b';   //错误，不能改变其值
```

const 在*的右边不能改变指针的指向

```
const char* p = "hello";
p++;   //错误，不能改变指向
```

##### 二，istringstream用法

istringstream类用于执行C++风格的串流的输入操作，它包含于头文件<<sstream>>中

istringstream对象可以绑定一行字符串，然后以空格为分隔符把该行分隔开来。

```
string text = "i love you";  //"  i   love  you"同
istringstream is(text);
string str;
while (is >>str)
{
cout << str << endl;   
}
输出：
i
love
you
```

不一定只以一个空格作为分隔，“  i   love            you"效果也相同。