## 要求
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和
## 示例
输入: [-2,1,-3,4,-1,2,1,-5,4],

输出: 6

解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
## 代码
- 暴力解法

-
	
	int maxSubArray(vector<int>& nums) {
        int sum = 0,max = INT_MIN,n = nums.size();
        for(int i=0;i<n;i++)
        {
            sum = 0;
            for(int j = i;j<n;j++)
            {
                if(sum<0) break;
                sum = sum + nums[j];
                max = max>sum?max:sum;
            }
        }
        return max;
    }
- 动态规划

-

	 int maxSubArray(vector<int>& nums) {
        int res = INT_MIN,n = nums.size();
        int dp = nums[0]; 
        res = nums[0];
        for(int i = 1;i<n;i++)
        {
            dp = max(dp+nums[i],nums[i]);
            res = max(res,dp);
        }
        return res;
    }
- 贪心解法

-
 	
	int maxSubArray(vector<int>& nums) {
       int n = nums.size(),sum = nums[0],res = nums[0];
       for(int i = 1;i<n;i++)
       {
           if(sum < 0) sum = 0;
           sum = sum + nums[i];
           res = max(res,sum);
       }
       return res;
    }
- 分治解法

-

	int maxSubArray(vector<int> &nums)
    {
        //类似寻找最大最小值的题目，初始值一定要定义成理论上的最小最大值
        int result = INT_MIN;
        int numsSize = int(nums.size());
        result = maxSubArrayHelper(nums, 0, numsSize - 1);
        return result;
    }

    int maxSubArrayHelper(vector<int> &nums, int left, int right)
    {
        if (left == right)
        {
            return nums[left];
        }
        int mid = (left + right) / 2;
        int leftSum = maxSubArrayHelper(nums, left, mid);
        //注意这里应是mid + 1，否则left + 1 = right时，会无线循环
        int rightSum = maxSubArrayHelper(nums, mid + 1, right);
        int midSum = findMaxCrossingSubarray(nums, left, mid, right);
        int result = max(leftSum, rightSum);
        result = max(result, midSum);
        return result;
    }

    int findMaxCrossingSubarray(vector<int> &nums, int left, int mid, int right)
    {
        int leftSum = INT_MIN;
        int sum = 0;
        for (int i = mid; i >= left; i--)
        {
            sum += nums[i];
            leftSum = max(leftSum, sum);
        }

        int rightSum = INT_MIN;
        sum = 0;
        //注意这里i = mid + 1，避免重复用到nums[i]
        for (int i = mid + 1; i <= right; i++)
        {
            sum += nums[i];
            rightSum = max(rightSum, sum);
        }
        return (leftSum + rightSum);
    
## 总结
- 暴力解法思想是每次先选择一个开始值，然后从开始值向后加，用max储存其中的最大值，如果遇到小于0，则换一个开始值再重复以上步骤。
- 动态规划法用dp储存前一个元素的最大值，所以整个最大值只可能取dp+当前元素和当前元素，遍历一遍后，就可以得出结果，时间复杂度O(n),空间复杂度O(1)。
- 贪心解法从前往后遍历，sum储存遍历过的元素之和，res储存每次加一个元素后中的最大值。当sum小于0时，说明不仅没有正的增益，而且如果最大值已经出来一定不包含该值，此时从此元素开始再次重复上述步骤，和暴力法的区别是省略了许多不必要的验证。
- 分治解法，将数组分为最大值在中心点左侧，中心点右侧，跨中心点三种情况，其中左右侧采用分治保存最大值的方式，跨中心点时以中心点为基准分别向左向右用贪心法求最大子序列和，然后将左右最大序列和加起来即跨中心最大值，结果取三者中最大值。