## 要求
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。
## 示例
示例 1:

输入: ["flower","flow","flight"]
输出: "fl"
示例 2:

输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀
## 代码
- 横向扫描法

-

	string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==0) return "";
        string prefix = strs[0]; //假设第一个为公共前缀
        for(int i = 1;i<strs.size();i++)
        {
            while(strs[i].find(prefix)!=0)//如果不含有prefix，则将prefix长度减1，再次判断prefix-1是否为其子串（==0表示含有该字串），直到prefix为空，
			{
				if (prefix == "") return "";//如果prefix为空串，则说明公共前缀为空
				prefix = prefix.substr(0, prefix.length() - 1);
			}
        }
        return prefix;
    }
- 纵向扫描法

-

	string longestCommonPrefix(vector<string>& strs) {
        string s="";
        if(strs.size()==0) return "";
        for(int i = 0;i<strs[0].size();i++)
        {
            char c = strs[0][i];
            for(int j = 1;j<strs.size();j++)
            {
                if(strs[j][i]!=c) return s;
            }
            s+=c;
        }    
        return s;
    }
- 二分法

-

	string longestCommonPrefix(vector<string>& strs) {
        int lenth = INT_MAX;
        if(strs.size()==0) return "";
        for(string s:strs)
        if(lenth>=s.size()) lenth = s.size();
        int left = 0,right = lenth;
        while(left<=right)
        {
            int mid = (left+right)/2;
            if(isokprefix(strs,mid)) left = mid+1;
            else right = mid-1;
        }
        return strs[0].substr(0, (left + right) / 2);
    }
    bool isokprefix(vector<string>& strs,int mid)
    {
        string s = strs[0].substr(0,mid);
        vector<string>::size_type flag;
        for(string t:strs)
        {
            flag = t.find(s);
            if(flag!=0) return false;
        }
		return true;
    	}
	};
## 总结
- 横向扫描法：
	- 先求出两个的最长前缀，然后利用求出的前缀和剩下的string不断比较，最长前缀不断更新，随着最长前缀的更新，比较次数也会变少，直到最长前缀为0或者所有string比较完后，即可求出结果。
	- 时间复杂度：O(S)O(S)，S 是所有字符串中字符数量的总和。
	最坏的情况下，n个字符串都是相同的。算法会将 S1S1 与其他字符串 都做一次比较。这样就会进行 S次字符比较，其中 S 是输入数据中所有字符数量。
	- 空间复杂度：O(1)，我们只需要使用常数级别的额外空间。
- 纵向扫描法：
	- 用s保存结果，每一次从第一个字符开始比较，一个一个字母比较，比较成功则把该字母存入s中，当遇到比较不匹配时，结束比较，返回s。

- 二分法：
	- 每次最短字符集的一半来进行比较，最后找到相同前缀的最后一个位置，即（left+right)/2。