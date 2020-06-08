#include<iostream>
#include<vector>
#include<string>
using namespace std;


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


int main(void) {
	string LongSequence = "AABCABCABASAAABCABCABAAAAABCABCABASA";
	string shortSequence = "ABCABCABA";
	vector<int> KMPtable = makeKMPTable(shortSequence);	//찾고자 하는 문자열로 테이블 만듬 
	cout << shortSequence;
	printf("에 대한 실패 테이블 출력 :");
	for (int i = 0; i < KMPtable.size(); i++) {
		printf("%d ", KMPtable[i]);
	}

	printf("\nLongSequence와 ShortSequence 비교 :\n");
	KMPCompare(LongSequence, shortSequence);
	return 0;
}