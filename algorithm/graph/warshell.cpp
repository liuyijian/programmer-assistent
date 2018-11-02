/* Warshell�㷨��ʵ�� �����ܸ�������·�� 


�������ʽ��
������������ͼ�����ܺ����ر߻��Ի����Ĵ洢��������о���Ľ��ܣ�
�� 1 �а����ո�����Ķ������ v��0 <= v < 2000���ͱߵĸ��� e��0 < e < 10000����
�� 2 �а��� v+1 ���������ո������p(i)��0 <= i <= v, 0 <= p(i) <= e����
�� 3 �а��� e ���������ո������q(i)��0 <= i <= e-1, 0 <= q(i) <= v-1����
�� 4 �а������Ե�Եĸ��� n��0 < n <= 100��
�� 5~4+n �а����ո��������ʼ���� Vs(i) ����ֹ���� Ve(i)��0 <= Vs, Ve <= v-1����

�������ʽ��
����ļ����� n �У�ÿ��Ϊ��Ӧ���Ե�Ե�����·�����磺
Vs(i) -> ... -> Ve(i)���μ������������
��������������·��������� NO PATH��
ÿ�н�β����Ҫ���з�

���������� 1��
��������������
9 13
0 3 4 5 6 7 9 10 11 13
1 3 5 4 4 6 8 0 4 7 5 5 7
5
0 0
0 2
0 4
0 6
0 8

��������� 1��
��������������
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
	//���ڴ�������
	int n, m;
	inputStream >> n;	//����ڵ���
	inputStream >> m;   //�������
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
	//��·���������

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
	//������ȡ���

	std::vector<int> **path=new std::vector<int> *[n];
	for (int i = 0; i < n; i++)
	{
		path[i] = new std::vector<int>[n];
		for (int j = 0; j < n; j++)
		{
			path[i][j].clear();
		}
	}
	//�����·�б���

	int temp1 = 0, temp2 = 0;//temp1��¼line1λ�Σ�Ҳ�����ڵ�ţ�temp2��¼line2λ��
	for (int i = 0; i < n; i++)
	{
		for (int j = line1[i]; j < line1[i + 1]; j++)
		{
			road[i][line2[j]] = true;
			path[i][line2[j]].push_back(line2[j]);
		}
	}
	//��ʼ��·������ɣ����ѽ���ʼ�߷�������·�б�path��

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
	//ͼ�������

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
	//���ڴ˸��Ĳ����ļ�
    std::string fileName = "test101.txt"; 
    
    USSolver unofficialSolver(fileName);
    const std::string unofficialAnswer = unofficialSolver.GetAnswer();

    std::cout << "Your Answer:" << unofficialAnswer << std::endl;
}
