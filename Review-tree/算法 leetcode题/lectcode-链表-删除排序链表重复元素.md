## 要求
给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次
## 示例
输入: 1->1->2

输出: 1->2

输入: 1->1->2->3->3

输出: 1->2->3
## 代码

    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *cur,*next;
        cur = head;   
        while(cur!=nullptr&&cur->next!=nullptr)
        {
            next = cur->next;
            if(cur->val==next->val)
            {
                ListNode *s;
                s = next;
                next = next->next;
                cur->next = next;
                delete s;
            }
            else cur = cur->next;
        }
        return head;       
    }

## 注意要点
- 需要用一个指针先指向删除元素，连接后，记得释放内存。
### 2019年12月18日