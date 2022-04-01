#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
using namespace std;
typedef long long ll;

//ʹ�ô������ָ��Ķ����ֵ���


struct Node
{
	Node* parent;//ÿ���ڵ㶼Ҫ��¼���ڵ�
	Node* LeftChild;//ֻ��¼��һ������
	Node* sibiling;//ƽ�������
	int file_type;//0�ļ� 1Ŀ¼
	string file_name;//�ļ�����Ŀ¼����
	ll fnum;//���ļ���Ŀ
	ll file_size;//���ļ���С
	
	//���Ŀ¼�ļ���˵��
	ll all_mx;//Ŀ¼��� �� ������
	ll son_used;//���еĺ���ռ�Ĵ�С

	char power;//Ȩ��

	Node(int type, string fname, ll size = 0) {
		file_type = type; file_size = size;
		fnum = 0;
		parent = NULL; LeftChild = NULL;
		sibiling = NULL;
		file_name = fname;
		all_mx = 0;
		son_used = 0;
		power = 'p';//r�ǹ���ԱȨ��
	}
	~Node() {  }
	bool pre_add_size(ll size) {//Ԥ���� �ļ�
		if (all_mx && son_used + size > all_mx)
			return false;
		return true;
	}
	void add_size(ll size) {//Ԥ����ɹ��Ž������
		son_used += size;
	}
	void get_size() {
		if (file_type == 0) {
			cout <<"�ļ���С: "<<file_size<<"\n";//�ļ�
		}
		else
		{
			cout << "Ŀ¼����С: " << all_mx << " ʹ���� " << son_used << "\n";
		}
		
	}
	bool set_size(ll all) {//����һ����� ֻ��Ŀ¼����
		if (all < son_used) return false;

		return true;
	}

};

class CatalogTree
{
private:
	Node* root;
	Node* CurNode;//��ǰλ��
	char my_power;
public:
	CatalogTree();
	~CatalogTree() { delete root; };

	string outname;
	string inname;
	ifstream ffin;
	ofstream ffout;
	int put_flag;//�����cmd ���� file
	
	//����
	void dir();//�г���ǰĿ¼�µ�������Ŀ¼���ļ���
	void cd();//�۳���ǰĿ¼�ľ���·��
	void cd_recur(Node* now);
	void cd_back();//��ǰĿ¼��Ϊ��ǰĿ¼�ĸ�Ŀ¼��
	void cdstr(string& str);//��ǰĿ¼��ΪSTR����ʾ·����Ŀ¼
	void mkdir(string& str);//�ڵ�ǰĿ¼�´���һ����Ŀ¼str����������򲻽����κβ���
	void mkfile(string& str);//�ڵ�ǰĿ¼�´���һ���ļ��������ڲ����С�
	void delet(string& str);//ɾ����ǰĿ¼������ΪSTR��Ŀ¼�����ļ�����������ڣ������в���
	void deletenode(Node* now);
	void save(string& str);//���Ӹ��ڵ㿪ʼ��Ŀ¼���ṹ���浽�ļ���
	void save_recur(ofstream& fout, Node* now, int depth);//�ݹ鱣��
	void load(string& str);//���ļ�STR�ж�ȡ֮ǰ�����Ŀ¼���ṹ�����Ҹ��������½�����ǰ��Ŀ¼��
	void load_recur(ifstream& fin, int depth);
	void read_data(int num);
	
	//size
	void mkfile_size(string& str, ll size);//make file with ��С����  str���·��
	void setdir_size(ll all_mx);//����ǰ ԭ�е� Ŀ¼�ļ��������
	void remove_size(string& str);//ɾ���ļ�����Ŀ¼
	
	//����
	void cd_root();//�ص�root
	void mkdir_p(string& str);//���д������Ŀ¼
	void put_size() { CurNode->get_size(); }//��ȡ��ǰĿ¼�����

   //Ȩ��
	void _r() { my_power = 'r'; }
	void _p() { my_power = 'p'; }
	void mkdir_r(string& str);//������Ȩ�޵�Ŀ¼
	void mkfile_r(string& str);//������Ȩ�޵��ļ�
	void delet_r(string& str);
	
	
    //��չ�ļ�����
	//����
	void mv_a2b(string &a,string &b);//��a�ƶ���b
	//����
	void cp_a2b(string& a, string& b);//�ѵ�ǰĿ¼�µ�a ���Ƶ�b�� b�²�����������
	void cp_r(Node *t);//�ݹ鿽���ڵ�
};

