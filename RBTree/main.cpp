
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
#include <ctype.h>
#include <ctime>
#include <vector>


#include "ui.h"
#include "main.h"
#include "class.h"
#include "student.h"
#include "BST.h"
#include "rbtree.h"

using namespace std;

Student rootTotal = NULL;
Student rootFresh = NULL;
Student rootSophomore = NULL;
Student rootJunior = NULL;
Student rootSenior = NULL;

extern vector<int> idList;
RBTree rb;


int main() {
    srand(time(NULL));
    courseFileReader();

    for(int i=0; i<200; ++i){
        Student temp = newStudent();

        idList.push_back(temp->id);

        Student tempTotal = copyStudentNode(temp);
        Student tempTotal2 = copyStudentNode(temp);

        cout << "id: " << temp-> id << "\n";
        rb.insert(temp);

        rb.leafNum=0;

        rootTotal = insertNode(rootTotal, tempTotal2);

        if(tempTotal->year == 1){
            rootFresh = insertNode(rootFresh, tempTotal);
        } else if(tempTotal->year == 2){
            rootSophomore = insertNode(rootSophomore, tempTotal);
        } else if(tempTotal->year == 3){
            rootJunior = insertNode(rootJunior, tempTotal);
        } else {
            rootSenior = insertNode(rootSenior, tempTotal);
        }
    }
//    rb.print();
    int emp = firstInput();

    return 0;
}
















