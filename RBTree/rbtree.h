//
// Created by Frank Ahn on 2016. 12. 5..
//

#ifndef FINAL_ALGO_RBTREE_H
#define FINAL_ALGO_RBTREE_H
using namespace std;


class RBTree
{
    Student root;
    Student q;
    int height = 0;


public :
    int leafNum = 0;
    int totalNode = 0;
    RBTree()
    {
        q=NULL;
        root=NULL;
    }
    void insert(Student );
    void insertfix(Student );
    void leftrotate(Student );
    void rightrotate(Student );
    void deletenode();
    Student successor(Student );
    void delfix(Student );
    void print();
    void display(Student );
    Student searchId(int );
    void putNewData(int id, Course newCourse);
    void printInfo(Student);
    void searchInput(int);
    void insertnewInput(int);
    void insertInput(Student);
    void studentInput(int);
    void getHeight();
    void getHeight2();
    void calHeight(Student , int );
    void printLeaves();
    void displayLeaves(Student s);
};


#endif //FINAL_ALGO_RBTREE_H
