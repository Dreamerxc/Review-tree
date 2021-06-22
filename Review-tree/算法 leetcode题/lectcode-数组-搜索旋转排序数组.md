## 要求
假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

你可以假设数组中不存在重复的元素。

你的算法时间复杂度必须是 O(log n) 级别

## 示例
输入: nums = [4,5,6,7,0,1,2], target = 0

输出: 4

输入: nums = [4,5,6,7,0,1,2], target = 3

输出: -1
## 代码
-因为要求时间复杂度为O(logn),所以首先想到二分法，只是这个题注意二分的条件。

    int search(vector<int>& nums, int target) {
        int start = 0;
		int end = nums.size() - 1;
		while (start <= end) 
        {
			int mid = (start + end) / 2;
			if (target == nums[mid]) return mid;
            //左半段是有序的
			if (nums[start] <= nums[mid]) 
            {
				if (target >= nums[start] && target < nums[mid])
					end = mid - 1;
                else start = mid + 1;
			
            }
            //右半段是有序的
			else 
            {
				if (target > nums[mid] && target <= nums[end])  start = mid + 1;
			    else  end = mid - 1;
			}
    }
    return -1;
    }
## 总结
- 算法基于一个事实，数组从任意位置劈开后，至少有一半是有序的，什么意思呢？

比如 [ 4 5 6 7 1 2 3] ，从 7 劈开，左边是 [ 4 5 6 7] 右边是 [ 7 1 2 3]，左边是有序的。

基于这个事实。

我们可以先找到哪一段是有序的 (只要判断端点即可)，然后看 target 在不在这一段里，如果在，那么就把另一半丢弃。如果不在，那么就把这一段丢弃。（参考网上大神）

