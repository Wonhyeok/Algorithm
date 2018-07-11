//
// Created by Won Hyeok Choi on 2016. 12. 5..
//
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <cstdio>
#include <string>
#include <ctype.h>
#include <ctime>
#include <vector>
#include <map>
#include "main.h"
#include "BST.h"
#include "class.h"

#include "rbtree.h"
using namespace std;

extern RBTree rb;
extern Student rootTotal;
extern Student rootFresh;
extern Student rootSophomore;
extern Student rootJunior;
extern Student rootSenior;

string firstName[10] = {"김", "박", "장", "최", "안", "이", "강", "고", "백", "임"};
string middleName[10] = {"승", "채", "효", "민", "태", "하", "석", "준", "진", "수"};
string lastName[10] = {"길", "혜", "근", "경", "준", "영", "용", "민", "신", "희"};
vector<int> idList;



string nameGenerator(){
    return firstName[rand() % 10] + middleName[rand()%10] + lastName[rand()%10];
}

int yearGenderator(){
    return rand() % 4 + 3;
}

int idGenerator(int year){
    string temp =  "201" + to_string(year);
    for(int i=0; i<6; ++i){
        temp += to_string(rand()%10);
    }
    return stoi(temp);
}

int yearToId(int year){
    return -1 * (year - 7);
}

// A utility function to create a new  node
Student newStudent(){
    Student temp =  new struct Node;
    int tempYear = yearGenderator(); // 3 <= tempYear <= 6
    int tempGrade = yearToId(tempYear);
    temp->id = idGenerator(tempYear);
    temp->year = tempGrade;
    temp->name = nameGenerator();
    temp->left = temp->right = temp->parent= NULL;
    temp->creditTotal = 140;
    temp->listCourse = courseGenerator(tempGrade); // 학년(1~4)
    temp->gpa = calGPA(temp->listCourse);
    temp->creditTaken = countCredit(temp->listCourse);
    temp->color='r';
    return temp;
}

Student createNewStudent(int id, int year, string name){
    Student temp =  new struct Node;
    temp->id = id;
    temp->year = year; //몇 학년?
    temp->name = name;
    temp->left = temp->right = temp->parent= NULL;
    temp->creditTotal = 140;
    temp->listCourse = NULL;
    temp->gpa = 0;
    temp->creditTaken = 0;
    temp->color='r';
    return temp;
}

void putNewData(Student node, Course newCourse){
    Course head = node->listCourse;
    if(head == NULL) head = newCourse;
    else{
        while(head->next != NULL){
            head = head->next;
        }
        head->next = newCourse;
    }

}

void inputNewData(int id, Course newCourse)
{
    Student foundNodeRb = rb.searchId(id);
    cout << "rb name: " << foundNodeRb->name << "\n";
    putNewData(foundNodeRb, newCourse);
//
//    Course copiedCourse = copyClassNode(newCourse);
//    Course copiedCourse2 = copyClassNode(newCourse);
//
//    double gpaForBst = foundNodeRb->gpa;
//    int yearForBst = foundNodeRb->year;
//
//    Student foundNodeBstTotal = searchNode(rootTotal, gpaForBst);
//    putNewData(foundNodeBstTotal, copiedCourse);
//
//    if(yearForBst == 1){
//        Student foundNodeBstFresh = searchNode(rootFresh, gpaForBst);
//        putNewData(foundNodeBstFresh, copiedCourse2);
//    } else if (yearForBst == 2){
//        Student foundNodeBstSopho = searchNode(rootSophomore, gpaForBst);
//        putNewData(foundNodeBstSopho, copiedCourse2);
//    } else if (yearForBst == 3){
//        Student foundNodeBstJunior = searchNode(rootJunior, gpaForBst);
//        putNewData(foundNodeBstJunior, copiedCourse2);
//    } else {
//        Student foundNodeBstSenior = searchNode(rootSenior, gpaForBst);
//        putNewData(foundNodeBstSenior, copiedCourse2);
//    }
};

Student copyStudentNode(Student node){
    Student temp = new student;
    *temp=*node;
    return temp;
}


