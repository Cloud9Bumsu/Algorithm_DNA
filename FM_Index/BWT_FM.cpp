//2018112085 �ڹ��� FM_index
#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <time.h>
//#include "shortread.cpp"

#define M 50
#define x 2  // ������ �߻��� Ȯ��
#define MAX_x 2 // ShortRead ���� ������ �ִ� ���� 

int N;
int k;

using namespace std;

static const char alphanum[] = "ACGT";
int stringLength = sizeof(alphanum) - 1;

class string_member
{
public:
	string str;
	int index=0;
};

void ShortRead(string_member* S, string_member* R) {

	int mutant;
	int index;

	for (int i = 0; i < N; i++) {
		//���� SEQUENCE���� 
		index = rand() * rand() % (M - k);
		int mutant_num = MAX_x;
		//cout << i+1 << "��° ShortRead ��������:";
		for (int j = index; j < index + k; j++) {

			R[i * k + (j - index)].str = S[j].str;
			R[i * k + (j - index)].index = S[j].index;
			//cout << S[j];

			// ������ �߻�
			/*mutant = rand() % 100;
			if (mutant <= x && mutant_num > 0) {
				cout << "���� �߻�!" << endl;

				switch (S[j])
				{
				case 'A':
					if (index % 3 == 0) R[i * k + (j - index)] = 'T'; else if (index % 3 == 1) R[i * k + (j - index)] = 'C'; else if (index % 3 == 2) R[i * k + (j - index)] = 'G';
					break;
				case 'T':
					if (index % 3 == 0) R[i * k + (j - index)] = 'A'; else if (index % 3 == 1) R[i * k + (j - index)] = 'C'; else if (index % 3 == 2) R[i * k + (j - index)] = 'G';
					break;
				case 'C':
					if (index % 3 == 0) R[i * k + (j - index)] = 'A'; else if (index % 3 == 1) R[i * k + (j - index)] = 'T'; else if (index % 3 == 2) R[i * k + (j - index)] = 'G';
					break;
				case 'G':
					if (index % 3 == 0) R[i * k + (j - index)] = 'A'; else if (index % 3 == 1) R[i * k + (j - index)] = 'T'; else if (index % 3 == 2) R[i * k + (j - index)] = 'C';
					break;
				}
				mutant_num--;
			}*/

		}
		//cout << endl;
	}
}

void TrivialMethod(char* Ref, char* Short, char* MyDNA) {
	for (int i = 0; i < N; i++) {
		bool find = false;
		for (int j = 0; j < M - k; j++)
		{
			int not_match = 0;
			for (int m = 0; m < k; m++)
			{

				if (Short[i * k + m] != Ref[j + m])
				{
					not_match++;
					if (not_match == MAX_x) { break; }
				}
				else if (m == k - 1) find = true;
			}
			if (find)
			{
				for (int m = 0; m < k; m++)
				{
					MyDNA[j + m] = Short[i * k + m];
					//cout << "short[" << i * k + m << "]: " << Short[i * k + m] << "=>";
					//cout << "MyDNA[" << j + m << "]: " << MyDNA[j + m] << endl;

				}
				//cout << i + 1 << "��° shortRead�� myDNASequence�� ����" << endl;
				break;
			}
		}
	}
	//if (find) cout << i+1 << " ��° shortRead�� match ����########" << endl;
	//else cout << i+1 << " ��° shortRead�� match ����" << endl;
}

void main()
{
	//shortread�κ�
	string ref_DNA_str;
	string_member Reference_DNA_sequence[M];
	string_member My_DNA_sequence[M];
	double matchrate;
	int different_DNA = 0;

	time_t start, end;
	// x�� ������ �õ尪 ���� 
	srand((unsigned int)time(0));

	// DNA sequence�� ������ �õ尪 random_device ����.
	random_device rd;

	// random_device�� ���� ���� ���� �ʱ�ȭ
	mt19937 gen(rd());

	// 0���� stringLength ���� �յ��ϰ� ��Ÿ���� ������ ������ ���� �յ� ���� ����.
	uniform_int_distribution<int> dis(0, stringLength - 1);

	cout << "Input N, k :" << endl;
	cin >> N >> k;

	//���� random�� ref_DNA����
	cout << "######REF_DNA_STR����########" << endl;
	for (int z = 0; z < M; z++)
	{
		//���� ������ Reference ����
		Reference_DNA_sequence[z].str = alphanum[dis(gen)];
		Reference_DNA_sequence[z].index = z;

		//My DNA ����
		My_DNA_sequence[z].str = Reference_DNA_sequence[z].str;
		My_DNA_sequence[z].index = Reference_DNA_sequence[z].index;

		ref_DNA_str += Reference_DNA_sequence[z].str;
		cout << ref_DNA_str[z];
	}


	cout << endl;

	//shortread���� ����
	string_member* s_read = new string_member[N * k];
	cout << "$";
	ShortRead(Reference_DNA_sequence, s_read);

	//####################################################BWT�κ�#######################################################
	//�Է� ���ڿ�
	string str_input = ref_DNA_str;
	string str_dollar = "$" + str_input;
	

	//ã�ƾ� �ϴ� ���ڿ�
	string shortread = "ACGT";

	string_member Fill_the_rest[M][M];

	vector <string_member> temp_str;
	string_member temp_str_mem;

	for (int i = 0; i < str_dollar.length(); i++)
	{
		//Fill_the_rest�� �ʱ�ȭ (���� $�� index�� 0 ������ �����ϱ� ���� 0���� �ʱ�ȭ��)
		Fill_the_rest[0][0].str="$";
		Fill_the_rest[0][0].index = 0;
	}

	for (int i = 1; i < str_dollar.length(); i++)
	{
		Fill_the_rest[0][i].str = My_DNA_sequence[i].str;
		Fill_the_rest[0][i].index = My_DNA_sequence[i].index;
	}

	
	cout << "%";
	//#######FILL THE REST#########
	cout << "#######FILL THE REST#########" << endl;
	for (int i = 1; i < str_dollar.length(); i++) // fill the rest, ���ڿ� ����
	{
		Fill_the_rest[i][0].str = Fill_the_rest[i - 1][str_dollar.length() - 1].str;
		Fill_the_rest[i][0].index = Fill_the_rest[i - 1][str_dollar.length() - 1].index;
		for (int j = 1; j < str_dollar.length(); j++) {
			Fill_the_rest[i][j].str=Fill_the_rest[i-1][j-1].str;
			Fill_the_rest[i][j].index = Fill_the_rest[i - 1][j - 1].index;
		}
	}

	//for (int i = 0; i < str_dollar.length(); i++) // Fill the rest ���
	//{
	//	for(int j=0;j<str_dollar.length();j++)
	//		cout<<Fill_the_rest[i][j].str;
	//	cout << endl;
	//}



	//#######SORT#######
	for (int i = 1; i < str_dollar.length(); i++)	// insertion sort�� ����
	{
		string_member *temp = Fill_the_rest[i];
		int index = i;
		for (int j = i; j > -1; j--)
		{
			if (Fill_the_rest[index][0].str <= Fill_the_rest[j][0].str) // Ž���ϴ� j��° string�� [0]�� i��° string�� [0]���� ũ��, [j] ~ [i-1] -> [j+1] ~ [i] 
			{
				for (int k = index; k > j; k--)
				{
					for(int m=0;m<=M;m++)
						Fill_the_rest[k][m].str = Fill_the_rest[k-1][m].str;
				}
				for (int m = 0; m <= M; m++)
					Fill_the_rest[j][m].str = temp[m].str;
				index = j;
			}
		}
	}

	//cout << "##############Sort##############" << endl;
	//for (int i = 0; i < str_dollar.length(); i++) // Fill the rest ���
	//{
	//	for (int j = 0; j < str_dollar.length(); j++)
	//		cout << Fill_the_rest[i][j].str;
	//	cout << endl;
	//}

	//cout << endl;

	



	//#######BWT(T)�����########
	vector<string_member> T_tail; 
	vector<string_member> T_head;
	
	for (int i = 0; i < str_dollar.length(); i++)		// T
	{
		T_tail.push_back(Fill_the_rest[i][str_dollar.length() - 1]);
		T_head.push_back(Fill_the_rest[i][0]);
	}

	for (int i = 0; i < str_dollar.length(); i++)		// T
	{
		cout << T_head[i].str << "\t" << T_tail[i].str;
		//if (T_head[i].str == T_tail[i].str) cout << "True"; else cout << "False";
		cout<<endl; 
	}

	// FM-Index�� �ǵ�����
	vector<string_member> digit_count;
	int index = 0;
	string_member init;
	string cmpstr;
	string post_cmpstr;

	init.str = shortread[shortread.length() - 1];

	digit_count.push_back(init);
	
	cmpstr = shortread[shortread.length() - 1];

	//bool find_shortread = true;
	cout << "#" << endl;
	vector<vector<int>> find_index(k);
	cout << "!" << endl;
	for (int i = 0; i < T_tail.size(); i++)
	{
		if (cmpstr == T_tail[i].str)
		{
			digit_count[0].index++;
			find_index[0].push_back(T_tail[i].index);
			cout << cmpstr;
		}
	}
	post_cmpstr = cmpstr;
	
	cout << "$" << endl;

	for (int j = shortread.length() - 2; j >= 0; j--)
	{
		cmpstr = shortread[j];
		init.str = shortread[j];
		digit_count.push_back(init);
		for (int i = 0; i < T_tail.size(); i++)
		{
			if (cmpstr == T_tail[i].str && post_cmpstr == T_head[i].str)
			{
				//find_shortread = true;

				digit_count[digit_count.size()-1].index++;
				find_index[digit_count.size() - 1].push_back(T_tail[i].index);
				cout<< "T_tail[i].str��"<< T_tail[i].str<<"�̰�"<< "T_head[i].str, post_cmpstr�� "<< post_cmpstr<<" �� ��, " << cmpstr<<"�� �ϳ� �þ / index:"<<T_tail[i].index<<endl;
				continue;
			}
			//find_shortread = false;
		}
		post_cmpstr = cmpstr;
		
	}

	cout << "%" << endl;

	int temp=999999999;

	int benchmark;

	for (int i = 0; i < digit_count.size(); i++)
	{
		cout << "���ڿ�"<<shortread<<"��"<<digit_count[i].str<<"�� ���� ����:" << digit_count[i].index<<endl;
		if (digit_count[i].index < temp)
		{
			temp = digit_count[i].index;
			//���� ���� ������ ���ڰ� benchmark
			benchmark = i;
		}
	}

	cout << "����, shortread�� ���� Ƚ��: " << temp << endl;

	//find_index ���
	cout << "find_index���" << endl;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < find_index[i].size(); j++) {
			cout << find_index[i][j]<<",";
		}
		cout << endl;
	}

	



	//#######���� ���ڿ��� �ǵ�����########
	//
	//vector<string> sequence;

	//int temp=0;


	//for (int j = 0;j<str_dollar.length();j++) {
	//	for (int i = 0; i < str_dollar.length(); i++)
	//	{
	//		if ((T_head[temp].index == T_tail[i].index) && (T_head[temp].str == T_tail[i].str))
	//		{	
	//			cout << "T_head[temp].str: " << T_head[temp].str << " T_tail[i]: " << T_tail[i].str << endl;
	//			temp = i;
	//			sequence.push_back(T_tail[i].str);
	//			break;
	//		}
	//	}
	//}

	//cout << "#######������ �ǵ��� ���ڿ�########" << endl;
	//for (int i = 0; i < str_dollar.length(); i++)
	//{
	//	cout << sequence[i];
	//}
	//cout << endl;

}