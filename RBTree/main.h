//
// Created by Frank Ahn on 2016. 12. 5..
//

#ifndef FINAL_ALGO_MAIN_H
#define FINAL_ALGO_MAIN_H

#include <string>
using namespace std;

typedef struct subNode *Course;
typedef struct subNode {
    Course next;
    string kName;
    string eName;
    int credit;
    string grade;
    int semester;
    int year;
}course;

typedef struct Node *Student;
typedef struct Node{
    Student right;
    Student left;
    Student parent;
    int id;
    int year;
    string name;
    double gpa;
    int creditTotal;
    int creditTaken;
    Course listCourse;
    char color;
}student;


#endif //FINAL_ALGO_MAIN_H
