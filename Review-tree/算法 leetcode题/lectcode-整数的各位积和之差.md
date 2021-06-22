## 要求
给你一个整数 n，请你帮忙计算并返回该整数「各位数字之积」与「各位数字之和」的差。

## 示例

示例 1：

输入：n = 234
输出：15 
解释：
各位数之积 = 2 * 3 * 4 = 24 
各位数之和 = 2 + 3 + 4 = 9 
结果 = 24 - 9 = 15
示例 2：

输入：n = 4421
输出：21
解释： 
各位数之积 = 4 * 4 * 2 * 1 = 32 
各位数之和 = 4 + 4 + 2 + 1 = 11 
结果 = 32 - 11 = 21

## 代码
- 整数取模法

-

	int subtractProductAndSum(int n) {
        if(n==0) return 0;
        int num = 1,sum = 0;
        while(n!=0)
        {
            cout<<n%10<<endl;
            sum = sum + n%10;
            num = num * (n%10);  //注意符号优先级
            n = n/10;
        }
        return num - sum;
    }

- 类型转换法

-

	int subtractProductAndSum(int n) {
        if(n==0) return 0;
        int num = 1, sum = 0;
        string str = to_string(n);
        for (auto c : str){
            int p = c-48;
            num = num * p;
            sum = sum + p;
        }
        return num-sum;
    }

## 总结
- 整数取模法很好理解，注意num = num * (n%10)要加括号，否则运算顺序会发生变化。
- 类型转换法时间复杂度会高一点，注意思想即可。