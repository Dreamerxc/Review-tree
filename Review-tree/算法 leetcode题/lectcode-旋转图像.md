## 要求
给定一个 n × n 的二维矩阵表示一个图像。

将图像顺时针旋转 90 度。

说明：

你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。

## 代码
- 转置加反转

-

	void rotate(vector<vector<int>>& matrix) {
        int m = matrix.size();
        for(int i = 0;i<m;i++)
            for(int j = i;j<m;j++)
            {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        for(int i = 0;i<m;i++)
            for(int j = 0;j<m/2;j++)
            {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][m-j-1];
                matrix[i][m-j-1] = temp;
            }
    }

## 总结
- 第一次for循环用于转置矩阵，第二次for循环用于将该矩阵反转对称。
- 时间复杂度O(n^2),空间复杂度O(1)。