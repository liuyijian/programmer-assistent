/*    Dijkstra 算法，求非负权有向图的最短路径

【输入格式】
采用正向表进行图（不含有重边或自环，但可能有环路）的存储，下面进行具体的介绍：
第 1 行包含空格隔开的顶点个数 v（0 < v < 2000）和边的个数 e（0 < e < 10000）。
第 2 行包含 v+1 个整数（空格隔开）p(i)（0 <= i <= v, 0 <= p(i) <= e）。
第 3 行包含 e 个整数（空格隔开）q(i)（0 <= i <= e-1, 0 <= q(i) <= v-1）。
第 4 行包含 e 个整数（空格隔开，代表权重）r(i)。
第 5 行包含测试点对的个数 n（0 < n <= 100）。
第 6~5+n 行包含空格隔开的起始顶点 Vs(i) 和终止顶点 Ve(i)（0 <= Vs, Ve <= v-1）。

【输出格式】
输出文件包含 n 行，每行为相应测试点对的最短路径和权值，如：
Vs(i) -> ... -> Ve(i) W（参见输出样例）。
若不存在这样的路径，则输出 NO PATH。
每行结尾都需要换行符

【输入样例 1】
－－－－－－－
9 13
0 3 4 5 6 7 9 10 11 13
1 3 5 4 4 6 8 6 4 7 5 5 7
2 3 2 4 5 3 1 2 2 3 5 2 1
5
0 2
0 3
0 4
0 6
0 7

－－－－－－－

【输出样例 1】
－－－－－－－
NO PATH
[0 -> 3 3]
[0 -> 5 -> 4 4]
[0 -> 5 -> 6 4]
[0 -> 5 -> 4 -> 8 -> 7 6]

－－－－－－－

【函数填充说明】
void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream){}
其中 inputStream 为输入流，outputStream 为输出流。
直接通过 inputStream 读入数据即可，无需从控制台输入。
输出结果写入到 outputStream 即可。
可以自行添加其它函数。

【请勿修改文件中其余部分的代码】

【函数测试说明】
main函数中fileName变量记录测试文件，测试文件的测试结果可由控制台输出，可通过修改测试文件进行不同的测试。

*/

#include <iostream>
#include <vector>
#include <string>

void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream)
{
	//road[][]为道路矩阵，初始化为正无穷大， link[][]为连通矩阵，初始化为0，连通则为1； 
	int n, m;
	inputStream >> n;	//读入节点数
	inputStream >> m;   //读入边数
	int** road = NULL;
	bool** link = NULL; 
	road = new int*[n]; 
	link = new bool*[n];
	
	for (int i = 0; i < n; i++)
	{
		road[i] = new int[n];
		link[i] = new bool[n];
		for (int j = 0; j < n; j++)
		{
			road[i][j] = 0;
			link[i][j] = false;
		}
	}
	//读入正向表 
	int *line1 = new int[n+1];
	int *line2 = new int[m];
	int *line3 = new int[m]; 
	for (int i = 0; i < n + 1; i++)
	{
		inputStream >> line1[i];
	}
	for (int i = 0; i < m; i++)
	{
		inputStream >> line2[i];
	}
	for (int i = 0; i < m; i++)
	{
		inputStream >> line3[i];
	}
	//解析正向表 至 道路矩阵 
	
	int k = 0; 
	for(int i = 0; i < n; i++)
	{
		for(int j = line1[i]; j < line1[i+1]; j++)
		{
			road[i][line2[j]] = line3[k++];
			link[i][line2[j]] = true;
		}
	}
	//用warshell跑一遍连通性
	for(int k = 0; k < n; k++)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				link[i][j] = link[i][j] || (link[i][k] && link[k][j]);
			}
		}
	} 
	//读入求解要求
	int num;
	inputStream >> num;
	int start;//起点 
	int end;//终点 
	int* length = new int[n];//记录最短路径的长度 
	int* status = new int[n];//节点属性记录
	std::string path;//记录最短路径
	int* shortroad = new int[n];
	std::vector<int> shortroad2;
	std::string result = ""; 
	int min = INT_MAX;
	int record;
	int record2 = 0;
	int record3;
	int newend;
	for(int i = 0; i < num; i++)
	{
		//输入点对 
		inputStream>>start;
		inputStream>>end; 
		//用Warshell判断是否有连通，若无，则输出 NO PATH，然后continue 
		if(!link[start][end])
		{
			result += "NO PATH\n";
			continue;
		}
		//重置一切
		for(int j = 0; j < n; j++) 
		{
			length[j] = INT_MAX;
			status[j] = 0;	
			shortroad[j] = start;	
		}
		record2 = 0;
		min = INT_MAX;
		path = "";
		//正式操作开始 
		length[start] = 0;
		status[start] = 1;
		for(int pp = 0; pp < n; pp++)
		{
			if(road[start][pp] > 0 && status[pp] != 1)
				length[pp] = road[start][pp];
		}
		while(1)
		{
			min = INT_MAX;
			for(int k = 0; k < n; k++)
			{
				if(status[k] == 1) continue;
				if(min >= length[k])
				{
					record = k;
					min = length[k];
				}	
			} 
			status[record] = 1;
			record2 = 0;
			for(int kk = 0; kk < n; kk++)
			{
				if(status[kk] == 0)
					record2 = 1;	
			}
			if(!record2) break;
			for(int mm = 0; mm < n; mm++)
			{
				if(status[mm] == 0 && road[record][mm] != 0)
				{
					if(length[mm] > length[record] + road[record][mm])
					{
						length[mm] = length[record] + road[record][mm];
						shortroad[mm] = record;
					}
				}	
			}		
		}
		//反读出最短路径，参考PPT
		newend = end;
		do
		{
			shortroad2.push_back(newend);
			newend = shortroad[newend];
		}while(newend!=start);
		shortroad2.push_back(start);
		reverse(shortroad2.begin(), shortroad2.end());
		path.append("[");
		for(auto i:shortroad2)
		{
			path.append(std::to_string(i));
			if(i == end) break;
			path.append(" -> ");
		}
		path.append(" ");
		path.append(std::to_string(length[end]));
		path.append("]");
		result += path;
		result += "\n"; 
	}                                                                                                                                                                                                                                                                  
	outputStream << result;
	std::cout<<result;
	return 0;
}
