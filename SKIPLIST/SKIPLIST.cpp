#include<iostream>
#include<sstream>
#include<cstdio>
#include<math.h>
#include"SKIPLIST.h"
#include<algorithm>
using namespace std;

static double find_nums=0;
static double find_times = 0;

static double insert_nums=0;
static double insert_times = 0;

static double erase_nums=0;
static double erase_times = 0;
//find search insert erase ����Ӷ�O(maxlevel+n)
//					ƽ�����Ӷ�O(log2 n)
//
//erase min O��1��
//erase max O (n)
//xor		O(n)
//�ع����������в������ɾ�����߲���ʱ count����>n
//�ع����Ӷȣ�

template<class K, class E>
skipList<K, E>::skipList(K largekey, int maxPairs, float prob)
{//���캯�� �ؼ���С��largekey �����Ը���size���Ϊmaxpairs 0<prob<1
	cutoff = prob * RAND_MAX;
	maxlevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
	levels = 0;//��ʼ������
	dSize = 0;
	tailKey = largekey;

	//����ͷ,tail���,last
	pair<K, E> tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxlevel + 1);
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E> * [maxlevel + 1];
	//����Ϊ��ʱ�����⼶�����е�ͷ�ڵ㶼ָ��β�ڵ�
	for (int i = 0; i <= maxlevel; i++)
	{
		headerNode->next[i] = tailNode;
	}
}

template<class K, class E>
pair< K, E>* skipList<K, E>::find(K& theKey)
{//����ƥ������Ե�ָ��
//���û��ƥ������ԣ�����NULL
	find_times++;
	if (theKey >= tailKey)
		return NULL;//��ƥ������
	//λ��beforeNode�ǹؼ���ΪtheKey�Ľڵ�֮ǰ�����ұߵ�λ��
	skipNode<K, E>* beforeNode = headerNode;
	int count = 0;
	for (int i = levels; i >= 0; i--)
	{//����i��ָ��
		while (beforeNode->next[i]->element.first < theKey)
		{
			count++;
			beforeNode = beforeNode->next[i];
		}
	}
	//�����һ���ڵ�Ĺؼ����Ƿ���theKey

	if (beforeNode->next[0]->element.first == theKey)
	{
		
		count++;
		cout << "find "<< theKey<<" ������ " << count << "��Ԫ�رȽ�";
		cout << "  ���Ϊ: YES\n";
		check(count);
		find_nums += count;
		return &beforeNode->next[0]->element;
	}
	cout << "find " << theKey << " ������ " << count << "��Ԫ�رȽ�";
	cout << "  ���Ϊ: NO\n";
	check(count);
	find_nums += count;
	return NULL;//��ƥ���
}

template<class K, class E>
int skipList<K, E>::level() const
{//����һ����ʾ������������������������maxlevel
	int lev = 0;
	while (rand() <= cutoff)
	{
		lev++;
	}
	return (lev <= maxlevel) ? lev : maxlevel;
}
template<class K, class E>
skipNode<K, E>* skipList<K, E>::search(K& theKey,int &count)
{//�����ؼ���theKey����ÿһ��������Ҫ�鿴�����һ���ڵ�洢������last��
//���ذ����ؼ���thekey�Ľڵ�
	//λ��beforenode�ǹؼ���thekey�Ľڵ�֮ǰ�����һ���ڵ�

	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		count++;
		while (beforeNode->next[i]->element.first < theKey)
		{
			count++;
			beforeNode = beforeNode->next[i];
		}
		last[i] = beforeNode;//���һ������i�Ľڵ�
	}
	//cout << "erase ������ " << count++ << "��Ԫ�رȽ�" << endl;
	return beforeNode->next[0];
}

template<class K, class E >
void skipList<K, E>::insert(pair< K, E>& thePair)
{//������pair�����ֵ� ���ǹؼ�����ͬ ���ڵ�����
	insert_times++;
	if (thePair.first >= tailKey)
	{
		ostringstream s;
		s << "Key = " << thePair.first << "Must be <" << tailKey;
		throw illegalValue(s.str());
	}
	int count = 0;
	//�鿴�ؼ���Ϊthekey�������Ƿ��Ѿ�����
	skipNode<K, E>* theNode = search(thePair.first,count);
	if (theNode->element.first == thePair.first)
	{//���� ����
		int theLevel = level(); //�½ڵ�ļ�
		//ʹ��theLevel Ϊ <=levels+1
		if (theLevel > levels)
		{
			theLevel = ++levels;
			last[theLevel] = headerNode;
		}

		//�ڽڵ�Node������½ڵ�
		skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
		for (int i = 0; i <= theLevel; i++)
		{//����i������
			newNode->next[i] = last[i]->next[i];
			last[i]->next[i] = newNode;
		}
		dSize++;
		cout << "insert " << thePair.first << " ������ " << count << "��Ԫ�رȽ�" << endl;
		check(count);
		insert_nums += count;
		return;
	}

	//������ ��ȷ���½ڵ����ڵļ�����
	int theLevel = level(); //�½ڵ�ļ�
	//ʹ��theLevel Ϊ <=levels+1
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}

	//�ڽڵ�Node������½ڵ�
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++)
	{//����i������
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	dSize++;
	cout << "insert "<<thePair.first<<" ������ " << count << "��Ԫ�رȽ�" << endl;
	insert_nums += count;
	check(count);
	return;
}

template<class K, class E >
void skipList<K, E>::erase(K& theKey)
{//ɾ��
	erase_times++;
	int count = 1;
	if (theKey >= tailKey)
		return;

	//�鿴�Ƿ���ƥ���
	skipNode<K, E>* theNode = search(theKey,count);
	count++;
	if (theNode->element.first != theKey)//������
	{
		cout << "erase " << theKey << " ʧ�ܣ��������޸�Ԫ�أ�����" << endl;
		erase_nums+=count;
		check(count);
		return;
	}
		
	//ɾ��
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
	{
		//count = count + 2;
		last[i]->next[i] = theNode->next[i];
	}

	//��������
	while (levels > 0 && headerNode->next[levels] == tailNode)
	{
		//count++;
		levels--;
	}
	erase_nums += count;
	cout << "erase "<<theKey<<" ������ " << count << "��Ԫ�رȽ�" << endl;
	delete theNode;
	dSize--;
	check(count);
	
}

template<class K, class E>
void skipList<K, E>::output()
{
	skipNode<K, E>* theNode = headerNode->next[0];
	while (theNode != tailNode)
	{
		cout <<"Ԫ��ֵ : "<<theNode->element.second << " ";
		cout << "���� : "<<theNode->lsize << endl;
		theNode = theNode->next[0];
	}
	cout << endl;
}

template<class K, class E>
void skipList<K, E>::erase_min()
{
	if (headerNode->next[0] == tailNode)
	{
		cout << "Nothing in skipList" << endl;
		return;
	}
	int minLevel = levels;
	while (headerNode->next[minLevel] != headerNode->next[0])
		minLevel--;
	skipNode< K, E>* minNode = headerNode->next[0];
	cout<<"ERASE MIN "<< minNode->element.second << " SUCCESS!!!"<<endl;
	for (int i = minLevel; i >= 0; i--)
	{
		headerNode->next[i] = minNode->next[i];
	}

	delete minNode;
	while (levels > 0 && headerNode->next[levels] == tailNode)
		levels--;
	dSize--;
}

template<class K, class E>
void skipList<K, E>::erase_max()
{
	int count = 0;
	if (headerNode->next[0] == tailNode)
		return;
	skipNode< K, E>* lastNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (lastNode->next[i] != tailNode)
		{
			count++;
			lastNode = lastNode->next[i];
		}
	}
	//cout << lastNode->element.first << endl;
	K theKey = lastNode->element.first;
	cout << "ERASE MAX " << theKey << " SUCCESS!!!" <<  " ������ " << count << " ��Ԫ�رȽ� " << endl;
	//erase(beforeNode->element.first);
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
		{
			beforeNode = beforeNode->next[i];
		}
		last[i] = beforeNode;//���һ������i�Ľڵ�
	}
	skipNode<K, E>* theNode = beforeNode->next[0];
	//ɾ��
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
	{
		last[i]->next[i] = theNode->next[i];
	}

	//��������
	while (levels > 0 && headerNode->next[levels] == tailNode)
	{
		//count++;
		levels--;
	}
	delete theNode;
	dSize--;
}

template<class K, class E>
void skipList<K, E>::op_xor()
{//�������Ԫ�ص�����
	skipNode<K, E>* scanNode = headerNode->next[0];
	K val = 0;
	while (scanNode != tailNode)
	{
		val ^= scanNode->element.second;
		scanNode = scanNode->next[0];
	}
	cout << val << endl;
	//ss<<val<<endl;
}

template<class K, class E>
void skipList<K, E>::reform()
{//��find ɨ����� > 
	//�ع�  O��n*seta(levels��)
	//����ÿ��Ӧ�õ�level
	int* rank = new int[dSize];
	for (int i = 0; i < dSize; i++)
	{
		rank[i] = 0;
	}
	get_level(rank, levels, 0, dSize); // rank����ÿ��Ԫ�صļ�
	
	skipNode< K, E>* ScanNode = headerNode->next[0];//ɨ��
	
	for (int i = 0; i <=maxlevel; i++)
	{//Ĭ���޸�һ�� last ����ÿ�� һ��������
		last[i] = headerNode;
		last[i]->next[i] = tailNode;
	}

	for (int i = 0; i < dSize; i++)
	{//���ν���next�ع� �����Լ����еļ���

		if (rank[i] <= levels) //������ܴ��ڵĶϼ�����
			levels = rank[i];
		
		//����һ�� ��һ���ڵ� ���潫��ǰ�ڵ��next�ع�
		ScanNode->lsize = rank[i];
		skipNode<K, E>* NextNode = ScanNode->next[0];//Ҫ���ӵ�
		ScanNode->next = new skipNode<K, E> * [rank[i] + 1];
		
		for (int j = 0; j <= rank[i]; j++)
		{//����i������
			ScanNode->next[j] = last[j]->next[j];
			last[j]->next[j] = ScanNode;
			last[j]= ScanNode;
		}
		ScanNode = NextNode;
	}
	cout << "�ع���ɣ�"<<endl;

}

template<class K, class E>
void skipList<K, E>::ideal_initial(int *a,int m)
{//���Ӷ�O(LOGN)//���� + O(logn)//rank + o(n)//��ʼ��
	//��ʼ��M�� ���Լ����� log2(m) +1 
	//����0---i�� i�����Ը����� n/2^i
	//��������������
	int level = log2(m);//����ȡ��
	int *b = new int[m];//ÿ������ż���
	for (int i = 0; i < m; i++) b[i] = 0;
	get_level(b, level,0,m-1); // b����ÿ��Ԫ�صļ�
	
	for (int i = 0; i < m; i++)
	{
		if (b[i]+1 > levels)
		{
			levels = b[i]+1;
			last[b[i]] = headerNode;
		}
		pair<K, E> thePair(make_pair(a[i], a[i]));
		skipNode<K, E>* newNode = new skipNode<K, E>(thePair,b[i]+1);
		for (int j = 0; j <= b[i]; j++)
		{//����i������
			newNode->next[j] = last[j]->next[j];
			last[j]->next[j] = newNode;
		}
	}
}

template<class K, class E>
void skipList<K, E>::get_level(int *b, int level, int low, int high)
{

	if (level <= 0) return;
	int mid = (low + high) / 2;
	if (mid == 0) return;
	if (b[mid] != 0) return;
	b[mid] = level;
	get_level(b, level - 1, mid, high);
	get_level(b, level - 1, low, mid);
}

template<class K, class E>
void skipList<K, E>::check(int count)
{
	if(need_reform==1)
	if (count >= (maxlevel + dSize + log2(dSize)) / 2)   // (maxlevel + dSize +log2(dSize))/2)
	{//�����ع�
		cout << "*****************************************************" << endl;
		cout << "�Ƚϴ������� �����ع�����" << endl;
		reform();
		cout << "*****************************************************" << endl;
	}
	else
	{
		return;
	}
	return;
}

template<class K, class E>
void skipList<K, E>::analyse()
{
	if (find_times != 0) {
		cout << "Total find nums: " << find_nums << endl;
		cout << "Averge find times: " << find_nums / find_times << endl;
	}
	else
	{
		cout << "Total find nums: " << find_nums << endl;
		cout << "Averge find times: " << 0 << endl;
	}
	if (insert_times != 0) {
		cout << "Total insert nums: " << insert_nums << endl;
		cout << "Averge insert times: " << insert_nums / insert_times << endl;
	}
	else
	{
		cout << "Total insert nums: " << insert_nums << endl;
		cout << "Averge insert times: " << 0 << endl;
	}
	if (erase_times != 0)
	{
		cout << "Total erase nums: " << erase_nums << endl;
		cout << "Averge erase times: " << erase_nums / erase_times << endl;
	}
	else
	{
		cout << "Total erase nums: " << erase_nums << endl;
		cout << "Averge erase times: " <<  0 << endl;
	}
	find_nums = 0;
	find_times = 0;
	insert_nums = 0;
	insert_times = 0;
	erase_nums = 0;
	erase_times = 0;
}



