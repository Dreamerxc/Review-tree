## 要求
给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

## 示例
例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

## 代码
- 排序加双指针
- 
-

     vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());  //排序
        if(nums.size()<3||nums[0]>0||nums[nums.size()-1]<0)
        return res;
        for(int i =0;i<nums.size()-2;i++)
        {
            if(i>0&&nums[i-1]==nums[i]) continue;  //去重
            if(nums[i]>0) break;        //可以直接判断了
            int j=i+1;
            int k = nums.size()-1;
            while(j<k)
            {
                if(nums[i]+nums[j]+nums[k]==0)
                {
                    res.push_back({nums[i],nums[j],nums[k]});
                    while(j<k&&nums[j]==nums[j+1]) j++;  //去重
                    while(j<k&&nums[k]==nums[k-1]) k--;  //去重
                    j++;k--;
                }
            else if(nums[i]+nums[j]+nums[k]<0) j++;   
            else k--;
            }
        }
        return res;
    }

## 评价
- 此种算法时间复杂度位O(n^2),比暴力解法好，暴力解法时间复杂度太高。
- 当排序数组nums[i]>0时就可以终止了，因为加起来就不开能为0了。
- 当这个题改为三数相加为某个数时，把0换成这个数就行。