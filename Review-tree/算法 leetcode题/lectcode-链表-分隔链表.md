## 要求
给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。

你应当保留两个分区中每个节点的初始相对位置。
## 示例
输入: head = 1->4->3->2->5->2, x = 3

输出: 1->2->2->4->3->5
## 代码
- 建立两个链表，一个链表储存值小于target,另一个储存值大于target的，最后将两链表连接起来。

-

    ListNode *r= new ListNode(0);
        ListNode *q = new ListNode(0);
        ListNode *t = q,*p = r;
        while(head!=nullptr)
        {
            if(head->val<x) 
            {
                p->next = head;
                p = p->next;
            }
            else
            {
                t->next = head;
                t = t->next;
            }
            head = head->next;
        }
        p->next= q->next;
        t->next = nullptr; //注意细节
        return r->next;
    }
## 总结
- 思路很清晰，就是建立两个链表再合并，时间复杂度O(n),空间复杂度O(1).