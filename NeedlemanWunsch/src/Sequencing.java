//2017112098 한재진

import java.util.Random;
import java.util.Vector;
import java.util.ArrayList;
import java.util.Scanner;

public class Sequencing
{
	
	char[] Sequence1;
	char[] Sequence2;
	int[][] matrix;
	String SString1 = "";
	String SString2 = "";
	final static int PRIME = 101;

	public static void main(String[] args)
	{

		Vector<String> MyDNA = makeDNA();
		Vector<String> Ref = makeRef(MyDNA);
		Vector<String> shortRead = makeSR(MyDNA);

        //실행시간 계산
        
        //long start = System.currentTimeMillis(); 
         
		//shortRead = makeSR(myReferenceDNA);
		//for (int i = 0; i < shortRead.size(); i++) {
			//if (shortRead.get(i) == "") break;
			//cout <<shortRead[i] <<endl;
			
		//}

        //long end = System.currentTimeMillis(); 
        //System.out.println( "shortRead를 생성하는데 걸린 시간  : " + ( end - start )/1000.0 + "초");
        //실행시간 계산
        
		System.out.println("데이터 삽입 후 shortRead의 크기 : "+ shortRead.size());
		System.out.println("shortRead 벡터 전체 출력 : "+ shortRead);
	      
		//needleman wunsch algorithim
	    //니들만 브니쉬 알고리즘

		String MyDNAString = "";
		String RefString = "";
      
		for (int i=0; i<MyDNA.size(); i++)
		{
				MyDNAString += MyDNA.get(i);
		}
		
		for (int i=0; i<MyDNA.size(); i++)
		{
				RefString += Ref.get(i);
		}

		
	  	//Scanner input = new Scanner(System.in);
		String FisrtSequence;
		String SecondSequence;


		Vector<String> RDNA = new Vector<String>(MyDNA.size());
		for (int i=0; i<MyDNA.size(); i++)
		{
				RDNA.add(i,"");
		}
		
		//System.out.println("초기화된 RDNA 벡터 전체 출력 : "+ RDNA);
		//System.out.println("초기화된 RDNA 벡터 전체 출력 : "+ RDNA.size());
		
        //실행시간 계산
        
        long start = System.currentTimeMillis(); 
        //시작
		
		int Count = 0;
		while(Count<shortRead.size())
		{
			//System.out.println("sr size : "+ shortRead.size());
			//System.out.println("Count : "+ Count);
			//System.out.print("Input Sequence 1:");
			FisrtSequence = RefString;
			//System.out.print("Input Sequence 2:");
			//secondSequence = MyDNAString;
			SecondSequence = shortRead.get(Count);

			Sequencing s = new Sequencing();
			s.Init(FisrtSequence.toUpperCase().replace(" ", "")
					.toCharArray(), SecondSequence.toUpperCase().replace(" ", "")
					.toCharArray());
			s.Process();
			Vector<String> forR = s.Backtrace();
			//System.out.println();
			//sequencer.printAlignment();
			
			String a = forR.get(0);
			String b = forR.get(1);
			
			
			// index 결정 문제
			

		
			int Index;
			
	        Vector<Integer> vector = new Vector<Integer>();
	        vector=rabinKarp(RefString, a);
	        //System.out.println(vector);
			
			// index 결정 문제
	
			
			//System.out.println("Ref : "+ RefString);
			//System.out.println("RNDA size : "+ RDNA.size());
			//System.out.println("RNDA size : "+ RDNA);
			

			for (int j=0; j<vector.size(); j++)	
			{
				Index = vector.get(j);
				for(int i = 0; i< a.length() ; i++)
				{

		
					if(b.charAt(i) != '_' && RDNA.get(Index + i) == "")
					{
						RDNA.add(Index+i, Character.toString(b.charAt(i)));
						//System.out.println("복원 DNA 벡터 전체 출력 : "+ RDNA);
						//System.out.println("RNDA size : "+ RDNA.size());
						RDNA.setSize(MyDNA.size());

					}
					else if(b.charAt(i) != '_' && RDNA.get(Index + i) != "")
					{

						if(RDNA.get(Index + i) == Character.toString(b.charAt(i)))
						{
							//System.out.println("복원 DNA 벡터 전체 출력 : "+ RDNA);
							//System.out.println("RNDA size : "+ RDNA.size());
							RDNA.setSize(MyDNA.size());
						}
						else if(RDNA.get(Index + i) != Character.toString(b.charAt(i)))
						{

							RDNA.add(Index+i, Character.toString(b.charAt(i)));
							//System.out.println("복원 DNA 벡터 전체 출력 : "+ RDNA);
							//System.out.println("RNDA size : "+ RDNA.size());
							RDNA.setSize(MyDNA.size());
						}
					}
					else if( b.charAt(i) == '_')
					{
						//System.out.println("복원 DNA 벡터 전체 출력 : "+ RDNA);
						//System.out.println("RNDA size : "+ RDNA.size());
						RDNA.setSize(MyDNA.size());
					}

				}
			}
			

			
			Count++;
		}


        long end = System.currentTimeMillis(); 
        System.out.println( "실행 시간 : " + ( end - start )/1000.0 + "초");
        //끝
        //실행시간 계산


		System.out.println("복원 DNA 벡터 전체 출력 : "+ RDNA);
		System.out.println("복원 DNA 벡터 크기 : "+ RDNA.size());
		String RDNAString="";
		for (int i=0; i<RDNA.size(); i++)
		{
				RDNAString += RDNA.get(i);
		}
	      
		System.out.println("복원 DNA 벡터 전체 출력 : "+ RDNAString);

		FisrtSequence = MyDNAString;
		//System.out.print("Input Sequence 2:");
		//secondSequence = MyDNAString;
		SecondSequence = RDNAString;

		Sequencing s2 = new Sequencing();
		s2.Init(FisrtSequence.toUpperCase().replace(" ", "")
				.toCharArray(), SecondSequence.toUpperCase().replace(" ", "")
				.toCharArray());
		s2.Process();
		Vector<String> forR = s2.Backtrace();
		System.out.println();
		s2.PrintR();
		
		String a = forR.get(0);
		String b = forR.get(1);
		
		System.out.println("복원 DNA와 MyDNA의 일치율");
		errorRate(a, b);
		System.out.println("MyDNA와 ReferenceDNA와의 일치율");
		errorRate(RefString, MyDNAString);
		
	}


	
	public static Vector<String> makeDNA()
	{
		Vector<String> DNA = new Vector<String>();
			
	    int size = 4;
	    
		for(int j=0; j<125; j++) { //j*4 = DNA 사이즈 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		
			ArrayList<Integer> list = new ArrayList<Integer>(size);
			for(int i = 1; i <= size; i++) {
				list.add(i);
			}

			Random Rand = new Random();
			while(list.size() > 0) 
			{
				int index = Rand.nextInt(list.size());
				switch(list.remove(index)){
				case 1: DNA.addElement("A"); break;
				case 2: DNA.addElement("C"); break;
				case 3: DNA.addElement("T"); break;
				case 4: DNA.addElement("G"); break;        
				}
			}

		}
		
		
		//아래 for문은 스닙 위치 표시. 주석처리시 위치 표시 없음.
		/*
		for (int j=1; 4*j<DNA.size(); j++)
		{
			DNA.set(4*j, DNA.get(4*j)+"*");  //j*n n은 n번째마다 스닙 발생.
		}
		*/

		
	      System.out.println("데이터 삽입 후 vector의 크기 : "+ DNA.size());
	      System.out.println("DNA 벡터 전체 출력 : "+DNA);
   
		
		return DNA;
	}
	
	public static Vector<String> makeRef(Vector<String> MyDNA)
	{
		Vector<String> Ref =new Vector<String>();
		
		for (int i=0; i<MyDNA.size(); i++)
		{
			Ref.add(MyDNA.get(i));
		}
			
	    int size = 4;
		for(int j=1; j<(MyDNA.size()/4); j++) {

		
			ArrayList<Integer> list = new ArrayList<Integer>(size);
			for(int i = 1; i <= size; i++) {
				list.add(i);
			}

			Random Rand = new Random();
			while(list.size() > 0) 
			{
				int index = Rand.nextInt(list.size());
				switch(list.remove(index)){
				case 1: Ref.set(j*4,"A"); break;
				case 2: Ref.set(j*4,"C"); break;
				case 3: Ref.set(j*4,"T"); break;
				case 4: Ref.set(j*4,"G"); break;        //j*n n은 n번째마다 스닙 발생, * 지우면 스닙 위치 표시 없음.
				}
			}

		}
		
	      System.out.println("데이터 삽입 후 Ref의 크기 : "+ Ref.size());
	      System.out.println("Ref 벡터 전체 출력 : "+Ref);

		return Ref;
	}
	
	public static Vector<String> makeSR(Vector<String> MyDNA)
	{
		Vector<String> shortRead =new Vector<String>();
		String a = "";
		int Count = 0;
		/*for (int i=0; i<MyDNA.size(); i++)
		{
			shortRead.add("");
		}*/
		
		while(Count<MyDNA.size())
		{
			int c = 8;

			for(int j=0; j<c; j++)
			{
				if(j+Count>=MyDNA.size())
				{a += "";}
				else
				{a += MyDNA.get(Count+j);}
			}

			shortRead.add(Count, a);
			a = "";

			Count++;
		}
		

		
		
		return shortRead;
	}
	
	void Init(char[] seqA, char[] seqB) {
		Sequence1 = seqA;
		Sequence2 = seqB;
		matrix = new int[Sequence1.length + 1][Sequence2.length + 1];
		for (int i = 0; i <= Sequence1.length; i++) {
			for (int x = 0; x <= Sequence2.length; x++) {
				if (i == 0) {
					matrix[i][x] = -x;
				} else if (x == 0) {
					matrix[i][x] = -i;
				} else {
					matrix[i][x] = 0;
				}
			}
		}
	}

	
	private int Weight(int i, int x) {
		if (Sequence1[i - 1] == Sequence2[x - 1]) {
			return 1;
		} else {
			return -1;
		}
	}

	void PrintR() {
		System.out.println("Sequence 1: " + SString1);
		System.out.println("Sequence 2: " + SString2);
	}

	void Process() {
		for (int i = 1; i <= Sequence1.length; i++) {
			for (int x = 1; x <= Sequence2.length; x++) {
				int scoreDiag = matrix[i - 1][x - 1] + Weight(i, x);
				int scoreLeft = matrix[i][x - 1] - 1;
				int scoreUp = matrix[i - 1][x] - 1;
				matrix[i][x] = Math
						.max(Math.max(scoreDiag, scoreLeft), scoreUp);
			}
		}
	}

	Vector<String> Backtrace() {
		Vector<String> forR = new Vector<String>();
		int i = Sequence1.length;
		int x = Sequence2.length;
		while (i > 0 && x > 0) {
			if (matrix[i][x] == matrix[i - 1][x - 1] + Weight(i, x)) {
				SString1 += Sequence1[i - 1];
				SString2 += Sequence2[x - 1];
				i--;
				x--;
				continue;
			} else if (matrix[i][x] == matrix[i][x - 1] - 1) {
				SString1 += "_";
				SString2 += Sequence2[x - 1];
				x--;
				continue;
			} else {
				SString1 += Sequence1[i - 1];
				SString2 += "_";
				i--;
				continue;
			}
		}
		SString1 = new StringBuffer(SString1).reverse()
				.toString();
		SString2 = new StringBuffer(SString2).reverse()
				.toString();
		
		forR.add(SString1);
		forR.add(SString2);
		return forR;
	}

	public static void errorRate(String str1, String str2) {
		float equalCnt = 0;
		float errCnt = 0;
		float equalFactor;

		for (int i = 0; i < str2.length(); i++) {
			if (str1.charAt(i) == str2.charAt(i)) {
				equalCnt++;
			}
			else {
				errCnt++;
			}
		}

		equalFactor = equalCnt / (equalCnt + errCnt);
		
		//cout << equalFactor;
		equalFactor *= 100;
		
		System.out.println("일치율 : "+ equalFactor);
	}
	
    private static Vector<Integer> rabinKarp(String text, String pattern) {
    	Vector<Integer> vector = new Vector<Integer>();
        int n = pattern.length();
        int m = text.length();
        int hash = hashF(pattern, n);

        String slide = "";

        for (int i = 0; i < n && i < m; i++) {
            slide += text.charAt(i);
        }

        int hashSlide = hashF(slide, slide.length());

        if (hashSlide == hash) {
        	vector.add(Comparator(text, pattern, n, 0));
        }

        int i = n;

        while (i < m) {
            hashSlide = hashRoll(text.charAt(i - n), text.charAt(i), hashSlide, n - 1);
            if (hash == hashSlide) {
                vector.add(Comparator(text, pattern, n, i - n + 1));
            }
            i++;
        }
        return vector;
    }

    static int Comparator(String text, String pat, int n, int i) {
        int k = 0;
        while (k < n) if (pat.charAt(k) != text.charAt(i + k++)) break;
        if (k == n) ;
        return i;
    }

    private static int hashRoll(char old, char nova, int hash, int n) {
        return (int) (((hash - (old)) / PRIME) + ((nova) * Math.pow(PRIME, n)));
    }

    private static int hashF(String pat, int n) {
        int res = pat.charAt(0);
        for (int i = 1; i < n; i++) {
            res += ((pat.charAt(i)) * Math.pow(PRIME, i));
        }
        return res;
    }


}
