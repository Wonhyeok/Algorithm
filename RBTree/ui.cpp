#include <iostream>
#include <string>
#include <vector>
#include "main.h"

#include "student.h"
#include "class.h"
#include "rbtree.h"

#include "BST.h"

using namespace std;

extern Student rootTotal;
extern Student rootFresh;
extern Student rootSophomore;
extern Student rootJunior;
extern Student rootSenior;

extern course listCourse[97];
extern string gradeChar[];
extern RBTree rb;

extern vector<int> idList;


bool choiceVal(int choice, int first, int last);
bool idVal(int id);
bool semVal(int s);
bool courseVal(string c);
bool gradeVal(string g);
bool yearVal(int year);

int infoInput_1();
int infoInput_1_2(int *year);
string infoInput_2();
string infoInput_3();
int infoInput_4();
int infoInput_5();
int infoInput_6();
string infoInput_7();

int inputMenu2();
int inputMenu3();

int firstInput();
int secondInput();
int thirdInput();
int fourthInput();

int idInput();



//By Ahn
bool choiceVal(int choice, int first, int last){
    if(choice < first || choice > last ){
        return false;
    } else {
        return true;
    }
}

//By Kim
bool idVal(int id){
    int idDivided = id/1000000;
    int isNotInList = find(idList.begin(), idList.end(), id) == idList.end();

    if(!(2013<= idDivided && idDivided <=2016) || isNotInList){

        return false;
    }
    else return true;
}

//By Ahn
bool idVal2(int id){
    int idDivided = id/1000000;
    int isInList = find(idList.begin(), idList.end(), id) != idList.end();

    if(!(2013<= idDivided && idDivided <=2016) || isInList){
        printf("WARN: Invalid information!\n\n");
        return false;
    }
    else return true;
}



//By Choi
// TODO 학생 과목 7개 넘는지 확인 + year와
bool semVal(int s)
{
    if(s==1 || s==2)
        return true;
    else
        return false;
}

//By Ahn
bool creditVal(int c)
{
    return c >= 1 && c <=3 ? true : false;
}

//By Choi
//TODO 뛰어쓰기
bool courseVal(string c) {

    for (int i = 0; i < 97; i++) {
        if (c.compare(listCourse[i].eName)) return true;
    }
    printf("WARN: Could not find the course in the list!\n\n");
    return false;

}
//
//bool courseVal(string c) {
//
//    transform(c.begin(), c.end(), c.begin(), ::toupper);
//    c.erase(remove_if(c.begin(), c.end(), isspace),c.end());
//
//    for (int i = 0; i < 97; i++) {
//        if (c.compare(listCourse[i].eName) && c.compare(listCourse[i].kName)){
//            return true;
//        }
//    }
//
//    printf("WARN: Could not find the course number in the list!\n\n");
//    return false;
//}


//By Ahn
//TODO 대문자
bool courseNumVal(string c) {

    for (int i = 0; i < 97; i++) {
        if (c.compare(listCourse[i].eName)) return true;
    }
    printf("WARN: Could not find the course in the list!\n\n");
    return false;

}

//By Choi
// TODO 학생 과목 7개 넘는지 확인 + year와
bool gradeVal(string g)
{
    int i;
    int found=0;
    for(i=0; i<9; i++) {
        if (g.compare(gradeChar[i]))
            return true;
    }
    printf("WARN: Could not find the grade in the list!\n\n");
    return false;
}

//By Kim
bool yearVal(int year){
    if(!(2013<= year && year <=2016)){
        printf("WARN: Invalid information!\n\n");
        return false;
    }
    else return true;
}

//bool choiceVal(string choice, int first, int last){
//    if(choice < to_string(first) || choice > to_string(last)
//       || stoi(choice) < first || stoi(choice) > last){
//        printf("WARN: Input valid command!\n");
//        return false;
//    } else {
//        return true;
//    }
//}

//By Ahn
int idInput() {
    int id;
    while (1) {
        cout << " What't the ID? =>  " ;
        scanf("%d", &id);
        if(idVal(id)){
            Student temp = rb.searchId(id);
            rb.printInfo(temp);
            return firstInput();
        } else{
            printf("WARN: Invalid information!\n\n");
        }
    }
}

//By Ahn
int firstInput() {
    int cmd;

//    cin.ignore();
    while (1) {
        printf("\n\nWhat do you want?\n\n");
        cout << "1. Show student's information by ID" << "\n"
             << "2. Input class information" << "\n"
             << "3. Input new student information" << "\n"
             << "4. Ranked information by GPA" << "\n"
             << "5. Delete information by ID" << "\n"
             << "6. Finish program" << "\n"
             << "\n"
             << "=> ";
//        cin.ignore(1000,'\n');
//        scanf("%d", &cmd);
        scanf("%d", &cmd);

        if(cmd < 1 || cmd > 6){
            printf("WARN: Input valid command!\n\n");
            continue;
        } else {

            cout << "\n" << "You chose " << cmd << "\n" << "\n";
            if (cmd == 6) {
                cout << "Bye, have a good day!";
                return 0;
            } else if (cmd == 5) {
                rb.leafNum = 0;
                rb.deletenode();
            } else if (cmd == 1) {
                return idInput();
            } else if (cmd == 2) {
                return inputMenu2();
            } else if (cmd == 3) {
                return inputMenu3();
            } else
                return secondInput();
        }
    }
}

//By Ahn
int infoInput_1(){
    int id;

    while (1) {
        cout << " What's the ID? =>  " ;
        scanf("%d", &id);
        if(idVal(id)) return id;
    }
}

//By Ahn
int infoInput_1_2(int *year){
    int id;

    while (1) {
        cout << " What's the ID? =>  " ;
        scanf("%d", &id);

        if(idVal2(id)) {
            *year = (((id / 1000000) % 10) - 7) * -1;
            return id;
        }
    }
}

//By Ahn
string infoInput_2(){
    string s;
    cout << " What's the name? =>  " ;
    cin >> s;
    cin.ignore(256,'\n');
    return s;
}


//By Ahn
string infoInput_3(){
    string s;

    while (1) {
        cout << " What's the grade? =>  " ;
        cin >> s;

        if(gradeVal(s)) return s;
    }
}

//By Ahn
int infoInput_4(){
    int y;

    while (1) {
        cout << " What's the year? =>  " ;
        cin >> y;
        cin.ignore(1000,'\n');
        if(yearVal(y)) return y;
    }
}

//By Ahn
int infoInput_5(){
    int sem;

    while (1) {
        cout << " What's the semester? =>  " ;
        cin >> sem;
        cin.ignore(1000,'\n');
        if(semVal(sem)) return sem;
    }
}




string infoInput_7(){
    string s;

    while (1) {
        cout << " What's class number? =>  " ;
        cin >> s;
        cin.ignore(1000,'\n');
        if(courseNumVal(s)) return s;
    }
}





//By Ahn
int secondInput() {
    int cmd;

    while (1) {
        cout << "\n"
             << "1. I want to see results regardless of grades" << "\n"
             << "2. I want to see results by grades" << "\n"
             << "3. Back to the first menu" << "\n"
             << "4. Finish program" << "\n"
             << "\n=> ";

        cin >> cmd;
        cin.ignore(1000,'\n');
        if(choiceVal(cmd, 1, 4)){
            cout << "You chose " << cmd << "\n";
            if (cmd == 3) {
                return firstInput();
            } else if (cmd == 4) {
                cout << "Bye, have a good day!";
                return 0;
            } else if (cmd == 1) {
                printNode(rootTotal);
            } else {
                return thirdInput();
            }
        }
    }
}

//By Ahn
int thirdInput() {
    int cmd;

    while (1) {
        cout << "\n"
             << "1. I want to see results in one screen" << "\n"
             << "2. I want to see results in seperate screens" << "\n"
             << "3. Back to the first menu" << "\n"
             << "4. Finish program" << "\n"
             << "\n=> " ;

        cin >> cmd;
        cin.ignore(1000,'\n');
        if (cmd == 3) {
            return firstInput();
        } else if (cmd == 4) {
            cout << "Bye, have a good day!";
            return 0;
        } else if(choiceVal(cmd, 1, 2)){

            cout <<"You chose: "<<cmd<<"\n";

             if(cmd == 1){
                cout << "\n" << "==================== Freshman [1st grade] ===================="<< "\n" << "\n";
                printNode(rootFresh);
                cout << "\n" << "==================== Sophomore [2nd grade] ===================="<< "\n" << "\n";
                printNode(rootSophomore);
                cout << "\n" << "==================== Junior [3rd grade] ===================="<< "\n" << "\n";
                printNode(rootJunior);
                cout << "\n" << "==================== Senior [4th grade] ===================="<< "\n" << "\n";
                printNode(rootSenior);

            } else if(cmd == 2){
                return fourthInput();

            }
        }
    }
}




int fourthInput() {
    int cmd;

    while (1) {
        cout << "\n"
             << "1. Freshman" << "\n"
             << "2. Sophomore" << "\n"
             << "3. Junior" << "\n"
             << "4. Senior" << "\n"
             << "5. Back to the first menu" << "\n"
             << "6. Finish program" << "\n"
             << "\n"
             << "=> ";

        cin >> cmd;
        cin.ignore(1000,'\n');
        if (cmd == 5){
            return firstInput();

        } else if(cmd == 6) {
            cout << "Bye, have a good day!";
            return 0;
        } else if(choiceVal(cmd, 1,6)){
            cout <<"You chose "<<cmd<<"\n";
            if(cmd == 1){
                cout << "\n" << "==================== Freshman [1st grade] ====================" << "\n"<< "\n";
                printNode(rootFresh);

            } else if(cmd == 2){
                cout << "\n" << "==================== Sophomore [2nd grade] ====================" << "\n"<< "\n";
                printNode(rootSophomore);

            } else if (cmd == 3) {
                cout << "\n" << "==================== Junior [3rd grade] ====================" << "\n"<< "\n";
                printNode(rootJunior);

            } else if (cmd == 4) {
                cout << "\n" <<"==================== Senior [4th grade] ====================" << "\n"<< "\n" ;
                printNode(rootSenior);

            }
        }
    }

}


int inputMenu2() {
    int id = infoInput_1();

    string eName = infoInput_7();
    string grade = infoInput_3();
    int semester = infoInput_5();
    int year = infoInput_4();
    Course newCourseData = newInputCourse(eName, grade, semester, year);
    cout << "name: " <<newCourseData->kName << "\n";
    inputNewData(id, newCourseData);

    return firstInput();
}

int inputMenu3(){
    int year;
    int id = infoInput_1_2(&year);
    string name = infoInput_2();
    idList.push_back(id);
    Student newStudentData = createNewStudent(id, year, name);
    rb.insert(newStudentData);
//                rb.leafNum=0;
    rootTotal = insertNode(rootTotal, newStudentData);
    if (newStudentData->year == 1) {
    } else if (newStudentData->year == 2) {
        rootSophomore = insertNode(rootSophomore, newStudentData);
    } else if (newStudentData->year == 3) {
        rootJunior = insertNode(rootJunior, newStudentData);
    } else {
        rootSenior = insertNode(rootSenior, newStudentData);
    }

    return firstInput();
}