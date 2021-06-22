## 要求
在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

示例 1:

输入: 4->2->1->3
输出: 1->2->3->4
示例 2:

输入: -1->5->3->4->0
输出: -1->0->3->4->5

## 代码
- 归并排序法

-

	ListNode* sortList(ListNode* head) {
        return mergesort(head);
    }
    ListNode *mergesort(ListNode *node)
    {
        if(!node||!node->next) return node;
        ListNode *fast = node;
        ListNode *slow = node;
        ListNode *ng = slow;
        while(fast&&fast->next)
        {
            fast = fast->next->next;
            ng = slow;
            slow = slow->next;
        }
        ng->next = nullptr;  //将两个链表断开
        ListNode *l1 = mergesort(node);
        ListNode *l2 = mergesort(slow);
        return merge(l1,l2);
    }
    ListNode *merge(ListNode *l1,ListNode *l2)
    {
        if(l1==nullptr) return l2;
        if(l2==nullptr) return l1;
        if(l1-> val<l2->val)                 
        {
             l1->next = merge(l1->next,l2);
             return l1;
        }
        else
        {
            l2->next = merge(l2->next,l1);
            return l2;
        }
    }
    };

## 总结
- 归并排序主要分为两个部分
	- 分隔阶段：将一个链表分为两个链表，然后不断递归，可以将一个链表全部分成单个的。
	- 合并阶段：两两按照大小顺序合并，然后形成新的一组链表，并按照上面方法不断递归，最后只有一条链表，便是结果。
