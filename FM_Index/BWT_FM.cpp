//2018112085 박범수 Week11
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class string_member
{
public:
	string str;
	int index=0;
};

void main()
{
	//입력 문자열
	string str_input = "ParkBumSuParkBumSuParkBumSuParkBumSu";
	string str_dollar = "$"+str_input ;
	
	//찾아야 하는 문자열
	string shortread = "Bum";

	vector<vector <string_member>> Fill_the_rest;

	vector <string_member> temp_str;
	string_member temp_str_mem;
	
	Fill_the_rest.push_back(temp_str);

	for (int i = 0; i < str_dollar.length(); i++)
	{
		Fill_the_rest[0].push_back(temp_str_mem);
	}

	for (int i = 0; i < str_dollar.length(); i++)
	{
		
		Fill_the_rest[0][i].str = str_dollar[i];
		for (int j = 0; j < i; j++)
		{
			if (Fill_the_rest[0][j].str == Fill_the_rest[0][i].str)
				Fill_the_rest[0][i].index++;
		}
	}

	

	//#######FILL THE REST#########
	cout << "#######FILL THE REST#########" << endl;

	for (int i = 0; i < str_dollar.length(); i++) // vector에 str채우기
	{
		Fill_the_rest.push_back(Fill_the_rest[0]);
	}

	for (int i = 1; i < str_dollar.length(); i++) // fill the rest, 문자열 변경
	{
		Fill_the_rest[i][0].str = Fill_the_rest[i - 1][str_dollar.length() - 1].str;
		Fill_the_rest[i][0].index = Fill_the_rest[i - 1][str_dollar.length() - 1].index;
		for (int j = 1; j < str_dollar.length(); j++) {
			Fill_the_rest[i][j].str=Fill_the_rest[i-1][j-1].str;
			Fill_the_rest[i][j].index = Fill_the_rest[i - 1][j - 1].index;
		}
	}

	for (int i = 0; i < str_dollar.length(); i++) // Fill the rest 출력
	{
		for(int j=0;j<str_dollar.length();j++)
			cout<<Fill_the_rest[i][j].str;
		cout << endl;
	}



	//#######SORT#######
	for (int i = 1; i < str_dollar.length(); i++)	// insertion sort로 정렬
	{
		vector<string_member> temp = Fill_the_rest[i];
		int index = i;
		for (int j = i; j > -1; j--)
		{
			if (Fill_the_rest[index][0].str <= Fill_the_rest[j][0].str) // 탐색하는 j번째 string의 [0]이 i번째 string의 [0]보다 크면, [j] ~ [i-1] -> [j+1] ~ [i] 
			{
				for (int k = index; k > j; k--)
				{
					Fill_the_rest[k] = Fill_the_rest[k-1];
				}
				Fill_the_rest[j] = temp;
				index = j;
			}
		}
	}

	cout << "##############Sort##############" << endl;
	for (int i = 0; i < str_dollar.length(); i++) // Fill the rest 출력
	{
		for (int j = 0; j < str_dollar.length(); j++)
			cout << Fill_the_rest[i][j].str;
		cout << endl;
	}

	cout << endl;

	



	//#######BWT(T)만들기########
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
		if (T_head[i].str == T_tail[i].str) cout << "True"; else cout << "False";
		cout<<endl; 
	}

	// FM-Index로 되돌리기
	vector<string_member> digit_count;
	int index = 0;
	string_member init;
	string cmpstr;
	string post_cmpstr;

	init.str = shortread[shortread.length() - 1];

	digit_count.push_back(init);
	
	cmpstr = shortread[shortread.length() - 1];

	for (int i = 0; i < T_tail.size(); i++)
	{
		if (cmpstr == T_tail[i].str)
		{
			digit_count[0].index++;
		}
	}
	post_cmpstr = cmpstr;
		
	for (int j = shortread.length() - 2; j >= 0; j--)
	{
		cmpstr = shortread[j];
		init.str = shortread[j];
		digit_count.push_back(init);
		for (int i = 0; i < T_tail.size(); i++)
		{
			if (cmpstr == T_tail[i].str && post_cmpstr == T_head[i].str)
			{

				digit_count[digit_count.size()-1].index++;
			}
		}
		post_cmpstr = cmpstr;
	}


	int temp=999999999;

	for (int i = 0; i < digit_count.size(); i++)
	{
		cout << "문자열"<<shortread<<"중"<<digit_count[i].str<<"에 대한 갯수:" << digit_count[i].index<<endl;
		if (digit_count[i].index < temp) temp = digit_count[i].index;
	}

	cout << "따라서, shortread의 등장 횟수: " << temp;



	//#######원래 문자열로 되돌리기########
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

	//cout << "#######원래로 되돌린 문자열########" << endl;
	//for (int i = 0; i < str_dollar.length(); i++)
	//{
	//	cout << sequence[i];
	//}
	//cout << endl;

}