## 要求
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组。如果不存在符合条件的连续子数组，返回 0。

## 示例
示例: 

输入: s = 7, nums = [2,3,1,2,4,3]
输出: 2
解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。

## 代码
- 暴力穷举法

-

	int minSubArrayLen(int s, vector<int>& nums) {
        int res = INT_MAX,flag = 0;
        for(int i =0;i<nums.size();i++)
            for(int j = i;j<nums.size();j++)
            {
                flag = 0;
                int sum = 0;
                for(int k = i;k <= j;k++)
                {
                    sum += nums[k];
                    if(sum>=s)
                    {
                        res = min(res,k-i+1);
                        flag = 1;
                        break;
                    }
                }
                if(flag==1) break;  //如果是从第三层循环跳出来的，可以直接结束第二层循环。
            }
        return res!=INT_MAX?res:0;
    }
- 优化的暴力

-

	int minSubArrayLen(int s, vector<int>& nums) {
        vector<int> sums(nums.size()+1,0);
        if(nums.size()==0) return 0;
        sums[0] = nums[0];
        int res = INT_MAX,flag = 0;
        for(int i =1;i<nums.size();i++)
        sums[i] = sums[i-1] + nums[i];
        for(int j = 0;j<nums.size();j++)
            for(int k = j;k<nums.size();k++)
            {
                int sum = sums[k] - sums[j] +nums[j];
                if(sum>=s)
                {
                    res = min(res,k-j+1);
                    break;
                }
            }
        return res!=INT_MAX?res:0;
    }

- 双指针法

-

	int minSubArrayLen(int s, vector<int>& nums) {
        int left = 0,sum = 0,res = INT_MAX;
        for(int i = 0;i<nums.size();i++)
        {
            sum = sum + nums[i];
            while(sum>=s)
            {
                res = min(res,i - left +1);
                sum -= nums[left++];
            }
        }
        return res!=INT_MAX?res:0;
    }


- 二分法优化第二个for循环。
 
- 
	
	int minSubArrayLen(int s, vector<int>& nums) {
    int n = nums.size();
    if (n == 0)
        return 0;
    int ans = INT_MAX;
    vector<int> sums(n + 1, 0); 
    for (int i = 1; i <= n; i++)
        sums[i] = sums[i - 1] + nums[i - 1];
    for (int i = 1; i <= n; i++) {
        int to_find = s + sums[i - 1];
        auto bound = lower_bound(sums.begin(), sums.end(), to_find);
        if (bound != sums.end()) {
            ans = min(ans, static_cast<int>(bound - (sums.begin() + i - 1)));
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}

## 总结
- 暴力穷举法时间复杂度O(n^3)。
- 用sums数组对应nums前i项和，可以将时间复杂度降低到O(n^2)。
- 双指针法一次遍历便可以得到结果，时间复杂度为O(n)。
- lower_bound()返回值是一个迭代器,返回指向大于等于key的第一个值的位置，对象：有序数组或容器。
- static_cast是一个c++运算符，功能是把一个表达式转换为某种类型，但没有运行时类型检查来保证转换的安全性。
