/*【题目要求】
实现二分图最大匹配的匈牙利算法

【输入格式】
第一行：边的数量
后续每一行表示一条边，用两个整数来表示，分别为第一个集合和第二个集合中的结点编号，从0开始，用空格隔开。

【输出格式】
依次输出最大匹配的所有边
每行输出边的两个结点编号，用空格隔开

【输入样例 1】
－－－－－－－
5
0 0
0 1
1 2
2 0
3 3
－－－－－－－
【输出样例 1】
－－－－－－－
0 1
1 2
2 0
3 3
*/
#include <iostream>
#include <string.h>
#define MAXN 1000
using namespace std;


//MAXN表示X集合和Y集合顶点个数的最大值
int nx,ny;                        //x和y集合中顶点的个数
int g[MAXN][MAXN];                //邻接矩阵，g[i][j]为1表示有连接
int cx[MAXN],cy[MAXN];        //cx[i],表示最终求得的最大匹配中，与x集合中元素Xi匹配的集合Y中顶点的索引
                              //cy[i],表示最终求得的最大匹配中，与y集合中元素Yi匹配的集合X中顶点的索引		
int mk[MAXN];//DFS算法中记录顶点访问状态的数据mk[i]=0表示未访问过，为1表示访问过

//从集合X中的定顶点u出发，用深度有限的策略寻找增广路
//这种增广路只能是当前的匹配数增加1

int path(int u)
{
    for(int v=0;v<ny;++v)
	{      //考虑所有Yi顶点v
        if(g[u][v] && !mk[v])
		{     //Y中顶点v与u邻接，且没有访问过
            mk[v]=1;                        //访问v
            //如果v没有匹配，则直接将v匹配给u，如果v已经匹配了，但是从cy[v],也就是从v之前已经匹配的x出发，找到一条增广路，但是这里记住这里v已经记录访问过了
            //如果第一个条件成立，则不会递归调用
            if(cy[v]==-1 || path(cy[v]))
			{
                cx[u]=v;         //把Y中v匹配给X中u
                cy[v]=u;            //把X中u匹配给Y中v
                return 1;
            }
        }
    }
    return 0;                        //如果不存在从u出发的增广路，则返回0
}

int maxMatch()//求二分图最大匹配的匈牙利算法
{        
    int res=0;
    memset(cx,-1,sizeof(cx));        //从0匹配开始增广，将cx和xy各元素都初始化为-1
    memset(cy,-1,sizeof(cy));
    for(int i=0;i<nx;++i)
	{
        if(cx[i]==-1)
		{                                    //从X集合中每个没有匹配的点出发开始寻找增广路
            memset(mk,0,sizeof(mk));
            res+=path(i);
        }
    }
    return res;
}

int main() 
{
	int n; //总边数 
	cin>>n;
    int tx,ty;
    int tx_max = 0;
	int ty_max = 0;
	
    for(int i = 0; i < n; i++)//置零
    {
    	for(int j = 0; j < n; j++)
    	{
    		g[i][j] = 0;
		}
	}
	 
    for(int i = 0; i < n; i++)
    {
    	cin>>tx>>ty;
    	g[tx][ty] = 1;
    	if(tx_max < tx)
    		tx_max = tx;
    	if(ty_max < ty)
    		ty_max = ty;
	}
	nx = tx_max+1;//x的总边数 
	ny = ty_max+1;//y的总边数
	 
    int num= maxMatch();
    
    for(int i = 0; i < num; ++i)
	{
        cout<<i<< " "<<cx[i]<<endl;
    }
    return 0;
}
