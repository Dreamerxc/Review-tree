# 要求
反转一个单链表。
# 示例
输入: 1->2->3->4->5->NULL

输出: 5->4->3->2->1->NULL
# 代码
- 采用头插法建立链表的思想，可以将链表反转。

-

	ListNode* reverseList(ListNode* head) {
        ListNode *first = new ListNode(0);
        ListNode *p = head;
        if(head==nullptr) return nullptr;
        first->next = nullptr;
        while(p!=nullptr)
        {

            ListNode *s = p;
            p = p->next;
            s->next = first->next;
            first->next = s;
        }
        return first->next;
    }
- 递归法

-

	ListNode* reverseList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode* p = reverseList(head->next); 
        head->next->next = head; 
        head->next = NULL;
        return p;
    } 
##总结
- 第一个方法思想比较简单，就是建立链表的头插法。
- 递归比较难以理解，注意head->next = NULL;否则会产生链循环。

​