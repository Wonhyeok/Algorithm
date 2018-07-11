#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM 7

// global variable: add count, multiplication count
int addCnt = 0;
int mulCnt = 0;

// Strassen Array Struct

typedef struct {
	int arrSize;
	int stNum;
	int rb, re; // row begin, row end
	int cb, ce; // column begin, column end
	int arr[8][8];
}SA;

// initialization to 2x2 matrix
SA initSA()
{
	int i, j;
	SA st;

	for( i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			st.arr[i][j] = 0;

	st.arrSize = 2;
	st.stNum = 2;
	st.rb = 0;
	st.re = 2;
	st.cb = 0;
	st.ce = 2;

	return st;
}

// addition
SA add(SA A, SA B)
{
	int i, j;
	SA result;

	result = initSA();
	result.rb = result.cb = 0;
	result.re = result.ce = A.stNum;
	result.stNum = A.stNum;

	for(i = 0; i < A.stNum; i++)
		for(j = 0; j < A.stNum; j++)
		{
			result.arr[i][j] = A.arr[i][j] + B.arr[i][j];
			addCnt++; // addition count increase
		}
	
	return result;
}


// substitution
SA sub(SA A, SA B)
{
	int i, j;
	SA result;

	result = initSA();
	result.rb = result.cb = 0;
	result.re = result.ce = A.stNum;
	result.stNum = A.stNum;

	for(i = 0; i < A.stNum; i++)
		for(j = 0; j < A.stNum; j++)
		{
			result.arr[i][j] = A.arr[i][j] - B.arr[i][j];
			addCnt++; // addition count increase
		}
	
	return result;
}

// find strassen number ( if arraysize = 3, stnum is 4 )
int findSNum(SA st)
{
	int i;
	int num = 2;

	for(i = 0; i < 10; i++)
		if(st.arrSize > num)
			num = num*2;
		else
			return num;

	return num;
}

// print array by row begin, row end, column begin, column end
void printArray(SA st)
{
	int i, j;
	
	printf("\n");

	for(i = st.rb; i < st.re; i++)
	{
		for(j = st.cb; j < st.ce; j++)
			printf("%7d", st.arr[i][j]);
		printf("\n");
	}
/*	
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
			printf("%7d", st.arr[i][j]);
		printf("\n");
	}
*/	
//	printf("add count: %d    mult count: %d\n", addCnt, mulCnt );

	printf("\n");
}

// recursive strassen matrix multiplication
// 
SA mul(SA A, SA B)
{
	SA A11, A12, A21, A22, B11, B12, B21, B22;
	SA C11, C12, C21, C22;
	SA M1, M2, M3, M4, M5, M6, M7;
	SA result;

// init structures
	A11 = initSA();
	A12 = initSA();
	A21 = initSA();
	A22 = initSA();
	B11 = initSA();
	B12 = initSA();
	B21 = initSA();
	B22 = initSA();
	C11 = initSA();
	C12 = initSA();
	C21 = initSA();
	C22 = initSA();
	M1 = initSA();
	M2 = initSA();
	M3 = initSA();
	M4 = initSA();
	M5 = initSA();
	M6 = initSA();
	M7 = initSA();
	result = initSA();

	int num, i, j;

// if stnum is 2, it is 2x2 matrix.
// simple calculation
	if( A.stNum == 2 )
	{
		int a, b, c, d, e, f, g, h;
		int m1, m2, m3, m4, m5, m6, m7;

		a = A.arr[A.rb][A.cb]; 
		b = A.arr[A.rb][A.cb+1];
		c = A.arr[A.rb+1][A.cb]; 
		d = A.arr[A.rb+1][A.cb+1];
		e = B.arr[B.rb][B.cb]; 
		f = B.arr[B.rb][B.cb+1];
		g = B.arr[B.rb+1][B.cb]; 
		h = B.arr[B.rb+1][B.cb+1];
	
		m1 = a*(f-h);
		m2 = (a+b)*h;
		m3 = (c+d)*e;
		m4 = d*(g-e);
		m5 = (a+d)*(e+h);
		m6 = (b-d)*(g+h);
		m7 = (a-c)*(e+f);

		result.arr[0][0] = m5+m4-m2+m6;
		result.arr[0][1] = m1+m2;
		result.arr[1][0] = m3+m4;
		result.arr[1][1] = m5+m1-m3-m7;
		
		addCnt += 18;
		mulCnt += 7;

		result.rb = 0;
		result.re = 2;
		result.cb = 0;
		result.ce = 2;
		result.stNum = 2;

		return result;
	}

// else, bigger than 2x2 matrix. 
// have to divide to small matrix.

	num = A.stNum / 2; 				// divide by 2


	// make 4 divided matrix
	// each position is stored

	// A11
	A11.stNum = num;
	A11.rb = 0;
	A11.re = num;
	A11.cb = 0;
	A11.ce = num;
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			A11.arr[i][j] = A.arr[i][j];

	// A12
	A12.stNum = num;
	A12.rb = 0;
	A12.re = num;
	A12.cb = 0;
	A12.ce = num;
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			A12.arr[i][j] = A.arr[i][j+num];

	// A21
	A21.stNum = num;
	A21.rb = 0;
	A21.re = num;
	A21.cb = 0;
	A21.ce = num;
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			A21.arr[i][j] = A.arr[i+num][j];

	// A22
	A22.stNum = num;
	A22.rb = 0;
	A22.re = num;
	A22.cb = 0;
	A22.ce = num;
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			A22.arr[i][j] = A.arr[i+num][j+num];

	// B11
	B11.stNum = num;
	B11.rb = 0; 
	B11.re = num;
	B11.cb = 0;
	B11.ce = num;
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			B11.arr[i][j] = B.arr[i][j];

	// B12
	B12.stNum = num;
	B12.rb = 0; 
	B12.re = num;
	B12.cb = 0;
	B12.ce = num;
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			B12.arr[i][j] = B.arr[i][j+num];

	// B21
	B21.stNum = num;
	B21.rb = 0; 
	B21.re = num;
	B21.cb = 0;
	B21.ce = num;
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			B21.arr[i][j] = B.arr[i+num][j];

	// B22
	B22.stNum = num;
	B22.rb = 0;
	B22.re = num;
	B22.cb = 0;
	B22.ce = num;
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			B22.arr[i][j] = B.arr[i+num][j+num];
	
//	printArray(A11);

//	printf("*** A11.stnum: %d\n", A11.stNum);

	// strassen calculation
	
	M1 = mul( A11, sub(B12, B22) );
	M2 = mul( add(A11, A12), B22 );
	M3 = mul( add(A21, A22), B11 );
	M4 = mul( A22, sub(B21, B11) );
	M5 = mul( add(A11, A22), add(B11, B22) );
	M6 = mul( sub(A12, A22), add(B21, B22) );
	M7 = mul( sub(A11, A21), add(B11, B12) );

	M1.stNum = M2.stNum = M3.stNum = M4.stNum = M5.stNum = M6.stNum = M6.stNum = num;
	M1.rb = M2.rb = M3.rb = M4.rb = M5.rb = M6.rb = M7.rb = 0;
	M1.re = M2.re = M3.re = M4.re = M5.re = M6.re = M7.re = num;
	M1.cb = M2.cb = M3.cb = M4.cb = M5.cb = M6.cb = M7.cb = 0;
	M1.ce = M2.ce = M3.ce = M4.ce = M5.ce = M6.ce = M7.ce = num;


	C11 = add( sub( add(M5, M4), M2), M6 );
	C12 = add( M1, M2 ); 
	C21 = add( M3, M4 );
	C22 = sub( sub( add(M5, M1), M3), M7 );

	result.stNum = A.stNum;
	result.rb = result.cb = 0;
	result.ce = result.re = A.stNum;

	// C11
	for(i = 0; i < num; i++)
		for(j = 0; j < num; j++)
			result.arr[i][j] = C11.arr[i][j];

	// C12
	for(i = 0; i < num; i++)
		for(j = num; j < result.stNum; j++)
			result.arr[i][j] = C12.arr[i][j-num];

	// C21
	for(i = num; i < result.stNum; i++)
		for(j = 0; j < num; j++)
			result.arr[i][j] = C21.arr[i-num][j];

	// C22
	for(i = num; i < result.stNum; i++)
		for(j = num; j < result.stNum; j++)
			result.arr[i][j] = C22.arr[i-num][j-num];

	return result;
}



int main()
{
	int i, j;
	int temp;
	SA m1, m2, m3;

	srand(time(NULL));
	
	// 3x3 matrix multiplication
	
	m1 = initSA();
	m2 = initSA();
	m3 = initSA();

	m1.arrSize = 3;
	m2.arrSize = 3;
	
	m1.rb = 0; m1.re = 3; m1.cb = 0; m1.ce = 3;
	m2.rb = 0; m2.re = 3; m2.cb = 0; m2.ce = 3;

	for (i=0; i < m1.arrSize; i++)
	{
		for (j=0; j < m1.arrSize; j++)
		{
			m1.arr[i][j] = rand()%100;
			m2.arr[i][j] = rand()%100;
		}
	}

	m1.stNum = findSNum(m1);
	m2.stNum = findSNum(m2);

	m3 = mul(m1, m2);

	m3.arrSize = 3;
	m3.rb = m3.cb = 0;
	m3.re = m3.ce = 3;

	printf("---A 3x3---\n");
	printArray(m1);
	printf("---B 3x3---\n");
	printArray(m2);
	printf("---C 3x3---\n");
	printArray(m3);
	printf("add count: %d, mul count: %d\n\n", addCnt, mulCnt);
	

	/* ---------------------------------- */

	// 7x7 matrix multiplication
	SA n1, n2, n3;
	n1 = initSA();
	n2 = initSA();

	addCnt = 0;
	mulCnt = 0;

	n1.arrSize = NUM;
	n2.arrSize = NUM;
	
	n1.rb = 0; n1.re = NUM; n1.cb = 0; n1.ce = NUM;
	n2.rb = 0; n2.re = NUM; n2.cb = 0; n2.ce = NUM;

	for (i = 0; i < n1.re; i++)
	{
		for (j = 0; j < n1.ce; j++)
		{
			n1.arr[i][j] = rand()%100;
			n2.arr[i][j] = rand()%100;
		}
	}

	n1.stNum = findSNum(n1);
	n2.stNum = findSNum(n2);

	n3 = mul(n1, n2);
	
	n3.arrSize = NUM;
	n3.rb = n3.cb = 0;
	n3.re = n3.ce = NUM;

	printf("---A 7x7---\n");
	printArray(n1);
	printf("---B 7x7---\n");
	printArray(n2);
	printf("---C 7x7---\n");
	printArray(n3);
	printf("add count: %d, mul count: %d\n\n", addCnt, mulCnt);
	return 0;
}
