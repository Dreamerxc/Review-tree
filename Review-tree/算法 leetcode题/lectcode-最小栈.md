## 要求
设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) -- 将元素 x 推入栈中。
pop() -- 删除栈顶的元素。
top() -- 获取栈顶元素。
getMin() -- 检索栈中的最小元素。

## 代码
- 链表自行构造栈

-

	class MinStack {
	public:
    typedef struct StackNode
    {
        int val,curmin;
        StackNode *next;
        StackNode(int x) : val(x),next(nullptr),curmin(x){}
    }stack;

    MinStack() {  //构造函数
        cur = nullptr;
        p = nullptr;
        size = 0;
    }
    
    void push(int x) {
        p = new stack(x);
        if(size++)
        {
            p->curmin = x<cur->curmin?x:cur->curmin;
            p->next = cur;
        }
        cur = p;
        return;
    }
    
    void pop() {
        p = cur;
        cur = cur->next;
        delete p;
        size--;
        return;
    }
    
    int top() {
        return cur->val;
    }
    
    int getMin() {
        return cur->curmin;
    }
	private:
    stack *cur,*p;
    int size;
	};

- 两个栈，一个栈保存数据，一个栈保存对应数据栈的最小值。

-

	class MinStack {
	public:
    stack<int> stackdata;
    stack<int> stackmin;
    /** initialize your data structure here. */
    MinStack() {  //构造函数
        
    }
    
    void push(int x) {
        stackdata.push(x);
        if(stackmin.empty()) stackmin.push(x);
        else if(x<stackmin.top()) stackmin.push(x);
        else stackmin.push(stackmin.top());
        return;
    }
    
    void pop() {
        stackdata.pop();
        stackmin.pop();
    }
    
    int top() {
        return stackdata.top();
    }
    
    int getMin() {
        return stackmin.top();
    }
	};

## 总结
- 选用链表构造栈，可以不用指明栈的大小，这是相较于数组构造栈的优点。因为要在常数时间找到最小值，可以在每个节点中保存该节点前的最小值，这样就可以以O(1)的时间找到最小值。
- 为了满足常数时间完成各项操作，选用两个栈，一个数据栈，一个保存最小值的栈。