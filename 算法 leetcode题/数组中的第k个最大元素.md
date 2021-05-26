#### 数组中的第k个最大元素



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