## 要求
峰值元素是指其值大于左右相邻值的元素。

给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。

数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞。

## 示例
示例 1:

输入: nums = [1,2,3,1]
输出: 2
解释: 3 是峰值元素，你的函数应该返回其索引 2。
示例 2:

输入: nums = [1,2,1,3,5,6,4]
输出: 1 或 5 
解释: 你的函数可以返回索引 1，其峰值元素为 2；
     或者返回索引 5， 其峰值元素为 6
## 代码
- 线性扫描

-

	int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0;i<n-1;i++)
        {
            if(nums[i]>nums[i+1]) return i;
        }
        return n-1;
    }
- 递归二分法

-

	int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        return findpeak(nums,0,n-1);
    }
    int findpeak(vector<int>& nums,int left,int right)
    {
        int mid = left + (right - left)/2;
        if(left == right) return left;
        if(nums[mid]>nums[mid+1]) return findpeak(nums,left,mid);
        else return findpeak(nums,mid+1,right);
    }

- 迭代二分查找

-

	int findPeakElement(vector<int>& nums) {
        int left = 0,right = nums.size()-1;
        while(left<right)
        {
            int mid = left + (right - left)/2;
            if(nums[mid]>nums[mid+1]) right = mid;
            else left = mid + 1;
        }
        return left;
    }

## 总结
- 线性扫描法因为是从开始比较的，所以返回第一个满足条件的位置。
- 二分法当有多个满足条件的值时，取决于mid,返回满足条件的值不一定时第一个。