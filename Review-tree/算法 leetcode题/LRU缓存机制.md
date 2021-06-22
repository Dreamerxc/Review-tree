#### LRU缓存机制

- LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
- int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
- void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

##### 方法一：单链表

```
class Listnode {
public:
    Listnode *next;
    pair<int, int> x;
    Listnode(pair<int,int> y):x(y), next(nullptr) {};
    Listnode() :next(nullptr){};
};
class LRUCache {
public:
    LRUCache(int capacity) {
        count = capacity;
        cur = 0;
        head = new Listnode();
    }
    
    int get(int key) {
        Listnode* node = head;
        int res = -1;
        while(node->next!=nullptr) {
            if(node->next->x.first == key) {
                res = node->next->x.second;
                break;
            }
            node = node->next;
        }
        if (node->next == nullptr) return res;
        Listnode* temp = node->next;
        node->next = temp->next;
        // 头插法
        inserthead(temp);
        return res;
    }
    
    void put(int key, int value) {
        if (get(key) != -1) {
            Listnode* temp = head->next;
            temp->x.second = value;
            return;
        }
        Listnode* node = new Listnode({key,value});
        cur++;
        inserthead(node);
    }

    void inserthead(Listnode* temp) {
        temp->next = head->next;
        head->next = temp;
        if (cur > count) {
            Listnode* node = head;
            while(node->next != nullptr && node->next->next !=nullptr) {
                node = node->next;
            }
            node->next = nullptr;
            cur--;
        }
        return;
    }
private:
    int count;
    int cur;
    Listnode* head;
};
```

##### 方法二：哈希 + 双向链表

```

```

























