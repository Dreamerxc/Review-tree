## 要求
给定长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

## 示例
示例:

输入: [1,2,3,4]
输出: [24,12,8,6]

## 代码
- 先求总和，再分除。

-

	vector<int> productExceptSelf(vector<int>& nums) {
        int sum = 1,count = 0,place = -1;  //count用于记录0的个数
        for(int i = 0;i<nums.size();i++)
        {
            if(nums[i]!=0)
            sum = sum * nums[i];
            else
            {
                count++;
                place = i;
            }
        }   
        vector<int> res;
        if(count>=1) res.resize(nums.size(),0); 
        if(count==0) //数组中没有0
        for(int j = 0;j<nums.size();j++)    
        res.push_back(sum/nums[j]);
        if(count==1) res[place] = sum; //数组中只有一个0
        return res;
    }

## 总结
- 可以分为两种小情况，数组中有0，数组中没有0
	- 数组中没有0，先求出所有元素乘积，如何求结果时，用总数除以每个元素即可。
	- 数组中有0时又分为两种情况，有两个以上0时，所求结果全为0，只有一个0时，除为0元素的位置等于总和外，其余位置全为0。