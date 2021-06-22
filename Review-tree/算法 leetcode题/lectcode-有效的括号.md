## 要求
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
注意空字符串可被认为是有效字符串。
## 示例
示例 1:

输入: "()"
输出: true
示例 2:

输入: "()[]{}"
输出: true
示例 3:

输入: "(]"
输出: false
示例 4:

输入: "([)]"
输出: false
示例 5:

输入: "{[]}"
输出: true

## 代码
- 栈

-

	stack<char> st;
    bool isValid(string s) {
        int n = s.size();
        if(n==0) return true;
        if(n%2!=0) return false;
        st.push(s[0]);
        for(int i = 1;i<n;i++)
        {
            if(!st.empty())
            {
            char c = st.top();
            if(!st.empty()&&cmp(c,s[i])) st.pop();
            else st.push(s[i]);
            }
            else st.push(s[i]);
        }
        if(st.empty()) return true;
        else return false;
    }
    bool cmp(char c1,char c2){
        if((c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}') || (c1 == '(' && c2 == ')')){
            return true;
        }else{
            return false;
        } 
    }
- 总结
- 遇到开括号，入栈，当遇到闭括号并和栈顶的开括号匹配时，栈顶元素出栈，直到处理完最后一个元素。如果最后栈中没有元素则匹配成功。