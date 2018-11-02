/*
【题目要求】
实现最小生成树算法（Prim），求给定图的最小生成树。
【输入格式】
采用正向表进行图（本题中的图应为无向图，但存储时用有向边的形式存储）的存储，下面进行具体的介绍：
第 1 行包含空格隔开的顶点个数 v（0 < v < 2000）和边的个数 e（0 < e < 10000）。
第 2 行包含 v+1 个整数（空格隔开）p(i)（0 <= i <= v, 0 <= p(i) <= e）。
第 3 行包含 e 个整数（空格隔开）q(i)（0 <= i <= e-1, 0 <= q(i) <= v-1）。
第 4 行包含 e 个整数（空格隔开，代表权重）r(i)。
【输出格式】
输出文件包含最小生成树的结构，以及最小生成树的权值（参见输出样例）。
如果存在多个最小生成树，只需输出其中一个即可。
输出最小生成树的结构时，请按照边加入的顺序输出。
每行结尾都需要换行符。

【输入样例 1】
9 28
0 2 5 9 12 14 18 21 25 28
1 7 0 2 7 1 8 5 3 2 5 4 3 5 4 3 2 6 5 8 7 6 8 1 0 6 7 2
4 8 4 8 11 8 2 4 7 7 14 9 9 10 10 14 4 2 2 6 1 1 7 11 8 6 7 2

【输出样例 1】
[0 -> 1][1 -> 2][2 -> 8][2 -> 5][5 -> 6][6 -> 7][2 -> 3][3 -> 4] 37

*/ 
#include<iostream>
#include<set>
using namespace std;
int main()
{
	//road[][]为道路矩阵，初始化为INT_MAX； 
	int n, m;
	cin >> n;	//读入节点数
	cin >> m;   //读入边数
	int** road = new int*[n];	
	for (int i = 0; i < n; i++)
	{
		road[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			road[i][j] = INT_MAX;
		}
	}
	//读入正向表 
	int *line1 = new int[n+1];
	int *line2 = new int[m];
	int *line3 = new int[m]; 
	for (int i = 0; i < n + 1; i++)
		cin >> line1[i];
	for (int i = 0; i < m; i++)
		cin >> line2[i];
	for (int i = 0; i < m; i++)
		cin >> line3[i];
	//解析正向表 至 道路矩阵 
	int k = 0; 
	for(int i = 0; i < n; i++)
	{
		for(int j = line1[i]; j < line1[i+1]; j++)
		{
			road[line2[j]][i] = road[i][line2[j]] = line3[k++];
		}
	}
	//建立集合对 
	set<int> s1, s2;
	s1.insert(0);
	for(int i= 1; i < n; i++)
		s2.insert(i);
	//添加最小边 
	int sum = 0;
	int start,end, min;
	while(!s2.empty()) 
	{
		min = INT_MAX;
		for(auto it : s2) 
		{
			for(auto jt : s1)
			{
				if(road[jt][it] < min)
				{
					start = jt;
					end = it;
					min = road[jt][it];
				}
			}
		}
		s1.insert(end);
		s2.erase(end);
		sum += min;
		cout<<"["<<start<<"->"<<end<<"]";
	}
	cout<<" "<<sum;
	return 0;
}
