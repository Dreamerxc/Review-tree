## 要求
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
## 示例
给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9

所以返回 [0, 1]
## 代码
- 暴力解决法-时间复杂度O(n^2)

-


    vector<int> twoSum(vector<int>& nums, int target) {
       for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] == target - nums[i]) {
                    return  { i, j };
                }
            }
        }
        return {};
    }


- 哈希法-时间复杂度O(N)

-


    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> m;  
        for(int i = 0; i < nums.size(); m[target - nums[i - 1]] = i++){
            if(m.count(nums[i])) return {m[nums[i]], i};
        }
        return {-1, -1};
    }
## 注意要点
- map函数：map是STL的一个关联容器，它提供一对一的hash，即一个关键字，和这个关键字对应的值，和python中的字典有点相似。
- map.count():返回的是被查找元素的个数。如果有，返回1；否则，返回0。注意，map中不存在相同元素，所以返回值只能是1或0。

### 2019年12月19日

