## 要求
现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，判断是否可能完成所有课程的学习？

## 示例
示例 1:

输入: 2, [[1,0]] 
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。
示例 2:

输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。

## 代码
- 拓扑排序

-

	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
       vector<int> inDegree(numCourses,0);
       vector<vector<int>> lst(numCourses,vector<int>());  //建立表
       for(auto v:prerequisites)
       {
           inDegree[v[0]]++;  //初始化入度列表
           lst[v[1]].push_back(v[0]);  //初始化邻接表,表头储存元素，表身储存该元素的入度元素
       }
       queue<int> que;
       for(int i = 0;i<numCourses;i++)
       {
           if(inDegree[i]==0) que.push(i);  //将入度为0放入队列
       }
       vector<int> res;
       while(!que.empty())
       {
           auto q = que.front();
           que.pop();
           res.push_back(q);

           for(auto s : lst[q])
           {
               if(--inDegree[s]==0) que.push(s);
           }
       }
       return res.size()==numCourses;
    }



## 总结
- 本题转化为判断一个图是否存在环，可以用拓扑排序法来做，拓扑排序的思想就是将入度为0的点删除，或去掉边，然后重新更新每个点的入度，当不存在环时，图中将没有边或点，反之则有环。