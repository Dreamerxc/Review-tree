## 要求
编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

每行中的整数从左到右按升序排列。
每行的第一个整数大于前一行的最后一个整数。

## 示例
示例 1:

输入:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
输出: true
示例 2:

输入:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
输出: false

## 代码
- 顺序查找，先确定行，再确定列。

-

	bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int i = 0;
        if(m==0) return false;
        int n = matrix[0].size();
        if(n==0) return false;
        for(;i<m;i++)
        {
            if(n==1&&matrix[i][0]==target) return true; 
            if(n>1&&matrix[i][0]<=target&&target<=matrix[i][n-1])
            break;
        }
        if(i==m) i = i-1;
        for(int j = 0;j<n;j++)
        {
            if(matrix[i][j]==target) return true;
        }
        return false;
    }

- 两次二分法，先二分确定行，再二分确定列

-

	bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int i = 0;
        if(m==0) return false;
        int n = matrix[0].size();
        if(n==0) return false;
        int low = 0,high = m-1;
        while(low<high)
        {
            int mid = low + (high - low)/2;
            if(matrix[mid][n-1]>=target) high = mid;
            else low = mid + 1;
        }
        int left = 0,right = n-1;
        while(left<=right)
        {
            int mid = left + (right-left)/2;
            if(matrix[low][mid]==target) return true;
            else if(matrix[low][mid]<target) left = mid + 1;
            else right = mid - 1;
        }
        return false;
    }

- 一次二分。

-

	bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m==0) return false;
        int n = matrix[0].size();
        if(n==0) return false;
        int left = 0,right = m*n-1;
        while(right>=left){
            int mid=(left+right)/2;
            int i=mid/n;//一维数组下标mid对应的行坐标i；
            int j=mid%n;//一维数组下标mid对应的列坐标j；
            if(matrix[i][j]==target){
                return true;
            }
            else if(matrix[i][j]>target){
                right=mid-1;
            }
            else{
                left=mid+1;
            }
        }
        return false;      
    }
## 总结
- 顺序查找先通过各行的最后一个数确定行，再在那一行上顺序查找。
- 两次二分法只是在顺序查找的基础上将顺序查找变为二分查找，当数据比较多时，会加快速度。
- 一次二分是将二维数组转换为一维数组来做，其中一维数组的下标mid和二维数组下标[i][j]的换算关系：[i][j]=[mid/列数][mid%列数]。然后相当于二分查找一个数了。