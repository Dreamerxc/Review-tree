## 要求
给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
## 示例
给定的有序链表： [-10, -3, 0, 5, 9],

一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：

        0
       / \
   	 -3   9
   	 /   /
 	-10  5

## 代码
- 快慢指针+递归

-

	 TreeNode* sortedListToBST(ListNode* head) {
        if(head==nullptr) return nullptr;
        ListNode *mid = findmindnode(head);
        TreeNode * node = new TreeNode(mid->val);
        if(mid==head) return node;
        node->left = sortedListToBST(head); //作左区间递归
        node->right = sortedListToBST(mid->next); //右区间递归
        return node;     
    }

    ListNode * findmindnode(ListNode *head)
    {
        ListNode *fast = head; //快指针
        ListNode *low = head;  //慢指针
        ListNode *low_pre = nullptr;  //保存慢指针前一个位置
        while(fast!=nullptr&&fast->next!=nullptr)
        {
            low_pre = low;
            low = low->next;
            fast = fast->next->next;
        }
        if(low_pre != nullptr) low_pre->next = nullptr;
        return low;  //慢指针此时指向中间位置
    }

- 当快指针指到底时，慢指针将好指向链表中间位置。
- low_pre->next = nullptr将链表划分为左右两个区间。
- 时间复杂度：O(N\log N)O(NlogN)
- 空间复杂度：O(\log N)O(logN)。因为使用递归的方法，所以需要考虑递归栈的空间复杂度

- 