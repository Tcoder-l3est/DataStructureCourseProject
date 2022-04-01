#pragma once
#include<bits/stdc++.h>
using namespace std;

//�����ظ�ֵ���������ظ������ݵĻ�����ֻ�Ե�һ�����в�����
//����ѽڵ� �ֵܸ������� ��֯�ṹ
template < typename K, typename V>
struct BinaryHeapNode
{
	BinaryHeapNode* parent;
	BinaryHeapNode* LeftChild;
	BinaryHeapNode* sibiling;
	int degree;
	K key;//ֵ
	V data;//��Ӧ���Ǹ�ά���ֵ�Ľṹ

	//Ĭ�Ϲ���
	BinaryHeapNode() {
		parent = LeftChild = sibiling = NULL;
		degree = 0; key = data = INT_MIN; //�Ͼ���Ҫ����
	}
	BinaryHeapNode(pair<K,V> p) {
		parent = LeftChild = sibiling = NULL;
		degree = 0; key = p.first; data = p.second;//�Ͼ���Ҫ����
	}
	//copy ����
	BinaryHeapNode(BinaryHeapNode& bhn) {
		parent = bhn.parent;
		LeftChild = bhn.LeftChild;
		sibiling = bhn.sibiling;
		degree = bhn.degree;
		key = bhn.key;
		data = bhn.data;
	}
	//����
	BinaryHeapNode(BinaryHeapNode* p, BinaryHeapNode* lc,
		BinaryHeapNode* sib, int deg, K k,V d) {
		parent = p;
		LeftChild = lc;
		sibiling = sib;
		degree = deg;
		key = k;
		data = d;
	}
	//���صȺ�
	BinaryHeapNode& operator=(BinaryHeapNode& bhn) {
		if (&bhn == this) {//�ų�
			return *this;
		}
		delete this->parent;
		delete this->LeftChild;
		delete this->sibiling;
		this->parent = bhn.parent;
		this->LeftChild = bhn.LeftChild;
		this->sibiling = bhn.sibiling;
		this->degree = bhn.degree;
		this->key = bhn.key;
		this->key = bhn.data;
		return *this;
	}
	//����<��
	bool operator<(const BinaryHeapNode& bhn) {
		return this->key < bhn.key;
	}

}; 




//���䣡����  �������˱ȽϷ��� �������ѣ�
template <typename K, typename V, typename Compare = less<K> >
class BinaryHeap 
{
public:
	//�� һ����Bnode һ����Bheap
	typedef BinaryHeapNode<K, V>	bnode;
	typedef BinaryHeap			Bheap;
	ofstream fout;
	ifstream fin;
	string inname;
	string outname;
	int putflag;
private:
	bnode* Root;//���ڵ㣬��Сֵ�ڵ�
	Compare compare;//���Ƚ�����Ĭ��С�ڣ�Ϊ��С��!
	int heap_degree;
	int size;
	

public:
	BinaryHeap(bnode* h, Compare c = Compare()) 
		:Root(h), compare(c), heap_degree(0),size(0), putflag(1) {}
	BinaryHeap(Compare c = Compare())
		:Root(nullptr), compare(c), heap_degree(0), size(0), putflag(1) {}
	BinaryHeap(string inn, string outn, Compare c = Compare())
	{
		Root = nullptr; compare = c; heap_degree = 0; size = 0;
		outname = outn;
		inname = inn;
		fout.open(outname);
		fin.open(inname);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "�ļ���ʧ��!\n";
			return;
		}
	}
	void Make_Heap(Compare c = Compare()) {
		Root = NULL; compare = c;
		heap_degree = 0; size = 0;
	}//��ʼ��һ���ն�

	void setcompare(Compare c) {
		compare = c;
	}
	void lineAtTail(bnode *&tail,bnode *cur) {//β�˲��� 
		if (Root == NULL) {
			Root = cur;
			tail = cur;
		}
		else {
			tail->sibiling = cur;
			tail = tail->sibiling;
		}
	}
	void treeLink(bnode* l, bnode* r)
	{//�������ŵȶ����Ķ���������
		l->parent = r;
		l->sibiling = r->LeftChild;
		r->LeftChild = l;
		r->degree ++;
	}
	bnode* find_pre(bnode* cur) {//����ĳ�ڵ�� ���ֵ�
		bnode* pre = NULL;
		if (cur->parent == NULL) 
			pre = Root;
		else if (cur->parent->LeftChild == cur) {//��ǰ��
			return pre;
		}
		else pre = cur->parent->LeftChild;
		while (pre->sibiling != cur) {
			pre = pre->sibiling;
		}
		return pre;
	}
	bool check_exist(pair<K, V> p);

	BinaryHeapNode<K,V>* Find_Min();//����һ��ָ����С�ؼ���Ԫ�ص�ָ��
	BinaryHeapNode<K, V>* Find(bnode* t,K KEY);//�ҵ��ؼ���K��ָ��

	void Union(Bheap& Heap);//���H�ϲ����ϲ��Ľ�������ڵ�ǰ����,H��Ϊ��
	void Merge_Root(Bheap& Heap);//�ϲ�����

	void reverse();//���� ����ɾ��

	void insert(pair<K,V> x);//����Ԫ��X
	void push(pair<K, V> x) { insert(x); }


	pair<K, V>* Extract_Min();//�Ӷ���ɾ����С�ؼ���Ԫ�أ�������ָ��ɾ��Ԫ�ص�ָ��
	void pop() {
		Extract_Min();
	}
	void top() {
		Find_Min();
	}

	void Decrease_Key(K oldkey, K newk);//��Ԫ��X�Ĺؼ��ָ�����ֵK
	
	void Delete(K KEY);//�Ӷ���ɾ��Ԫ��X

	void Post(bnode* x);//�������
	void preTravel(bnode* x);//ǰ�����
	void preT();//ǰ�����
	void levelTravel();//��α���

	void outputPost() { Post(Root); }
	void outputpre() { preT(); };
	
	void visualize(string filename);

	//���ȶ������� Ӧ��ֻ�õ�insert Extract MIN FINDmin FIND Delete  Decrease_Key
};
