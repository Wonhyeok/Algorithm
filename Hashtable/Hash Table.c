#include<stdio.h>
#include<stdlib.h>
#include<time.h>

double count1=0,count2=0,count3=0;

int len1=0,len2=0,len3=0;

struct Node{
	int data; // 노드 안의 수.
	struct Node* next; // 다음 노드 포인터.
}; // 각 데이터를 저장하기 위한 노드 선언.

struct Chain{
	int key; // Function에서 Modulus 계산 후에 나온 Key 값. 
	struct Node* list; 
}; // 각 Key별로 데이터를 저장하고 있는 Chain.

struct Table{
	int size; // 전체 Table의 크기. 즉 Table의 크기는 Hash Function의 Divisor만큼의 크기. 
	struct Chain** table; // Table이 1차 배열이므로 Chain의 Element를 쓰기 위해서는 포인터 2개.
}; // 전체 Hash Table 선언. 배열 형. 

struct Table* create(int tSize)  
{
	int i=0;
	
	struct Table* h;
	h = (struct Table*)malloc(sizeof(struct Table)); // Hash Chain들을 저장할 Table 할당. 

	if(!h) // 동적할당 실패시 NULL 값 반환. 
		return NULL;

	h->size= tSize; // size는 전체 table 크기. 
	h->table= (struct Chain**)malloc(sizeof(struct Chain*)*tSize); // 

	if(!h->table) // 동적할당 실패시 NULL 값 반환. 
		return NULL;

	for(; i<tSize; i++)
	{
		h->table[i] = (struct Chain*)malloc(sizeof(struct Chain)); // Hash Node들을 저장할 Chain을 array로 할당.
		if (!h->table[i])
			return NULL;

		h->table[i]->key =0;
		h->table[i]->list=NULL;
	}

	return h;

}

int function(int data, int tSize)
{
	return data%tSize;
}


void insert(struct Table* h, int data)
{
	struct Chain* hChain;
	struct Node* temp;
	struct Node* node=(struct Node*)malloc(sizeof(struct Node));
	
	hChain = h->table[function(data, h->size)];

	temp = hChain->list;

	if(!node)
	{
		return;
	}

	node ->data = data;
	node ->next = NULL;

	if(!temp)
	{
		hChain->list =node;
		count1++;
		count2++;
		count3++;

	}
	else
	{
		struct Node* temp2;
		temp2 = hChain ->list;
		hChain->list = node;
		node ->next = temp2;
		count1++;
		count2++;
		count3++;
	}



	return;
} 

int print(struct Table* h, int *A1)
{
	int i=0;
	int j=0;
	double num=0;
	int temp,max,min;

	for(i=0; i< h->size; i++)
	{
		A1[i]=0;
	}

	for(i=0; i< h->size; i++)
	{
		struct Chain * hChain = h ->table[i];
		struct Node * temp= hChain -> list;

		printf("Key %d: ", i);
		while (temp)
		{
			printf("%d ", temp->data);
			temp = temp ->next;
			A1[i]++;
			num++;
		}

		printf("\n");
	}
	
	for(i=0; i<h->size-1; i++)
	{
		min=i;
		for(j=i+1; j<h->size; j++)
		{
			if(A1[j]<A1[min])
			{
				min=j;
			}
		}

		temp=A1[i];
		A1[i]=A1[min];
		A1[min]=temp;

	}
	printf("Min Length: %d\n",A1[0]);
	printf("Max Length: %d\n",A1[h->size-1]);
	printf("Average Length: %.2lf\n",num/h->size);
	
	return 0;
}

int main(void)
{
	int i,j;
	unsigned int c; // 난수 생성을 위한 변수. 
	struct Table* h1 = create(11);
	struct Table* h2 = create(17);
	struct Table* h3 = create(34);
	int *A1;
	double num;

	srand(time(NULL)); // 난수 생성을 위한 함수. 

	

	A1=(int*)malloc(34 * sizeof(*A1));
	

	for (i = 0; i < 100; i++)
	{
		c=rand();
		c=c%100;
		insert(h1, c);
		insert(h2, c);
		insert(h3, c);
	}
	
	printf("The Hash Table by function 1\n");
	print(h1,A1);
	printf("\n");
	printf("The Hash Table by function 2\n");
	print(h2,A1);
	printf("\n");
	printf("The Hash Table by function 3\n");
	print(h3,A1);
	printf("\n");

	count1=0,count2=0,count3=0;

	insert(h1, 733);
	insert(h1, 27);
	insert(h1, 1);
	insert(h1, 999);
	insert(h1, 222);
	insert(h1, 319);
	insert(h1, 88);

	printf("The Hash Table by function 1 after insertion\n");
	print(h1,A1);
	printf("Average Number of Comparison : %.2lf",count1/7);
	printf("\n");

	count1=0,count2=0,count3=0;

	insert(h2, 733);
	insert(h2, 27);
	insert(h2, 1);
	insert(h2, 999);
	insert(h2, 222);
	insert(h2, 319);
	insert(h2, 88);

	printf("The Hash Table by function 2 after insertion\n");
	print(h2,A1);
	printf("Average Number of Comparison : %.2lf", count2/7);
	printf("\n");

	count1=0,count2=0,count3=0;

	insert(h3, 733);
	insert(h3, 27);
	insert(h3, 1);
	insert(h3, 999);
	insert(h3, 222);
	insert(h3, 319);
	insert(h3, 88);

	printf("The Hash Table by function 3 after insertion\n");
	print(h3,A1);
	printf("Average Number of Comparison : %.2lf", count3/7);
	printf("\n");

	free(A1);
	//주석 한번에 설정. Ctrl K C 해제는 Ctrl K U

	return 0;
}