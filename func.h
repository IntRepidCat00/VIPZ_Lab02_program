#ifndef LAB02_FUNC_H
#define LAB02_FUNC_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

struct Student
{
    std::string m_sSurname;
    std::string m_sName;
    struct tm m_birthday;
    int m_nGrades[5];

    struct Student *m_pNext;
};

//Prototypes of functions
struct Student *createListOfStudents(std::string sFilePath);

void printStudents(struct Student *pListHead);

void sortStudents(struct Student **ppListHead);

void swap(int *pNum1, int *pNum2);

void printLowerAvg(struct Student *pListHead);

void addNewStudent(struct Student **ppListHead);

void deleteTheLowest(struct Student **ppListHead, int nNumToDelete);

#endif //LAB02_FUNC_H
