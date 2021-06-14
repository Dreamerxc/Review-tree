#### STL list 

##### 一，forward_list (单向链表)

##### 二，list (双向链表)

```
struct list_base {
	
}
struct list_data : public list_base {
	
}

迭代器
list_iterator : public iterator{

}
```





移动构造函数必须声明为noeccept才能使用吗？



```
void assign(size_type n, const value_type& value);

        template <class Iter, typename std::enable_if<
                MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
        void assign(Iter first, Iter last)
        { copy_assign(first, last); }
        
 如果没有template <class Iter, typename std::enable_if<
                MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
  会发生错误，assign(10,5); 会产生调用。              
```

