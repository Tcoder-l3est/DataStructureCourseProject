#include<iostream>
#include <fstream>
#include<sstream>
#include<cstdio>
#include"SKIPLIST.h"
#include"SKIPLIST.cpp"
#include<algorithm>
using namespace std;

void input_data(int i)
{
	FILE* stream1;
	string sin = "input_";
	string sout = "output_";
	char c = i + '0';
	sin += c;
	sout += c;
	sin += ".txt";
	sout += ".txt";
	freopen_s(&stream1, sin.c_str(), "r", stdin);
	//fclose(stream1);
	freopen_s(&stream1, sout.c_str(), "w", stdout);
}

void input_datanon(int i)
{
	FILE* stream1;
	string sin = "ninput_";
	string sout = "noutput_";
	char c = i + '0';
	sin += c;
	sout += c;
	sin += ".txt";
	sout += ".txt";
	freopen_s(&stream1, sin.c_str(), "r", stdin);
	freopen_s(&stream1, sout.c_str(), "w", stdout);
}

void input_data_db(int i)
{
	FILE* stream1;
	string sin = "dbinput_";
	string sout = "dboutput_";
	char c = i + '0';
	sin += c;
	sout += c;
	sin += ".txt";
	sout += ".txt";
	freopen_s(&stream1, sin.c_str(), "r", stdin);
	freopen_s(&stream1, sout.c_str(), "w", stdout);
}

void input_data_any()
{//��������
	FILE* stream1;
	string sin, sout;;
	cout << "������txt�ļ�·����(�磺d:\\123.txt (txt����Ҫ����))" << endl;
	cin >> sin;
	sout = sin+"-output";
	sin += ".txt";
	sout += ".txt";
	freopen_s(&stream1, sin.c_str(), "r", stdin);
	freopen_s(&stream1, sout.c_str(), "w", stdout);

}

bool cmp(int a, int b)
{
	return a > b;
}

void func1(string ans)
{
	int count = 10;
	cout << "�Ƿ���Ҫ��;�����ع�  ������(0/1)" << endl;
	int flag = 0; cin >> flag;
	while (count)
	{
		int n, m;
		skipList<int, int> sl(1000000, 10000, 0.5);
		sl.need_reform = flag;
		if (ans == "Y")//��ʼ��Ϊ�ϸ�����
		{
			input_data(--count);
			cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
			int* a = new int[m];//�����ݴ�
			for (int i = 0; i < m; i++)
			{
				cin >> a[i];
			}
			sort(a, a + m, cmp);//������
			sl.ideal_initial(a, m);
			cout << "��ʼ���ϸ��������� :" << endl;
			sl.output();
		}
		else
		{
			input_data(--count);
			cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
			for (int i = 0; i < m; i++)
			{
				int temp;
				cin >> temp;
				pair<int, int> p = make_pair(temp, temp);
				sl.insert(p);
				
			}
			cout << "-----------------------------------------------------" << endl;
			cout << "��ʼ�����ϸ��������� :" << endl;
			sl.output();
			cout << "-----------------------------------------------------" << endl;
		}
		//op
		for (int i = 0; i < n - 1; i++)
		{
			int op;
			cin >> op;
			int num;
			switch (op)
			{
			case 1:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				sl.find(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				pair<int, int> p = make_pair(num, num);
				sl.insert(p);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 3:
			{
				cin >> num;
				cout << "---------------------------------------------------------\n";
				sl.erase(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 4:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_min();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 5:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_max();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 6:
			{
				cout << "---------------------------------------------------------\n";
				cout << "����Ԫ������Ϊ : ";
				sl.op_xor();
				cout << "---------------------------------------------------------\n";
				break;
			}
			default:
			{
				cout << "�������ָ���������ȷ�Ĳ���ָ���Լ����ݣ�����" << endl;
				break;
			}
			}
		}
	}
	
	
}

void func2( string ans)
{
	int count = 10;
	cout << "�Ƿ���Ҫ��;�����ع�  ������(0/1)" << endl;
	int flag = 0; cin >> flag;
	while (count)
	{
		int n, m;
		skipList<int, int> sl(1000000, 10000, 0.5);
		sl.need_reform = flag;
		if (ans == "Y")//��ʼ��Ϊ�ϸ�����
		{
			input_datanon(--count);
			cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
			int* a = new int[m];//�����ݴ�
			for (int i = 0; i < m; i++)
			{
				cin >> a[i];
			}
			sort(a, a + m, cmp);//������
			sl.ideal_initial(a, m);
			cout << "��ʼ���ϸ��������� :" << endl;
			sl.output();
		}
		else
		{
			input_datanon(--count);
			cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
			for (int i = 0; i < m; i++)
			{
				int temp;
				cin >> temp;
				pair<int, int> p = make_pair(temp, temp);
				sl.insert(p);

			}
			cout << "-----------------------------------------------------" << endl;
			cout << "��ʼ�����ϸ��������� :" << endl;
			sl.output();
			cout << "-----------------------------------------------------" << endl;
		}
		//op
		for (int i = 0; i < n - 1; i++)
		{
			int op;
			cin >> op;
			int num;
			switch (op)
			{
			case 1:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				sl.find(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				pair<int, int> p = make_pair(num, num);
				sl.insert(p);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 3:
			{
				cin >> num;
				cout << "---------------------------------------------------------\n";
				sl.erase(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 4:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_min();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 5:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_max();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 6:
			{
				cout << "---------------------------------------------------------\n";
				cout << "����Ԫ������Ϊ : ";
				sl.op_xor();
				cout << "---------------------------------------------------------\n";
				break;
			}
			default:
			{
				cout << "�������ָ���������ȷ�Ĳ���ָ���Լ����ݣ�����" << endl;
				break;
			}
			}
		}
	}
	//cout << "����ɹ� ��鿴�ļ�������" << endl;

}

void func3()
{
	int n, m;
	string ans;
	cout << "������������� Ԫ�ظ��� " << endl;
	cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
	cout << "�Ƿ���Ҫ��ʼ��Ϊ�ϸ�������(Y/N)" << endl;
	cin >> ans;
	skipList<int, int> sl(1000000, 10000, 0.5);
	cout << "�Ƿ���Ҫ��;�����ع�  ������(0/1)" << endl;
	int flag = 0; cin >> flag;
	sl.need_reform = flag;
	cout << "������ "<<m<<" ������" << endl;
	if (ans == "Y")//��ʼ��Ϊ�ϸ�����
	{
		int* a = new int[m];//�����ݴ�
		for (int i = 0; i < m; i++)
		{
			cin >> a[i];
		}
		sort(a, a + m, cmp);//������
		sl.ideal_initial(a, m);
		cout << "��ʼ���ϸ��������� :" << endl;
		sl.output();
	}
	else
	{
		for (int i = 0; i < m; i++)
		{
			int temp;
			cin >> temp;
			pair<int, int> p = make_pair(temp, temp);
			sl.insert(p);
		}
		cout << "-----------------------------------------------------" << endl;
		cout << "��ʼ�����ϸ��������� :" << endl;
		sl.output();
		cout << "-----------------------------------------------------" << endl;
	}
	//op n�� ����n-1��
	for (int i = 0; i < n; i++)
	{
		cout << "��ѡ�� Ҫ���еĲ��� : " << endl;
		cout << "���� " << n - i << " �β���" << endl;
		cout << "op 1 : ����ĳԪ�� " << endl;
		cout << "op 2 : ����Ԫ��" << endl;
		cout << "op 3 : ɾ��Ԫ��" << endl;
		cout << "op 4 : ɾ����СԪ�� " << endl;
		cout << "op 5 : ɾ�����Ԫ��" << endl;
		cout << "op 6 : �������Ԫ������" << endl;
		int op;
		cin >> op;
		int num;
		switch (op)
		{
		case 1:
		{
			cout << "������Ҫ���ҵ�Ԫ��" << endl;
			cout << "---------------------------------------------------------\n";
			cin >> num;
			sl.find(num);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 2:
		{
			cout << "������Ҫ�����Ԫ��" << endl;
			cout << "---------------------------------------------------------\n";
			cin >> num;
			pair<int, int> p = make_pair(num, num);
			sl.insert(p);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 3:
		{
			cout << "������Ҫɾ����Ԫ��" << endl;
			cin >> num;
			sl.erase(num);
			break;
		}
		case 4:
		{
			cout << "---------------------------------------------------------\n";
			sl.erase_min();
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 5:
		{
			cout << "---------------------------------------------------------\n";
			sl.erase_max();
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 6:
		{
			cout << "---------------------------------------------------------\n";
			cout << "����Ԫ������Ϊ : ";
			sl.op_xor();
			cout << "---------------------------------------------------------\n";
			break;
		}
		default:
		{
			cout << "�������ָ���������ȷ�Ĳ���ָ���Լ����ݣ�����" << endl;
			break;
		}
		}
	}
}

void func4(string ans)
{//�����ÿ�����ݼ� ÿ���������� ��һ���Ǵ��ع� �ڶ��β���
	int count = 10;
	cout << "���жԱȣ���һ�β��ع����ڶ����ع�������" << endl;

	while (count)
	{
		int n, m;
		skipList<int, int> sl(1000000, 10000, 0.5);
		skipList<int, int> sl2(1000000, 10000, 0.5);
		sl.need_reform = 0;
		sl2.need_reform = 1;
		if (ans == "Y")//��ʼ��Ϊ�ϸ�����
		{
			input_data_db(--count);
			cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
			int* a = new int[m];//�����ݴ�
			for (int i = 0; i < m; i++)
			{
				cin >> a[i];
			}
			sort(a, a + m, cmp);//������
			sl.ideal_initial(a, m);
			cout << "��ʼ���ϸ��������� :" << endl;
			sl.output();
		}
		else
		{
			input_data_db(--count);
			cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
			for (int i = 0; i < m; i++)
			{
				int temp;
				cin >> temp;
				pair<int, int> p = make_pair(temp, temp);
				sl.insert(p);

			}
			cout << "-----------------------------------------------------" << endl;
			cout << "��ʼ�����ϸ��������� :" << endl;
			sl.output();
			cout << "-----------------------------------------------------" << endl;
		}
		//op
		for (int i = 0; i < n - 1; i++)
		{
			int op;
			cin >> op;
			int num;
			switch (op)
			{
			case 1:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				sl.find(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				pair<int, int> p = make_pair(num, num);
				sl.insert(p);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 3:
			{
				cin >> num;
				cout << "---------------------------------------------------------\n";
				sl.erase(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 4:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_min();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 5:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_max();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 6:
			{
				cout << "---------------------------------------------------------\n";
				cout << "����Ԫ������Ϊ : ";
				sl.op_xor();
				cout << "---------------------------------------------------------\n";
				break;
			}
			default:
			{
				cout << "�������ָ���������ȷ�Ĳ���ָ���Լ����ݣ�����" << endl;
				break;
			}
			}
		}
		cout << "���ع���ʱ�����£�\n";
		sl.analyse();
		if (ans == "Y")//��ʼ��Ϊ�ϸ�����
		{
			int* b = new int[m];//�����ݴ�
			for (int i = 0; i < m; i++)
			{
				cin >> b[i];
			}
			sort(b, b + m, cmp);//������
			sl2.ideal_initial(b, m);
			cout << "��ʼ���ϸ��������� :" << endl;
			sl2.output();
		}
		else
		{
			for (int i = 0; i < m; i++)
			{
				int temp;
				cin >> temp;
				pair<int, int> p = make_pair(temp, temp);
				sl2.insert(p);

			}
			cout << "-----------------------------------------------------" << endl;
			cout << "��ʼ�����ϸ��������� :" << endl;
			sl2.output();
			cout << "-----------------------------------------------------" << endl;
		}
		//op
		for (int i = 0; i < n - 1; i++)
		{
			int op;
			cin >> op;
			int num;
			switch (op)
			{
			case 1:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				sl2.find(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				pair<int, int> p = make_pair(num, num);
				sl2.insert(p);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 3:
			{
				cin >> num;
				cout << "---------------------------------------------------------\n";
				sl2.erase(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 4:
			{
				cout << "---------------------------------------------------------\n";
				sl2.erase_min();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 5:
			{
				cout << "---------------------------------------------------------\n";
				sl2.erase_max();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 6:
			{
				cout << "---------------------------------------------------------\n";
				cout << "����Ԫ������Ϊ : ";
				sl2.op_xor();
				cout << "---------------------------------------------------------\n";
				break;
			}
			default:
			{
				cout << "�������ָ���������ȷ�Ĳ���ָ���Լ����ݣ�����" << endl;
				break;
			}
			}
		}
		cout << "�ع���ʱ�����£�\n";
		sl2.analyse();
	}
}

void func5(string ans)
{
	cout << "�Ƿ���Ҫ��;�����ع�  ������(0/1)" << endl;
	int flag = 0; cin >> flag;

	int n, m;
	skipList<int, int> sl(1000000, 10000, 0.5);
	sl.need_reform = flag;
	if (ans == "Y")//��ʼ��Ϊ�ϸ�����
	{
		input_data_any();
		cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
		int* a = new int[m];//�����ݴ�
		for (int i = 0; i < m; i++)
		{
			cin >> a[i];
		}
		sort(a, a + m, cmp);//������
		sl.ideal_initial(a, m);
		cout << "��ʼ���ϸ��������� :" << endl;
		sl.output();
	}
	else
	{
		input_data_any();
		cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
		for (int i = 0; i < m; i++)
		{
			int temp;
			cin >> temp;
			pair<int, int> p = make_pair(temp, temp);
			sl.insert(p);

		}
		cout << "-----------------------------------------------------" << endl;
		cout << "��ʼ�����ϸ��������� :" << endl;
		sl.output();
		cout << "-----------------------------------------------------" << endl;
	}
	//op
	for (int i = 0; i < n - 1; i++)
	{
		int op;
		cin >> op;
		int num;
		switch (op)
		{
		case 1:
		{
			cout << "---------------------------------------------------------\n";
			cin >> num;
			sl.find(num);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 2:
		{
			cout << "---------------------------------------------------------\n";
			cin >> num;
			pair<int, int> p = make_pair(num, num);
			sl.insert(p);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 3:
		{
			cin >> num;
			cout << "---------------------------------------------------------\n";
			sl.erase(num);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 4:
		{
			cout << "---------------------------------------------------------\n";
			sl.erase_min();
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 5:
		{
			cout << "---------------------------------------------------------\n";
			sl.erase_max();
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 6:
		{
			cout << "---------------------------------------------------------\n";
			cout << "����Ԫ������Ϊ : ";
			sl.op_xor();
			cout << "---------------------------------------------------------\n";
			break;
		}
		default:
		{
			cout << "�������ָ���������ȷ�Ĳ���ָ���Լ����ݣ�����" << endl;
			break;
		}
		}
	}

}


void welcome()
{
	while (1)
	{
		string ans;//�ʴ�
		cout << "*****************************************************" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "��ѡ�� �������ݷ�ʽ:" << endl;
		cout << "option 1 : ����ʮ���ظ����ݼ���" << endl;
		cout << "option 2 : ����ʮ�����ظ����ݼ���" << endl;
		cout << "option 3 : �Լ���������" << endl;
		cout << "option 4 : ����ʮ�����ݼ��Ͻ����ع��Ա�" << endl;
		cout << "option 5 : ����ָ��·��������" << endl;
		cout << "quit  (q): �˳�" << endl;
		cin >> ans;
		if (ans == "1")
		{
			cout << "�Ƿ���Ҫ��ʼ��Ϊ�ϸ�������(Y/N)" << endl;
			cin >> ans;
			func1(ans);
		}
		else if (ans == "2")
		{
			int num = 0;
			cout << "�Ƿ���Ҫ��ʼ��Ϊ�ϸ�������(Y/N)" << endl;
			cin >> ans;
			func2(ans);
		}
		else if (ans == "3")
		{
			func3();
		}
		else if (ans == "4")
		{
			cout << "�Ƿ���Ҫ��ʼ��Ϊ�ϸ�������(Y/N)" << endl;
			cin >> ans;
			func4(ans);
		}
		else if (ans == "5")
		{
			cout << "�Ƿ���Ҫ��ʼ��Ϊ�ϸ�������(Y/N)" << endl;
			cin >> ans;
			func5(ans);
		}
		else if (ans == "q")
		{
			cout << "�˳��ɹ���" << endl;
			break;
		}
		else
		{
			cout << "�������ָ���������ȷ�Ĳ���ָ�����" << endl;
			break;
		}
		cout << "*****************************************************" << endl;

	}
}


//�ۺ� 
int main()
{
	welcome();//��ʾ��ӭ���沢���ṩ������ʾ
	
	return 0;
}



//
////���뻯��ʼ
//int main()
//{
//	FILE* stream1;
//	freopen_s(&stream1, "input_1.txt", "r", stdin);
//	freopen_s(&stream1, "output_1.txt", "w", stdout);
//	int n, m;
//	cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
//	skipList<int, int> sl(1000000, 10000, 0.5);
//	int* a = new int[m];//�����ݴ�
//	for (int i = 0; i < m; i++)
//	{
//		cin >> a[i];
//	}
//	sort(a, a + m,cmp);//������
//	sl.ideal_initial(a,m);
//	cout << "���뻯�������:" << endl;
//	sl.output();
//
//
//
//
//	return 0;
//}

//�Ա��ع��ļ�ֵ
//int main()
//{
//	//FILE* stream1;
//	//freopen_s(&stream1, "input_11.txt", "r", stdin);
//	//freopen_s(&stream1, "output_11.txt", "w", stdout);
//	int n, m;
//	cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
//	skipList<int, int> sl(1000000, 10000, 0.5);
//	for (int i = 0; i < m; i++)
//	{
//		int temp;
//		cin >> temp;
//		pair<int, int> p = make_pair(temp, temp);
//		sl.insert(p);
//	}
//	cout << "δ�ع� ֱ�Ӳ��������Ϊ:" << endl;
//	sl.output();
//
//	sl.reform();
//	cout << "�ع�������Ϊ:" << endl;
//	sl.output();
//
//	//for (int i = 0; i < n - 1; i++)
//	//{
//	//	int op;
//	//	cin >> op;
//	//	int num;
//	//	switch (op)
//	//	{
//	//	case 1:
//	//	{
//	//		cin >> num;
//	//		sl.find(num);
//	//		break;
//	//	}
//	//	case 2:
//	//	{
//	//		cin >> num;
//	//		pair<int, int> p = make_pair(num, num);
//	//		sl.insert(p);
//	//		break;
//	//	}
//	//	case 3:
//	//	{
//	//		cin >> num;
//	//		sl.erase(num);
//	//		break;
//	//	}
//	//	case 4:
//	//	{
//	//		sl.erase_min();
//	//		break;
//	//	}
//	//	case 5:
//	//	{
//	//		sl.erase_max();
//	//		break;
//	//	}
//	//	case 6:
//	//	{
//	//		cout << "����Ԫ������Ϊ�� ";
//	//		sl.op_xor();
//	//		break;
//	//	}
//	//	default:
//	//		break;
//	//	}
//	//}
//	//sl.reform();
//	//cout << "�ع�������Ϊ:" << endl;
//	//sl.output();
//	//cout << "�ع�����ͬ������" << endl;
//	//for (int i = 0; i < n - 1; i++)
//	//{
//	//	int op;
//	//	cin >> op;
//	//	int num;
//	//	switch (op)
//	//	{
//	//	case 1:
//	//	{
//	//		cin >> num;
//	//		sl.find(num);
//	//		break;
//	//	}
//	//	case 2:
//	//	{
//	//		cin >> num;
//	//		pair<int, int> p = make_pair(num, num);
//	//		sl.insert(p);
//	//		break;
//	//	}
//	//	case 3:
//	//	{
//	//		cin >> num;
//	//		sl.erase(num);
//	//		break;
//	//	}
//	//	case 4:
//	//	{
//	//		sl.erase_min();
//	//		break;
//	//	}
//	//	case 5:
//	//	{
//	//		sl.erase_max();
//	//		break;
//	//	}
//	//	case 6:
//	//	{
//	//		cout << "����Ԫ������Ϊ�� ";
//	//		sl.op_xor();
//	//		break;
//	//	}
//	//	default:
//	//		break;
//	//	}
//	//}
//	return 0;
//}

//������ ������ļ�
//int main()
//{
//	int count = 10;
//	while (count)
//	{
//		input_data(--count);
//		int n, m;
//		cin >> n >> m;//nΪ�������� mΪ��ʼ��Ԫ��
//		skipList<int, int> sl(1000000, 10000, 0.5);
//		for (int i = 0; i < m; i++)
//		{
//			int temp;
//			cin >> temp;
//			pair<int, int> p = make_pair(temp, temp);
//			sl.insert(p);
//		}
//		for (int i = 0; i < n - 1; i++)
//		{
//			int op;
//			cin >> op;
//			int num;
//			switch (op)
//			{
//			case 1:
//			{
//				cin >> num;
//				sl.find(num);
//				break;
//			}
//			case 2:
//			{
//				cin >> num;
//				pair<int, int> p = make_pair(num, num);
//				sl.insert(p);
//				break;
//			}
//			case 3:
//			{
//				cin >> num;
//				sl.erase(num);
//				break;
//			}
//			case 4:
//			{
//				sl.erase_min();
//				break;
//			}
//			case 5:
//			{
//				sl.erase_max();
//				break;
//			}
//			case 6:
//			{
//				cout << "����Ԫ������Ϊ�� ";
//				sl.op_xor();
//				break;
//			}
//			default:
//				break;
//			}
//		}
//		sl.analyse();
//		
//	}
//	return 0;
//}

