/*����ĿҪ��
�����������ʱ�����������ؼ�·���������������������ʱ�䣨PTͼ����

�������ʽ��
���������ţ���������ʱ���Լ���Ӧ��������������о���Ľ��ܣ�
�� 1 �й���ĸ��� n��0 < n < 2000����
�� 2~1+n �а����ո�����Ĺ���� V(i) ,����ʱ�� t �������� Vpre(i)��0 <= V(i) < n, 0 <= Vpre(i) < n��������������������Ϊ�գ����ж�����������ö��Ÿ�����������ʽ��ο���������

�������ʽ��
����ļ������������ݣ��������£�
�ؼ�·����ʱ��
�ؼ�·������������ж����ؼ�·�������������ÿ��һ�������˳����Ҫ��
��������������ʱ�䣨�� n �У�

ÿ�н�β����Ҫ���з�
����μ����������

���������� 1��
13
0 2
1 6 0
2 3 0
3 2 1
4 4 2,3
5 3 3
6 8 3
7 4 3
8 2 6,7
9 3 6
10 8 7,4
11 5 9
12 6 10
��������� 1��
28
[0 -> 1 -> 3 -> 4 -> 10 -> 12 -> end]
[0 -> 1 -> 3 -> 7 -> 10 -> 12 -> end]
0
0
5
0
0
15
2
0
8
2
0
2
0

*/

#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<queue>

using namespace std;

struct Node
{
	int num;
	int time;
	int max_time;
	int min_time;
	int count;
	int late;
	vector<int> NodeTo;
	vector<int> NodeFrom;
	vector<int> keyNode;
	Node() : time(0), max_time(0),min_time(0),late(99999),count(0) {}
	~Node() {}
};

void findpath(Node* node, int Nodenum, vector<int>& k, string& s)
{
	k.push_back(Nodenum);
	if(node[Nodenum].count == 0)
	{
		s.clear();
		s.append("[");
		for(int i = k.size() - 1; i > 0; i--)
		{
			s.append(to_string(k[i]));
			s.append(" -> ");
		}
		s.append("end]");
		cout<<s<<endl;
		return;
	}
	for(auto i : node[Nodenum].keyNode)
	{
		findpath(node, i, k, s);
		k.pop_back();
	}
}

int main()
{
	int Nodenum;//����� 
	cin>>Nodenum;
	Node* node = new Node[Nodenum+1];//�������
	Node* node1 = new Node[Nodenum+1];
	node[Nodenum].num = Nodenum;
	node1[Nodenum].num = Nodenum;
	string s;
	bool* sign = new bool[Nodenum];//��¼��Щ�������Ϊ��β���� 
	for(int i = 0; i <Nodenum; i++)
	{
		sign[i] = 0;
	}
	//��ʼ��������Ϣ 
	cin>>node[0].num;
	node1[0].num = node[0].num;
	cin>>node[0].time;
	node1[0].time = node[0].time;
	for(int i = 1,temp = 0; i < Nodenum; i++)
	{
		cin>>node[i].num;
		node1[i].num = node[i].num;
		cin>>node[i].time;
		node1[i].time = node[i].time;
		getline(cin,s);
		temp = 0;
		for(unsigned int j = 1; j < s.size(); j++)
		{
			if(s[j] == ',')
			{
				node[i].NodeFrom.push_back(temp);
				node1[i].NodeFrom.push_back(temp);
				node[temp].NodeTo.push_back(i);
				node1[temp].NodeTo.push_back(i);
				sign[temp] = 1; 
				node[i].count++;
				node1[i].count++;
				temp = 0;
			}
			else
			{
				temp *= 10;
				temp += (int)s[j] - 48;
			}
			if(j == s.size() -1)
			{
				node[i].NodeFrom.push_back(temp);
				node1[i].NodeFrom.push_back(temp);
				node[temp].NodeTo.push_back(i);
				node1[temp].NodeTo.push_back(i);
				sign[temp] = 1;
				node[i].count++;
				node1[i].count++;
			}
		}
	}
	//�������β��� 
	for(int i = 0; i < Nodenum; i++)
	{
		if(sign[i] == 0)
		{
			node[Nodenum].NodeFrom.push_back(i);
			node1[Nodenum].NodeFrom.push_back(i);
			node[Nodenum].count++;
			node1[Nodenum].count++;
			node[i].NodeTo.push_back(Nodenum);
			node1[i].NodeTo.push_back(Nodenum);
		}		
	}
	//�Խ�������������  
	bool* ranksign = new bool[Nodenum+1];//������
	for(int i =0 ; i <= Nodenum; i++)//
		 ranksign[i] = 0; 
	 vector<int> rank;
	 int order = 1;
	 while(1)
	 {
		order = 1;
		for(int i = 0; i <= Nodenum; i++)
		{
			
			if(node1[i].count == 0 && ranksign[i] == 0)
			 {
				 rank.push_back(i);
				 for(auto k : node1[i].NodeTo)
					 node1[k].count--;
				 ranksign[i] = 1;
				 order = 0;
			 }
		 }
		if(order) break;
	 }
	 //�ؼ�·���㷨
	 node[rank[0]].max_time = node[rank[0]].time; 
	 node[rank[0]].min_time = node[rank[0]].time;
	 int max = 0;
	 int min = 9999;
	 for(int k = 1; k < Nodenum + 1; k++)
	 {
	 	//���θ���max����time
	 	for(auto t: node[rank[k]].NodeFrom)
		{
		  if(node[t].max_time > max)
		  {
		  	max = node[t].max_time;
		  	node[rank[k]].keyNode.clear();
		  	node[rank[k]].keyNode.push_back(node[t].num);
		  }
		  else if(node[t].max_time  == max)
		  {
		  	node[rank[k]].keyNode.push_back(node[t].num);
		  }	
		  else{}

		  if(node[t].min_time < min)
		  {
		  	min = node[t].min_time;
		  }
		} 
		node[rank[k]].max_time = max + node[rank[k]].time;
		node[rank[k]].min_time = min + node[rank[k]].time;
		max = 0;
		min = 9999;
	 } 
	 //����ʱ���㷨
	 node[Nodenum].late = node[Nodenum].max_time;
	 for(int k = Nodenum; k >= 0; k--)
	 {
	 	//���θ���late,lateΪ�������ʱ��
	 	for(auto t: node[rank[k]].NodeTo)
		{
			if(node[k].late > node[t].late - node[t].time)
		  	   node[k].late = node[t].late - node[t].time;
		} 
	 } 
	//�������
	 vector<int> keypath;
	 string result;
	cout<<node[rank[Nodenum]].max_time<<endl; 
	findpath(node, Nodenum, keypath, result);
	for(int i = 0; i < Nodenum; i++)
		cout<<node[i].late-node[i].max_time<<endl;
}


