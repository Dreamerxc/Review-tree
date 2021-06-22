## 要求
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

## 示例
LRUCache cache = new LRUCache( 2 /* 缓存容量 */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4

## 代码
- 哈希链表法

-

	private:
    int cap;
    list<pair<int,int>> cache; //双链表：装着（key,value)元组。
    unordered_map<int,list<pair<int,int>>::iterator> map;
    //哈希表：key映射到（key,value)在cache中的位置。
public:
    LRUCache(int capacity) {
        this->cap = capacity;
    }
    
    int get(int key) {
        auto it = map.find(key);
        if(it == map.end()) return -1;
        //key存在，把（k,v)换到队头
        pair<int,int> kv = *map[key];
        cache.erase(map[key]); //删除
        cache.push_front(kv); //在头部创建

        map[key] = cache.begin();
        return kv.second; //返回值。
    }
    
    void put(int key, int value) {
        //先判断key是否存在
        auto it = map.find(key);
        if(it == map.end()) // 如果不存在，判断是否已满
        {
            if(cache.size() == cap)//如果cache已满
            {
                //删除cache和map中的元素
                auto lastpair = cache.back();//返回引用
                int lastkey = lastpair.first;
                map.erase(lastkey);
                cache.pop_back();
            }
            //没满可以直接添加
            cache.push_front(make_pair(key,value));
            map[key] = cache.begin();
        }
        else
        {
            //key存在，更改value到队头
            cache.erase(map[key]); //先删除
            cache.push_front(make_pair(key,value));
            map[key] = cache.begin();
        }
    }
    };

## 总结
- 查找采用哈希表，删除，添加采用双向链表，结合了两种数据结构的特点，组成新的数据结构哈希链表。