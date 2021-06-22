## 要求
给定一个整数数组，你需要寻找一个连续的子数组，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

你找到的子数组应是最短的，请输出它的长度。

## 示例

输入: [2, 6, 4, 8, 10, 9, 15]
输出: 5
解释: 你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。

## 代码
### 先排序后比较

-

	int findUnsortedSubarray(vector<int>& nums) {
        if(nums.size()==0) return 0;
        vector<int> temp(nums);
        sort(temp.begin(),temp.end());
        int i= 0,j = 0,res = 0;
        for(i = 0;i<nums.size();i++)
        if(temp[i]!=nums[i]) break;
        for(j = nums.size()-1;j>=0;j--)
        if(temp[j]!=nums[j]) break;
        res = j - i + 1;
        return res>=0?res:0;
    }
- 最短无序连续子数组存在于数组的内部，如果将该数组排序，那么除了无序数组改变外，数组的首尾并没有变化，所以通过比较数组的首尾就可以求出最短无序数组的长度。

### 找无序数组的最大，最小元素

-

	int findUnsortedSubarray(vector<int>& nums) {
        int min_value = INT_MAX, max_value = INT_MIN;
        bool flag = false;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1])
                flag = true;
            if (flag)
                min_value = min(min_value, nums[i]);
        }
        flag = false;
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] > nums[i + 1])
                flag = true;
            if (flag)
                max_value = max(max_value, nums[i]);
        }
        int left = 0,right = 0;
        for (left = 0; left < nums.size(); left++) {
            if (min_value < nums[left])
                break;
        }
        for (right = nums.size() - 1; right >= 0; right--) {
            if (max_value > nums[right])
                break;
        }
        return right - left < 0 ? 0 : right - left + 1;
    }

- 这个算法背后的思想是无序子数组中最小元素的正确位置可以决定左边界，最大元素的正确位置可以决定右边界。


