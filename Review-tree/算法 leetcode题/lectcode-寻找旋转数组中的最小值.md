## 要求
假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

请找出其中最小的元素。

## 示例
示例 1:

输入: [3,4,5,1,2]
输出: 1
示例 2:

输入: [4,5,6,7,0,1,2]
输出: 0

## 代码
- 二分法-寻找落差位置

-

	int findMin(vector<int>& nums) {
        int n = nums.size();
        if(n==1) return nums[0];
        int left = 0,right = nums.size()-1;
        if(nums[right]>nums[0]) return nums[0]; //排除没有落差的情况
        while(left<right)
        {
            int mid = left + (right - left)/2;
            if(nums[mid+1]<nums[mid]) return nums[mid+1]; 
            if(nums[mid-1]>nums[mid]) return nums[mid];
            if(nums[mid]>nums[0]) left = mid + 1;
            else right = mid;
        }
        return -1;
    }

## 总结
- 因为是在一个旋转的升序数组中查找最小值，所以最小值一定和最大值紧挨者，这样就形成一个落差，判断条件当后一个数比前一个数大时便是落差位置，然后通过二分法缩短区间即可。