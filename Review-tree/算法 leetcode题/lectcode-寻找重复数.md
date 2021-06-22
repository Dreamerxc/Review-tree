## 要求
给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。

## 示例
示例 1:

输入: [1,3,4,2,2]
输出: 2
示例 2:

输入: [3,1,3,4,2]
输出: 3

## 代码
- 先排序，再寻找

-

	int findDuplicate(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        for(int i = 0;i<nums.size()-1;i++)
        {
            if(nums[i]==nums[i+1]) return nums[i];
        }
        return -1;
    }

- 二分法

-

	int findDuplicate(vector<int>& nums) {
        int right = nums.size();
        int left = 0;
        while(left<right)
        {
            int count = 0;
            int mid = (left + right)/2;
            for(int i = 0;i<nums.size();i++)
        {
            if(nums[i]<=mid) count++;
        }
        if(count>mid) right = mid;
        else left = mid+1;
        }
        return left;
    }

## 总结
- 先排序，再查找，是因为有n+1个数据，数据的范围为1~n,排序后相等相邻元素为结果。
- 二分法的原理和分硬币重量(10个一样大的硬币，有一个重量和其他九个不同）有些类似，先两两比较，不断缩小范围。