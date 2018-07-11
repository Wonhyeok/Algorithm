#include<stdio.h>
#include<time.h>
#include<stdlib.h>


void createArray(int *A1,int *A2,int *A3)
{
	int i, a=0, b=600;
	unsigned int c; // 난수 생성을 위한 변수. 
	srand(time(NULL)); // 난수 생성을 위한 함수. 
	for (i = 0; i < 300; i++)
	{
		c=rand();
		c=c%10000;
		A1[i]=c; // 랜덤 숫자로 배열 1 생성.
	}
	for (i = 0; i < 300; i++)
	{
		A2[i]=a;
		a=a+2;  // 올림차순으로 배열 2 생성. 2씩 등차 수열.
	}
	for (i = 0; i < 300; i++)
	{
		A3[i]=b;
		b=b-2;  // 내림차순으로 배열 3 생성. 2씩 등차 수열.
	}
}

void print(int *A1, int *A2, int *A3) // Array Sorting 전 출력 함수. 
{
	int i; // Loop 변수
	
	for (i = 0; i < 300; i++) 
	{
		printf("%8d",A1[i]); // 각 숫자마다 8칸 씩 출력.
		if(i%10==9)
			printf("\n"); // 줄마다 10개 씩 출력.
	}
	printf("Array Before Sorting for Case 1\n");
	
	for (i = 0; i < 300; i++)
	{
		printf("%8d",A2[i]); // 각 숫자마다 8칸 씩 출력.
		if(i%10==9)
			printf("\n"); // 줄마다 10개 씩 출력.
	
	}
	printf("Array Before Sorting for Case 2\n");
	
	for (i = 0; i < 300; i++)
	{
		printf("%8d",A3[i]); // 각 숫자마다 8칸 씩 출력.
		if(i%10==9)
			printf("\n"); // 줄마다 10개 씩 출력.
	}
	printf("Array Before Sorting for Case 3\n");
}

void printArray(int A[], int num, int count, char type[]) // Parameter: 배열, Case 번호, 연산 수, Sort 종류
{
	int i; 
	for (i = 0; i < 300; i++) // Array 모두 출력.
	{
		printf("%8d",A[i]); //8칸 씩 맞춰서 출력.
		if(i%10==9) // 열개 씩 출력.
		printf("\n");
	}
	printf("Array After Sorting for Case %d\n", num);
	printf("Instruction Count Case for %s Sort %d: %d\n",type, num ,count); // 총 연산 수 출력.
}


void bubbleSort(int A[], int num)
{
	int i,j,count=1; // 루프, 횟수 변수.
	int temp; // 교환 매개 변수.
	char type[20]="Bubble"; // Sort 종류 이름.
	for(i=0; i<299; i++) 
	{
		for(j=0; j<299; j++)
		{
			if(A[j]<=A[j+1]) // 배열의 앞 칸이 뒷 칸보다 작을 때 교환., 즉 내림차순.
			{
				temp=A[j]; 
				A[j]=A[j+1];
				A[j+1]=temp;
				count++; // 연산 횟수 Count 
			}
		}
	}
	printArray(A, num, count, type); // Array 출력. Argument: 배열, Case 번호, 연산 수, Sort 종류
}


int main(void)
{
	int A1[300]; // 배열 A1 선언.
	int A2[300]; // 배열 A2 선언.
	int A3[300]; // 배열 A3 선언.

	//주석 한번에 설정. Ctrl K C 해제는 Ctrl K U

	createArray(A1,A2,A3); // 배열 A1,A2,A3 생성.
	print(A1,A2,A3); // Sorting 전 배열 출력.

	bubbleSort(A1,1); // Argument: 배열 A1 , Case 번호1
	bubbleSort(A2,2); // Argument: 배열 A2 , Case 번호2
	bubbleSort(A3,3); // Argument: 배열 A3 , Case 번호3



	return 0;
}
