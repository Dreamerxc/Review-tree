## 要求
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

## 示例
给定这个链表：1->2->3->4->5

当 k = 2 时，应当返回: 2->1->4->3->5

当 k = 3 时，应当返回: 3->2->1->4->5
## 代码
- 递归法

    	ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *pre,*cur;
        pre = nullptr;   //指向前一个元素
        cur = head;     //指向当前元素
        int n = 0;      //保存链表长度
        if(head==nullptr) return nullptr;
        while(cur!=nullptr)
        {
            cur = cur->next;
            n++;
        }
        cur = head;
        if(k>n) return head;   //剩余长度无法反转，直接返回
        for(int i = 0;i<k;i++)
        {
            ListNode *next = cur->next;  //指向下一个元素
            cur->next = pre;
            pre = cur;     //改变指向，移动指针
            cur = next;
        }
        head->next = reverseKGroup(cur,k);  //k个元素不断递归
        return pre;
    	}  
## 注意要点
- 前面两两反转的题是这个题的特殊形式，只能两个节点一交换，两个节点交换时只使用了两个指针，当大于三个节点交换时，需用3个指针才行。

### 2019年12月17日