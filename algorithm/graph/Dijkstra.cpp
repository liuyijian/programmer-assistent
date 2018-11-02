/*    Dijkstra �㷨����Ǹ�Ȩ����ͼ�����·��

�������ʽ��
������������ͼ���������ر߻��Ի����������л�·���Ĵ洢��������о���Ľ��ܣ�
�� 1 �а����ո�����Ķ������ v��0 < v < 2000���ͱߵĸ��� e��0 < e < 10000����
�� 2 �а��� v+1 ���������ո������p(i)��0 <= i <= v, 0 <= p(i) <= e����
�� 3 �а��� e ���������ո������q(i)��0 <= i <= e-1, 0 <= q(i) <= v-1����
�� 4 �а��� e ���������ո����������Ȩ�أ�r(i)��
�� 5 �а������Ե�Եĸ��� n��0 < n <= 100����
�� 6~5+n �а����ո��������ʼ���� Vs(i) ����ֹ���� Ve(i)��0 <= Vs, Ve <= v-1����

�������ʽ��
����ļ����� n �У�ÿ��Ϊ��Ӧ���Ե�Ե����·����Ȩֵ���磺
Vs(i) -> ... -> Ve(i) W���μ������������
��������������·��������� NO PATH��
ÿ�н�β����Ҫ���з�

���������� 1��
��������������
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

��������������

��������� 1��
��������������
NO PATH
[0 -> 3 3]
[0 -> 5 -> 4 4]
[0 -> 5 -> 6 4]
[0 -> 5 -> 4 -> 8 -> 7 6]

��������������

���������˵����
void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream){}
���� inputStream Ϊ��������outputStream Ϊ�������
ֱ��ͨ�� inputStream �������ݼ��ɣ�����ӿ���̨���롣
������д�뵽 outputStream ���ɡ�
���������������������

�������޸��ļ������ಿ�ֵĴ��롿

����������˵����
main������fileName������¼�����ļ��������ļ��Ĳ��Խ�����ɿ���̨�������ͨ���޸Ĳ����ļ����в�ͬ�Ĳ��ԡ�

*/

#include <iostream>
#include <vector>
#include <string>

void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream)
{
	//road[][]Ϊ��·���󣬳�ʼ��Ϊ������� link[][]Ϊ��ͨ���󣬳�ʼ��Ϊ0����ͨ��Ϊ1�� 
	int n, m;
	inputStream >> n;	//����ڵ���
	inputStream >> m;   //�������
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
	//��������� 
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
	//��������� �� ��·���� 
	
	int k = 0; 
	for(int i = 0; i < n; i++)
	{
		for(int j = line1[i]; j < line1[i+1]; j++)
		{
			road[i][line2[j]] = line3[k++];
			link[i][line2[j]] = true;
		}
	}
	//��warshell��һ����ͨ��
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
	//�������Ҫ��
	int num;
	inputStream >> num;
	int start;//��� 
	int end;//�յ� 
	int* length = new int[n];//��¼���·���ĳ��� 
	int* status = new int[n];//�ڵ����Լ�¼
	std::string path;//��¼���·��
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
		//������ 
		inputStream>>start;
		inputStream>>end; 
		//��Warshell�ж��Ƿ�����ͨ�����ޣ������ NO PATH��Ȼ��continue 
		if(!link[start][end])
		{
			result += "NO PATH\n";
			continue;
		}
		//����һ��
		for(int j = 0; j < n; j++) 
		{
			length[j] = INT_MAX;
			status[j] = 0;	
			shortroad[j] = start;	
		}
		record2 = 0;
		min = INT_MAX;
		path = "";
		//��ʽ������ʼ 
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
		//���������·�����ο�PPT
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
