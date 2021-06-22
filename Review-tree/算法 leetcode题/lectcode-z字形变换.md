## z字形变换
将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

L   C   I   R
E T O E S I I G
E   D   H   N
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

## 示例
示例 1:

输入: s = "LEETCODEISHIRING", numRows = 3

输出: "LCIRETOESIIGEDHN"

示例 2:

输入: s = "LEETCODEISHIRING", numRows = 4

输出: "LDREOEIIECIHNTSG"

解释:

L     D     R
E   O E   I I
E C   I H   N
T     S     G
## 代码
- 按行排序

-

    string convert(string s, int numRows) {
        int n = s.size();
        vector<string> res(min(numRows,n));
        int rows = 0;
        bool godown = false;
        if(n<=numRows||numRows ==1) return s;
        for(char c:s)
        {
            res[rows] += c;
            if(rows==0||rows==numRows-1) godown = !godown;
            rows += godown?1:-1;
        }
        rows = 0;
        string ret;
        for(string row:res) ret += row;
        return ret;
    }
- 按行访问

-

	 string convert(string s, int numRows) {
        if(numRows==1) return s;
        int n = s.size();
        int rows = 2*numRows-2;  
        string ret;              
        for(int i = 0;i<numRows;i++)
            for (int j = 0; j + i < n; j += rows) {
                ret += s[j + i];
                if (i != 0 && i != numRows - 1 && j + rows - i < n)
                    ret += s[j + rows - i];
            }
        return ret;
    }
## 总结
- 按行排序按照z字形形成的过程来构造，容易理解，但注意n<=numRows||numRows ==1这两个条件成立可以直接输出，如果numRows=1可以运行到下一级，会发生rows=-1的情况，会发生错误。
- 按行访问将z字形的每个字母的位置找出来，然后存入结果中。
