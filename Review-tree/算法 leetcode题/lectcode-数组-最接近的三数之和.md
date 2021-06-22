## 要求
给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案
## 示例
例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.

与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
## 代码
- 排序加双指针法

-

    int threeSumClosest(vector<int>& nums, int target) {  
        sort(nums.begin(),nums.end());  //排序，时间复杂度nlogn
        int sum_1 = nums[0]+nums[1]+nums[2];
        for(int i =0;i<nums.size()-2;i++)
        {
            int j=i+1;
            int k = nums.size()-1;
            while(j<k)
            {
                int sum_2 = nums[i]+nums[j]+nums[k];
                if (sum_2==target) return sum_2;
                sum_1 = abs(sum_1-target)<abs(sum_2-target)?sum_1:sum_2;
            if(sum_2<target) j++;   
            else k--;
            }
        }
        return sum_1;
    }
## 评价
- 此题相当于三数之和的变形，搞清楚三数之和后这题就很简单了。
