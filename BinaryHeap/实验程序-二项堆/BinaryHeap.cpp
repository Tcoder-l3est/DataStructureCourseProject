#include"BinaryHeap.h"
#include<bits/stdc++.h>
using namespace std;


/*  ���عؼ�����С�Ľڵ�
         O(logn)       */
template <typename K, typename V, typename Compare>
BinaryHeapNode<K,V>* BinaryHeap<K, V, Compare>::Find_Min()
{//��С��һ���ڸ����� ɨ��
	if (Root == NULL) {
		if(putflag)
			cout << "empty\n";
		else fout<< "empty\n";
		return NULL;
	}
	bnode* minPtr = NULL;
	bnode* scan = Root;
	K min_k = INT_MAX;
	while (scan != NULL) {
		if (compare(scan->key, min_k)) {
			min_k = scan->key;
			minPtr = scan;
		}
		scan = scan->sibiling;
	}
	return minPtr;
}


/*    �ϲ����������
		 O(logn)       */
template <typename K, typename V, typename Compare>
void BinaryHeap<K,V,Compare>::Union(Bheap& Heap)
{//���жѺϲ�
	//�Ⱥϲ�����
	//�жϷǿ�
	/*if (Heap.Root == NULL) {
		return;
	} 
	if (Root == NULL) {
		Root = Heap.Root;
		Heap.Root = NULL;
		return;
	}*/

	Merge_Root(Heap);
	if (Root == NULL) {
		cout << "��������ʧ�ܣ�\n";
		return;
	}
	//ɨ��ָ��
	bnode* prex = NULL;
	bnode* cur = Root;
	bnode* next = Root->sibiling;

	while (next != NULL) {//����ÿ���������ĸ�
		if ((cur->degree != next->degree) || (next->sibiling != NULL
			&& next->sibiling->degree == cur->degree)) {
			//��ǰ������һ�����Ȳ��ȣ� �������������Ķ���������ȡ�
			//����Ҫָ��Ǩ��
			prex = cur; cur = next;
		}
		else if (compare(cur->key, next->key)) {
			//����������Ķ���� ��cur�ĸ�key С
			cur->sibiling = next->sibiling;
			treeLink(next, cur);//next ��Ϊ cur����
		}
		else {//next keyС cur ��Ϊnext ������
			if (prex == NULL) Root = next;
			else
				prex->sibiling = cur->sibiling;
			treeLink(cur, next);
			cur = next;
		}
		next = cur->sibiling;
	}
}


/*    �ϲ����� �����ǵݼ�
		 O(logn)       
	                   */
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::Merge_Root(Bheap& Heap)
{
	if (Heap.Root == NULL) {
		return;
	}
	if (Root == NULL) {
		Root = Heap.Root;
		Heap.Root = NULL;
		return;
	}
	//ʹ������ָ��ɨ��
	bnode* pa = Root, *pb = Heap.Root, *tail = NULL;
	Root = NULL; Heap.Root = NULL;
	while (pa != NULL && pb != NULL) {
		//�������� until��һ��Ϊ��
		if (pa->degree <= pb->degree) {
			lineAtTail(tail, pa);//β�˲���
			pa = pa->sibiling;
		}
		else {
			lineAtTail(tail, pb);
			pb = pb->sibiling;
		}
	}
	//���Ǹ�����ʣ�µ�
	if (pa != NULL) {
		tail->sibiling = pa;
	}
	else if (pb != NULL) {
		tail->sibiling = pb;
	}
	else {//��ûʣ��
		tail->sibiling = NULL;
	}

}


/*    ����һ����Ԫ��
		 O(logn)
					   */
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::insert(pair<K, V> x)
{
	/*if (check_exist(x)) {
		cout<< "��Ԫ���Ѿ�����,��ֹ���룡\n";
		return;
	}*/
	size++;
	bnode* cur = new bnode(x);
	if (Root == NULL) Root = cur;
	else {
		Bheap H(cur, compare);
		Union(H);
	}
}


/*   �Ӷ���ɾ����С/�� KEYԪ�أ����ҷ���ɾ��Ԫ�ص�ָ��
		 O(logn)
		����pairָ��			   */
template <typename K, typename V, typename Compare>
pair<K,V>* BinaryHeap<K, V, Compare>::Extract_Min()
{
	if (Root == NULL) {
		if(putflag)
			cout << "empty\n";
		else fout<< "empty\n";

		return NULL;
	}
	bnode* minptr = NULL, * pre = NULL, * cur = Root;
	K mink = Root->key;//��ʼ ������ֵ
	while (cur->sibiling != NULL) {//����������ֵ
		if (compare(cur->sibiling->key, mink)) {
			mink = cur->sibiling->key;
			pre = cur;
		}
		cur = cur->sibiling;
	}
	if (pre == NULL) {//ֻ��һ��Ԫ�� ���߸�Ϊ����
		minptr = Root;
		Root = Root->sibiling;
	}
	else {//���� 
		minptr = pre->sibiling;
		pre->sibiling = minptr->sibiling;
	}
	Bheap h(minptr->LeftChild, compare);//��Сֵ ��ȥ���� ��
	h.reverse();
	Union(h);//�ٺϲ���ȥ
	pair<K, V> rv = pair<K, V>(minptr->key, minptr->data);
	delete minptr;
	size--;
	return &rv;
}


/*�Ա�ɾ���Ĳ��ֽ������� ����ϲ�
		 O(logn)
						*/
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::reverse() {
	bnode* cur = Root,*rcur;
	Root = NULL;
	while (cur != NULL) {
		cur->parent = NULL;//��һ��
		rcur = cur;
		cur = cur->sibiling;
		if (Root == NULL) {
			Root = rcur;
			rcur->sibiling = NULL;
		}
		else {
			rcur->sibiling = Root;
			Root = rcur;
		}
	}
}


/*    Ԫ��X�ؼ��ָ�����ֵ(��С)
		 O(logn)
	                    */
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::Decrease_Key(K oldkey, K newk)
{//��ֵ�� ���� ������������

	if (!compare(newk, oldkey)) {
		if (putflag == 1)
			cout << "new key is greater! Refuse!\n";
		else fout << "new key is greater! Refuse!\n";
		return;
	}

	bnode* x = Find(Root,oldkey);
	if (x == NULL) {
		if(putflag == 1)
			cout << "not exist can't decrease!\n";
		else fout << "not exist can't decrease!\n";
		return;
	}
	
	x->key = newk;
	//ֻ��Ҫ����ֵ������
	bnode* z = x->parent, * y = x;
	while (z != NULL && z->key > y->key) {
		swap(z->key, y->key);
		y = z;
		z = y->parent;
	}

	//bnode* par = x->parent, * xs = x->sibiling;
	//����
	//while (par != NULL && compare(x->key, par->key)) {
	//	//��������
	//	//������ ��Ҫ�������ֵ�
	//	x->sibiling = par->sibiling;
	//	par->sibiling = xs;
	//	//��� X is ĳ�����м�
	//	bnode* x_pre=find_pre(x), *par_pre=find_pre(par);
	//	if (x_pre != NULL) {
	//		x_pre->sibiling = par;
	//	}
	//	if (par_pre != NULL) {
	//		par_pre->sibiling = x;
	//	}
	//	if (par->parent != NULL && par->parent->LeftChild == par) {
	//		par->parent->LeftChild = x;//��� X����ȥ��������
	//	}
	//	//�޸�X ����
	//	bnode* x_child = x->LeftChild;
	//	if (x->parent->LeftChild == x) {//x������
	//		x->LeftChild = par;
	//	}
	//	else {
	//		x->LeftChild = par->LeftChild;
	//		par->LeftChild->parent = x;
	//	}
	//	x->parent = par->parent;
	//	par->parent = x;
	//	//�޸�par ����
	//	par->LeftChild = x_child;
	//	if (x_child != NULL) {
	//		x_child->parent = par;
	//	}
	//	swap(x->degree, par->degree);//��������
	//	par = x->parent;
	//}

}


/*    ɾ���ؼ���ΪKey�Ľڵ�
		 O(logn)+O(n)
						*/
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::Delete(K KEY)
{
	bnode* x = Find(Root,KEY);
	if (x == NULL) {
		if(putflag == 1)
			cout << "not exist! can't delete��\n";
		else 
			fout << "not exist! can't delete��\n";
		return ;
	}

	Decrease_Key(x->key, INT_MIN);
	Extract_Min();
	
}

template<typename K, typename V, typename Compare>
BinaryHeapNode<K, V>* BinaryHeap<K, V, Compare>::Find(bnode* t, K KEY)
{
	bnode* cur = t, * x = NULL;
	while (cur != NULL) {
		if (cur->key == KEY)
			return cur;
		else {
			x = Find(cur->LeftChild, KEY);
			if (x != NULL) {//�ݹ���
				return x;
			}
			cur = cur->sibiling;
		}
	}
	return NULL;//û�ҵ�
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::Post(bnode* x)
{//�������
	bnode* cur = x;
	while (cur != NULL) {
		Post(cur->LeftChild);
		cout << "key is " << cur->key << "\ndata is " << cur->data
			<< "\ndegree is " << cur->degree << "\n";
		cur = cur->sibiling;
	}
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::preTravel(bnode* x)
{//ǰ�����
	bnode* cur = x;
	if (cur != NULL) {
		cout << "key is " << cur->key << "\ndata is " << cur->data
			<< "\ndegree is " << cur->degree << "\n";
		if (cur->LeftChild != NULL) {
			for (bnode* t = cur->LeftChild; t != NULL; t = t->sibiling) {
				preTravel(t);
			}
		}
	}
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::preT()
{
	for (bnode* t = Root; t != NULL; t = t->sibiling) {
		preTravel(t);
	}
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::levelTravel()
{//��α���
	queue< bnode* > q; q.push(Root);
	while (!q.empty()) {
		bnode* cur = q.front(); q.pop();
		bnode* t = cur;
		while (t->sibiling !=NULL)
		{
			q.push(t->sibiling);
			t = t->sibiling;
		}
		if (cur->LeftChild != NULL) q.push(cur->LeftChild);

		cout << "key is " << cur->key << "\ndata is " << cur->data
			<< "\ndegree is " << cur->degree << "\n";

	}
}

template<typename K, typename V, typename Compare>
bool BinaryHeap<K, V, Compare>::check_exist(pair<K,V> p)
{
	queue< bnode* > q; q.push(Root);
	while (!q.empty()) {
		bnode* cur = q.front(); q.pop();
		if (cur->key == p.first) {
			return true;
		}

		bnode* t = cur;
		while (t->sibiling != NULL)
		{
			q.push(t->sibiling);
			t = t->sibiling;
		}
		if (cur->LeftChild != NULL) q.push(cur->LeftChild);

	}
	return false;
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::visualize(string filename) {
	//dot��ͼ �������ڵ� Ȼ��ָ����ɫ
	int i = -1;
	fstream fo(filename+".dot", ios::out);
	fo << "digraph g{" << "\n";
	bnode* r = Root;
	string str;
	if (r != NULL) {
		str += "{rank=\"same\";" + to_string(r->key) + ';';
	}
	while (r != NULL) {
		queue<bnode* > q;
		q.push(r);
		while (q.size()) {
			string ss= "{rank=\"same\";";
			bnode* e = q.front(); q.pop();
			bnode* child = e->LeftChild;
			while (child != NULL) {
				fo << e->key << "->" << child->key<< "[color = blue]";
				q.push(child);
				if (child->sibiling != NULL) {
					fo << ";\n";
				}
				else fo << "[weight=10][color=blue]; \n";
				ss += to_string(child->key) + ";";
				child = child->sibiling;
			}
			ss += "};\n";
			fo << ss << endl;
		}
		bnode* temp = r;
		r = r->sibiling;
		if (r != NULL) {
			fo << temp->key << "->" << r->key << "[color=blue];" << '\n' << endl;
			str += to_string(r->key) + ";";
		}
	}
	str += "};\n";
	fo << str << endl;
	if (i != -1)
		fo << i << "[label=\" dest: " << i << "\",style=filled, fillcolor=green]" << endl;
	fo << "}" << endl;
	string sss = "dot -Tjpg " + filename + ".dot -o " + filename + ".jpg";
	system(sss.c_str());
}
