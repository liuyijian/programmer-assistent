/* Warshell算法的实现 ，并能给出所有路径 


【输入格式】
采用正向表进行图（可能含有重边或自环）的存储，下面进行具体的介绍：
第 1 行包含空格隔开的顶点个数 v（0 <= v < 2000）和边的个数 e（0 < e < 10000）。
第 2 行包含 v+1 个整数（空格隔开）p(i)（0 <= i <= v, 0 <= p(i) <= e）。
第 3 行包含 e 个整数（空格隔开）q(i)（0 <= i <= e-1, 0 <= q(i) <= v-1）。
第 4 行包含测试点对的个数 n（0 < n <= 100）
第 5~4+n 行包含空格隔开的起始顶点 Vs(i) 和终止顶点 Ve(i)（0 <= Vs, Ve <= v-1）。

【输出格式】
输出文件包含 n 行，每行为相应测试点对的所有路径，如：
Vs(i) -> ... -> Ve(i)（参见输出样例）。
若不存在这样的路径，则输出 NO PATH。
每行结尾都需要换行符

【输入样例 1】
－－－－－－－
9 13
0 3 4 5 6 7 9 10 11 13
1 3 5 4 4 6 8 0 4 7 5 5 7
5
0 0
0 2
0 4
0 6
0 8

【输出样例 1】
－－－－－－－
[0 -> 1 -> 4 -> 8 -> 5 -> 0][0 -> 1 -> 4 -> 8 -> 7 -> 5 -> 0][0 -> 3 -> 6 -> 7 -> 5 -> 0][0 -> 5 -> 0]
NO PATH
[0 -> 1 -> 4][0 -> 3 -> 6 -> 7 -> 5 -> 4][0 -> 5 -> 4]
[0 -> 3 -> 6]
[0 -> 1 -> 4 -> 8][0 -> 3 -> 6 -> 7 -> 5 -> 4 -> 8][0 -> 5 -> 4 -> 8]

*/

#include <iostream>
#include <vector>
#include <string>

void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream)
{
	//请在此填充代码
	int n, m;
	inputStream >> n;	//读入节点数
	inputStream >> m;   //读入边数
	bool **road = NULL;
	road = (bool **)realloc(road, sizeof(bool *)*n);
	for (int i = 0; i < n; i++)
	{
		road[i] = (bool *)calloc(n, sizeof(bool));
		for (int j = 0; j < n; j++)
		{
			road[i][j] = false;
		}
	}
	//道路矩阵定义完成

	int *line1 = new int[n+1];
	int *line2 = new int[m];
	for (int i = 0; i < n + 1; i++)
	{
		inputStream >> line1[i];
	}
	for (int i = 0; i < m; i++)
	{
		inputStream >> line2[i];
	}
	//正向表读取完成

	std::vector<int> **path=new std::vector<int> *[n];
	for (int i = 0; i < n; i++)
	{
		path[i] = new std::vector<int>[n];
		for (int j = 0; j < n; j++)
		{
			path[i][j].clear();
		}
	}
	//具体道路列表定义

	int temp1 = 0, temp2 = 0;//temp1记录line1位次，也即起点节点号，temp2记录line2位次
	for (int i = 0; i < n; i++)
	{
		for (int j = line1[i]; j < line1[i + 1]; j++)
		{
			road[i][line2[j]] = true;
			path[i][line2[j]].push_back(line2[j]);
		}
	}
	//初始道路矩阵完成，并已将初始边放入具体道路列表path中

	bool append_flag;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (road[j][i] == true && road[i][k] == true)
				{
					road[j][k] = true;
					for (int x = 0; x < path[j][i].size(); x++)
					{
						append_flag = true;
						for (int y = 0; y < path[j][k].size(); y++)
						{
							if (path[j][i][x] == path[j][k][y])
							{
								append_flag = false;
								break;
							}
						}
						if (append_flag == true)
						{
							path[j][k].push_back(path[j][i][x]);
						}
					}
				}
			}
		}
	}
	//图建立完成

	std::vector<int> result;
	result.reserve(n);
	result.clear();
	std::vector<int> v;
	v.reserve(n);
	v.clear();
	bool point_same;
	bool continue_flag = true;
	int start, end;
	int temp_int;
	int times;
	std::string print_string;
	char temp_char[8] = { 0 };
	inputStream >> times;
	for (int t = 0; t < times; t++)
	{
		inputStream >> start;
		inputStream >> end;
		result.clear();
		v.clear();
		result.push_back(start);
		v.push_back(path[start][end].size() - 1);
		print_string.clear();
		continue_flag = true;
		while (continue_flag)
		{
			if (result[result.size() - 1] == end&&result.size() != 1)
			{
				for (int i = 0; i < result.size(); i++)
				{
					if (i == 0)
					{
						print_string += '[';
						itoa(result[i],temp_char,10);
						print_string += temp_char;
					}
					else
					{
						print_string += " -> ";
						itoa(result[i], temp_char, 10);
						print_string += temp_char;
					}
				}
				print_string += ']';
				result.pop_back();
				v.pop_back();
			}
			else
			{
				while (true)
				{
					if (v[v.size() - 1] < 0)
					{
						v.pop_back();
						result.pop_back();
						break;
					}
					else
					{
						temp_int = path[result[result.size() - 1]][end][v[v.size() - 1]];
						point_same = false;
						if (result[0] != end)
						{
							for (int m = 0; m < result.size(); m++)
							{
								if (result[m] == temp_int)
								{
									point_same = true;
									break;
								}
							}
						}
						else if (result[0] == end)
						{
							for (int m = 1; m < result.size(); m++)
							{
								if (result[m] == temp_int)
								{
									point_same = true;
									break;
								}
							}
						}
						if (point_same == false)
						{
							result.push_back(temp_int);
							v[v.size() - 1]--;
							v.push_back(path[result[result.size() - 1]][end].size() - 1);
							break;
						}
						else
						{
							v[v.size() - 1]--;
							continue;
						}
					}
				}
			}
			continue_flag = false;
			for (int n = 0; n < v.size(); n++)
			{
				if (v[n] != -1)
				{
					continue_flag = true;
				}
			}
		}
		if (print_string.length() == 0)
		{
			print_string += "NO PATH";
		}
		print_string += '\n';
		outputStream << print_string;
		std::cout << print_string;
	}
}

int main(int argc, char *argv[])
{
	//可在此更改测试文件
    std::string fileName = "test101.txt"; 
    
    USSolver unofficialSolver(fileName);
    const std::string unofficialAnswer = unofficialSolver.GetAnswer();

    std::cout << "Your Answer:" << unofficialAnswer << std::endl;
}
