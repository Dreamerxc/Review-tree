## 要求
给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。

说明:

初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
## 示例
示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]

## 代码
- 先合并，再排序

-

	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int i = m,j = 0;i<m+n;i++,j++)
        nums1[i] = nums2[j];
        sort(nums1.begin(),nums1.end());
    }

- 将nums1拷贝，然后采用双指针法

-


	vector<int> temp(nums1.begin(),nums1.begin()+m);
        int i = 0,j = 0,k = 0;
        while(i<m&&j<n)
        {
            if(temp[i]<=nums2[j])
            {
                nums1[k] = temp[i];
                i++;
            }
            else
            {
                nums1[k] = nums2[j];
                j++;
            }
            k++;
        }
        while(i<m) nums1[k++] = temp[i++];
        while(j<n) nums1[k++] = nums2[j++];
    }

- 双指针从后往前排

-

	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1,j = n-1,k = m+n-1;
        while(i>=0&&j>=0)
        nums1[k--] = nums1[i]>nums2[j]?nums1[i--]:nums2[j--];
        if(i<0)
        while(j>=0) nums1[k--] = nums2[j--];
    }
## 总结
- 双指针从后往前排，时间和空间复杂度最低。