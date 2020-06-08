#include<iostream>
#include<vector>
#include<string>
using namespace std;


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


int main(void) {
	string LongSequence = "AABCABCABASAAABCABCABAAAAABCABCABASA";
	string shortSequence = "ABCABCABA";
	vector<int> KMPtable = makeKMPTable(shortSequence);	//ã���� �ϴ� ���ڿ��� ���̺� ���� 
	cout << shortSequence;
	printf("�� ���� ���� ���̺� ��� :");
	for (int i = 0; i < KMPtable.size(); i++) {
		printf("%d ", KMPtable[i]);
	}

	printf("\nLongSequence�� ShortSequence �� :\n");
	KMPCompare(LongSequence, shortSequence);
	return 0;
}