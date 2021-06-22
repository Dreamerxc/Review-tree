## 要求
实现 int sqrt(int x) 函数。

计算并返回 x 的平方根，其中 x 是非负整数。

由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

## 示例
示例 1:

输入: 4
输出: 2
示例 2:

输入: 8
输出: 2
说明: 8 的平方根是 2.82842..., 
     由于返回类型是整数，小数部分将被舍去。

## 代码
- 二分法

-

	int mySqrt(int x) {
        int left = 0;
        int right = x/2+1;
        while(left<right)
        {
           long mid = left + (right-left+1)/2;
           if(mid*mid>x) right = mid-1;
           else left = mid; 
        }
        return left;
    }

- 牛顿迭代法

-

	int mySqrt(int x) {
        if (x == 0) return 0;
        double pre=0;
        double res=1;
        while(res!=pre)
        {
            pre=res;
            res=(res+x/res)/2;
        }
        return int(res);
    }
## 总结
- 二分法时需用mid*mid来验证区间，如果用int型会溢出，要改为long型。
- 牛顿迭代法主要将数学的思想用代码表示出来，迭代速度很快，需要理解其数学思想，以后可用于近似求解各种方程。