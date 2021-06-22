## 要求
给定一个链表，判断链表中是否有环。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。

## 示例、
输入：head = [3,2,0,-4], pos = 1

输出：true

解释：链表中有一个环，其尾部连接到第二个节点。

(图搬不过来）。。。
## 代码
- 双指针法

-

    bool hasCycle(ListNode *head) {
        ListNode *s,*k;
        if(head == nullptr|| head->next == nullptr) return false;
        s = head;
        k = head->next;
        while(k!=nullptr&&k->next!=nullptr)
        {
            if(k==s) return true;
            s = s->next;  //慢指针
            k = k->next->next;  //快指针
        } 
        return false;
    }
## 总结
- 个人认为想当于把一个是否有圈的问题用追赶来解答而已，当有圈时，速度快的一定追的到速度慢。
-  两个指针的速度最好按上面的，如果步长过大，第一判断条件会多，第二可能速度大反而可能会过几圈才相等，得不偿失。（瞎想的有点多..)
-  主要掌握快慢指针的一种应用场景。