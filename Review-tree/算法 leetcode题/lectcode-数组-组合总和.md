## 要求
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：

所有数字（包括 target）都是正整数。
解集不能包含重复的组合

## 示例
输入: candidates = [2,3,6,7], target = 7,

所求解集为:
[
  [7],
  [2,2,3]
]

## 代码
- DFS（深度优先遍历）+ 剪枝 + 回溯

-

 	class Solution {
	private:
    vector<vector<int>> res;  //储存结果
    vector<int> path;  //暂时储存路径
	public:
    void DFS(vector<int> &candidates,int start,int target)
    {
        if(target==0) res.push_back(path);  //将满足条件的路径加入结果中
        for(int i = start;i<candidates.size()&&candidates[i]<=target;i++)
        {
            path.push_back(candidates[i]);
            DFS(candidates,i,target-candidates[i]);
            path.pop_back();   //不满足条件，回溯。
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(),candidates.end());  //先排序，避免重复项
    DFS(candidates,0,target);
    return res;   
    }   
	};
## 总结
- 回溯算法基本思想：采用深度优先搜索方法从一条路往前走，能进则进，不能进则退回来，换一条路再试。
- 将数组排序，既可以节省比较次数，也能避免重复项。
- 第一次正式接触回溯，写了部分path数组中的变化，主要是递归。
	- path[2] DFS(0,5)
	- path[2,2] DFS(0,3)
	- path[2,2,2] DFS(0,1)
	- path[2,2,3] DFS(1,0)
	- target==0,储存[2,2,3]到res
	- path[2,3] DFS(1,5)
	- ......