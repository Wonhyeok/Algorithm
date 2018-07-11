//
// Created by Won Hyeok Choi on 2016. 12. 5..
//

#include <iostream>
#include "main.h"
#include "class.h"
#include "rbtree.h"
using namespace std;

//int leafNum=0;
extern RBTree rb;

void RBTree::insert(Student s)
{
    Student x, y;
    x=root;
    y=NULL;
    if(root==NULL) //만약에 root에 아직 아무런 노드가 없으면.
    {
        root=s; //맨 처음 들어오는 Student 노드가 root가 됨.
        s->parent=NULL; //맨 처음 node의 parent는 없으므로 NULL값을 대입.
    }
    else
    {
        while(x!=NULL) // 루트에서 출발.
        {
            y=x;
            if(x->id < s->id) //큰 값이면 오른쪽으로
                x=x->right;
            else //작은 값이면 왼쪽으로
                x=x->left;
        }
        s->parent=y; //x가 NULL이 되서 탈출하는 순간에는 y는 x의 부모값을 가리키고 있는 상태. 즉 s의 부모가 y를 가리키게 만듬.
        if(y->id<s->id) //큰 값이면 오른쪽으로
            y->right=s;
        else //작은 값이면 왼쪽으로
            y->left=s;
        s->left=NULL;
        s->right=NULL;
        s->color='r';
    }
    rb.totalNode++;
    insertfix(s);
    getHeight();
}

void RBTree::insertfix(Student s)
{
//    printf("start");

    Student u; // u는 삼촌. uncle
    if(root==s) // 루트면 검은 색.
    {
        s->color='b';
        return;
    }
    while(s->parent!=NULL && s->parent->color=='r') // 만일 부모가 red가 되지 않을 때 까지
    {
        if(s->parent->parent->left==s->parent){ // 부모가 왼쪽 자식이고
            if(s->parent->parent->right!=NULL){ // 오른쪽에 삼촌이 존재할 때 (Case 1)
                u=s->parent->parent->right; // 삼촌 값 대입.
                if(u->color=='r'){ // 삼촌이 red이면
                    s->parent->color='b';
                    u->color='b';
                    s->parent->parent->color='r'; // 부모, 삼촌은 black으로 교체. 조부모는 red로 교체.
                    s=s->parent->parent; // 조부모를 다시 s에 대입. 왜냐하면 계속 조상 위로 올라가면서 color를 바꿔줌.
                }else{
                    if(s->parent->right == s){
                        s=s->parent;
                        leftrotate(s);
                    }
                    s->parent->color='b';
                    s->parent->parent->color='r';
                    rightrotate(s->parent->parent);

                }
            }else{
                if(s->parent->right == s){
                    s=s->parent;
                    leftrotate(s);
                }
                s->parent->color='b';
                s->parent->parent->color='r';
                rightrotate(s->parent->parent);
            }
        }else{ // 부모가 오른쪽 자식이고
            if(s->parent->parent->left!=NULL){ // 왼쪽에 삼촌이 존재할 때
                u=s->parent->parent->left;
                if(u->color=='r'){
                    s->parent->color='b';
                    u->color='b';
                    s->parent->parent->color='r';
                    s=s->parent->parent;
                }else{
                    if(s->parent->right == s){
                        s=s->parent;
                        leftrotate(s);
                    }
                    s->parent->color='b';
                    s->parent->parent->color='r';
                    rightrotate(s->parent->parent);

                }             // 만일 삼촌이 블랙일 때도 밑에 코드가 한번 더 불려야 된다.
            }else{
                if(s->parent->left == s){
                    s=s->parent;
                    rightrotate(s);
                }
                s->parent->color='b';
                s->parent->parent->color='r';
                leftrotate(s->parent->parent);
            }
        }
    }
    root->color='b';
}

void RBTree::leftrotate(Student p) // p는 s의 parent node를 인자로 받은 상태.
{
//    printf("sl");
    if(p->right==NULL)
        return ;
    else //(Case 2-1)
    {
        Student y=p->right;// y는 현재 삽입 되는 값.
        if(y->left!=NULL)
        {
            p->right=y->left;
            y->left->parent=p;
        }
        else // y의 왼자식이 없다면
            p->right=NULL; //y 부모의 오른쪽 값을 일단 비워줌.

        if(p->parent==NULL){
            root=y;
            y->parent=NULL;
        }else
        {
            y->parent=p->parent;
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->left=p;
        p->parent=y;
    }
//    printf("fl");
}


void RBTree::rightrotate(Student p)
{
//    printf("sr");
    if(p->left==NULL)
        return ;
    else
    {
        Student y=p->left;
        if(y->right!=NULL)
        {
            p->left=y->right;
            y->right->parent=p;
        }
        else
            p->left=NULL;

        if(p->parent==NULL){
            root=y;
            y->parent=NULL;
        }else
        {
            y->parent=p->parent;
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->right=p;
        p->parent=y;
    }
//    printf("fr");
}



Student RBTree::searchId(int id) {
    if (root == NULL) // 만일 root가 없으면 Empty Tree.
    {
        cout << "\nEmpty\n";
        return NULL;
    }
    Student branch = root;

    int flag = 0;

    while (branch != NULL && flag == 0) // 만일 Empty Tree가 아니고 flag 가 0 (값을 못찾은 state)일때 까지. flag가 1이 되면 loop 탈출.
    {
        if (branch->id == id) // 값이 존재
            flag = 1;
        if (flag == 0) {
            if (branch->id < id) // 찾는  값이 크면 오른쪽으로
                branch = branch->right;
            else // 찾는 값이 작으면 왼쪽으로
                branch = branch->left;
        }
    }

    if (flag == 0) {// s가 NULL (leaf밑) 에 도달했을 때 까지 값을 못찾으면
        cout << "\nStudent Not Found.";
        return NULL;
    } 
	else
	{
		return branch;
	}
}





void RBTree:: printInfo(Student s)
{
    cout<<"\n ID: "<<s->id
        <<"\n Name: "<<s->name
        <<"\n GPA: "<<s->gpa
        <<"\n Credit hours remained: "<<s->creditTotal - s->creditTaken << "/140"
        <<"\n All the courses taken: ";
        printCourse(s->listCourse);
}


void RBTree::deletenode()
{
    int x;
    int flag=0;
    Student p=root;
    Student y=NULL;
    Student q=NULL;

    if(root==NULL)
    {
        cout<<"\nEmpty." ;
        return ;
    }

    cout<<"\nEnter the id of the student for deletion: ";
    cin>>x;



    while(p!=NULL&&flag==0)
    {
        if(p->id==x)
            flag=1;
        if(flag==0)
        {
            if(p->id<x)
                p=p->right;
            else
                p=p->left;
        }
    }
    if(flag==0)
    {
        cout<<"\nStudent Not Found.";
        return ;
    }
    else
    {
        cout<<"\nDeleted Student Information ";
        /*cout<<"\nColour: ";
        if(p->color=='b')
    cout<<"Black\n";
   else
    cout<<"Red\n";*/

        printInfo(p);

        if(p->left==NULL||p->right==NULL)
            y=p;
        else
            y=successor(p);
        if(y->left!=NULL)
            q=y->left;
        else
        {
            if(y->right!=NULL)
                q=y->right;
            else
                q=NULL;
        }
        if(q!=NULL)
            q->parent=y->parent;
        if(y->parent==NULL)
            root=q;
        else
        {
            if(y==y->parent->left)
                y->parent->left=q;
            else
                y->parent->right=q;
        }
        if(y!=p)
        {
            p->color=y->color;
            p->id=y->id;
        }
        if(y->color=='b')
            delfix(q);



    }
    totalNode--;
    rb.getHeight2();


}

void RBTree::delfix(Student p)
{
    Student s;
    while(p!=root&&p->color=='b')
    {
        if(p->parent->left==p)
        {
            s=p->parent->right;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                leftrotate(p->parent);
                s=p->parent->right;
            }
            if(s->right->color=='b'&&s->left->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->right->color=='b')
                {
                    s->left->color=='b';
                    s->color='r';
                    rightrotate(s);
                    s=p->parent->right;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->right->color='b';
                leftrotate(p->parent);
                p=root;
            }
        }
        else
        {
            s=p->parent->left;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                rightrotate(p->parent);
                s=p->parent->left;
            }
            if(s->left->color=='b'&&s->right->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->left->color=='b')
                {
                    s->right->color='b';
                    s->color='r';
                    leftrotate(s);
                    s=p->parent->left;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->left->color='b';
                rightrotate(p->parent);
                p=root;
            }
        }
        p->color='b';
        root->color='b';
    }
}


Student RBTree::successor(Student p)
{
    Student x=NULL;
    if(p->left!=NULL)
    {
        x=p->left;
        while(x->right!=NULL)
            x=x->right;
    }
    else
    {
        x=p->right;
        while(x->left!=NULL)
            x=x->left;
    }
    return x;
}

void RBTree::print()
{
    display(root);
}

void RBTree::display(Student s)
{
    if(root==NULL) // root값에 아무것도 없으면 Empty Tree
    {
        printf("\nEmpty.");
        return ;
    }
    if(s!=NULL) //
    {
        //cout<<"\n\t NODE: ";
        cout<<"\n Id: "<<s->id;
        cout<<"\n Colour: ";
        if(s->color=='b')
            cout<<"Black";
        else
            cout<<"Red";
        if(s->parent!=NULL)
            cout<<"\n Parent: "<<s->parent->id;
        else
            cout<<"\n There is no parent of the node.  ";
        if(s->right!=NULL)
            cout<<"\n Right Child: "<<s->right->id;
        else
            cout<<"\n There is no right child of the node.  ";
        if(s->left!=NULL)
            cout<<"\n Left Child: "<<s->left->id;
        else
            cout<<"\n There is no left child of the node.  ";
        cout<<endl;
        if(s->left)
        {
            /*cout<<"\n\nLeft:\n";*/
            display(s->left);
        }
        /*else
         cout<<"\nNo Left Child.\n";*/
        if(s->right)
        {
            /*cout<<"\n\nRight:\n";*/
            display(s->right);
        }
        /*else
         cout<<"\nNo Right Child.\n"*/
    }
}

//By Kim
void RBTree::getHeight(){
    if(root==NULL){
        height=0;
        return;
    }
    else
        calHeight(root, 0);
    cout << "\n * RBTree insertion occurred height: " << height << " ";

    rb.printLeaves();

    cout << "leaf: " << leafNum
         << " total node: " << totalNode
         << " *"<< "\n";
}

//By Kim
void RBTree::getHeight2(){
    if(root==NULL){
        height=0;
        return;
    }
    else
        calHeight(root, 0);
    cout << "\n\n * RBTree deletion occurred height: " << height << " ";

    rb.printLeaves();

    cout << "leaf: " << leafNum
         << " total node: " << totalNode
         << " *"<< "\n";
}

//By Kim
void RBTree::calHeight(Student p, int l){
    int i=l;
    if(p!=NULL){
        i++;
        if(height<i){
            height=i;
        }
        calHeight(p->left, i);
        calHeight(p->right, i);
    }

}

//By Choi
void RBTree::printLeaves()
{
    displayLeaves(root);

}


//By Choi
void RBTree::displayLeaves(Student s)
{
    int count=0;

    if(s->left)
    {

        displayLeaves(s->left);
    }
    else
    {
        count++;
    }
    if(s->right)
    {
        displayLeaves(s->right);
    }
    else
    {
        count++;
    }
    if(count==2)
    {
        leafNum++;
    }

}