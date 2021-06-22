## 要求
给定一个用字符数组表示的 CPU 需要执行的任务列表。其中包含使用大写的 A - Z 字母表示的26 种不同种类的任务。任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。CPU 在任何一个单位时间内都可以执行一个任务，或者在待命状态。

然而，两个相同种类的任务之间必须有长度为 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。

你需要计算完成所有任务所需要的最短时间。

## 示例 

输入: tasks = ["A","A","A","B","B","B"], n = 2
输出: 8
执行顺序: A -> B -> (待命) -> A -> B -> (待命) -> A -> B.

## 代码
- 排序法

-

	int leastInterval(vector<char>& tasks, int n) {
        map<char,int> mp{};
        for(auto x:tasks)
        mp[x]++;
        vector<int> vec;
        for(auto &it:mp)
        vec.push_back(it.second);
        sort(vec.begin(),vec.end());
        int res = 0,temp = vec.size()-1; //res保存结果，temp为计数器
        while(vec[temp]>0)
        {
            for(int i = 0;i<=n;i++)
            {
                if(vec[temp]==0) break;
                if((temp-i)>=0&&vec[temp-i]>0) vec[temp-i]--;
                res++;
            }
            sort(vec.begin(),vec.end());
        }
        return res;
	}
- 求出所有字母出现的频率，进行排序后，一轮一轮的进行安排，每一轮安排次数为n+1次，优先安排频率高的，安排后该字母次数减1，如果所有次数都为1说明安排完毕.