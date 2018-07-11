//
// Created by Frank Ahn on 2016. 12. 5..
//

#ifndef FINAL_ALGO_STUDENT_H
#define FINAL_ALGO_STUDENT_H

#include <string>

Student newStudent(); // A utility function to create a new  node
Student createNewStudent(int id, int year, string name);
void putNewData(Student node, Course newCourse);
void inputNewData(int id, Course newCourse);
Student copyStudentNode(Student node);


string nameGenerator();
int yearGenderator();
int idGenerator(int year);

#endif //FINAL_ALGO_STUDENT_H
