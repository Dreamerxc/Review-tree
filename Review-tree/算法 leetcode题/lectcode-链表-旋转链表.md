## 要求
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数
## 示例
输入: 1->2->3->4->5->NULL, k = 2

输出: 4->5->1->2->3->NULL

解释:

向右旋转 1 步: 5->1->2->3->4->NULL

向右旋转 2 步: 4->5->1->2->3->NULL
## 代码

        ListNode* rotateRight(ListNode* head, int k) {
        ListNode *p,*q;
        if(head==nullptr) return 0;
        int n = 0;
        p = head;
        q = head;
        while(q->next!=nullptr)
        {
            q = q->next;
            n++;
        }
        q->next = p;
        for(int i = 0;i<n-k%(n+1);i++)
        p = p->next;
        ListNode *s = p->next;
        p->next = nullptr;
        return s;              
        }
##注意要点
- 先让链表成环，然后移动位置，找到头节点后又断开。
- 在移动的时候要考虑到移动的步数比链表长的情况，可取模解决。

### 2019年12月17日