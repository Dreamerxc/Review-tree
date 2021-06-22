## 要求
实现 pow(x, n) ，即计算 x 的 n 次幂函数。

## 示例
示例 1:

输入: 2.00000, 10
输出: 1024.00000
示例 2:

输入: 2.10000, 3
输出: 9.26100
示例 3:

输入: 2.00000, -2
输出: 0.25000
解释: 2-2 = 1/22 = 1/4 = 0.25

## 代码
- 直接暴力法

-

	double myPow(double x, int n) {
        double res = 1.0;
        if(n<0)  
        {
            n = -n;
            x = 1/x;
        }
        for(int i = 0;i<n;i++)
        {
            res = res*x;
        }
        return res;
    }

- 快速排幂法（时间复杂度：O(log n)空间复杂度：O(logn)。

-

	double myPow(double x, int n) {
        if(n==0||x==1) return 1;
        else if(n<0) return myPow(1/x,-(n+1))/x; //防止溢出
        else if(n==1) return x;
        else if(n%2==0) return myPow(x*x,n/2);
        else return myPow(x*x,n/2)*x;
    }
- 快速排幂法（循环）

-

	double myPow(double x, int n) {
        long long N = n;
        double res = 1.0;
        if(N<0)
        {
            N = -N;
            x = 1/x;
        }
        for(long long i = N;i;i = i/2)
        {
            cout<<(i%2);
            if(i%2==1) res = res*x;
            x = x*x;
        }
        return res;
    }
	
## 总结
- 暴力法时间复杂度O(n),空间复杂度O(1）。当n过大时，会超出时间限制。
- 快速排幂的递归写法，是根据数学公式而来的，幂为偶数时，它可有它的二分之一幂平方而来，幂为奇数时，它可有它的二分之一幂平方在乘本身得，这样就比暴力法省略了相乘得次数。注意n为INT_MIN时，转换为正数时，会溢出，所以我们可以处理n+1,这样就不会出现溢出得情况。
- 快速排幂法循环写法，用long long 型储存n,避免了转换为正数时出现的溢出问题。
  