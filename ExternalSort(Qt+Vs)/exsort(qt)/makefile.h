#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include<fstream>
#include"minlosertree.h"
#include <bits/stdc++.h>
#include<QMessageBox>
using namespace std;

void make_num(long int max_n, ofstream &fout)
{
    fout << sizeof_file << endl;
    srand((unsigned)time(NULL));
    for (int i = 0; i < sizeof_file; i++)
        fout << rand()%max_n << " ";

    QMessageBox msgBox;
    msgBox.setText("The file has been Created!!! Go Sort!!!");
    msgBox.exec();
    return;
}
void make_file()
{//�ļ������Լ���
    //cout << "�������ļ������֡������������ֵ ���磺data10 10000 500000\n";
    //cin >> file_name; cin >> sizeof_file; cin >> max_n;
    string input_file = path + "\\" + file_name + ".txt";//�����ļ�
    std::ofstream fout(input_file);
    /*if (fout.is_open())
    {//�ļ������� ���ļ�
       
    }
    else
    {//�����ļ� ������
        do
        {
            cout << "�ļ��Ѿ����� ������������" << endl;
            cin >> file_name;
            input_file = path + "\\" + file_name + ".txt";//�����ļ�
            fout.open(input_file,ios::_Noreplace);
        } while (!fout.is_open());
    }*/
    make_num(max_n, fout);
}


