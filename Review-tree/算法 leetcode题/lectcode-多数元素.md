## 要求
给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

## 示例
示例 1:

输入: [3,2,3]
输出: 3
示例 2:

输入: [2,2,1,1,1,2,2]
输出: 2

## 代码
- 暴力法

-

	int majorityElement(vector<int>& nums) {
        int num = 0,ret = 0;
        for(int i = 0;i<nums.size();i++)
        {
            int count = 0;
            for(int j = 0;j<nums.size();j++)
            {
                if(nums[i]==nums[j]) 
                count++;
            }
            if(count > num) 
            {
                num = count;
                ret = nums[i];
            }
            if(num>nums.size()/2) return ret;
        }
        return -1;
    }

- 哈希法

-

	int majorityElement(vector<int>& nums) {
        unordered_map<int,int> hash;
        for(int i = 0;i<nums.size();i++)
        {
            ++hash[nums[i]];
            if(hash[nums[i]]>nums.size()/2)
            return nums[i];
        }
        return -1;
    }

- 排序法

-

	int majorityElement(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()/2];
    }

- Boyer-Moore算法

-

	int majorityElement(vector<int>& nums) {
        int num = 0,ret = nums[0];  //num为计数器。
        for(int elem:nums)
        {
            if(num==0) ret = elem;
            if(elem==ret) num++;
            else num--;
        }
        return ret;
    }

## 总结
- 暴力法时间复杂度O(n^2),空间复杂度O(1)。
- 哈希法键保存元素，值保存元素出现个数，当元素出现个数超过条件时，直接返回。
- 当存在元素个数超过一半时，将所有元素排序后，超过一般的元素肯定正在排完序元素的中间。
- Boyre-Moore算法思想是当存在大于所有元素一半的众数时，选取当前元素为众数，计数器+1，当下一个元素不等于这个元素时，计数器减一，当计数器为0时，重置众数。前面让计数器为0的元素相当于抵消了元素，最后计数器一定时大于0的，因为众数是大于总数一半的。

