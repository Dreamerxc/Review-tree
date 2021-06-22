## 要求
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表
## 示例
给定 1->2->3->4, 你应该返回 2->1->4->3.
## 代码
- 迭代法


     	ListNode* swapPairs(ListNode* head) {
        ListNode* first=new ListNode(0); //加一个哨兵节点
        first->next=head;
        ListNode* p1=first; //p1为需交换的节点前面一个节点
        ListNode* p3=first;
        ListNode* p2; //将节点p2与p2->next交换。这样不需要额外记录交换节点之前的节点。
        while(p1->next!=NULL&&p1->next->next!=NULL)
        {
            p2=p1->next;
            p1->next=p2->next;
            p2->next=p2->next->next;
            p1->next->next=p2;
            p1=p2; //更新p1

        }
        return first->next;  
    	}
- 递归法



    	ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode* p1 = head;
        ListNode* p2 = p1->next;
        p1->next = swapPairs(p2->next);
        p2->next = p1;
        return p2;
    	}
## 注意要点
- 迭代法中p1->next->next=p2;p1->next的指向发生了变化。

### 2019年12月15日