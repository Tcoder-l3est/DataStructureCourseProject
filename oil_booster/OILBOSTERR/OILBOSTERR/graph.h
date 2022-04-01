#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<fstream>
#include<sstream>
#include<climits>
#include<string>
#include<windows.h>
#include<time.h>
#include<sys/timeb.h>
#include<math.h>
using namespace std;

#define ll long long 

//��ռ�: ĳ�㴦��booster 1 ���� ���� 0;
/*
3. �������һ����x , x�ж������e[1]..e[n] , x����ѹ��`p[x] = max(p[x], p[e[i].from] - e[i].cost) `
��x����ѹ��Ϊ����x����ѹ���е����ֵ
4. ͼ��ÿ�����ϵ��κ�һ�㶼Ҫ�ܵ��� , һ���ڵ��ѹ������󵽴�ѹ�� , ��
ÿ���߶���һ����Ч�Ĺܵ� ҲҪ������������
���� �������һ����x ,  x����ѹ��>Pmin , ������һ���� e , p[e.from] - e.cost < Pmin ��Ҳ�ǲ��Ϸ���
*/
//���Ӷ� O��2^n��
//�ռ� O(�·��) O(2^n��

ifstream fin;
ofstream fout;

struct btnode {//���ڷ�֧������Ӽ��� 
	btnode* parent;//ָ�򸸽ڵ�
	int press;//
	int level;//�Ӽ����㼶
	bool bst_here;//�Ƿ�ŷŴ���
	int bstnum;//���ȼ� �Ӹ����ڵ�x��·���ϵ�bst����
	int max_to_cost;
	btnode() {
		parent = NULL;
		press = 0; level = 0; bst_here = false;
		bstnum = 0;

	}
	btnode(int pres, int lev, btnode* par = NULL, int bstn = 0) {
		parent = par;
		press = pres; level = lev;
		bstnum = bstn;
		bst_here = false;
	}

};

class Edge {
public:
	int to;// �յ���
	int cost;// ����
	Edge(int to, int cost) : to(to), cost(cost) {}
	~Edge() {}
};

class inEdge {
public:
	int from;// �յ���
	int cost;// ����
	inEdge(int from, int cost) : from(from), cost(cost) {}
	~inEdge() {}
};


class Node {
public:
	vector<Edge> edges;//��¼���г���
	int press;
	bool booster;
	int max_to_cost;
	vector<inEdge> inedges;//��¼��� ��������press
	int toponum;//���������ǵڼ�
	Node() {
		press = 0;
		booster = false;
		edges.clear();
		inedges.clear();
		max_to_cost = 0;
		toponum = 0;
	}
	~Node() {}
};

struct cmp
{
	bool operator () (const btnode* p1, const btnode* p2) {
		return p1->bstnum > p2->bstnum;
	}
};

class DAG {
private:

	int Pmin, Pmax;//
	vector<Node> nodes;// �ڽӱ�
	vector<int> in_deg;
	vector<int> dig;//��������
	vector<bool> place_bst;//�Ƿ�Ҫ������
	priority_queue<btnode*, vector<btnode*>, cmp> pq;//��С��


public:
	int n, m;//������ ��
	DAG() {
		fin >> n >> m >> Pmax;
		Pmin = 0;
		best_ans = INT_MAX;
		nodes.clear();
		in_deg.resize(n + 1, 0);
		dig.resize(n + 1, 0);
		place_bst.resize(n + 1, false);

		//��ʼ������
		for (int i = 0; i <= n; i++)
			nodes.emplace_back(Node());
		//�����
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			fin >> u >> v >> w;
			nodes[u].edges.emplace_back(v, w);
			//�޸����
			in_deg[v]++;
			nodes[u].max_to_cost = max(nodes[u].max_to_cost, w);
			//�������
			nodes[v].inedges.emplace_back(u, w);
		}
		nodes[1].press = Pmax;
		place_bst[1] = true;
	}
	~DAG() {}
	int best_ans;//���Ž� ��Ŀ

	void visualize(int i);//���ӻ����
	void visualize2(int i);//���ӻ����
	void topsort();//���������� ��ȷ���Ⱥ��ϵ
	void recountpre();
	void output_bst();//���booster
	void backtracking(int level, int cnt);//���ݽ��
	void branch_bound();//��֧������

};

void DAG::topsort()
{//ȷ��һ���������� �Ա����
	int cnt = 1;
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (in_deg[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		nodes[u].toponum = cnt;
		dig[cnt++] = u;//����
		for (auto e : nodes[u].edges) {
			if (--in_deg[e.to] == 0)
				q.push(e.to);
		}
	}
	if (cnt < n) {
		cout << "ͼ���л�·��������Ҫ��\n";
		return;
	}
	//for (int i = 1; i <= n; i++) 
		//cout << "top " << i << " " << dig[i] << "\n";
}

// ������Ҫ�����������ܣ� dfs
void DAG::backtracking(int level, int cnt)
{//���л��ݾ��������� ���Ǹýڵ㲻�� �������Ƿ�
	//������level�� 
	int u = dig[level];//��ǰ�� levelҲ������������

	if (level >= n) {//��ײ���
		best_ans = min(cnt, best_ans);
		//��¼����õ���� ��Ȼ�ᱻ����
		//���·������
		for (int i = 1; i <= n; i++) {
			place_bst[i] = false;
			place_bst[i] = nodes[i].booster;
		}
		return;
	}

	if (level == 1) {//��һ�� Դ��϶����ˣ����㣩ֻ��Ҫ�ж������� ������� ����v��
		backtracking(2, 0);
	}
	else {//������  �����v ���� ���� u��
		int j;
		int flag = 0;
		int temp_pre = -1;//��ʱ����pre �������ݣ�

		//��press[u]  �Ż� �����
		//for (auto& c : nodes[u].inedges) {
		//	int f = c.from;
		//	if (nodes[f].toponum < nodes[u].toponum)
		//	{//������������ǰ���
		//		temp_pre = max(temp_pre, nodes[u].press - c.cost);
		//	}
		//}
		for (int k = 1; k < level; k++) {//�� ǰ�浽 
			for (auto& x : nodes[dig[k]].edges) {
				if (x.to == u)
					//nodes[u].press = max(nodes[u].press, nodes[dig[k]].press - x.cost);
					temp_pre = max(temp_pre, nodes[dig[k]].press - x.cost);
			}
		}

		for (j = 0; j < 2; j++)
		{//�������־���
			//��֦1
			if (temp_pre >= Pmax) {
				backtracking(level + 1, cnt);
				break;
			}
			//��֦2
			if (temp_pre < Pmin)
			{
				cnt++;
				nodes[u].booster = true;
				//��֦3
				if (cnt >= best_ans) {
					return;
				}
				backtracking(level + 1, cnt);
			}
			if (j == 0) {//���� ������Ҫ
				for (auto& v : nodes[u].edges) {//�������г��߽����ж�
					int next_pr = temp_pre - v.cost;
					if (next_pr < Pmin) {
						flag = 1;
						break;
					}
				}
			}
			//���� put
			if (j == 1 || flag == 1) {//��
				cnt++;
				nodes[u].press = Pmax;
				nodes[u].booster = true;
				//��֦
				if (cnt >= best_ans)
					return;
				else {
					backtracking(level + 1, cnt);
				}
			}
			//not put
			else if (j == 0) {//��Ӧ�� j==0 && flag!=1 
				nodes[u].press = temp_pre;
				nodes[u].booster = false;
				backtracking(level + 1, cnt);
			}
		}
	}
}

//��С�ķ� ��֧����
void DAG::branch_bound()
{//��֧���� ����--��չ���-- �Ӽ��ռ���
	btnode* enode = new btnode(Pmax, 2);//����
	int level = 2;
	while (level <= n - 1)
	{//���л������չ
		int vert = dig[level];//�ò���չ�Ľڵ�
		int temp_press = -1;
		int flag = 0;

		//����չ����ѹ��
		for (int k = 1; k <= level - 1; k++) {
			for (auto& e : nodes[dig[k]].edges) {
				if (e.to == vert) {
					btnode* p = enode;
					//????
					for (int j = level - 1; j > k; j--)
						p = p->parent;

					temp_press = max(temp_press, p->press - e.cost);
				}
			}
		}
		//�޽纯�� -��󻨷� С�����
		if (temp_press - nodes[vert].max_to_cost < Pmin) {
			flag = 1;
		}
		//check �� �ڽӵ��Ƿ����Ҫ��
		/*for (auto& e : nodes[vert].edges) {
			if (temp_press < Pmin + e.cost) {
				flag = 1; break;
			}
		}*/
		if (flag == 0) {//���� �Ż��߷�

			btnode* t = new btnode(temp_press, level + 1, enode, enode->bstnum);
			pq.push(t);
			btnode* tt = new btnode(Pmax, level + 1, enode, enode->bstnum + 1);
			tt->bst_here = true;
			pq.push(tt);
		}
		else {//�����
			btnode* tt = new btnode(Pmax, level + 1, enode, enode->bstnum + 1);
			tt->bst_here = true;
			pq.push(tt);
		}
		enode = pq.top(); pq.pop();
		level = enode->level;
	}
	best_ans = enode->bstnum;

	btnode* p = enode;
	while (p) {
		place_bst[dig[p->level - 1]] = p->bst_here;
		p = p->parent;
	}

}

void DAG::output_bst()
{
	for (int i = 1; i <= n; i++) {
		if (place_bst[i])
			cout << "node " << i << " \n";
	}
}

void DAG::visualize(int i)
{//���ӻ�
	recountpre();
	//system("cd C:\\Users\\12042\\Desktop\\dagData\\outputimage");
	string name = to_string(i) + ".dot";
	std::ofstream out(name);
	out << "digraph g {\n";
	for (int i = 1; i < nodes.size(); i++) {
		out << i;
		if (place_bst[i])
			out << "[label=\"node" << i << ";pre = " << nodes[i].press << "\",style=filled, fillcolor=red];\n";
		else
			out << "[label=\"node" << i << ";pre = " << nodes[i].press << "\",style=filled, fillcolor=white];\n";
	}
	for (auto i = 1; i <= n; ++i) {
		for (auto& edge : nodes[i].edges) {
			out << i << "->" << edge.to << "[label=\"cost=" << edge.cost << "\"];\n";
		}
	}
	out << "}\n";
	out.close();
	string order = "dot -Tjpg " + to_string(i) + ".dot -o solve" + to_string(i) + ".jpg";
	system(order.c_str());
}
void DAG::visualize2(int i)
{//���ӻ�
	recountpre();
	string name = to_string(i) + "-B.dot";
	std::ofstream out(name);
	out << "digraph g {\n";
	for (int i = 1; i < nodes.size(); i++) {
		out << i;
		if (place_bst[i])
			out << "[label=\"node" << i << ";pre = " << nodes[i].press << "\",style=filled, fillcolor=red];\n";
		else
			out << "[label=\"node" << i << ";pre = " << nodes[i].press << "\",style=filled, fillcolor=white];\n";
	}
	for (auto i = 1; i <= n; ++i) {
		for (auto& edge : nodes[i].edges) {
			out << i << "->" << edge.to << "[label=\"cost=" << edge.cost << "\"];\n";
		}
	}
	out << "}\n";
	out.close();
	//system("C:");
	//system("cd C:\\Users\\12042\\Desktop\\dagData\\outputimage");
	string order = "dot -Tjpg " + to_string(i) + "-B.dot -o solve-B" + to_string(i) + ".jpg";
	system(order.c_str());
}

void DAG::recountpre() {
	for (int i = 2; i <= n; i++) {
		int v = dig[i];
		if (place_bst[v]) {
			nodes[v].press = Pmax;
		}
		else {
			nodes[v].press = 0;
			for (int j = 1; j < i; j++) {
				for (auto& e : nodes[dig[j]].edges) {
					if (e.to == v) {
						nodes[v].press = max(nodes[v].press, nodes[dig[j]].press - e.cost);
					}
				}
			}
		}
	}

}

void check() {
	int flag = 0;
	stringstream ss;
	for (int i = 1; i <= 100; i++) {
		cout << "���ڲ������ݼ�: " << i << "\n";
		string opstd = "C:\\Users\\12042\\Desktop\\dagData\\outputSTD\\";
		string myin = "C:\\Users\\12042\\Desktop\\dagData\\output\\";
		opstd += to_string(i) + ".out";
		myin += to_string(i) + ".out";
		ifstream finstd(opstd);
		if (!finstd.is_open()) {
			cout << "�ļ���ʧ��\n";
		}
		int ans; finstd >> ans;
		finstd.close();

		ifstream finmy(myin);
		if (!finmy.is_open()) {
			cout << "�ļ���ʧ��\n";
		}
		int me; finmy >> me;
		finmy.close();
		if (me != ans) {
			cout << "Wrong Answer\n";
			ss << i << "WA��\n";
			flag = 1;
		}
		else {
			cout << "Accept\n";
		}
	}
	if (!flag) {
		cout << "All Accept!\n";
	}
	else cout << "Wrong Answer\n";
	cout << ss.str();
}


