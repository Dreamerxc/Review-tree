## 要求
给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。
## 示例
输入: 1->2->3->3->4->4->5

输出: 1->2->5

输入: 1->1->1->2->3

输出: 2->3
## 代码
- 自己写的



    	ListNode* deleteDuplicates(ListNode* head) {
        ListNode *first = new ListNode(0);
        first->next = head;
        ListNode *p;
        p = first;
        while(p->next!=nullptr)
        {
            ListNode *q = p->next;
            if(q->next!=nullptr&&q->val==q->next->val)  //注意前后顺序不能写反
            {
                int  n = q->val;
                while(q!=nullptr&&q->val==n) //注意前后顺序不能写反
                {
                    ListNode *s;
                    ListNode *next = q->next;
                    s = q;
                    q = next;
                    p->next = next;
                    delete s;
                }
            }
            
            else p = p->next;
        }
        return first->next;
    }
- 大神精简代码
-


    ListNode* deleteDuplicates(ListNode* head) {
        ListNode H(-1), *p, *q;
        for(H.next=head, p=&H; p && p->next;){
            for(q=p->next; q && q->next && q->val==q->next->val; q=q->next);
            if(p->next==q) p=p->next;
            else p->next=q?q->next:NULL;
        }
        return H.next;
    }



## 注意要点
- 在有&&时，连接的条件是从前往后执行的，要注意条件的顺序。如(q->next!=nullptr&&q->val==q->next->val)如果顺序放反的话，q->next就有可能为空，就没有q->next->val,就会报错。
### 2019年12月18日