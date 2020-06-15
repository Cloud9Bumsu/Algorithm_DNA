#include<iostream>
#include<vector>
#include<string>
#include <random>	//c++ �����Լ�
#include<time.h>
using namespace std;
#define SIZE 1000
#define SNP 20
/*
makeResult  �Լ����� �ݺ����� i ���� �ڿ��� �ٲ㼭 �ذ�
*/


/*
ũ�⸦ �ʿ信 ���� �����Ҽ� �ִ� Ŭ������ �����Ǿ� �ִ� vector���(�迭�ϰ� �����)
ã���� �ϴ� ���ڿ� sequence
���� ���̺� ���λ�� ���̻��� �ִ� ���̸� �����ϴ� ���̺�
makeKMPTable �Լ��� KMP ���̺��� ����� ��ȯ�ϴ� �Լ���

j �� i �ΰ����� �ε����� ����ϰ� j�� 0���� i �� 1���� �����ϸ�
i �ε����� j �ε����� ���� ��ġ�Ѵٸ� j  �� i �ǰ��� �Ѵ� 1�� ���������ְ�
i �ε����� j �ε����� ���� ��ġ���� �ʴ´ٸ� --j �� �� �ٽ� i �� j �ε����� ���� ���Ѵ�

i �ε����� j �ε����� ���� ��ġ������ i �ε����� �����ٰ� j �ε����� ��+1�� �־��ش�

���Ͱ���������� table���͸� ���� table���͸� ��ȯ���ش�.
*/

vector<int> makeKMPTable(string sequence) {
	int  sequenceSize = sequence.size();	//�Է¹��� ���ڿ��� ���̸� �ʱ�ȭ
	vector<int> table(sequenceSize, 0);		// vector�� ���� table�� ������ 0���� �ʱ�ȭ
	int j = 0;		// j = 0 index���� ����
	//��� ���ڸ� �ϳ��� �˻�
	//i�� 0���� ������������ ������ j == 0  i ==1 �ε������� �����ϱ⶧����!
	for (int i = 1; i < sequenceSize; i++) {
		// i ��° ���ڿ� j ��° ���ڰ� ��ġ���� �ʴ´ٸ�
		//j >0 �� �ǹ̴� �����Ҷ� j == 0 i == 1 ��ġ���� �����ϱ� ���� j�� 0���� �۾����� �ȵ�!�ε������̱⶧����
		while (j > 0 && sequence[i] != sequence[j]) {
			j--;		//i�� j �ε����� ���� ��ġ���� �������� j �� ���� -1 ������
						// i �� j �ε����� ���� �ٽ� ����!	

		}
		// i ��° �ε����� j ��° �ε����� ���� ��ġ�ϴ� ���
		// j �� ���� +1 �� ���� i �ε����� ������ �־���

		// i �ε����� j �ε����� ���� ���ٸ� j �� i �Ѵ� 1�� ������ 
		if (sequence[i] == sequence[j]) {
			table[i] = ++j;		// j = j+1 �� ������ i��° �ε����� ���� j�� ���� �־���
								//�տ������� 2�� ���Դµ� ��ġ�Ѵٸ� 3�� �־��ָ� �ȴٴ� ��
		}
	}
	return table;	//���� KMP���̺��� ��ȯ��
}


void KMPCompare(string LongSequence, string ShortSequence) {
	vector<int> table = makeKMPTable(ShortSequence);	//������ ���� �������̺� �̿���
	int LoneSequenceSize = LongSequence.size();
	int shortSequenceSize = ShortSequence.size();

	int j = 0;
	/*
	i �� �� �ؽ�Ʈ j �� ª�� �ؽ�Ʈ�ε� i �� +1 ���� ���ֱ⶧���� �ð����⵵�� O(N)�̶�����
	*/
	for (int i = 0; i < LoneSequenceSize; i++) {

		/*
		��ġ���� �ʾ�����
		*/
		while (j > 0 && LongSequence[i] != ShortSequence[j]) {
			j--;		//i�� j �ε����� ���� ��ġ���� �������� j �� ���� -1 ������(makeKMPTalbe�� ���)
		}
		/* ShortSequence�� ��� ���ڰ� ���� ������ LongSequence�� ������
		�� ���ڿ��� ��ġ�Ѵٴ� ����! */
		if (LongSequence[i] == ShortSequence[j]) {
			if (j == shortSequenceSize - 1) {
				//�ε�����ȣ�� �Ϸ��� +1 ������ ����Ҷ� �츮�� �ν��ϱ� ���� 1���� �����ڷ�����Ϸ��� +2
				printf("%d��°���� ���ڿ��� ��ġ�մϴ�!\n", i - shortSequenceSize + 2);
				/*
				KMP �˰��򿡼� ���� �ٽ����� �κ����� �ð����⵵�� ���ڿ� ã���� ����
				O(N*M)�ΰ��� O(N+M)���� ���ִ� ����ε� j��ŭ ��������!
				*/
				j = table[j];
			}

			else {
				j++;	//j�� 1�� �������Ѽ� LongSequence�� ShortSequence�� ��Ī�Ǵ��� ��� Ȯ��
			}
		}
	}
}



//�Ű������� myDNA�� ��Ʈ���带 �־��ָ� ��Ʈ���带 �������
vector<string> MakeShortRead(vector<string> myDNA, vector<string> shortRead) {
	random_device rand;		//�õ尪�� ���� �� �ִ�.
	mt19937 gen(rand());	//���� ���� ���� �ʱ�ȭ
	//dis(gen)���� �������� ������
	uniform_int_distribution<int> shortPass(0, 4);	//10~15�ε����� �̵�
	uniform_int_distribution<int> shortLen(5, 8);	//sohrt�� ����20~25
	string tmp;
	int passCheck;
	int cnt = 0;
	int over = 0;

	for (int i = 0; i < myDNA.size(); i++) {
		//ó������ �ε��� �̵� ����
		if (cnt == 0) {
			for (int j = 0; j < shortLen(gen) + 5; j++) {
				tmp += myDNA[j];
			}
			shortRead[cnt] = tmp;
		}
		cnt++;			//ī����
		tmp = "";		//tmp�ʱ�ȭ
		//������ �ε����� �̵��ϸ鼭 ����ؾ���
		passCheck = shortPass(gen);	//0~4 �����ǰ�
		i += passCheck;		//���� �ε����� passCheck�� ��ŭ ����
		for (int j = i; j < i + shortLen(gen); j++) {
			if (j == myDNA.size()) {
				over = 1;
				break;
			}
			else {
				tmp += myDNA[j];	//shrotPass���̸�ŭ �������ΰ��� shrotLen��ŭ�� ����ũ�⸸ŭ �ݺ�
			}

		}
		shortRead[cnt] = tmp;

		//cout << shortRead[cnt] << endl;
		if (over == 1) {
			break;
		}
	}

	return shortRead;
}





//������ ���

void errorRate(string str1, string str2) {
	float equalCnt = 0;
	float errCnt = 0;
	float equalFactor;

	for (int i = 0; i < str1.size(); i++) {
		if (str1[i] == str2[i]) {
			equalCnt++;
		}
		else {
			errCnt++;
		}
	}
	cout << "�� ���⼭���� ���� : " << (equalCnt + errCnt) << endl;
	cout << "��ġ�ϴ� ���⼭���� ���� : " << equalCnt << endl;
	cout << "���δٸ� ���⼭���� ���� :" << errCnt << endl;

	equalFactor = equalCnt / (equalCnt + errCnt);

	//cout << equalFactor;
	equalFactor *= 100;
	cout << "��ġ���� " << equalFactor << "%�Դϴ�" << endl;
}


int trivialResult(string referenceDNA, string shortRead) {
	int errcnt = 0;
	int cnt = 0;
	bool ok = false;
	for (int i = 0; i < referenceDNA.size()-shortRead.size(); i++) {
		cnt++;
		for (int j = 0; j < shortRead.size(); j++) {
			if (referenceDNA[i + j] == shortRead[j]) {
				;
			}
			else {
				errcnt++;
			}
			
		}
		
		if (errcnt <= 5) {
			ok = true;
			break;
		}
		errcnt = 0;
	}

	if (ok) {
		return cnt - shortRead.size();
	}
	else return -1;
}




/*Ʈ�����~

*/

int main(void) {
	string LongSequence = "ACATCTGCAAAT";
	string shortSequence = "ABCABCABA";
	string resultSequence = "aa";
	string resultRead;
	string tmp;
	string referenceDNASequence;
	string myDNASequence;
	int cnt = 0;
	int triIndex;
	int triCnt = 0;
	clock_t start, end;		//�Լ��� �ð�����
	double clockT = 0;		//end - start ���� ������ ����
	float equalCnt = 0;
	float errCnt = 0;
	float equalFactor;

	/*������ rand()�Լ��� �õ尪�� ���� ���ϱ⶧���� �յ��ϰ� ������ �������� �ʴ� ������ �ִ�
	C++ �� �����Լ��� random_device�� �� �������� ������ ����ؼ� �� ����!
	*/
	random_device rand;		//�õ尪�� ���� �� �ִ�.
	mt19937 gen(rand());	//���� ���� ���� �ʱ�ȭ
	//dis(gen)���� �������� ������
	uniform_int_distribution<int> dis(1, 4);	//1~4�� ���� �յ��ϰ� ��������


	vector<string> referenceDNA(SIZE);
	vector<string> myReferenceDNA(SIZE);
	vector<string> shortRead(SIZE);




	//dis(gen)�� �̿��Ͽ� �����ϰ� A C G T �� ����
	for (int i = 0; i < referenceDNA.size(); i++) {
		if (dis(gen) == 1) {
			referenceDNA[i] = 'A';
		}
		else if (dis(gen) == 2) {
			referenceDNA[i] = 'C';
		}
		else if (dis(gen) == 3) {
			referenceDNA[i] = 'G';
		}
		else {
			referenceDNA[i] = ' T';
		}
	}



	//�����ϵ� 1000��°���� ������ �߻�
	for (int i = 0; i < myReferenceDNA.size(); i++) {
		if ((i + 1) % SNP == 0) {
			if (dis(gen) == 1) {
				myReferenceDNA[i] = 'A';
			}
			else if (dis(gen) == 2) {
				myReferenceDNA[i] = 'C';
			}
			else if (dis(gen) == 3) {
				myReferenceDNA[i] = 'G';
			}
			else {
				myReferenceDNA[i] = ' T';
			}
		}
		else myReferenceDNA[i] = referenceDNA[i];
	}

	vector<int> KMPtable = makeKMPTable(shortSequence);	//ã���� �ϴ� ���ڿ��� ���̺� ���� 


	//��Ʈ ���� ����
	start = clock();	//�ð� ���� ����

	shortRead = MakeShortRead(myReferenceDNA, shortRead);
	for (int i = 0; i < shortRead.size(); i++) {
		if (shortRead[i] == "") break;
		//cout <<shortRead[i] <<endl;

	}
	end = clock();		//�ð� ���� ����
	clockT = (double)(end - start);
	clockT /= 1000;
	cout << "shortRead�� �����ϴµ� �ɸ� �ð� :" << clockT << "��" << endl;


	for (int i = 0; i < referenceDNA.size(); i++) {
		referenceDNASequence += referenceDNA[i];
		myDNASequence += myReferenceDNA[i];
	}

	shortSequence = "";
	/*cout << referenceDNASequence << endl;
	cout << myDNASequence << endl;
	cout << trivialResult(referenceDNASequence, shortRead[0])<<endl;*/

	//cout << shortRead[0] << endl;

	cout <<"shortReadSize : "<< shortRead.size() << endl;
	cout << shortRead[0] << endl;
	cout << shortRead[0].size();
	start = clock();

	for (int i = 0; i < shortRead.size(); i++) {
		triIndex = trivialResult(referenceDNASequence, shortRead[i]);
		if (triIndex > 0 || i ==0) {
			shortSequence = shortRead[i];
			for (int j = triIndex; j < (triIndex + shortRead[i].size() ); j++) {

				
				myDNASequence[j] = shortSequence[triCnt++];

			}
		}
		else {
			continue;
		}
		triCnt = 0;
		
		cout << (((float)i * 100) / (float)shortRead.size()) << "%��ŭ �����" << endl;
	}

	end = clock();		//�ð� ���� ����
	clockT = (double)(end - start);
	clockT /= 1000;
	cout << "trivial�� �����ϴµ� �ɸ� �ð� :" << clockT << "��" << endl;

	/*cout << referenceDNASequence << endl;
	cout << myDNASequence << endl;*/

	cout << "refenceDNASequence�� myDNASequence�� ��ġ���� :";
	errorRate(referenceDNASequence, myDNASequence);
	//cout << endl << endl;
	//cout << referenceDNASequence << endl << myDNASequence << endl;
	return 0;
}