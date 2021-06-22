## 要求
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

## 示例
示例 1:

输入:
11110
11010
11000
00000

输出: 1
示例 2:

输入:
11000
11000
00100
00011

输出: 3


## 代码
- 递归遍历

-

	void dfs(vector<vector<char>>& grid,int i,int j)  //i表示纵坐标，j表示横坐标。
    {
        int K = grid.size(),L = grid[0].size();
        grid[i][j] = '0';
        if(i+1<K&&grid[i+1][j]!='0') dfs(grid,i+1,j);
        if(i-1>=0&&grid[i-1][j]!='0') dfs(grid,i-1,j);
        if(j-1>=0&&grid[i][j-1]!='0') dfs(grid,i,j-1);
        if(j+1<L&&grid[i][j+1]!='0') dfs(grid,i,j+1);
        return;
    }
    int numIslands(vector<vector<char>>& grid) {
        int K = grid.size(); //K表示二维网络的高
        if(K==0) return 0;
        int L = grid[0].size();  //L表示二维网络的宽。
        int ret = 0;
        if(K==0||L==0) return 0;
        for(int i = 0;i<K;i++)
            for(int j = 0;j<L;j++)
            {
                if(grid[i][j]!='0')
                {
                    dfs(grid,i,j);
                    ret++;
                }
            }
        return ret;
    }

- 队列辅助遍历

-

	int numIslands(vector<vector<char>>& grid) {
        int K = grid.size();
        if(!K) return 0;
        int L = grid[0].size();
        int ret = 0;
        for(int i = 0;i<K;i++)
            for(int j = 0;j<L;j++)
            {
                if(grid[i][j]=='1')
                {
                    ret++;
                    grid[i][j] = '0';
                    queue<pair<int,int>> que;
                    que.push({i,j});
                    while(!que.empty())
                    {
                        auto rc = que.front();
                        que.pop();
                        int row = rc.first,col = rc.second;
                        if(row-1>=0&&grid[row-1][col]=='1')
                        {
                            que.push({row-1,col});
                            grid[row-1][col] = '0';
                        } 
                        if(row+1<K&&grid[row+1][col]=='1')
                        {
                            que.push({row+1,col});
                            grid[row+1][col] = '0';
                        }
                        if(col-1>=0&&grid[row][col-1]=='1')
                        {
                            que.push({row,col-1});
                            grid[row][col-1] = '0';
                        } 
                        if(col+1<L&&grid[row][col+1]=='1')
                        {
                            que.push({row,col+1});
                            grid[row][col+1] = '0';
                        }
                    }
                }
            }
            return ret;
		}
	

## 总结
- 采用递归的方法遍历，递归的条件是紧挨的为1，并不超界，遍历的方向可以随意调整，即dfs代码中的if语句顺序。
- 采用队列储存周围符条件的位置，将遍历过的赋值为‘0’。
- 递归和队列只是在保存数据上方式有所不同，核心思想还是遍历方式和遍历过的赋值为‘0’。