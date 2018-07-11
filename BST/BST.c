#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

typedef struct Node{
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
}node;

typedef node* tp; 

struct queue{
    tp element;
    struct queue *next;
};

typedef struct queue Queue;


void createArray(int *A)
{
	int i;
	unsigned int c; // 난수 생성을 위한 변수. 
	srand(time(NULL)); // 난수 생성을 위한 함수. 
	for (i = 0; i < 30; i++)
	{
		c=rand();
		c=c%100;
		A[i]=c; // 랜덤 숫자로 배열 1 생성.
	}
}

tp makenode(int num)
{
	tp node = (tp)malloc(sizeof(struct Node));
	node ->left=NULL;
	node ->data=num;
	node ->right=NULL;
	return node;
}

void makeleft(tp node1, tp node2) // node1은 node2가 달릴 주소. 
{
	if(node1->left!=NULL)
		free(node1 ->left);
	node1->left=node2;
}

void makeright(tp node1, tp node2) // node1은 node2가 달릴 주소. 
{
	if(node1->right!=NULL)
		free(node1 ->right);
	node1->right=node2;
}

void changeleft(tp node1, tp node2)
{
	node1->left = node2;
}

void changeright(tp node1, tp node2)
{
	node1->right = node2;
}

tp removeleft(tp node)
{
	tp rnode;

	if(node!=NULL)
	{
		rnode=node->left;
		node->left=NULL;
	}
	return rnode;
}

tp removeright(tp node)
{
	tp rnode;

	if(node!=NULL)
	{
		rnode=node->right;
		node->right=NULL;
	}
	return rnode;
}

void recover(tp node, int num)
{
	node->data=num;
}



//tp searchparent(tp node, tp temp)
//{
//	if(node->left!=NULL && node->left==temp)
//	{
//		return node;
//	}
//	else if(node->left!=NULL)
//	{
//		searchparent(node->left,temp);
//		if(node->right!=NULL)
//			searchparent(node->right,temp);
//	}
//	if(node->right!=NULL && node->right==temp)
//	{
//		return node;
//	}
//	else if(node->left!=NULL)
//	{
//		searchparent(node->left,temp);
//		if(node->right!=NULL)
//			searchparent(node->right,temp);
//	}
//}

tp parent(tp node, int num) // 부모노드를 찾아주는 함수
{ 
	tp temp;
	tp parent = NULL; // 부모노드 초기화. 

	do
	{
		temp = node; 
		if(num == node->data) // 노드의 값이 부모값과 동일 하면 
			return parent;
		if(num < node->data)
		{
			parent = node; 
			node = node->left;
		}
		else
		{
			parent = node;
			node = node->right;
		}
	}while(node);

	return parent;
}

tp treeSearch(tp node, int key) // 이진 탐색 트리 자체에서 키 값 찾는 함수. 
{ 
	while(node)
	{
		if(key == node->data) // 만일 노드의 데이터 값이 key와 동일 하면 노드 값 반환. 
		{
			printf("%d Key Found\n",node->data);
			return node;
		}
		if(key < node->data)
		{
			printf("%d ", node->data);
			node = node->left;
		}
		else
		{
			printf("%d ", node->data);
			node = node->right;
		}
	}
	return NULL;
}

tp search(tp root, int key) // Recursive식으로 키 값을 찾는 함수
{ 
	if(!root)
		return NULL;
	if(key == root->data)
		return root;
	if(key < root->data)
		return search(root->left, key);
	else
		return search(root->right, key);
}


void insert(tp* node, int num)
{
	tp pnode = NULL;
	tp cnode = *node;
	tp nnode = NULL;


	while(cnode != NULL)
	{ 
		if(num== cnode->data) // 중복된 수는 제외.
			return;
		pnode = cnode;

		if(cnode->data >= num)
			cnode = cnode->left;
		else
			cnode = cnode->right;
	}

	nnode=makenode(num);


	if(pnode!=NULL)
	{
		if(num<pnode->data)
			makeleft(pnode, nnode);
		else
			makeright(pnode, nnode);
	}
	else
		*node = nnode;
}

tp removenode(tp* node, int num)
{
	tp temp=makenode(NULL); // 가상노드.
	tp rparent =temp; // 부모노드 포인터에 가상노드 주소 삽입.
	tp cnode = *node; // 현재노드.
	tp rnode; // 지우려는 대상 노드.

	tp child;

	tp renode;
	tp ppnode;

	int rdata;

	changeright(temp, *node);

	while(cnode!=NULL && cnode->data != num)
	{
		rparent = cnode;
		if(num<cnode->data)
			cnode=cnode->left;
		else 
			cnode=cnode->right;
	}
	if(cnode==NULL)
		return NULL;
	rnode=cnode;

	if(rnode->left == NULL && rnode-> right == NULL)
	{
		if(rparent->left == rnode)
			removeleft(rparent);
		else
			removeright(rparent);
	}

	else if(rnode->left==NULL || rnode->right ==NULL)
	{
		

		if(rnode->left!=NULL)
			child = rnode->left;
		else
			child = rnode->right;

		if(rparent->left== rnode)
			changeleft(rparent, child);
		else
			changeright(rparent, child);
	}

	else
	{
		renode = rnode->right; // 대체 하려는 노드.
		ppnode = rnode; // 대체 노드의 부모 노드.

		while(renode->left !=NULL)
		{
			ppnode = renode;
			renode = renode ->left;
		}

		rdata=rnode->data;
		recover(rnode,renode->data);

		if(ppnode->left == renode)
			changeleft(ppnode, renode->right);
		else
			changeright(ppnode, renode->right);

		rnode=renode;
	}

	if(temp ->right != *node)
		*node = temp->right;

	free(temp);
	return rnode;
}

tp minnode(struct Node* root) 
{ 
	if(root == NULL) return NULL; 
	while(root->left != NULL) 
		root = root->left; 
	return root; 
} 

tp maxnode(struct Node* root) 
{ 
	if(root == NULL) return NULL; 
	while(root->right != NULL) 
		root = root->right; 
	return root; 
} 

tp successor(tp node,int num) 
{ 
	tp y=parent(node,num);
	tp x=node;

	if(node ==NULL) return NULL;
	if(node->right!=NULL)
	{
		return maxnode(node->right);
	}
	while(y!=NULL && x==y->right)
	{
		x=y;
		y=parent(y,num);
	}
	return y;
} 

tp predecessor(tp node, int num)
{
	tp y=parent(node,num);
	tp x=node;

	if(node ==NULL) return NULL;
	if(node->left!=NULL)
	{
		return maxnode(node->left);
	}
	while(y!=NULL && x==y->left)
	{
		x=y;
		y=parent(y,num);
	}
	return y;
}


void inorder(tp ptr)
{ 
	if(ptr)
	{	
		inorder(ptr->left);
		printf("%2d  ", ptr->data);
		inorder(ptr->right);
	}
	
}

void enqueue(Queue **queue, tp node)
{
	Queue *q  = NULL;
	Queue *head  = *queue;
	Queue * temp;
	
	if(!(*queue))
	{
		q =(Queue *)malloc(sizeof(Queue));
		q->element = node;
		q->next = NULL;
		*queue = q;
	}
	else
	{
		q = *queue;
		while(q->next)
		{
			q = q->next;
		}
		
		temp =(Queue *)malloc(sizeof(Queue));
		q->next = temp;
		temp->element = node;
		temp->next = NULL;
		*queue = head;
	}
}

int empty( Queue *q)
{
	if(!q) return 1;
	
	return 0;
}
tp front(Queue *queue)
{
	if(queue)
		return queue->element;
}

void dequeue(Queue **queue)
{
	Queue *q = *queue;
	
	Queue *node = q;
	q = node->next;
	node = NULL;
	free(node);
	
	*queue = q;
}

void levelorder(tp node)
{

 Queue *q =  NULL;
 enqueue(&q, node);

 
 while(!empty(q))
 {
 	tp cNode = front(q);
 	
 	printf("%2d  ", cNode->data);
    
    if(cNode->left)
     	enqueue(&q, cNode->left);
    if(cNode->right)
    	enqueue(&q, cNode->right);
	
	dequeue(&q);
 }
}


int main(void)
{
	int A[30];
	int i=0; 
	tp node= NULL;
	tp rnode;

	tp suc=NULL;
	tp prc=NULL;

	//주석 한번에 설정. Ctrl K C 해제는 Ctrl K U

	createArray(A); // 배열 A1생성.

	printf("Random 30 Keys\n"); 
	for(; i<30; i++) 
	{
		printf("%2d  ",A[i]);
	}
	printf("\n\n",A[i]);
	
	for(i=0; i<30; i++) // 2-2 랜덤 숫자 30개로 Binary Tree 형성.
	{
		insert(&node, A[i]);
	}

	printf("Question 2 Binary Tree Elements(Same Keys are Ignored)\n"); 
	levelorder(node);
	printf("\n\n"); 

	printf("Question 3 Search Elements & Question 4 Nearest Neighbours\n");
	if(treeSearch(node, 17)==NULL)
	{
		printf("Search Failed for 17\n");
		//prc=predecessor(parent(node,17), 17);
		//printf("Predecessor: %d\n", prc->data);
	}
	else
		printf("17 is the nearest key itself\n");

	prc=NULL;
	if(treeSearch(node, 22)==NULL)
	{
		printf("Search Failed for 22\n");
		//prc=predecessor(parent(node,22),22);
		//printf("Predecessor: %d\n", prc->data);
	}
	else
		printf("22 is the nearest key itself\n");

	prc=NULL;
	if(treeSearch(node, 88)==NULL)
	{
		printf("Search Failed for 88\n");
		//prc=predecessor(parent(node,88),88);
		//printf("Predecessor: %d\n", prc->data);
	}
	else
		printf("88 is the nearest key itself\n");
	printf("\n"); 

	printf("Question 5 Insert Elements\n");
	insert(&node, 15);
	printf("Insert Result for 15 \n");
	levelorder(node);
	printf("\n");

	//inorder(node);

	insert(&node, 55);
	printf("Insert Result for 55 \n");
	levelorder(node);
	printf("\n");

	//inorder(node);

	insert(&node, 95);
	printf("Insert Result for 95 \n");
	levelorder(node);
	printf("\n\n");

	//inorder(node);

	printf("Question 6 Delete Elements\n");
	if(treeSearch(node, 37)!=NULL)
	{
		rnode=removenode(&node, 37);
		free(rnode);
		printf("BST after deletion for 37\n");
		levelorder(node);
		printf("\n");
	}
	else
		printf("Delete Failed. There is no correponding element\n");
	if(treeSearch(node, 98)!=NULL)
	{
		rnode=removenode(&node, 98);
		free(rnode);
		printf("BST after deletion for 98\n");
		levelorder(node);
		printf("\n");
	}
	else
		printf("Delete Failed. There is no correponding element\n");
	if(treeSearch(node, 50)!=NULL)
	{
		rnode=removenode(&node, 50);
		free(rnode);
		printf("BST after deletion for 50\n");
		levelorder(node);
		printf("\n");
	}
	else
		printf("Delete Failed. There is no correponding element\n");
	if(treeSearch(node, 70)!=NULL)
	{
		rnode=removenode(&node, 70);
		free(rnode);
		printf("BST after deletion for 70\n");
		levelorder(node);
		printf("\n");
	}
	else
		printf("Delete Failed. There is no correponding element\n");

	return 0;
}