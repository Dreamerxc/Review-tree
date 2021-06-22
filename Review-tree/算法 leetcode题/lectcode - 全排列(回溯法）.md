## 要求
给定一个没有重复数字的序列，返回其所有可能的全排列。

## 示例


输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

## 代码
- 回溯法

-

	vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        backtrack(nums,res,0);
        return res;
    }

        void swap(int &a,int &b)
        {
            int temp = a;
            a = b;
            b = temp;
        }
    void backtrack(vector<int> &nums,vector<vector<int>> &res,int i)
    {
        if(nums.size()==i) res.push_back(nums);
        for(int j = i;j<nums.size();j++)
        {
            swap(nums[i],nums[j]);
            backtrack(nums,res,i+1);
            swap(nums[i],nums[j]);
        }
    }

## 总结
- 遍历索引 first 到索引 n - 1 的所有整数。
- 在排列中放置第 i 个整数，
- 即 swap(nums[first], nums[i]).
- 继续生成从第 i 个整数开始的所有排列: backtrack(first + 1).
- 现在回溯，即通过 swap(nums[first], nums[i]) 还原.
