## 要求
实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须原地修改，只允许使用额外常数空间。

## 示例
以下是一些例子，输入位于左侧列，其相应输出位于右侧列。

1,2,3 → 1,3,2

3,2,1 → 1,2,3

1,1,5 → 1,5,1
## 代码
- 采用双指针法，理清数学原理。

-

       void nextPermutation(vector<int>& nums) {
        int i=nums.size()-1;
        int flag = 0;
        for(;i>0;i--)
        if(nums[i-1]<nums[i])
        {
            flag = i-1;
            break;
        }
        if(i==0) sort(nums.begin(),nums.end());
        else
        {
            sort(nums.begin()+i,nums.end());
            int j = i;
            for(;j<nums.size();j++)
            if(nums[j]>nums[flag])
            break;
            int temp;
            temp = nums[j];
            nums[j] = nums[flag];
            nums[flag] = temp;              
        }
        }
## 评价
- 从后往前遍历，先找到相邻两个后一个数大于前一个数的数对，对遍历过的数按从小到大排序，在排序的数组中从前往后遍历，找到第一个比nums[flag]大的数进行交换。