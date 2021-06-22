## 要求
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头

来源：力扣（LeetCode）

链接：https://leetcode-cn.com/problems/add-two-numbers

## 示例
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)

输出：7 -> 0 -> 8

原因：342 + 465 = 807
## 代码
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int len1=1;//记录l1的长度
        int len2=1;//记录l2的长度
        ListNode* p=l1;
        ListNode* q=l2;
        while(p->next!=NULL)//获取l1的长度
        {
            len1++;
            p=p->next;
        }
        while(q->next!=NULL)//获取l2的长度
        {
            len2++;
            q=q->next;
        }
        if(len1>len2)//l1较长，在l2末尾补零
        {
            for(int i=1;i<=len1-len2;i++)
            {
                q->next=new ListNode(0);
                q=q->next;
            }
        }
        else//l2较长，在l1末尾补零
        {
            for(int i=1;i<=len2-len1;i++)
            {
                p->next=new ListNode(0);
                p=p->next;
            }
        }
        p=l1;
        q=l2;
        bool count=false;//记录进位  也可以用 int count = 0; 
        ListNode* l3=new ListNode(-1);//存放结果的链表
        ListNode* w=l3;//l3的移动指针
        int i=0;//记录相加结果
        while(p!=NULL&&q!=NULL)
        {
            i=count+p->val+q->val;    //bool和int可以相加，true代表1，flase代表0
            w->next=new ListNode(i%10);
            count=i>=10?true:false;  //判断是否需要进位
            w=w->next;
            p=p->next;
            q=q->next;
        }
        if(count)//若最后还有进位
        {
            w->next=new ListNode(1);
            w=w->next;
        }
        return l3->next; 
    }
	};
## 注意要点
- 首先需要判断是否需要加0，因为给的数据不一定位数相同
- 必须要考虑进位问题，因为是两数相加，所以最大进位为1，可以用bool型来判断进位并且加减，如果是此种形式的多数相加，需要用int型来判断进位，因为三数相加会出现进2以上的数字。     



### 2019年12月11日记录