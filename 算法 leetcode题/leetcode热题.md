## leetcode热题

#### 一，两数之和

​     给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 的那 两个 整数，并返回它们的数组下标。你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。你可以按任意顺序返回答案。

```
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
```

##### 方法一：map

C++版：

```
 vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> mp;
        for(int i = 0;i<nums.size();i++){
            if(mp.find(target-nums[i])!=mp.end()){
                return {i,mp[target-nums[i]]};
            }
            mp[nums[i]] = i;
        }
        return {-1,-1};
    }
```

Golang版：

```
func twoSum(nums []int, target int) []int {
    mp := make(map[int]int)
    for index,val := range nums{
        if val,ok := mp[target - val];ok{
            return []int{index,val}
        }
        mp[val] = index
    }
    return nil
};
```



#### 二，两数相加

​      给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。请你将两个数相加，并以相同形式返回一个表示和的链表。你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

```
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
```

##### 方法一：遍历 （记得进位）

C++版：

```
 ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int temp = 0;
        ListNode* res = new ListNode(-1);
        ListNode* head = res;
        while(l1!=nullptr||l2!=nullptr||temp!=0){
            int sum = temp;
            if(l1!=nullptr){
                sum += l1->val;
                l1 = l1->next;
            } 
            if(l2!=nullptr){
                sum += l2->val;
                l2 = l2->next;
            } 
            temp = sum/10;
            sum = sum%10;
            ListNode* node = new ListNode(sum);
            head->next = node;
            head = head->next;
        }
        return res->next;
    }
```

Golang版：

```
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    head := new(ListNode)
    tail := head
    temp := 0
    for l1!=nil || l2!=nil || temp!=0{
        sum := temp
        if l1!=nil{
            sum += l1.Val
            l1 = l1.Next
        }
        if l2!=nil{
            sum += l2.Val
            l2 = l2.Next
        }
        tail.Next = new(ListNode)
        tail = tail.Next
        tail.Val = sum%10
        temp = sum/10
    }
    return head.Next
}
```



#### 三，无重复字符的最长字串

​		给定一个字符串，请你找出其中不含有重复字符的 **最长子串** 的长度。

```
输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```

##### 方法一：滑动窗口  

C++版：

```
 int lengthOfLongestSubstring(string s) {
        int m = s.size(),res = 0;
        if(m==0) return 0;
        set<char> st;
        int left = 0,right = 0;
        while(right<m){
            if(st.find(s[right])==st.end()){
                st.insert(s[right]);
                right++;
                res = max(res,right - left);
            }else{
                st.erase(s[left]);
                left++;
            }
        }
        return res;
    }
```

golang版：

```
func lengthOfLongestSubstring(s string) int {
    m := len(s)
    left,right := 0,0
    res := 0
    mp := make(map[byte]bool)
    for right<m{
        if _,ok := mp[s[right]];!ok{
            mp[s[right]] = true
            right++
            res = Max(res,right-left)
        }else{
            delete(mp,s[left])
            left++
        }
    }
    return res
}

func Max(x, y int) int {
    if x < y {
        return y
    }
    return x
}
```



#### 四，最长回文字串

​	给你一个字符串 `s`，找到 `s` 中最长的回文子串。

```
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
```

##### 方法一：中心扩展法

C++版：

```
string longestPalindrome(string s) {
        int m = s.size();
        if(m==0) return "";
        string res;
        res.push_back(s[0]);
        for(int i = 0;i<m;i++){
            int l = max(isok(i,i,s),isok(i,i+1,s));            
            if(l>res.size()){
                res = s.substr(i-(l-1)/2,l);
            }
        }
        return res;
    }

    int isok(int left,int right,string& s){
        int m = s.size();
        while(left>=0&&right<m){
            if(s[left]!=s[right]) break;
            left--;
            right++;
        }
        return right - left - 1;
    }
```

golang版：

```
func longestPalindrome(s string) string {
    m := len(s)
    var res string
    for i:=0;i<m;i++{
        l := max(isok(i,i,s),isok(i,i+1,s));
        if l>len(res){
            res = s[i-(l-1)/2:i+(l+1)/2+(l+1)%2]
        }
    }
    return res
}

func max(a,b int) int{
    if a>b {
        return a
    } else{
        return b
    }
     
}

func isok(left,right int,s string) int{
    m := len(s)
    for left>=0 && right<m{
        if s[left]!=s[right]{
            break
        }
        left--
        right++
    }
    return right - left - 1
}
```

##### 方法二：动态规划

C++版：

```
 string longestPalindrome(string s) {
        int n = s.size();
        string res = "";
        vector<vector<bool>> dp(n,vector<bool>(n,false));
        for(int i = 0;i<n;i++){
            dp[i][i] = true;
        }
        for(int i = n-1;i>=0;i--){
            for(int j = i;j<n;j++){
                if(s[i]!=s[j]){
                    dp[i][j] = false;
                }else{
                    if(j-i<3) dp[i][j] = true;
                    else dp[i][j] = dp[i+1][j-1];
                    if(dp[i][j]&&j-i+1>res.size()){
                        res = s.substr(i,j-i+1);
                    }
                }
            }
        }
        return res;
    }
```



#### 五，Z字形变换

​		将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

```
P   A   H   N
A P L S I I G
Y   I   R
```

C++版：

```
string convert(string s, int numRows) {
        if(numRows<=1) return s;
        int m = s.size(), i = 0,row = 0;
        vector<string> temp(numRows,"");
        bool up = false;
        while(i<m){
            temp[row] += s[i];
            if(row==0||row==numRows-1) up = !up;
            if(up){
                row++;
            }else{
                row--;
            }
            i++;
        }
        string res;
        for(auto x:temp){
            res += x;
        }
        return res;
    }
```

golang版：

```
func convert(s string, numRows int) string {
    if numRows<=1{
        return s
    }
    temp := make([]string,numRows)
    m := len(s)
    i := 0
    up := false
    row := 0
    for i<m{
        temp[row] += string(s[i])
        if row==0 || row==numRows-1{
            up = !up
        }
        if up{
            row++
        }else{
            row--
        }
        i++
    }
    var res string
    for _,val := range temp{
        res += val
    }
    return res
}
```

#### 六，盛最多水的容器

​		给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。



```
输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
```

![img](https://aliyun-lc-upload.oss-cn-hangzhou.aliyuncs.com/aliyun-lc-upload/uploads/2018/07/25/question_11.jpg)

C++版：

```
 int maxArea(vector<int>& height) {
        int res = 0,left = 0,right = height.size()-1;
        while(left < right){
            res = max(res,(right - left)*min(height[left],height[right]));
            if(height[left]<height[right]){
                left++;
            }
            else{
                right--;
            }
        }
        return res;
    }
```



#### 七，三数之和

给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

```
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
```

```
vector<vector<int>> threeSum(vector<int>& nums) {
        int m = nums.size();
        vector<vector<int>> res;
        if(m<3) return res;
        sort(nums.begin(),nums.end());
        for(int i = 0;i<m;i++){
            if(nums[i]>0) return res;
            if(i>0&&nums[i]==nums[i-1]) continue;
            int left = i+1,right = m-1;
            while(left<right){
                int sum = nums[i] + nums[left] + nums[right];
                if(sum==0){
                    res.push_back({nums[i],nums[left],nums[right]});
                    while(left<right&&nums[left]==nums[left+1]) left++;
                    while(left<right&&nums[right]==nums[right-1]) right--;
                    left++;
                    right--;
                }
                else if(sum>0) right--;
                else left++;
            }
        }
        return res;
    }
```



#### 八，电话号码的字母组合

​		给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/original_images/17_telephone_keypad.png)

```
示例：
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
```



##### 回溯算法：

```
vector<string> res;
    vector<string> letterCombinations(string digits) {
        map<char,string> mp;
        mp['2'] = "abc";
        mp['3'] = "def";
        mp['4'] = "ghi";
        mp['5'] = "jkl";
        mp['6'] = "mno";
        mp['7'] = "pqrs";
        mp['8'] = "tuv";
        mp['9'] = "wxyz";
        string rt;
        if(digits.size()==0) return res;
        dfs(digits,mp,0,rt);
        return res; 
    }

    void dfs(string digits,map<char,string>& mp,int index,string rt){
        if(index==digits.size()){
            res.push_back(rt);
            return;
        } 
        string temp = mp[digits[index]];
        for(int j = 0;j<temp.size();j++){
            rt.push_back(temp[j]);
            dfs(digits,mp,index+1,rt);
            rt.pop_back();
        }
    }
```



#### 九，有效的括号

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。

```
示例 1：
输入：s = "()"
输出：true
```

##### 栈：

```
bool isValid(string s) {
        stack<char> st;
        for(int i = 0;i<s.size();i++){
            if(s[i]=='('||s[i]=='{'||s[i]=='['){
                st.push(s[i]);
            }else{
                if(st.empty()) return false;
                if(s[i]==')'){
                    if(st.top()=='(') st.pop();
                    else return false;
                }
                if(s[i]=='}'){
                    if(st.top()=='{') st.pop();
                    else return false;
                }
                if(s[i]==']'){
                    if(st.top()=='[') st.pop();
                    else return false;
                }
            }
        }
        return st.empty();
    }
```



#### 十，合并两个有序链表

将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

```
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
```

##### 迭代一：

```
 ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1==nullptr&&l2==nullptr) return nullptr;
        ListNode* node = new ListNode(-1);
        ListNode* ret = node;
        while(l1!=nullptr||l2!=nullptr){
            if(l2==nullptr||l1!=nullptr&&l1->val < l2->val){
                node->next = l1;
                l1 = l1->next;
            }else{
                node->next = l2;
                l2 = l2->next;
            }
            node = node->next;
        }
        return ret->next;
    }
```

##### 迭代二：

```
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1==nullptr&&l2==nullptr) return nullptr;
        ListNode* node = new ListNode(-1);
        ListNode* ret = node;
        while(l1!=nullptr&&l2!=nullptr){
            if(l1->val < l2->val){
                node->next = l1;
                l1 = l1->next;
            }else{
                node->next = l2;
                l2 = l2->next;
            }
            node = node->next;
        }
        node->next = l1==nullptr?l2:l1;
        return ret->next;
    }
```

#### 十一，括号生成

​		数字 `n` 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 **有效的** 括号组合。

```
示例：
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
```

##### 深度优先搜索：

```
 vector<string> res;
    vector<string> generateParenthesis(int n) {
        string temp = "";
        dfs(temp,n,n);
        return res;
    }

    void dfs(string temp,int left,int right){
        if(left==0&&right==0){
            res.push_back(temp);
            return;
        }
        if(left>0){
            dfs(temp+'(',left-1,right);
        }
        if(left<right){
            dfs(temp+')',left,right-1);
        }
    }
```

##### 广度优先搜索：

```
 vector<string> generateParenthesis(int n) {
        vector<string> res;
        queue<pair<string,pair<int,int>>> qu;
        qu.push({"",{n,n}});
        while(!qu.empty()){
            auto x = qu.front();
            qu.pop();
            string temp = x.first;
            int left = x.second.first;
            int right = x.second.second;
            if(left==0&&right==0){
                res.push_back(temp);
            }
            if(left>0){
                qu.push({temp+'(',{left-1,right}});
            }
            if(right>left){
                qu.push({temp+')',{left,right-1}});
            }
        }
        return res;
    }
```



#### 十二，下一个排列

实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须 原地 修改，只允许使用额外常数空间。

```
示例：
输入：nums = [1,2,3]
输出：[1,3,2]
```

 

##### C++版：

```
  void nextPermutation(vector<int>& nums) {
        int m = nums.size();
        if(m<=1) return;
        bool flag = false;
        for(int i = m-2;i>=0;i--){
            if(nums[i]<nums[i+1]){
                flag = true;
                int temp = i+1;
                for(int j = i+1;j<m;j++){
                    if(nums[j]>nums[i]&&nums[j]<nums[temp]){
                        temp = j;
                    }
                }
                swap(nums[i],nums[temp]);
            }
            if(flag){
                sort(nums.begin()+i+1,nums.end());
                break;
            } 
        }
        if(!flag) sort(nums.begin(),nums.end());
    }
```

