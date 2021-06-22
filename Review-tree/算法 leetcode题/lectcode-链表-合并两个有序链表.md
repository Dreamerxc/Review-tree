## 要求
将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
## 示例
输入：1->2->4, 1->3->4

输出：1->1->2->3->4->4
## 代码
- 采用迭代法。通过两个指针分别指向两个链表，通过比较值的大小，移动指针，把小的值接到head后面。时间空间复杂度都为O(m+n）
 
    	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *p,*q,*r;
        ListNode *head = new ListNode(0);
        r = head;
        p = l1;
        q = l2;     
        while(q!=NULL&&p!=NULL)
        {
            if(p->val<=q->val)
            {
                r->next = p;
                p = p->next;   
            }
            else
            {
                r->next = q;
                q = q->next;          
            }
			r = r->next;
        } 
        	if(p==NULL) r->next = q;  //说明l1已经全部比较完成，返回l2剩余元素即可
        	else r->next = p;       //说明l2已经全部比较完成，返回l1剩余元素即可
         	return head->next;
    }

- 采用递归的方法。时间空间复杂度都为O(m+n）

     	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr) return l2;   //说明l1已经全部比较完成，返回l2剩余元素即可
        if(l2 == nullptr) return l1;   //说明l2已经全部比较完成，返回l1剩余元素即可
        if(l1->val<l2->val)
        {
            l1->next = mergeTwoLists(l1->next,l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1,l2->next);
            return l2;
        }
    	}

## 注意要点
- 迭代法更易理解，递归掌握还不牢。
- 时间空间复杂度虽然都为O(m+n），但递归更占内存。


### 2019年12月13日记录