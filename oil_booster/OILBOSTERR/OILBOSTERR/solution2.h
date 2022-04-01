#pragma once

#include<bits/stdc++.h>
#include"graph.h"

using namespace std;


void solution2() {
	for (int i = 1; i <= 100; i++) {
		string iin = "C:\\Users\\12042\\Desktop\\dagData\\input\\input";
		iin += to_string(i) + ".in";
		string iout = "C:\\Users\\12042\\Desktop\\dagData\\output2\\";
		iout += to_string(i) + ".out";
		fin.open(iin);
		fout.open(iout);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "�ļ���ʧ�ܣ�\n";
		}

		DAG g;
		g.topsort();
		g.branch_bound();
		fout << g.best_ans << "\n";
		fin.close();
		fout.close();
		cout << "�������ɿ��ӻ�ͼƬ " << i << "\n";
		//g.visualize2(i);
		cout << "�������\n";
	}
	cout << "���ڽ��н��ж���...\n";
	check();
}


void solution2_nojpg() {
	for (int i = 1; i <= 100; i++) {
		LARGE_INTEGER start_time; //��ʼʱ��
		LARGE_INTEGER end_time;   //����ʱ��
		double dqFreq;            //��ʱ��Ƶ��
		LARGE_INTEGER freq;       //��ʱ��Ƶ��
		QueryPerformanceFrequency(&freq);
		dqFreq = (double)freq.QuadPart;

		string iin = "C:\\Users\\12042\\Desktop\\dagData\\input\\input";
		iin += to_string(i) + ".in";
		string iout = "C:\\Users\\12042\\Desktop\\dagData\\output2\\";
		iout += to_string(i) + ".out";
		fin.open(iin);
		fout.open(iout);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "�ļ���ʧ�ܣ�\n";
		}
		QueryPerformanceCounter(&start_time); //��ʱ��ʼ

		DAG g;
		g.topsort();
		g.branch_bound();
		fout << g.best_ans << "\n";

		QueryPerformanceCounter(&end_time); //��ʱ��ʼ
		fin.close();
		fout.close();
		ofstream fo("cost2.txt", ios::app);
		double run_time = (end_time.QuadPart - start_time.QuadPart) / dqFreq * 1000;
		fo << i << " " << run_time << "\n";
		fo.close();

		//�ռ� ��2�� ��֧����
		ofstream foo("room2.txt", ios::app);
		//int 4     btnode   
		ll romcost = 32 * g.n + 4 * g.m;
		foo << i << " " << romcost << "\n";
		foo.close();

	}
}