#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include"CatalogTree.h"
using namespace std;
typedef long long ll;
const ll MAXN = 1e8;

vector<string> split(const string& str, char c)
{
	vector<string> res;//��ָ����string����
	string temp;
	for (auto i : str)
	{
		if (i == c) res.push_back(temp), temp.clear();
		else temp += i;
	}
	if (!temp.empty()) res.push_back(temp);
	return res;
}

CatalogTree::CatalogTree()
{//���췽��
	delete root;
	root = new Node(1, "/");//��Ŀ¼ ��/
	CurNode = root;
	put_flag = 1;//1Ĭ��Ϊ������ļ� 0�����cmd
	my_power = 'p';//person
}

//dir ��Ҫ�����ֵ������  ����������ļ�  ���ļ���
void CatalogTree::dir()
{//�г���ǰĿ¼�µ�������Ŀ¼���ļ���
//������ɨ ������� �ļ������* Ŀ¼����
//dir��������˳�����ֵ������У�����������ļ�����������ļ�������
	map<string, int> file_mp;
	map<string, int> dir_mp;
	Node* now = CurNode->LeftChild;
	for (; now != NULL; now = now->sibiling) {
		if (now->file_type == 0) {//�ļ�
			string s = now->file_name + "*\n";
			file_mp[s] = 0;
		}
		else if (now->file_type == 1) {//Ŀ¼
			string s = now->file_name + "\n";
			dir_mp[s] = 1;
		}
	}
	//���:
	for (auto s : file_mp) {
		if(put_flag)
			ffout << s.first;
		else 
			cout << s.first;
	}
	for (auto s : dir_mp) {
		if (put_flag)
			ffout << s.first;
		else
			cout << s.first;
	}
}

void CatalogTree::cd_recur(Node* now) {//�ݹ� ��Ϊ�����Ȼص��������
	if (now == root) {
		if (put_flag)
			ffout << "/";
		else
			cout << "/";
		return;
	}
	else {//�ݹ鵽��
		cd_recur(now->parent);
		if (now->parent == root) {
			if (put_flag)
				ffout << now->file_name;
			else
				cout << now->file_name;
		}
		else
			if (put_flag)
				ffout << "/" << now->file_name;
			else
				cout << "/" << now->file_name;
	}
}

void CatalogTree::cd_back()
{//�ص�����Ŀ¼
	if (CurNode == root) {
		//cout << "�Ѿ��Ǹ�Ŀ¼!\n";
		return;
	}
	CurNode = CurNode->parent;
	return;
}

void CatalogTree::cdstr(string& str)
{//STR�����Ǿ���·�� Ҳ������ ���·��  Ҫ�ı�CurNode
	Node* now;
	if (str[0] == '/') {//����·��
		Node* t = root;
		vector<string> res = split(str, '/');
		int flag;
		for (int i = 0; i < res.size(); i++) {
			string s = res[i];
			if (s != "") {
				flag = 0;
				for (now = t->LeftChild; now != NULL; now = now->sibiling) {
					if (now->file_name == s && now->file_type == 1)
					{//�ҵ��˸�Ŀ¼
						t = now;//�ı�CUR
						flag = 1;
						break;
					}
				}
				if (!flag) {
					//��һ��û�ҵ�
					if(put_flag)
						ffout << "·������δ�ҵ���\n";
					else
						cout << "·������δ�ҵ���\n";

					
					return;
				}
			}
		}
		//����copy Ϊ�˷�ֹ�д���·�� 
		//���Խ�Curͣ���������ڵ���ȷĿ¼��
		CurNode = t;
	}
	else {//���·��
		vector<string> res = split(str, '/');
		Node* copy_cur = CurNode;
		int flag;
		for (int i = 0; i < res.size(); i++) {
			string s = res[i];
			flag = 0;
			if (s != "") {
				for (now = copy_cur->LeftChild; now != NULL; now = now->sibiling) {
					if (now->file_name == s && now->file_type == 1)
					{//�ҵ��˸�Ŀ¼
						copy_cur = now;//�ı�CUR
						flag = 1;
						break;
					}
				}
				if (!flag) {
					//û�ҵ� ��һ��û�� �Ͳ���
					if (put_flag)
						ffout << "���·������δ�ҵ���\n";
					else
						cout<< "���·������δ�ҵ���\n";
					return;
				}
			}
		}
		CurNode = copy_cur;

	}
}

void CatalogTree::cd()
{//�г���ǰĿ¼�ľ���·��
	cd_recur(CurNode);
	if (put_flag)
		ffout << "\n";
	else cout << "\n";
}

void CatalogTree::mkdir(string& str)
{//����һ��Ŀ¼
	Node* now;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//���ֵ�����������
		if (now->file_name == str && now->file_type == 1)
		{//������
			if(put_flag)
				ffout << "��Ŀ¼�Ѿ����ڣ�\n";
			else
				cout<< "��Ŀ¼�Ѿ����ڣ�\n";
			return;
		}
	}
	now = new Node(1, str, MAXN);
	now->parent = CurNode;
	now->file_size = 0;//Ŀ¼�ļ��޴�С
	now->all_mx = MAXN;
	now->son_used = 0;
	now->sibiling = CurNode->LeftChild;//����
	CurNode->LeftChild = now;
}

void CatalogTree::mkfile(string& str)
{//�ڵ�ǰĿ¼�� ����һ���ļ�  ��������ļ���
	Node* now = CurNode->LeftChild;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//���ֵ�����������
		if (now->file_name == str && now->file_type == 0)
		{//������
			if(put_flag)
				ffout << "���ļ��Ѿ����ڣ�\n";
			else
				cout<< "���ļ��Ѿ����ڣ�\n";
			return;
		}
	}
	now = new Node(0, str, 0);
	now->parent = CurNode;
	now->file_size = 0;
	now->sibiling = CurNode->LeftChild;//����
	CurNode->LeftChild = now;
	//�����ڵ��ǵ�size
	for (auto t = CurNode; t != NULL; t = t->parent) {
		t->fnum++;
	}
}

void CatalogTree::delet(string& str)
{//ɾ����ǰĿ¼������Ϊstr��Ŀ¼�����ļ�
	Node* now;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		if (now->file_name == str) {
			if (now->power == 'r'&&my_power!='r') {
				cout << "Ȩ�޲�����\n";
				return;
			}
			deletenode(now);
			return;
		}
	}
	//û�ҵ�
	ffout << "can't find file or dir\n";
	return;
}

void CatalogTree::deletenode(Node* t)
{//���о����ɾ��
	if (t->power == 'r' && my_power != 'r') {
		cout << "Ȩ�޲�����\n";
		return;
	}


	if (t->file_type == 0) {//���Ҫɾ���ļ�
		Node* now = t->parent->LeftChild;//��λ������
		if (t == now) {//���ɾ���������ӣ�����Ҫ�ĸ��ڵ�ָ��
			t->parent->LeftChild = now->sibiling;
			delete t;
			return;
		}

		for (auto now = t->parent->LeftChild; now != NULL; now = now->sibiling) {
			if (t == now->sibiling) {
				now->sibiling = t->sibiling;
				delete t;
				return;
			}
		}

	}
	else {//ɾ������Ŀ¼ 
		if (t->LeftChild != NULL) {//dir����file �ݹ�ɾ��
			while (t->LeftChild != NULL)
			{
				for (auto now = t->LeftChild; now != NULL; now = now->sibiling) {
					if (now->sibiling == NULL) {
						deletenode(now);
						break;
					}
				}
			}
			deletenode(t);
		}
		else {
			if (t->LeftChild == root) return;
			if (t->parent->LeftChild == t) t->parent->LeftChild = t->sibiling;
			else {
				for (auto now = t->parent->LeftChild; now != NULL; now = now->sibiling) {
					if (t == now->sibiling) {
						now->sibiling = t->sibiling;
						return;
					}
				}
			}
			delete t;
		}
	}
}

void CatalogTree::save(string& str)
{//����Ҫ���� CURNODE����
	//str = str + ".txt";
	ofstream fout(str);
	if (!fout.is_open()) {
		cout << "�ļ���ʧ�ܣ�\n";
		return;
	}
	else {//��Ŀ¼�� �����ļ�
		save_recur(fout, root, 0);
		//����һ��END ������־ 
		fout << "END\n";
		fout << "CUR:";
		fout.close();
		string oname = outname;
		ffout.close();
		ffout.open(str, ios::app);
		cd();
		ffout.close();
		ffout.open(oname, ios::app);
		cout << "save success";
	}
}

void CatalogTree::save_recur(ofstream& fout, Node* now, int depth)
{//ǰ�漸�� |  �ͼ���Ŀ¼  ǰ��
	if (now != NULL) {
		//��־����һ���ļ�
		for (int i = 0; i <= depth; i++) {
			fout << "|";
		}
		if (now->file_type == 0) {//�ļ�
			fout << now->file_name << "\n";
		}
		else if (now->file_type == 1) {//Ŀ¼
			fout << "-" << now->file_name << "\n";
		}
		if (now->file_type == 1) {//Ŀ¼�ļ���������ļ��Ļ�
			for (auto t = now->LeftChild; t != NULL; t = t->sibiling) {
				save_recur(fout, t, depth + 1);
			}
		}
	}
}

//���� | ����ڼ��� �����- ˵����Ŀ¼ û��˵�����ļ�
int judge_depth(string& str) {
	int cnt = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '|') cnt++;
		else break;
	}
	return cnt;
}

void CatalogTree::load(string& str)
{//���ļ����� ��Ŀ¼����������
	//Ŀ¼�ͼ��� ����
	//str += ".txt";
	ifstream fin(str);
	string s;
	if (!fin.is_open()) {
		cout << "�ļ���ʧ��! �޷����� ! \n";
		fin.close();
		return;
	}
	else {
		getline(fin, s);//����һ�� Ϊ����
		delete root;
		root = new Node(0, "/");
		CurNode = root;//CurNode �ص���Ŀ¼��
		load_recur(fin, 1);

		getline(fin, s);
		string str = s.substr(4);
		cdstr(str);//��curnode
		fin.close();
		if(put_flag)
			ffout << "load success !\n";
		else cout << "load success !\n";
		return;
	}
}

void CatalogTree::load_recur(ifstream& fin, int depth)
{//�ݹ���� 
	string s; getline(fin, s);
	if (s != "END") {//û����ĩβ

		int deep = judge_depth(s);
		//deal with CurNode
		for (int i = deep; i < depth; i++) {//��ǰ��
			cd_back();//Ȼ��ص�ԭ����Ŀ¼��
		}

		if (s[deep] == '-') {//Ŀ¼
			//Ŀ¼����
			string str = s.substr(deep + 1);
			mkdir(str);
			//֮������Ŀ¼ Ȼ����еݹ�
			cdstr(str);
			load_recur(fin, deep + 1);
		}
		else {//�ļ�
			string str = s.substr(deep);
			mkfile(str);
			load_recur(fin, deep);
		}

	}
}

void CatalogTree::read_data(int num)
{
	inname = "in" + to_string(num) + ".txt";
	outname = "out" + to_string(num) + ".txt";

	ffin.open(inname);
	ffout.open(outname, ios::app);
}

void CatalogTree::mkfile_size(string& str, ll size)
{//�������ļ� ����Ӹ���ʼ�ж� ��Ϊ��� ���������� ǰ��Ҳ��һ������
	Node* now = CurNode->LeftChild;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//���ֵ�����������
		if (now->file_name == str && now->file_type == 0)
		{//������
			if (put_flag)
				ffout << "���ļ��Ѿ����ڣ�\n";
			else
				cout << "���ļ��Ѿ����ڣ�\n";
			return;
		}
	}


	if (CurNode->son_used+size > CurNode->all_mx) {
		cout << "���������Ҫ��! ���̫��!\n";
		return;
	}
	else {
		now = new Node(0, str, size);
		now->parent = CurNode;
		now->sibiling = CurNode->LeftChild;//����
		CurNode->son_used += size;
		now->file_size = size;
		CurNode->LeftChild = now;
	}
	
	//�����ڵ��ǵ�fnum
	for (auto t = CurNode; t != NULL; t = t->parent) {
		t->fnum++;
	}
}

void CatalogTree::setdir_size(ll all_mx)
{//ֻ�޸� Ŀ¼����� һ���� Ȼ�� ÿ��
	if (CurNode->file_type != 1) {
		cout << "ֻ�ܶ�Ŀ¼�ļ��������!\n";
		return;
	}
	if (CurNode->parent->son_used + all_mx > CurNode->all_mx) {
		cout << "�������̫Сn";
		return;
	}
	if (CurNode->son_used > all_mx) {
		cout << "�������̫Сn";
		return;
	}
	CurNode->all_mx = all_mx;
	cout << "����ɹ���\n";
	return;
}

void CatalogTree::remove_size(string& str)
{

}

void CatalogTree::cd_root()
{
	CurNode = root;
}

void CatalogTree::mkdir_r(string& str)
{
	Node* now;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//���ֵ�����������
		if (now->file_name == str && now->file_type == 1)
		{//������
			if (put_flag)
				ffout << "��Ŀ¼�Ѿ����ڣ�\n";
			else
				cout << "��Ŀ¼�Ѿ����ڣ�\n";
			return;
		}
	}
	now = new Node(1, str);
	now->parent = CurNode;
	now->file_size = 0;//Ŀ¼�ļ��޴�С
	now->power = 'r';
	now->sibiling = CurNode->LeftChild;//����
	CurNode->LeftChild = now;
}

void CatalogTree::mkdir_p(string& str)
{//���ɶ༶Ŀ¼ ���봫�����·�� ����·���� ������ھ�ֱ�ӽ��� �����ھ��½�
	vector<string> res = split(str, '/');
	int flag;
	Node* now;
	Node* t = root;
	for (int i = 0; i < res.size(); i++) {
		string s = res[i];
		if (s != "") {
			flag = 0;
			for (now = t->LeftChild; now != NULL; now = now->sibiling) {
				if (now->file_name == s && now->file_type == 1)
				{//�ҵ��˸�Ŀ¼
					flag = 1;
					t = now;//�ı�CUR
					break;
				}
			}
			if (!flag) {
				//û�ҵ� ���½�
				CurNode = t;
				mkdir(s);
				t = CurNode->LeftChild;
			}
		}
	}

	CurNode = t;
	cout << "mkdir-p success\n";
}

void CatalogTree::mkfile_r(string& str)
{
	Node* now = CurNode->LeftChild;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//���ֵ�����������
		if (now->file_name == str && now->file_type == 0)
		{//������
			if (put_flag)
				ffout << "���ļ��Ѿ����ڣ�\n";
			else
				cout << "���ļ��Ѿ����ڣ�\n";
			return;
		}
	}
	now = new Node(0, str, 1);
	now->parent = CurNode;
	now->sibiling = CurNode->LeftChild;//����
	now->power = 'r';
	CurNode->LeftChild = now;
	//�����ڵ��ǵ�nums
	for (auto t = CurNode; t != NULL; t = t->parent) {
		t->fnum++;
	}
}

void CatalogTree::delet_r(string& str)
{
	my_power = 'r';
	delet(str);
	my_power = 'p';
}

void CatalogTree::mv_a2b(string& a, string& b)
{//����ǰĿ¼�� a �����ļ�����Ŀ¼ ת�Ƶ� b ·����  �����Ǹ�Ŀ¼
	//�ҵ�a Ȼ�󱣴�һ��ָ�� �ҵ�bֱ����ָ�������
	if (a == "/") {
		cout << "�����ƶ���Ŀ¼\n";
		return;
	}
	Node* now;

	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		if (now->file_name == a) {
			if (now->power == 'r' && my_power != 'r') {
				cout << "Ȩ�޲�����\n";
				return;
			}
			//�ҵ����ļ���
			if (now == now->parent->LeftChild) {
				now->parent->LeftChild = now->sibiling;
			}
			vector<string> sons=split(b,'/');
			for (auto s : sons) {
				if (s == now->file_name) {
					cout << "���ܽ���Ŀ¼�ƶ�����Ŀ¼��!\n";
					return;
				}
			}
			cdstr(b);//�޸�CurNode
			now->sibiling = CurNode->LeftChild;
			CurNode->LeftChild = now;
			now->parent = CurNode;
			//������ļ�����Ŀ¼
			cout << "move success!\n";
			return;
		}
	}
	//û�ҵ�
	ffout << "can't find file or dir\n";
	return;
}

void CatalogTree::cp_a2b(string& a, string& b)
{//���� ���ҵ�a �ļ�����Ŀ¼ ֮���� ������Ҫ�ݹ鸴��
//֮�� ��cd b ����û�������� û�� ��ֱ�� ���������
	if (a == "/") {
		cout << "���ܸ��Ƹ�Ŀ¼\n";
		return;
	}
	Node* now;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		if (now->file_name == a) {
			if (now->power == 'r' && my_power != 'r') {
				cout << "Ȩ�޲�����\n";
				return;
			}
			//�ҵ����ļ���
			//���Ƹýڵ�
			Node* t = CurNode;//��¼ԭ����curNode
			//CurNode ��������
			Node* scanNode = now;//����ɨnow�Ǳ�
			cdstr(b);//�޸�CurNode
			//check û��a
			for (auto checknode = CurNode->LeftChild; 
				checknode != NULL; 
				checknode = checknode->sibiling) {
				if (checknode->file_name == a && checknode->file_type == now->file_type) {
					cout << "Ŀ¼��" << b << " �£��Ѿ����� " << a << " �����Ը��ƣ�\n";
					return;
				}
			}
			cp_r(now);
			cdstr(b);//�޸�CurNode
			
			//������ļ�����Ŀ¼
			cout << "copy success!\n";
			return;
		}
	}
	//û�ҵ�
	ffout << "can't find file or dir\n";
	return;
}

void CatalogTree::cp_r(Node* t)
{//t��Ҫ���ƵĽڵ� scanode������ɨ��Ҫ���ƵĽڵ���ӽڵ�
	if (t->power == 'r' && my_power != 'r') {
		cout << "Ȩ�޲�����\n";
		return;
	}

	if (t->file_type == 0) {//����ļ�
		mkfile(t->file_name);
	}
	else {//���Ƶ���Ŀ¼ 
		mkdir(t->file_name);
		cdstr(t->file_name);

		for (auto now = t->LeftChild; now != NULL; now = now->sibiling) {
			if (now->file_type == 1) {//Ŀ¼
				cp_r(now);
				break;
			}
			else
			{
				mkfile(now->file_name);
			}
		}
		
		cd_back();
	}
}





