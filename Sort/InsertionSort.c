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



void insertSort(int A[], int num)
{
	int i,j,count=1; // 루프, 횟수 변수.
	int temp; // 기준 값 변수.
	char type[20]="Insertion";
	for(i=1; i<300; i++) 
	{
		temp=A[i]; // 기준 값 설정. 
		j=i-1; // 기준 값 바로 이전 값.
		while(j>=0 && A[j]<=temp) // 기준 값보다 이전 값이 작거나 같을 때 (내림차순), 루프는 기준 이전 값부터 0까지 순차적으로 비교.
		{
			A[j+1]=A[j]; // 기준 값에 이전 값을 대입.
			j--; // 루프 변수 -1
			count++; // 연산+1 
		}
		A[j+1]=temp; // 해당 위치에 기준 값을 삽입.
	}

	printArray(A, num, count, type); // Array 출력. Argument: 배열, Case 번호, 연산 수, Sort 종류
	
}


int main(void)
{
	int A1[300]; // 배열 A1 선언.
	int A2[300]; // 배열 A2 선언.
	int A3[300]; // 배열 A3 선언.


	createArray(A1,A2,A3); // 배열 A1,A2,A3 생성.
	print(A1,A2,A3); // Sorting 전 배열 출력.

	insertSort(A1,1); // Argument: 배열 A1 , Case 번호1
	insertSort(A2,2); // Argument: 배열 A2 , Case 번호2
	insertSort(A3,3); // Argument: 배열 A3 , Case 번호3

	return 0;
}