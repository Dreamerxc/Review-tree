## 要求
给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。

函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。

说明:

返回的下标值（index1 和 index2）不是从零开始的。
你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素

## 示例
示例:

输入: numbers = [2, 7, 11, 15], target = 9
输出: [1,2]
解释: 2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2

## 代码
- 暴力法

-

	vector<int> twoSum(vector<int>& numbers, int target) {
        for(int i = 0;i<numbers.size()-1;i++)
        {
            for(int j = i+1;j<numbers.size();j++)
            {
                if(numbers[i]+numbers[j]==target)
                return {i+1,j+1};
            }
        }
        return {-1,-1};
    }
-双指针

-

	 vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0,right = numbers.size()-1;
        while(left<right)
        {
            if(numbers[left]+numbers[right]==target) 
            return {left+1,right+1};
            if(numbers[left]+numbers[right]>target) right--;
            else left++;  
        }
        return {-1,-1};
    }

## 总结
- 暴力法时间复杂度O(n^2).
- 双指针时间复杂度O(n).