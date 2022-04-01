#pragma once
#include<iostream>
#include<sstream>
#include<cstdio>
//�����ظ�
using namespace std;
class illegalValue
{
public:
	illegalValue(string m = "the value is illegal !") :message(m) {}
	void output() { cerr << message; }
private:
	string message;
};

template <class K, class E>
struct skipNode
{
	typedef pair<K, E> pairType;

	pairType element;
	skipNode<K, E>** next;//ָ������
	int lsize;//����
	skipNode(pairType& thePair, int size)
		:element(thePair) {
		lsize = size-1;
		next = new skipNode<K, E> * [size];
	}
};

template<class K, class E>
class skipList
{
public:
	bool empty()const { return dSize == 0; }//o(1)
	int size() const { return dSize; }
	skipList(K largekey, int maxPairs = 10000, float prob = 0.5);
	pair< K, E>* find(K& thekey);
	int level() const;
	skipNode<K, E>* search(K& theKey,int &count);//search���Ӷ� O(log2 n)
	void insert(pair< K, E>& thePair);//���븴�Ӷ� ��search O(logn)+ ��ָ�� +O(thelevel)
	void erase(K& theKey);//ɾ�� ��search O(logn)+ ��ָ�� +O(levels)
	void output();
	void erase_min();//O(minlevel)
	void erase_max();//o(log n)+erase 
	void op_xor();
	void reform();//�ع�
	//��ʼ��Ϊ�ϸ�����
	void ideal_initial(int *a,int m);
	void get_level(int *b, int level, int low, int high);
	void check(int count);
	//void display();//��������м򵥵ؿ��ӻ�����
	void analyse();//���з���
	int need_reform = 1;//Ĭ����Ҫ�ع�
private:
	float cutoff;//����ȷ������
	int levels; //��ǰ���ķǿ�����
	int dSize; //�ֵ�����Ը���
	int maxlevel;//���������������
	K tailKey; //���ؼ���
	skipNode<K, E>* headerNode; //ͷ���ָ��
	skipNode<K, E>* tailNode;//Ϊ�ڵ�ָ��
	skipNode<K, E>** last;//ָ�� ����  ÿ��������Ϊһ��ָ�� last[i] ָ�� i�����һ���ڵ�
	//last[i] ��ʾi�����ڵ�
	
};

