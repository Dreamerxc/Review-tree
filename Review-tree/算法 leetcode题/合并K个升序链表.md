#### 23，合并K个升序链表

给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

```
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-k-sorted-lists
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
```



##### 方法一：两两合并

```
ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if(n==0) return nullptr;
        ListNode* node = lists[0];
        for(int  i = 1;i<n;i++){
            node = mergelist(node,lists[i]);
        } 
        return node;
    }

    ListNode* mergelist(ListNode* first,ListNode* second){
        ListNode* res = new ListNode(-1);
        ListNode* node = res;
        while(first!=nullptr&&second!=nullptr){
            if(first->val<second->val){
                node->next = first;
                first = first->next;
            }else{
                node->next = second;
                second = second->next;
            }
            node = node->next;
        }
        node->next = first==nullptr?second:first;
        return res->next;
    }
```

##### 方法二：优先队列

```
struct cmp{
        int val;
        ListNode* ptr;
        bool operator < (const cmp &rhs) const{
            return val>rhs.val;
        }
    };
    priority_queue<cmp> qu;
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int m = lists.size();
        if(m==0) return nullptr;
        for(int i = 0;i<m;i++){
            if(lists[i]!=nullptr) qu.push({lists[i]->val,lists[i]});
        }
        ListNode* node = new ListNode(-1);
        ListNode* res = node;
        while(!qu.empty()){
            auto [x,y] = qu.top();
            qu.pop();
            node->next = y;
            y = y->next;
            if(y!=nullptr) qu.push({y->val,y});
            node = node->next; 
        }
        return res->next;
    }
```















