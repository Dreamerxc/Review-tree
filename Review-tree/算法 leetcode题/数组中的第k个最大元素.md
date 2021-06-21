#### TOP k问题

##### 数组中的第k个最大元素

##### 方法一：快速排序

```
int findKthLargest(vector<int>& nums, int k) {
        // 快速排序
        return fastsort(nums,k,0,nums.size()-1);
    }

    int fastsort(vector<int>& nums, int k, int left, int right) {
        if (left == right) return nums[left];
        int privot = left-1;
        int val = nums[left];
        for(int i = left;i<=right;i++) {
            if (nums[i] >= val){
                privot++;
                swap(nums[i],nums[privot]);
            }
        }
        swap(nums[privot],nums[left]);
        int len = privot-left+1;
        if (len == k) return val;
        else if (len<k) return fastsort(nums,k-len,privot+1,right);
        else return fastsort(nums,k,left,privot-1);
    }
```

##### 方法二：堆排序



##### 前K个高频元素

给你一个整数数组 `nums` 和一个整数 `k` ，请你返回其中出现频率前 `k` 高的元素。你可以按 **任意顺序** 返回答案。

##### 方法一：快速排序

```
vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int,int> mp;
        for (auto x: nums) {
            mp[x]++;
        }
        set<int> st;
        for (auto x:mp) {
            st.insert(x.first);
        }
        vector<int> temp(st.begin(), st.end());
        quicksort(mp,temp, k, 0, temp.size()-1);
        vector<int> res(temp.begin(), temp.begin() + k);
        return res;
    }

    void quicksort(map<int,int>& mp, vector<int>& nums, int k, int left, int right) {
        if (left >= right) return;
        int privot = left - 1, val = mp[nums[left]];
        for (int index = left;index <= right; index++) {
            if (mp[nums[index]] >= val) {
                privot++;
                swap(nums[index], nums[privot]);
            }
        }
        swap(nums[privot], nums[left]);
        int len = privot-left+1;
        if (len == k) return;
        else if (len<k) return quicksort(mp,nums,k-len,privot+1,right);
        else return quicksort(mp,nums,k,left,privot-1);
    }
```

