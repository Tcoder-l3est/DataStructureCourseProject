#include<bits/stdc++.h>
#include"graph.h"
#include"solution1.h"
#include"solution2.h"
using namespace std;

//���ܷ���
void test() {
	cout << "�����������ܶԱ�����...\n";
	solution1_nojpg();
	solution2_nojpg();
	cout << "�����������,�ԱȽ���Ѿ�չʾ��ͼ��!\n";
	system("testtime.py");
	system("testroom.py");
}

void data1() {
	cout << "���ڲ���solution1(����)...\n";
	solution1();
	cout << "���ڲ���solution2(��֧����)...\n";
	solution2();
	

}
void data2()
{
	cout << "������ �����ļ�·��\n";
	string path; cin >> path;
	ifstream fin(path);
	DAG g;
	g.topsort();
	//g.backtracking(1, 0);
	g.branch_bound();
	cout << g.best_ans << "\n";//*/
	g.output_bst();

}
void data3()
{
	cout << "����������:\n";
	DAG g;
	g.topsort();
	//g.backtracking(1, 0);
	g.branch_bound();
	cout << g.best_ans << "\n";//*/
	g.output_bst();
	
}

void welcome() {
	cout << "*****ʯ�ͷŴ�������*****\n";
	cout << "***DATA1 ����100������***\n";
	cout << "***DATA2 ����ָ�����ݼ�***\n";
	cout << "***DATA3 �ֶ��������ݲ���***\n";
	while (1) {
		string op; cin >> op;
		if (op == "DATA1") {
			data1();
		}
		else if (op == "DATA2") {
			data2();
		}
		else if (op == "DATA3") {
			data3();
		}
		else {
			cout << "�������ޣ�����������\n";
		}
	}
}

int main() {
	welcome();
	return 0;
}