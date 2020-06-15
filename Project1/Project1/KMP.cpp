#include<iostream>
#include<vector>
#include<string>
#include <random>	//c++ 랜덤함수
#include<time.h>
using namespace std;
#define SIZE 3000000
#define SNP 1000
/*
makeResult  함수에서 반복문의 i 값을 뒤에로 바꿔서 해결
*/


/*
크기를 필요에 따라 조절할수 있는 클래스로 구현되어 있는 vector사용(배열하고 비슷함)
찾고자 하는 문자열 sequence
실패 테이블 접두사와 접미사의 최대 길이를 포함하는 테이블
makeKMPTable 함수는 KMP 테이블을 결과로 반환하는 함수로

j 와 i 두가지의 인덱스를 사용하고 j는 0부터 i 는 1부터 시작하며
i 인덱스와 j 인덱스의 값이 일치한다면 j  와 i 의값을 둘다 1씩 증가시켜주고
i 인덱스와 j 인덱스의 값이 일치하지 않는다면 --j 한 후 다시 i 와 j 인덱스의 값을 비교한다

i 인덱스와 j 인덱스의 값이 일치했을때 i 인덱스의 값에다가 j 인덱스의 값+1을 넣어준다

위와같은방식으로 table벡터를 만들어서 table벡터를 반환해준다.
*/

vector<int> makeKMPTable(string sequence) {
	int  sequenceSize = sequence.size();	//입력받은 문자열의 길이를 초기화
	vector<int> table(sequenceSize, 0);		// vector로 만든 table의 값들을 0으로 초기화
	int j = 0;		// j = 0 index부터 시작
	//모든 문자를 하나씩 검사
	//i를 0부터 시작하지않은 이유는 j == 0  i ==1 인덱스부터 시작하기때문임!
	for (int i = 1; i < sequenceSize; i++) {
		// i 번째 문자와 j 번째 문자가 일치하지 않는다면
		//j >0 의 의미는 시작할때 j == 0 i == 1 위치에서 시작하기 때문 j가 0보다 작아지면 안됨!인덱스값이기때문에
		while (j > 0 && sequence[i] != sequence[j]) {
			j--;		//i와 j 인덱스의 값이 일치하지 않을때는 j 의 값을 -1 해준후
						// i 와 j 인덱스의 값을 다시 비교함!	

		}
		// i 번째 인덱스와 j 번째 인덱스의 값이 일치하는 경우
		// j 의 값에 +1 한 값을 i 인덱스의 값으로 넣어줌

		// i 인덱스와 j 인덱스의 값이 같다면 j 와 i 둘다 1씩 더해줌 
		if (sequence[i] == sequence[j]) {
			table[i] = ++j;		// j = j+1 을 해준후 i번째 인덱스의 값에 j의 값을 넣어줌
								//앞에번에서 2가 나왔는데 일치한다면 3을 넣어주면 된다는 뜻
		}
	}
	return table;	//만든 KMP테이블을 반환함
}


void KMPCompare(string LongSequence, string ShortSequence) {
	vector<int> table = makeKMPTable(ShortSequence);	//위에서 만든 실패테이블 이용함
	int LoneSequenceSize = LongSequence.size();
	int shortSequenceSize = ShortSequence.size();

	int j = 0;
	/*
	i 는 긴 텍스트 j 는 짧은 텍스트인데 i 는 +1 씩만 해주기때문에 시간복잡도가 O(N)이라고보면됨
	*/
	for (int i = 0; i < LoneSequenceSize; i++) {

		/*
		일치하지 않았을때
		*/
		while (j > 0 && LongSequence[i] != ShortSequence[j]) {
			j--;		//i와 j 인덱스의 값이 일치하지 않을때는 j 의 값을 -1 해준후(makeKMPTalbe과 비슷)
		}
		/* ShortSequence의 모든 문자가 지금 비교중인 LongSequence와 같을때
		즉 문자열이 일치한다는 뜻임! */
		if (LongSequence[i] == ShortSequence[j]) {
			if (j == shortSequenceSize - 1) {
				//인덱스번호로 하려면 +1 이지만 출력할때 우리가 인식하기 쉽게 1부터 센숫자로출력하려면 +2
				printf("%d번째에서 문자열이 일치합니다!\n", i - shortSequenceSize + 2);
				/*
				KMP 알고리즘에서 제일 핵심적인 부분으로 시간복잡도가 문자열 찾을때 보통
				O(N*M)인것을 O(N+M)으로 해주는 기능인데 j만큼 점프해줌!
				*/
				j = table[j];
			}

			else {
				j++;	//j를 1씩 증가시켜서 LongSequence와 ShortSequence가 매칭되는지 계속 확인
			}
		}
	}
}



//매개변수로 myDNA와 쇼트리드를 넣어주면 쇼트리드를 만들어줌
vector<string> MakeShortRead(vector<string> myDNA, vector<string> shortRead) {
	random_device rand;		//시드값을 얻을 수 있다.
	mt19937 gen(rand());	//난수 생성 엔진 초기화
	//dis(gen)으로 난수값을 가져옴
	uniform_int_distribution<int> shortPass(10, 15);	//0~4인덱스를 이동
	uniform_int_distribution<int> shortLen(20, 25);	//sohrt의 길이5~8
	string tmp;
	int passCheck;
	int cnt = 0;
	int over = 0;

	for (int i = 0; i < myDNA.size(); i++) {
		//처음에만 인덱스 이동 안함
		if (cnt == 0) {
			for (int j = 0; j < shortLen(gen) + 5; j++) {
				tmp += myDNA[j];
			}
			shortRead[cnt] = tmp;
		}
		cnt++;			//카운팅
		tmp = "";		//tmp초기화
		//이제는 인덱스를 이동하면서 출력해야함
		passCheck = shortPass(gen);	//0~4 임의의값
		i += passCheck;		//시작 인덱스를 passCheck값 만큼 증가
		for (int j = i; j < i + shortLen(gen); j++) {
			if (j == myDNA.size()) {
				over = 1;
				break;
			}
			else {
				tmp += myDNA[j];	//shrotPass길이만큼 우측으로가서 shrotLen만큼의 길이크기만큼 반복
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


/*
쇼트 시퀀스가 롱 시퀀스의 뒷부분에 일치하다면 롱 시퀀스를 반환
*/

string makeResult(string LongSequence, string ShortSequence) {
	vector<int> table = makeKMPTable(ShortSequence);	//위에서 만든 실패테이블 이용함
	int LoneSequenceSize = LongSequence.size();
	int shortSequenceSize = ShortSequence.size();
	int check = 0;
	int j = 0;
	/*
	shortSequence의 길이만큼 LongSequence의 뒤랑 비교
	*/
	for (int i = LoneSequenceSize - shortSequenceSize; i < LoneSequenceSize; i++) {

		/*
		일치하지 않았을때
		*/
		while (j > 0 && LongSequence[i] != ShortSequence[j]) {
			j--;		//i와 j 인덱스의 값이 일치하지 않을때는 j 의 값을 -1 해준후(makeKMPTalbe과 비슷)
		}
		/* ShortSequence의 모든 문자가 지금 비교중인 LongSequence와 같을때
		즉 문자열이 일치한다는 뜻임! */
		if (LongSequence[i] == ShortSequence[j]) {
			if (j == shortSequenceSize - 1) {
				//인덱스번호로 하려면 +1 이지만 출력할때 우리가 인식하기 쉽게 1부터 센숫자로출력하려면 +2
				//printf("%d번째에서 문자열이 일치합니다!\n", i - shortSequenceSize + 2);
				check = 1;
				/*
				KMP 알고리즘에서 제일 핵심적인 부분으로 시간복잡도가 문자열 찾을때 보통
				O(N*M)인것을 O(N+M)으로 해주는 기능인데 j만큼 점프해줌!
				*/
				j = table[j];
			}

			else {
				j++;	//j를 1씩 증가시켜서 LongSequence와 ShortSequence가 매칭되는지 계속 확인
			}
		}
	}
	//일치했었다면 LongSequence 반환
	if (check == 1) return LongSequence;
	else
	{
		return "일치없음";
	}
}


//오차율 출력

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
	cout << "총 염기서열의 개수 : " << (equalCnt + errCnt) << endl;
	cout << "일치하는 염기서열의 개수 : " << equalCnt << endl;
	cout << "서로다른 염기서열의 개수 :" << errCnt << endl;

	equalFactor = equalCnt / (equalCnt + errCnt);

	//cout << equalFactor;
	equalFactor *= 100;
	cout << "일치율은 " << equalFactor << "%입니다" << endl;
}




int main(void) {
	string LongSequence = "ACATCTGCAAAT";
	string shortSequence = "ABCABCABA";
	string resultSequence = "aa";
	string resultRead;
	string tmp;
	string referenceDNASequence;
	string myDNASequence;
	int cnt = 0;
	clock_t start, end;		//함수의 시간측정
	double clockT = 0;		//end - start 값을 저장할 변수
	float equalCnt = 0;
	float errCnt = 0;
	float equalFactor;

	/*기존의 rand()함수는 시드값이 점점 변하기때문에 균등하게 난수를 생성하지 않는 문제가 있다
	C++ 의 랜덤함수인 random_device는 비 결정적인 난수를 사용해서 더 좋다!
	*/
	random_device rand;		//시드값을 얻을 수 있다.
	mt19937 gen(rand());	//난수 생성 엔진 초기화
	//dis(gen)으로 난수값을 가져옴
	uniform_int_distribution<int> dis(1, 4);	//1~4의 수를 균등하게 나오게함


	vector<string> referenceDNA(SIZE);
	vector<string> myReferenceDNA(SIZE);
	vector<string> shortRead(SIZE);



	//dis(gen)을 이용하여 랜덤하게 A C G T 를 생성
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



	//복사하되 1000번째마다 스닙이 발생
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




	//출력 해봄
	/*cout << "referenceDNA :" << endl;;
	for (int i = 0; i < SIZE; i++) {
		cout << referenceDNA[i];
	}
	cout << endl;
	cout << "myReferenceDNA :" << endl;;
	for (int i = 0; i < SIZE; i++) {
		cout << myReferenceDNA[i];
	}
	cout << endl;*/









	vector<int> KMPtable = makeKMPTable(shortSequence);	//찾고자 하는 문자열로 테이블 만듬 


	//쇼트 리드 만듬
	start = clock();	//시간 측정 시작

	shortRead = MakeShortRead(myReferenceDNA, shortRead);
	for (int i = 0; i < shortRead.size(); i++) {
		if (shortRead[i] == "") break;
		//cout <<shortRead[i] <<endl;

	}
	end = clock();		//시간 측정 종료
	clockT = (double)(end - start);
	clockT /= 1000;
	cout << "shortRead를 생성하는데 걸린 시간 :" << clockT << "초" << endl;

	start = clock();

	resultRead = shortRead[0];







	for (int i = 1; i < shortRead.size(); i++) {
		if (makeResult(resultRead, shortRead[i]) == resultRead) {
			//cout << "resultRead : " << resultRead << endl;
			;
		}
		else
		{

			tmp = shortRead[i];
			//tmp.resize(tmp.size() - i);
			for (int j = 0; j < shortRead[i].size(); j++) {

				tmp.resize(tmp.size() - 1);

				if (makeResult(resultRead, tmp) == resultRead) {
					cnt = j + 1;
					break;
				}



			}
			tmp = shortRead[i];
			for (int j = shortRead[i].size() - cnt; j < shortRead[i].size(); j++) {
				resultRead += tmp[j];
			}
		}
		//cout << "resultRead : " << resultRead << endl;

		cout << (((float)i * 100) / (float)shortRead.size()) << "%만큼 진행됨" << endl;

	}
	end = clock();
	clockT = (double)(end - start);
	clockT /= 1000;
	cout << "shortRead를 합치는데 걸린 시간 :" << clockT << "초" << endl;

	//cout << "refence  myDNA result 순임 :" << endl;
	for (int i = 0; i < SIZE; i++) {
		referenceDNASequence += referenceDNA[i];
	}
	//cout <<referenceDNASequence<< endl;
	for (int i = 0; i < SIZE; i++) {
		myDNASequence += myReferenceDNA[i];
	}
	//cout <<myDNASequence<< endl;
	resultRead.resize(SIZE);

	//cout << resultRead << endl << endl << endl;


	cout << "reference DNA와 shortRead를 사용하여 만든 resultDNA 일치율 :" << endl;;
	errorRate(referenceDNASequence, resultRead);
	return 0;
}