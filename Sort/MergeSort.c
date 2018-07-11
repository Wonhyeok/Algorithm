#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

int count; // 연산 횟수 변수.

void createArray(int *A1,int *A2,int *A3) // Array 생성 함수.
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

int merge(int A[], int left, int mid, int right) // 쪼개진 배열을 다시 합쳐서 재정렬 하는 함수. Parameter: 배열, 첫 index, 중간 index, 마지막 index.
{
	int leftFront=left; // 첫 index.
	int leftEnd=mid; // 중간 index.
	int rightFront=mid+1; // 중간+1 index.
	int rightEnd=right; // 마지막 index.
	int i=0; // Loop 변수.

	int* A4= (int*)malloc(sizeof(int)*(right+1)); // 0부터 right값의 index를 가진 integer형 배열 할당. 두 쪼개진 배열을 합쳐 재배열을 위한 임시 배열.
	int j =left; // 쪼개진 배열의 가장 첫번째 index

	
	while((leftFront<=leftEnd) && (rightFront <=rightEnd)) // 양쪽 쪼개진 배열의 각 첫째값들을 비교해서 작은 순으로 배열에 삽입. 
	{
		if(A[leftFront]>A[rightFront]) // 양쪽 쪼개진 배열 중 첫번째 배열의 첫 index가 두번쨰 배열의 첫 index 값 보다 클 때.
		{
			A4[j]=A[rightFront++]; // 재정렬 하는 배열에 둘 중 작은 두번째 배열 값을 대입하고, 두번째 배열의 index 값 +1
			count++; // 연산횟수 증가.
		}
		else // 양쪽 쪼개진 배열 중 첫번째 배열의 첫 index가 두번쨰 배열의 첫 index 값 보다 작거나 같을 때.
		{
			A4[j]=A[leftFront++]; // 재정렬 하는 배열에 둘 중 작거나 같은 첫번째 배열 값을 대입하고, 첫번째 배열의 index 값 +1
			count++; // 연산횟수 증가.
		}
		j++; // 재정렬 배열의 index 도 증가.
	}

	if(leftFront>leftEnd) // 첫번째 배열이 먼저 모두 정렬 되었을 때
	{
		for(i=rightFront; i<= rightEnd; i++) // 두번째 배열의 남아 있는 index 들 만큼 Loop.
		{
			A4[j++] = A[i]; // 두번째 배열의 각 index 값을 남아 있는 재정렬 행렬에 삽입 후 재정렬 행렬의 index 증가.
			count++; // 연산횟수 증가.
		}
	}
	else // 두번째 배열이 먼저 모두 정렬 되었을 때
	{
		for(i=leftFront; i<= leftEnd; i++) // 첫번째 배열의 남아 있는 index 들 만큼 Loop.
		{
			A4[j++] = A[i]; // 첫번째 배열의 각 index 값을 남아 있는 재정렬 행렬에 삽입 후 재정렬 행렬의 index 증가.
			count++; // 연산횟수 증가.
		}
	}

	for(i=left; i<=right; i++) // 재정렬 한 행렬을 또 다시 원래 행렬에 복사 후 반복. 
	{
		A[i]=A4[i]; // index 값 증가. 
		count++; // 연산횟수 증가.
	}

	free(A4); // 임시행렬 동적 할당 해제. 

	return 0;

}

int mergeDivide(int A[], int left, int right) // 배열을 이등분 하는 함수. Parameter: 배열, 배열 첫 index, 배열의 마지막 index
{
	int mid=0; // mid 값 선언.
	
	if(left<right) // 배열의 맨 앞 index 가 맨 뒤 index 보다 작을때, 즉 더 이상 이등분이 불가능 할때 까지 재귀 함수를 호출.
	{
		mid=(left+right)/2; // 배열의 중간 index. 
		mergeDivide(A,left,mid); // 배열의 첫 index부터 중간 index까지 다시 이등분.
		mergeDivide(A,mid+1,right); // 배열의 중간 index+1부터 마지막 index까지 다시 이등분.
		merge(A,left,mid,right); // 쪼개진 배열을 다시 합쳐서 재정렬 하는 함수. Argument: 배열, 첫 index, 중간 index, 마지막 index.
		
	}

	return 0;
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



int main(void)
{
	int A1[300]; // 배열 A1 선언.
	int A2[300]; // 배열 A2 선언.
	int A3[300]; // 배열 A3 선언.
	int aSize; // 배열의 방 갯수를 구하는데 쓰이는 변수.
	char type[20]="Merge"; // 배열 종류 명.


	createArray(A1,A2,A3); //배열 A1,A2,A3 생성.
	print(A1,A2,A3); // Sorting 전 배열 출력.

	aSize=(sizeof(A1)/sizeof(int)); // 배열의 index 갯수를 구하는 공식. 여기선 300으로 A1,A2,A3 동일.

	count=1;// 연산 횟수 초기화.
	mergeDivide(A1,0,aSize-1); // 배열을 이등분 하는 함수. Argument: 배열, 배열 첫 index=0, 배열의 마지막 index
	printArray(A1, 1, count, type); // 배열 출력 함수 Argument: 배열, Case 번호, 연산 횟수, 배열 종류 명.

	count=1;// 연산 횟수 초기화.
	mergeDivide(A2,0,aSize-1); // 배열을 이등분 하는 함수. Argument: 배열, 배열 첫 index=0, 배열의 마지막 index
	printArray(A2, 2, count, type); // 배열 출력 함수 Argument: 배열, Case 번호, 연산 횟수, 배열 종류 명.

	count=1;// 연산 횟수 초기화.
	mergeDivide(A3,0,aSize-1); // 배열을 이등분 하는 함수. Argument: 배열, 배열 첫 index=0, 배열의 마지막 index
	printArray(A3, 3, count, type); // 배열 출력 함수 Argument: 배열, Case 번호, 연산 횟수, 배열 종류 명.

	return 0;
}

