## 要求
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。

注意你不能在买入股票前卖出股票。
## 示例
示例 1:

输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
示例 2:

输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

## 代码
- 暴力法

-

	int maxProfit(vector<int>& prices) {
        int res = 0;
        if(prices.size()<2) return 0;
        for(int i = 0;i<prices.size()-1;i++)
        {
            for(int j = i;j<prices.size();j++)
            {
                int temp = prices[j] - prices[i];
                res = max(res,temp);
            }
        }
        return res;
    }

- 一次遍历(保存当前最小值）

-

	int maxProfit(vector<int>& prices) {
        int res = 0;
        int minprice = INT_MAX;
        for(int i =0;i<prices.size();i++)
        {
            if(minprice>prices[i]) minprice = prices[i];
            res = max(res,prices[i] - minprice);
        }
        return res;
    }

## 总结
- 暴力法很好理解，就是穷举出所有情况，取最大值。
- 股票要想获得高利润，则需低买高卖，所以我们保存当前遍历的最小值，后面元素与当前最小值之差最大则是所求结果。(要点是找到谷底点）