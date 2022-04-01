#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include"CatalogTree.h"

using namespace std;
typedef long long ll;
//ʹ�ô������ָ��Ķ����ֵ���


void op1(int num,int put_f) {
	string s;
	CatalogTree ct;
	ct.put_flag = put_f;
	ct.read_data(num);
	while (getline(ct.ffin, s)) {
		if (s == "dir") {
			ct.dir();
		}
		else if (s == "cd") {
			ct.cd();
		}
		else if (s == "cd ..") {//cd..
			ct.cd_back();
		}
		else if (s[0] == 'c' && s[1] == 'd' && s[3] != '.') {
			string str = s.substr(3);
			ct.cdstr(str);
		}
		else if (s.substr(0, 5) == "mkdir") {
			string str = s.substr(6);
			ct.mkdir(str);
		}
		else if (s.substr(0, 6) == "mkfile") {
			string str = s.substr(7);
			ct.mkfile(str);
		}
		else if (s.substr(0, 6) == "delete") {
			string str = s.substr(7);
			ct.delet(str);
		}
		else if (s.substr(0, 4) == "save") {
			string str = s.substr(5);
			ct.save(str);
		}
		else if (s.substr(0, 4) == "load") {
			string str = s.substr(5);
			ct.load(str);
		}
		else if (s == "quit") {
			cout << "�������˳�\n";
			break;
		}
		else {
			cout << "wrong ops!\n";
		}
	}
}
void op2() {
	string s;
	CatalogTree ct;
	ct.put_flag = 0;
	cout << "***********************************************************\n";
	cout << "dir         \t\t\t\t�г���ǰĿ¼������Ŀ¼��\n";
	cout << "cd          \t\t\t\t�г���ǰ·��\n";
	cout << "cd str		 \t\t\t\t��ǰĿ¼��Ϊstr����ʾ·����Ŀ¼\n";
	cout << "cd ..		 \t\t\t\t��ǰĿ¼��Ϊ��ǰĿ¼�ĸ�Ŀ¼\n";
	cout << "cd ~		 \t\t\t\t�ص���Ŀ¼\n";
	cout << "mkdir str	 \t\t\t\t�ڵ�ǰĿ¼�´���һ����Ϊstr��Ŀ¼\n";
	cout << "mkfile str	 \t\t\t\t�ڵ�ǰĿ¼�´���һ����Ϊstr���ļ�\n";
	cout << "delete str	 \t\t\t\tɾ����ǰĿ¼����Ϊstr��Ŀ¼���ļ�\n";
	cout << "save str	 \t\t\t\t��������Ŀ¼��str�ļ���\n";
	cout << "load str	 \t\t\t\t����str�ļ��е�����Ŀ¼\n\n";

	cout << "-r			 \t\t\t\tϵͳȨ�ޱ�ΪrootȨ��\n";
	cout << "-p			 \t\t\t\tϵͳȨ�ޱ�Ϊ'p'Ȩ��\n";
	cout << "mkdir-r str \t\t\t\t��ǰĿ¼�´���һ����ΪstrĿ¼��Ȩ��Ϊr\n";
	cout << "mkfile-r str\t\t\t\t��ǰĿ¼�´���һ����ΪstrĿ¼��Ȩ��Ϊr\n";
	cout << "delete-r str\t\t\t\t��rootȨ��,ɾ����ǰĿ¼����Ϊstr��Ŀ¼���ļ�\n\n";
	
	cout << "mkdir-m str \t\t\t\t���������str����·�������ɶ༶Ŀ¼\n\n";
	
	cout << "mv a b	     \t\t\t\t�ѵ�ǰ·���µ�a���е�����·��b��\n";
	cout << "cp a b		 \t\t\t\t�ѵ�ǰ·���µ�a���Ƶ�����·��b��\n\n";

	cout << "mkfile-s str size\t\t\t�ڵ�ǰ�´�����СΪsize,��Ϊstr���ļ�\n";
	cout << "Q size		 \t\t\t\t����ǰ·����Ŀ¼�������Ϊsize\n";
	cout << "remove str	 \t\t\t\tɾ������·��str���һ���ļ��Լ�Ŀ¼\n";
	cout << "show		 \t\t\t\tչʾ��ǰĿ¼������С�Լ�ʹ��������ļ��Ĵ�С\n\n";

	cout << "quit		 \t\t\t\t�˳�\n";
	cout << "***********************************************************\n";
	getline(cin, s);
	while (getline(cin, s)) {
		if (s == "dir") {
			ct.dir();
		}
		else if (s == "-r") {
			ct._r();
		}
		else if (s == "-p") {
			ct._p();
		}
		else if (s == "cd") {
			ct.cd();
		}
		else if (s == "cd ~") {
			ct.cd_root();
		}
		else if (s == "cd ..") {//cd..
			ct.cd_back();
		}
		else if (s[0]=='Q') {
			ll size = stoi(s.substr(2));
			ct.setdir_size(size);
		}
		else if (s == "show") {
			ct.put_size();
		}
		else if (s[0] == 'c' && s[1] == 'p') {
			string stra, strb;
			int pos = 3;
			for (int i = 3; i < s.size(); i++) {
				if (s[i] != ' ') {
					stra += s[i];
				}
				else break;
			}
			strb = s.substr(pos + 2);
			ct.cp_a2b(stra, strb);
		}
		else if (s[0] == 'm' && s[1] == 'v') {
			string stra, strb;
			int pos = 3;
			for (int i = 3; i < s.size(); i++) {
				if (s[i] != ' ') {
					stra += s[i];
				}
				else break;
			}
			strb = s.substr(pos+2);
			ct.mv_a2b(stra, strb);
		}
		else if (s[0] == 'c' && s[1] == 'd' && s[3] != '.') {
			string str = s.substr(3);
			ct.cdstr(str);
		}
		else if (s.substr(0, 5) == "mkdir") {
			if (s[5] == '-'&&s[6]=='s') {
				string str = s.substr(8);
				ct.mkdir_r(str);
			}
			else if (s[5] == '-' && s[6] == 'm') {
				string str = s.substr(8);
				ct.mkdir_p(str);
			}
			else {
				string str = s.substr(6);
				ct.mkdir(str);
			}
		}
		else if (s.substr(0, 6) == "mkfile") {
			if (s[6] == '-'&& s[7]!='s') {
				string str = s.substr(9);
				ct.mkfile_r(str);
				continue;
			}
			else if (s[6] == '-' && s[7] == 's') {// mkfile-s a 100
				string stra, strb;
				int pos = 0;
				for (int i = 9; i < s.size(); i++) {
					if (s[i] != ' ') {
						stra += s[i];
					}
					else {
						pos = i;
						break;
					}
				}
				strb = s.substr(pos + 1);
				int num = stoi(strb);
				ct.mkfile_size(stra, num);
				continue;
			}
			string str = s.substr(7);
			ct.mkfile(str);
		}
		else if (s.substr(0, 6) == "delete") {
			if (s[6] == '-') {
				string str = s.substr(9);
				ct.delet_r(str);
				continue;
			}
			string str = s.substr(7);
			ct.delet(str);
		}
		else if (s.substr(0, 4) == "save") {
			string str = s.substr(5);
			ct.save(str);
		}
		else if (s.substr(0, 4) == "load") {
			string str = s.substr(5);
			ct.load(str);
		}
		else if (s == "quit") {
			cout << "�������˳�\n";
			break;
		}
		else {
			cout << "wrong ops!\n";
		}
	}
}
void op3(string inname) {
	string s;
	CatalogTree ct;
	ct.put_flag=0 ;
	ct.inname=inname;
	while (getline(ct.ffin, s)) {
		if (s == "dir") {
			ct.dir();
		}
		else if (s == "cd") {
			ct.cd();
		}
		else if (s == "cd ..") {//cd..
			ct.cd_back();
		}
		else if (s[0] == 'c' && s[1] == 'd' && s[3] != '.') {
			string str = s.substr(3);
			ct.cdstr(str);
		}
		else if (s.substr(0, 5) == "mkdir") {
			string str = s.substr(6);
			ct.mkdir(str);
		}
		else if (s.substr(0, 6) == "mkfile") {
			string str = s.substr(7);
			ct.mkfile(str);
		}
		else if (s.substr(0, 6) == "delete") {
			string str = s.substr(7);
			ct.delet(str);
		}
		else if (s.substr(0, 4) == "save") {
			string str = s.substr(5);
			ct.save(str);
		}
		else if (s.substr(0, 4) == "load") {
			string str = s.substr(5);
			ct.load(str);
		}
		else if (s == "quit") {
			cout << "�������˳�\n";
			break;
		}
		else {
			cout << "wrong ops!\n";
		}
	}
}

void welcome() {
	while (1)
	{
		cout << "*********************************\n";
		cout << "�����ļ�ϵͳ\n";
		cout << "ѡ���������뷽ʽ\n";
		cout << "DATA1 ����ʮ���������ݼ�\n";
		cout << "DATA2 �ֶ���������\n";
		cout << "DATA3 ����ָ��·�����ļ�\n";
		cout << "*********************************\n";
		string da; cin >> da;

		if (da == "DATA1") {
			cout << "�����CMD�����ļ���\nCMD : 0\nFILE :1\n";
			int ans; cin >> ans;
			for (int i = 0; i <= 9; i++)
			{
				op1(i, ans);
			}
		}
		else if (da == "DATA2") {
			op2();
		}
		else if (da == "DATA3") {
			cout << "������·����\n";
			string inname; cin >> inname;
			op3(inname);
		}
		else {
			cout << "��������룡���������룡";
		}
	}
}


int main() {
	welcome();
	return 0;
}

