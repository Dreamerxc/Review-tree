## 要求
给定一个仅包含大小写字母和空格 ' ' 的字符串 s，返回其最后一个单词的长度。

如果字符串从左向右滚动显示，那么最后一个单词就是最后出现的单词。

如果不存在最后一个单词，请返回 0 。

## 示例
输入: "Hello World"

输出: 5
## 代码
    int lengthOfLastWord(string s) {
        int n = s.length(),res = 0;
        if(n==0) return 0;
        for(int i = n-1;i>=0;i--)
        {
            if(s[i]!=' ') res++;
            else
            {
                if(res) break;
            } 
        }
        return res;
    }

## 总结
- 从后往前遍历，遇到空字符停止。
- 注意如果末尾是空字符，要先去除空字符再计算。