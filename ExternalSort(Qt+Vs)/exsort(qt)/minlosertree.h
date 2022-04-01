#pragma once
#include<iostream>
#include<math.h>
#include<fstream>
#include<cstdio>
#include<vector>
#include<map>
using namespace std;

static long int sizeof_MM;//�ڴ�ռ������ɵ�Ԫ����
static string path;//Ҫ��������ļ�·�� ����: F:\vscpp\EXSORT\EXSORT
static string file_name;//������ļ�����
static long int sizeof_file;//�������ļ������ָ���
static string ff_name;//�����������
static int max_run = 0;//��һ�����ٸ�˳��
static int all_temps = 0;//��ʱ�ļ�
static int buffer_size = 100;//�ϲ�ʱ�����
static int page_size;
static int page_num;
static int disk_times;//���̷��ʴ���
static int max_n;

struct Player
{//ѡ��
	int element;//Ԫ��ֵ 
	int num;//˳����
	//bool operator<(const Player &p1)
	//{//�ȿ�˳�����ٿ�Ԫ��
	//	return (num != p1.num) ? (num < p1.num) : (element < p1.element);
	//}
	bool operator<=(const Player& p1)
	{//�ȿ�˳�����ٿ�Ԫ��
		return (num != p1.num) ? (num < p1.num) : (element < p1.element);
	}
	Player& operator=(const Player& p)
	{
		num = p.num;
		element = p.element;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Player& p) {
		out << p.element;
		return out;
	};
};

class illegalParameterValue
{
public:illegalParameterValue(string s = "value is not legal") :message(s) {};
	  void output() { cout << message; }
private:
	string message;
};

template<class T>
class minLoserTree
{
public:
	minLoserTree(T* ThePlayers = NULL, int n = 0);
	~minLoserTree() { delete[] tree; delete[] edges; }

	void initialize(T* thePlayer,
		int theNumberOfPlayers);
	void play_once(int p, int leftChild, int rightChild);
	int winner(int x, int y) //���ظ�С��Ԫ���±�
	{ //winner ��� 
		return players[x] <= players[y] ? x : y;
	};
	int loser(int x, int y)//���ظ����Ԫ���±�
	{//loser ���ڲ��ڵ�
		return players[x] <= players[y] ? y : x;
	};
	void replay(int thePlayer);//�ع�
	void output();
	void maintain() { tree[0] = edges[1]; };//ά��tree[0]
	long long int top() {//������С��tree[0]
		return tree[0];
	};
	void make_run(fstream& fin);
	//void make_run1(fstream& fin);
	//void adjust(int pos,int k,int level);//����λ�� r1 2 4  
	//void clear();//���
	void merge_K(int k, int sta, int level);

	void get_total() {
		totals = 0;
		if (max_run % kk == 0) {
			int temp = max_run / kk; totals += temp;
			while (temp != 1)
			{
				temp /= kk;
				totals += temp;
			}
		}
		else
		{
			int temp = max_run / kk; totals += temp; totals++;
			while (temp != 0)
			{
				temp /= kk;
				totals += temp;
				totals++;
			}
		}
	};
	int kk;				  // K
private:
	T* players;//Ԫ������
	int* edges;//���ϵĽ�����Ԫ��
	int numberofPlayers;//�ܹ����ٲ�����
	int* tree;//ר�ż�¼�ڲ��ڵ㣬tree[0]������¼��������
	int lowExt;           // lowest-level external nodes
	int offset;           // 2^log(n-1) - 1
	int totals = 0;           //K·�ϲ��ܹ����� S

};
