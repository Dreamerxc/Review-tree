## 要求
编写一个程序，找到两个单链表相交的起始节点。
## 示例
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3

输出：Reference of the node with value = 8

输入解释：相交节点的值为 8 （注意，如果两个列表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
## 代码
- 暴力法（时间复杂度O(n*m))

-

	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *m = new ListNode(0);
        ListNode *n = new ListNode(0);
        m->next = headA;
        n->next = headB;
        ListNode *p = m,*q = n;
        while(p!=nullptr)
        {
            while(q!=nullptr)
            {
                if(p->next==q->next) return q->next;
                q = q->next;
            }
            q = n;
            p = p->next;
        }  
        return nullptr;  
    }
- 双指针法（时间复杂度O(m+n))

-

	 ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA,*q = headB;
        while(p||q)
        {
            if(p==q) return p;
            p = p ?p->next:headB;
            q = q ?q->next:headA;
        }
        return nullptr;
    }

- 哈希表法（时间复杂度O(m+n))

-

	 ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> hash;
        while(headA){
            hash.insert(headA);//将headA添加至哈希表中
            headA = headA->next;
        }
        while(headB){
            if(hash.count(headB)) return headB;//如果hash中包含headB（此时为第一个），返回headB
            headB = headB->next;
        }
        return nullptr;
    }

## 总结
- 双指针法：headA第一遍遍历长度A，然后把遍历headA的指针指向headB,第二遍遍历长度B，走过的长度为A+B；headB走过的长度则为B+A；所以如果有相交，两个指针一起遍历时，会在小于A+B的路径中相等。如果没有相交，则会一起指向nullptr;
-  哈希表法：先将headA所有放入哈希表，再遍历headB，找到一个已有的节点返回