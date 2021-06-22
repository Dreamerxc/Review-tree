## 要求
合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。

## 示例

输入:

[

  1->4->5,

  1->3->4,

  2->6
]

输出: 1->1->2->3->4->4->5->6
## 代码
- 在合并两个有序链表的基础上，逐个从容器中拿出两个链表进行合并。

-

     ListNode* mergeKLists(vector<ListNode*>& lists) {
        int size = lists.size();
        if(size == 0) return nullptr;
        if(size == 1) return lists[0];
        ListNode *s = lists[0];
        if(size>1){
            for(int i = 1;i<size;i++)
            s = mergeLists(s,lists[i]);
        }
        return s;  
    }
    ListNode *  mergeLists(ListNode *l1,ListNode *l2)
    {
        if(l1==nullptr) return l2;
        if(l2==nullptr) return l1;
        if(l1->val<l2->val)
        {
            l1->next = mergeLists(l1->next,l2);
            return l1;
        }
        else
        {
            l2->next = mergeLists(l1,l2->next);
            return l2;
        }
    }

- 采用分治递归的办法合并。

-

    ListNode* mergeKLists(vector<ListNode*>& lists) {
    if(lists.size()==0) return nullptr;
    if(lists.size()==1) return lists[0];
    if(lists.size()==2) return mergeLists(lists[0],lists[1]);
    int mid = (lists.size()+1)/2;
    vector<ListNode*>l1;
    vector<ListNode*>l2;
    for(int i= 0;i<mid;i++)
    l1.push_back(lists[i]);
    for(int i = mid;i<lists.size();i++)
    l2.push_back(lists[i]);
    ListNode*m = mergeKLists(l1);
    ListNode*n = mergeKLists(l2);
    return mergeLists(m,n);
    }

    ListNode *  mergeLists(ListNode *l1,ListNode *l2)
    {
        if(l1==nullptr) return l2;
        if(l2==nullptr) return l1;
        if(l1->val<l2->val)
        {
            l1->next = mergeLists(l1->next,l2);
            return l1;
        }
        else
        {
            l2->next = mergeLists(l1,l2->next);
            return l2;
        }
    }

## 注意要点
- 第一种方法和第二种方法相比，只是在取链表的方式上有所差异，第一种是在容器中从前往后取并合并，第二种则是不断从中间划分，两两合并，但其实两种方法合并的次数是相同的，都需要合并n-1次，但从执行速度看分治的方法更快，目前还不知道为什么快？希望以后能狗解答。
- 总结一下分治算法：
 - 核心思想：把一个复杂的问题分成两个或更多的相同或相似的子问题，再把子问题分成更小的子问题……直到最后子问题可以简单的直接求解，原问题的解即子问题的解的合并
 - 一般需要一个分解函数和一个合并函数，在排序上速度较快。

### 2019年12月14日