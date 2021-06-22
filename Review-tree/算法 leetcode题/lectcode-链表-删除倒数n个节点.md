## 要求
给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点
## 示例
给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
## 代码
- 采用两个指针的办法，一次遍历解决


    	ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *St =  new ListNode(0);
        St->next = head;   //指向头节点
        ListNode *q,*p;    
        q = St;
        p = St;
        for(int i = 0;i<n+1;i++)
        p = p->next;
        while(p)      //p指针指向nullpttr时，q指针指向删除节点的前一个节点
        {
            p = p->next;
            q = q->next;
        }
         ListNode *S =  new ListNode(0);
         S = q->next;
         q->next = S->next;  //链表的删除操作
         delete S;
         return St->next;
    	}

- 直接通过计算找出删除节点的前一个位置


    	ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *p;
        p = head;
        int length = 0;  //n用来保存链表的长度
        while(p!=nullptr)
        {
            length ++;
            p = p->next;
        }
        p = head;
        if(n>length) return NULL;   //如果删除位置大于链表长度，返回null;
        if(n==length) return p->next;  //如果删除位置等于链表长度，说明删除第一个元素，直接返回下一个元素即可。
        for(int i = 0;i<length-n-1;i++)  //通过for循环找到删除元素前一个位置
        {
            p = p->next;
        }
        ListNode *s;
        s = p->next;
        p->next = s->next;
        delete s;    //销毁删除元素
        return head; 
   		 }
    	
## 注意要点
- 第一种方法时间和空间复杂度都较低，推荐。
- 第二种方法通过计算来直接找位置，需要考虑好三种情况，否则容易出错


### 2019年12月11日