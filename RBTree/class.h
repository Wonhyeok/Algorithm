//
// Created by Frank Ahn on 2016. 12. 5..
//

#ifndef FINAL_ALGO_CLASS_H
#define FINAL_ALGO_CLASS_H


// FILE READER
void courseFileReader(); // 과목 데이터 읽는 함



// GENERATORS
int ranCourseSelect(); // 수업 랜덤선택 함수 ( 0 ~ 95 )
int numClassGenerator(); // 학기당 수업 개수 랜덤생성 함수 ( 3 ~ 7 )
string generateGrade(); // 랜덤 학점 생성 함수
Course courseGenerator(int year); // 과목 생성 함수
Course newCourse(int idx, int year, int sem); // 새로운 과목 노드 생성 함수
Course newInputCourse(string eName, string grade, int sem,int year);
Course checkAndGenerate(int *checkArr, int year, int semester, int idx); //중복 체크 및 과목 생성
Course copyClassNode(Course node);
//Course getNode(Course avail); // Garbage list에서 노드 획득


// CALCULATORS
int countCredit(Course head); // Credit 덧셈 함수
double calGPA(Course head); // 평균학점 계산


// PRINTER
void printCourse(Course head); // 과목 정보 출력 함수

#endif //FINAL_ALGO_CLASS_H
