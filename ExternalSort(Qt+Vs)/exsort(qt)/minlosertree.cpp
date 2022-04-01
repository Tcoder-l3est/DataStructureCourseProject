#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<cstdio>
#include<vector>
#include"minlosertree.h"

using namespace std;


//������ 
struct Page {
	long int* arr;
	int position; //��ǰ˳��ɨ���λ�� 
	Page() {
		position = 0;
	}
	Page(int page_size) {
		position = 0;
		arr = new long int[page_size + 1];
	}
};



template<class T>
minLoserTree<T>::minLoserTree(T* ThePlayers, int n)
{
	initialize(ThePlayers, n);
}

template<class T>
void minLoserTree<T>::initialize(T* thePlayer, int theNumberOfPlayers)
{
	int n = theNumberOfPlayers;
	if (n < 2)
		throw illegalParameterValue("��������������Ԫ�أ�");

    //delete[] players;

	players = thePlayer;
	numberofPlayers = n;
    //delete[]tree; delete[]edges;
	tree = new int[n];//���ṹ���� 0Ϊ��С�Ľڵ� n���ڵ�
	edges = new int[n];//һ��n-1���� 0���� 1 - n-1

	//���� s = 2^log (n-1),S����ײ������˵��ڲ��ڵ�
	//int s = 2*log2(n - 1);
	int s;
	for (s = 1; 2 * s <= n - 1; s += s);

	lowExt = 2 * (n - s);//n-s����ײ��ⲿ�ڵ����
	offset = 2 * s - 1;

	int i;
	// ���ڵ����
	for (i = 2; i <= lowExt; i += 2)
		play_once((offset + i) / 2, i - 1, i);

	//����ʣ�µĽڵ�
	if (n % 2 == 1)
	{//nΪ����
		play_once(n / 2, edges[n - 1], lowExt + 1);
		//������ �ⲿ ����ÿ��+=2  ������һ��+1+2
		i = lowExt + 3;
	}
	else i = lowExt + 2;

	//
	for (; i <= n; i += 2)
	{
		play_once((i - lowExt + n - 1) / 2, i - 1, i);
	}

	maintain();
	//cout << tree[0] << endl;
};

template<class T>
void minLoserTree<T>::play_once(int p, int leftChild, int rightChild)
{
	//get now
	tree[p] = loser(leftChild, rightChild);//���ڵ�����Ŵ��
	edges[p] = winner(leftChild, rightChild);

	//ѭ���ݹ�ʵ����������
	while (p % 2 == 1 && p > 1)
	{
		tree[p / 2] = loser(edges[p - 1], edges[p]);
		edges[p / 2] = winner(edges[p - 1], edges[p]);
		p = p / 2;//������ �Ҹ�ĸ
	}
}

template<class T>
void minLoserTree<T>::replay(int thePlayer)
{//�Ӹı�Ŀ�ʼ ���� �ر�  ֻ����λ��
	int n = numberofPlayers;
	if (thePlayer <= 0 || thePlayer > numberofPlayers)
		throw illegalParameterValue("��������!");

	int matchNode,    //Ҫ���б����Ľڵ�
		leftChild,
		rightChild;

	if (thePlayer <= lowExt)
	{//�������ڵ㿪ʼ���б���
		matchNode = (offset + thePlayer) / 2;
		leftChild = 2 * matchNode - offset;
		rightChild = leftChild + 1;//���ڱ���
	}
	else
	{//����������һ���ⲿ�ڵ㣬����һ��
		matchNode = (thePlayer - lowExt + n - 1) / 2;
		if (2 * matchNode == n - 1)
		{//������� �ı�Ľڵ�Ϊ���ŵ��Ǹ��ڵ�����
			leftChild = edges[2 * matchNode];//����Ϊ���ڵ�
			rightChild = thePlayer;//�Һ��Ӿ����Լ�
		}
		else
		{//����һ�����
			leftChild = 2 * matchNode - n + 1 + lowExt;
			rightChild = leftChild + 1;
		}
	}

	tree[matchNode] = loser(leftChild, rightChild);
	edges[matchNode] = winner(leftChild, rightChild);

	//��������ĵ���
	if (matchNode == n - 1 && n % 2 == 1)
	{//�����������Ԫ�ز�����һ��Ҫ���Ǹ����ŵı�
		matchNode /= 2;//���ڵ�
		tree[matchNode] = loser(edges[n - 1], lowExt + 1);
		edges[matchNode] = winner(edges[n - 1], lowExt + 1);
	}

	//��������
	matchNode /= 2;
	for (; matchNode >= 1; matchNode /= 2)
	{
		tree[matchNode] = loser(edges[2 * matchNode], edges[2 * matchNode + 1]);
		edges[matchNode] = winner(edges[2 * matchNode], edges[2 * matchNode + 1]);
	}

	maintain();

}

template<class T>
void minLoserTree<T>::output()
{
	cout << "numbers of players = " << numberofPlayers << " lowExt(���ⲿԪ��) = "
		<< lowExt << " offset = " << offset << endl;
	cout << "���Լ����ڵı߽ṹΪ�� \n";
	for (int i = 1; i < numberofPlayers; i++)
	{
		cout << "Tree[" << i << "] = " << players[tree[i]] << " ";
		cout << "Edge[" << i << "] =" << players[edges[i]] << endl;
	}
	cout << "Tree[0] = " << players[tree[0]] << endl;
}

template<class T>
void minLoserTree<T>::make_run(fstream& fin)
{//ʹ��minloser ����˳��

	//����make_run���̷�����
	//Ӧ����:ÿ�ζ����������buffer�� 1��  Ȼ������������˳�� ���ʱÿ��Ҫ����һ��
	// 	   ����Ż��� �������� ˳����+���� ����������Ӧ�ļ�
	//		���Ǵ������⣺ �޷�ȷ�����������������С 
	//������㷽�� �� ȫ��Ϊ���뻺���� ÿ���������һ��disk ���㡣
	disk_times += (sizeof_file / sizeof_MM) + 1;


	if (!fin.is_open()) {
		cout << "�򲻿��ļ���" << endl;
		return;
	}

	//�ڴ��С���Լ��趨
	//sizeof_MM = 3;

	//�ж��ٸ����˳�� ȡ���ڶ��ٸ� ˳����num
	cout << "��������˳��......\n";
	int pos = top();//�滻��λ��
	while (players[pos].num != INT_MAX)
	{//����δ�����
		pos = top();//�滻��λ��
		if (players[pos].num > max_run && players[pos].num != INT_MAX) max_run = players[pos].num;
		Player p;//�����滻��
		string output_file = ff_name + "_R" + to_string(players[pos].num) + ".txt";
		ofstream fout(output_file, ios::app);
		disk_times++;//���
		fout << players[pos].element << " ";//���
		fout.close();//���ֹر�
		//������һ��
		long int temp;
		if (fin >> temp)
		{//�����ļ�ĩβ	
			if (!fin.eof())
			{
				p.element = temp;
				//disk_times++;
				if (p.element < players[pos].element) {
					p.num = players[pos].num + 1;
				}
				else p.num = players[pos].num;
			}
			else {//������
				fin.close();
				p.element = INT_MAX;
				p.num = INT_MAX;
			}

		}
		else {//������
			fin.close();
			p.element = INT_MAX;
			p.num = INT_MAX;
		}
		players[pos] = p;//�滻
		replay(pos);
		pos = top();//�滻��λ��
	}
	all_temps = max_run;
	cout << max_run << " ��˳�����ɳɹ�������\n";

	for (int i = 1; i <= max_run; i++)
	{
		string s = ff_name + "_r" + to_string(i) + ".txt";
		ofstream fo(s, ios::app);
		fo << INT_MAX;
	}
}

//K·�鲢
template<class T>
void minLoserTree<T>::merge_K(int k, int sta, int level)
{//ע�� ������Player�ṹ����  �鲢���Ƚ�run num   ÿ�ν���һ�εĹ鲢
 //ÿ�ι鲢���ֻ��һ�� ÿ����    
	int file_num = all_temps + 1 - sta;
	int end_level = all_temps;
	int times;//����ÿ��鲢����
	int next_sta = sta;

	if (file_num <= 1) {
		cout << "�ϲ���ɣ�" << endl;
		return;
	}
	

	if (file_num % k != 0) times = (file_num / k) + 1;
	else times = file_num / k;

	if (times == 0)
		times = 1;

	while (times--)
	{//ÿ���κϲ�

		int now_k = min(end_level - next_sta + 1, k);//������治�����õ����
		next_sta += now_k;
		map<int, string> name;//���������
		ifstream* fins = new ifstream[now_k + 1];

		page_num = now_k + 1;
		page_size = sizeof_MM / page_num;
		Page* inBuffer = new Page[now_k + 1];
		vector<long> outBuffer(page_size, 0);

		int outpoint = 0;//���ָ��
		for (int i = 0; i <= now_k; i++)
		{
			inBuffer[i] = Page(page_size);
		}

		
		if (level == 0) {//����run 
			for (int i = sta; i < sta + now_k; i++)
			{
				string s = ff_name + "_R" + to_string(i) + ".txt";
				name[i] = s;
				fins[i - sta + 1].open(s);
			}
		}
		else
		{//����S
			for (int i = sta; i < sta + now_k; i++)
			{
				name[i] = ff_name + "_S" + to_string(i) + ".txt";
				fins[i - sta + 1].open(name[i]);
			}
		}

		//������inBuffer
		for (int i = 1; i <= now_k; i++)
		{
			int cnt = 0;
			while (cnt < page_size && !fins[i].eof())
			{
				fins[i] >> inBuffer[i].arr[cnt++];
			}
			inBuffer[i].position = 0;
			disk_times++;//��һ�� ����
		}

		T* ps = new T[now_k + 1];
		ps[0] = INT_MAX;
		for (int i = 1; i <= now_k; i++)
		{
			ps[i] = inBuffer[i].arr[0];
			inBuffer[i].position++;
		}



		//for (int i = sta; i < sta + now_k; i++)
		//{//�������run��һ������
		//	long int temp;
		//	if (!fins[i - sta + 1].is_open()) {
		//		cout << "˳�� "<<i-sta+1<<" ��ʧ�ܣ�" << endl;
		//		return;
		//	}
		//	//�ȶ���
		//	//int num = 0;
		//	//while (num < page_size && !fins[i - sta + 1].eof()) {
		//	//	fins[i - sta + 1] >> in_buffer[i - sta + 1][num];
		//	//	num++;
		//	//}
		//	//in_pointers[i - sta + 1] = 0;

		//	//	//��ȡ�ⲿ�ڵ� 
		//	//for (int j = 1; j <= now_k; j++) {
		//	//	players[j] = in_buffer[j][0];
		//	//	in_pointers[j]++;
		//	//}


		//	if (fins[i - sta + 1] >> temp)
		//	{
		//		if (fins[i - sta + 1].eof())
		//		{
		//			fins[i - sta + 1].close();
		//			ps[i - sta + 1] = INT_MAX;
		//			continue;
		//		}
		//		ps[i - sta + 1] = temp;
		//	}
		//	else
		//	{
		//		ps[i - sta + 1] = INT_MAX;
		//	}
		//}

		string output_file = ff_name + "_S" + to_string(++all_temps) + ".txt";
		if (all_temps - max_run == totals) {
			output_file = ff_name + "_sorted.txt";//���һ�����
		}
		ofstream fout(output_file, ios::app);

		//��ʼ��֮ǰҪ�ж� �����һ��Ԫ�� ���������
		//if (now_k == 1)
		//{
		//	fout << ps[1];
		//	long int temp;
		//	while (fins[1] >> temp)
		//	{
		//		//����
		//		if (fins[1].eof()||temp==INT_MAX)
		//		{
		//			fins[1].close();
		//			break;
		//		}
		//		fout << temp;
		//		disk_times += 2;
		//	}
		//	//������һ��ѭ��
		//	for (int i = sta; i < sta + now_k; i++)
		//	{
		//		fins[i - sta + 1].close();
		//	}
		//	fout.close();
		//	sta = next_sta;
		//	continue;
		//}

		//ÿ�ζ��ó�ʼ��
		initialize(ps, now_k);

		int pos = top();//�滻��λ��
		while (players[pos] != INT_MAX)
		{
			pos = top();//�滻��λ��
			outBuffer[outpoint++] = players[pos];
			//T p;//�����滻��
			
			//fout << players[pos] << " ";//���
			
			//��������������������ݿ�д����� 
			if (outpoint == page_size) {
				for (outpoint = 0; outpoint < page_size; outpoint++) {
					fout << outBuffer[outpoint] << " ";
				}
				outpoint = 0;
				disk_times++;//һ�������һ��
			}
			//disk_times++;

			//���뻺�����ѿգ������������ݿ� 
			if (inBuffer[pos].position >= page_size) {
				int cnt = 0;
				while (cnt < page_size && !fins[pos].eof()) {
					fins[pos] >> inBuffer[pos].arr[cnt++];
				}
				inBuffer[pos].position = 0;
				players[pos] = inBuffer[pos].arr[inBuffer[pos].position];
				inBuffer[pos].position++;
				disk_times++;
			}
			//������ȡ������ 
			else {
				players[pos] = inBuffer[pos].arr[inBuffer[pos].position];
				inBuffer[pos].position++;
			}


			////������һ��
			//if (fins[pos] >> p)
			//{//�����ļ�ĩβ	
			//	disk_times++;
			//	if (fins[pos].eof())
			//	{
			//		fins[pos].close();
			//		p = INT_MAX;
			//		break;
			//	}
			//}
			//else {//������
			//	fins[pos].close();
			//	p = INT_MAX;
			//}



			//players[pos] = p;//�滻
			replay(pos);
			pos = top();//�滻��λ��
		}

		for (int indx = 0; indx < outpoint; indx++) {
			fout << outBuffer[indx] << " ";
		}
		disk_times++;//����ʣ���
		if (all_temps - max_run != totals) {
			fout << INT_MAX;
		}
		

		for (int i = sta; i < sta + now_k; i++)
		{
			fins[i - sta + 1].close();
		}
		fout.close();
		sta = next_sta;
	}
	if (next_sta > max_run)
		merge_K(k, next_sta, 1);//��־ ������run��
	else
		merge_K(k, next_sta, 0);

}
