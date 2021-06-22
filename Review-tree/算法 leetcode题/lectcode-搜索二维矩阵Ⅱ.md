## 要求
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
## 示例

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

## 代码
- 根据大小关系逐步搜索

-

	bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0) return false;
        int left = matrix[0].size()-1,low = 0;
        while(left>=0&&low<matrix.size())
        {
            if(matrix[low][left]>target) left--;
            else if(matrix[low][left]<target) low++;
            else return true;
        }
        return false;
    }


## 总结
- 时间复杂度O(m+n),最坏情况搜索位于对角处。
- 选取右上角（或左下角）元素，因为这两处元素有一个特点，它的左方，下方和这个元素的大小关系是相反的(对于右上角元素而言），所以利用这个特点，target不断和当前元素比较，当大于当前元素，说明target在下方，当小于当前元素，说明target在左侧，如果超过界限还没有找到说明没有此元素，返回flase。