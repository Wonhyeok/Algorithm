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

using namespace std;

Course avail;
Student listStudent[300];
course listCourse[97];

string gradeChar[9]={"A+", "A", "B+", "B", "C+", "C", "D+", "D", "F"};
map<string, double> gradeNum= {{"A+", 4.5},
                               {"A", 4.0},
                               {"B+", 3.5},
                               {"B", 3.0},
                               {"C+", 2.5},
                               {"C", 2.0},
                               {"D+", 1.5},
                               {"D", 1.0},
                               {"F", 0.0}};

void courseFileReader(){
    ifstream file("course.txt");
    int i=0;
    if(!file.is_open()){
        cerr << "failed to open file.";
    }
    while(file.good()){
        string tempStr;

        getline(file, listCourse[i].eName, ',');
        getline(file, listCourse[i].kName, ',');
        getline(file, tempStr);
        listCourse[i].credit = stoi(tempStr);
//        cout << "credit" <<listCourse[i].credit  << "\n";
        i++;
        if(i==96) break;
    }
    file.close();
}

// 수업 랜덤선택 함수 ( 0 ~ 95 )
int ranCourseSelect(){
    return rand() % 96;
}

// 학기당 수업 개수 랜덤생성 함수 ( 3 ~ 7 )
int numClassGenerator(){
    return rand() % 5 + 3;
}

string generateGrade(){
    int A= 50 + rand()%20 + rand()%10;
    int B= 70 + rand()%10 + rand()%10;
    int C= 80 + rand()%10;
    int i= rand()%101;

    if(0<=i && i<=A){
        return gradeChar[rand()%2];
    }else if(A<i && i<=B){
        return gradeChar[rand()%2+2];
    }else if(B<i && i<=C){
        return gradeChar[rand()%2+4];
    }else if(C<i && i<=98){
        return gradeChar[rand()%2+6];
    }else if(i==99 || i==100){
        return gradeChar[8];
    }

}

//Course getNode(Course avail){//get node from garbage list
//    Course nptr;
//    if(avail !=NULL){
//        nptr = avail;
//        avail = avail -> next;
//        nptr -> next = NULL;
//    }
//    else{
//        nptr = (Course) malloc (sizeof(course));
//        nptr -> next = NULL;
//    }
//    return nptr;
//}

Course newCourse(int idx, int year, int sem){
    Course nptr= new course;
    nptr-> kName = listCourse[idx].kName;
    nptr-> eName = listCourse[idx].eName;
    nptr-> credit = listCourse[idx].credit;
    nptr-> year = year;
    nptr-> semester = sem;
    nptr-> next= NULL;
    nptr-> grade = generateGrade();
    return nptr;
}


Course newInputCourse(string eName, string grade, int sem,int year){
    int foundIdx;
    Course nptr= new course;
    nptr-> eName = eName;
    for(int i = 0; i<97; ++i){
        if(listCourse[i].eName == eName) foundIdx = i;
    }
    nptr-> kName = listCourse[foundIdx].kName;
    nptr-> credit = listCourse[foundIdx].credit;
    nptr-> year = year;
    nptr-> semester = sem;
    nptr-> next= NULL;
    nptr-> grade = grade;
    return nptr;
}



// 중복 체크 및 코스 생성 함수

// checkArr : 중복 체크 배열
// year : 학년
// semester : 학기
// idx : 랜덤 수업을 위한 인덱스 ( 0 ~ 95 )

Course checkAndGenerate(int *checkArr, int year, int semester, int idx){
    if(!checkArr[idx]){ // 한 번도 access되지 않았다면,
        checkArr[idx]++;
        return newCourse(idx, year, semester);
    } else //한 번이라도 access되었다면,
        return checkAndGenerate(checkArr, year, semester, ranCourseSelect()); //다시 뽑기
}


Course courseGenerator(int year){

    int checkArr[96] = {0,}; //과목 중복 체크를 위한 배열
    Course head = NULL;
    Course tail = head;

    for(int i=1; i<=year*2; ++i){ // 학기는 year * 2만큼 존재
        int classPerSem = numClassGenerator(); // 학기당 수업 개수 ( 3 ~ 7 )
        int orderedSem = i % 2 ? i : 2;
        for(int j=0; j<classPerSem; ++j){
            // 과목 구조체에
            Course wrappedCourse = checkAndGenerate(checkArr, year, orderedSem,
                                                    ranCourseSelect());
            if(head == NULL){
                head = wrappedCourse;
                tail = head;
            } else {
                tail->next = wrappedCourse;
                tail = tail->next;
            }
        }
    }
    return head;
}




void printCourse(Course head){
    int count = 1;
    while(head != NULL){
        cout << "\n [" << count << "] "
             << " 과목명: " << head->kName
             << " 학수명: " <<head->eName
             << " Grade: " <<head->grade
             << " Credit: " <<head->credit;
        head = head->next;
        count++;
    }
}

int countCredit(Course head){
    int count = 0;
    while(head != NULL){
        count += head->credit;
        head = head->next;
    }
    return count;
}

double calGPA(Course head){
    double sumCreditMulGrade = 0;
    int numCredit = 0;


    while(head != NULL){

        int tmpCredit = head->credit;

        sumCreditMulGrade += gradeNum[head->grade] * tmpCredit;
        numCredit += tmpCredit;
        head = head->next;
    }
    return sumCreditMulGrade / numCredit;
}

Course copyClassNode(Course node){
    Course temp = new course;
    *temp=*node;
    return temp;
}

