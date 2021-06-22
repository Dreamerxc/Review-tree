## 要求
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序

## 示例
示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]

## 代码
- 直接法

-

	void moveZeroes(vector<int>& nums) {
       int end = nums.size()-1;
       int i = 0;
       while(i<=end)
       {
           if(nums[i] == 0)
           {
               for(int j = i;j<nums.size()-1;j++)
               {
                   nums[j] = nums[j+1];
               }
               nums[end] = 0;
               end--;
           }
           else i++;
       }
    }
- 直接法优化

-

	void moveZeroes(vector<int>& nums) {
       int lastplace = 0;
       for(int i = 0;i<nums.size();i++)
       if(nums[i]!=0) nums[lastplace++] = nums[i];
       for(int j = lastplace;j<nums.size();j++)
       nums[j] = 0;
    }
- 快慢指针法

-

	void moveZeroes(vector<int>& nums) {
    for (int lastplace = 0, cur = 0; cur < nums.size(); cur++) {
        if (nums[cur] != 0) {
            swap(nums[lastplace++], nums[cur]);
        }
    }
## 总结
- 从前往后遍历，当遇到0时，从后往前覆盖，到达去除该元素的效果，并在末尾赋值0；
- 采用双指针，先将不为0的元素全部移动到前面，然后把后面的元素全赋为0；
- 快慢指针法，慢指针之前元素全部不为0，快慢指针之间元素全为0，当快指针指向不为0的元素时，交换快慢指针指向元素的位置。