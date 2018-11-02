/*
����ĿҪ��
ʵ����С�������㷨��Prim���������ͼ����С��������
�������ʽ��
������������ͼ�������е�ͼӦΪ����ͼ�����洢ʱ������ߵ���ʽ�洢���Ĵ洢��������о���Ľ��ܣ�
�� 1 �а����ո�����Ķ������ v��0 < v < 2000���ͱߵĸ��� e��0 < e < 10000����
�� 2 �а��� v+1 ���������ո������p(i)��0 <= i <= v, 0 <= p(i) <= e����
�� 3 �а��� e ���������ո������q(i)��0 <= i <= e-1, 0 <= q(i) <= v-1����
�� 4 �а��� e ���������ո����������Ȩ�أ�r(i)��
�������ʽ��
����ļ�������С�������Ľṹ���Լ���С��������Ȩֵ���μ������������
������ڶ����С��������ֻ���������һ�����ɡ�
�����С�������Ľṹʱ���밴�ձ߼����˳�������
ÿ�н�β����Ҫ���з���

���������� 1��
9 28
0 2 5 9 12 14 18 21 25 28
1 7 0 2 7 1 8 5 3 2 5 4 3 5 4 3 2 6 5 8 7 6 8 1 0 6 7 2
4 8 4 8 11 8 2 4 7 7 14 9 9 10 10 14 4 2 2 6 1 1 7 11 8 6 7 2

��������� 1��
[0 -> 1][1 -> 2][2 -> 8][2 -> 5][5 -> 6][6 -> 7][2 -> 3][3 -> 4] 37

*/ 
#include<iostream>
#include<set>
using namespace std;
int main()
{
	//road[][]Ϊ��·���󣬳�ʼ��ΪINT_MAX�� 
	int n, m;
	cin >> n;	//����ڵ���
	cin >> m;   //�������
	int** road = new int*[n];	
	for (int i = 0; i < n; i++)
	{
		road[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			road[i][j] = INT_MAX;
		}
	}
	//��������� 
	int *line1 = new int[n+1];
	int *line2 = new int[m];
	int *line3 = new int[m]; 
	for (int i = 0; i < n + 1; i++)
		cin >> line1[i];
	for (int i = 0; i < m; i++)
		cin >> line2[i];
	for (int i = 0; i < m; i++)
		cin >> line3[i];
	//��������� �� ��·���� 
	int k = 0; 
	for(int i = 0; i < n; i++)
	{
		for(int j = line1[i]; j < line1[i+1]; j++)
		{
			road[line2[j]][i] = road[i][line2[j]] = line3[k++];
		}
	}
	//�������϶� 
	set<int> s1, s2;
	s1.insert(0);
	for(int i= 1; i < n; i++)
		s2.insert(i);
	//�����С�� 
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
