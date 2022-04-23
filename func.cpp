#include "func.h"

//-----------------------------------------------------------------------------

// Creates list of struct Student
// Read and write data from file
// Receives two parameters string filePath and int studNum
// filePath is a path of file from which data will be read
// studNum is a number of student that will be read from file
// Returns a pointer on the head of the list
struct Student *createListOfStudents(std::string sFilePath) {
  // Creating filestream for reading data from file
  std::ifstream fFile(sFilePath);

  // If file wasn't open printing a message and returning nullptr
  if(!fFile) {
    std::cout << "Error: file wasn't opened" << std::endl;
    return nullptr;
  }

  // Reading data from file and writing data in the list
  if(fFile.peek() == std::ifstream::traits_type::eof())
  {
    return nullptr;
  }
  struct Student *pHead = nullptr;
  struct Student *pPrevious = nullptr;
  while(!fFile.eof()) {
    if(isspace(fFile.peek()))
    {
      break;
    }
    struct Student *pNewElement = new struct Student;
    pNewElement->m_pNext = nullptr;
    if(pPrevious != nullptr) {
      pPrevious->m_pNext=pNewElement;
    }
    if(pHead == nullptr) {
      pHead = pNewElement;
    }
    pPrevious = pNewElement;

    if(!std::isalpha(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> pNewElement->m_sSurname;
    fFile.ignore();
    if(!std::isalpha(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> pNewElement->m_sName;
    int nDay, nMonth, nYear;
    fFile.ignore();
    if(!std::isdigit(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> nDay ;
    fFile.ignore();
    if(!std::isdigit(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> nMonth;
    fFile.ignore();
    if(!std::isdigit(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> nYear;
    pNewElement->m_birthday.tm_mday = nDay;
    pNewElement->m_birthday.tm_mon = nMonth-1;
    pNewElement->m_birthday.tm_year = nYear-1900;
    fFile.ignore();
    if(!std::isdigit(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> pNewElement->m_nGrades[0];
    fFile.ignore();
    if(!std::isdigit(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> pNewElement->m_nGrades[1];
    fFile.ignore();
    if(!std::isdigit(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> pNewElement->m_nGrades[2];
    fFile.ignore();
    if(!std::isdigit(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> pNewElement->m_nGrades[3];
    fFile.ignore();
    if(!std::isdigit(fFile.peek()))
    {
      std::cout << "~~~~~ WRONG DATA ~~~~~" << std::endl;
      pHead = nullptr;
      break;
    }
    fFile >> pNewElement->m_nGrades[4];
    fFile.ignore();
    }
  return pHead;
}

//-----------------------------------------------------------------------------

// Prints formatted table of students
// Receives one parameter struct Student *pListHead
// This parameter is a head of the list we want to print
// Returns nothing
void printStudents(struct Student *pListHead) {
  if(pListHead == nullptr)
  {
    std::cout << "There is no students in the list" << std::endl;
    return;
  }
  int nSpacing{0};
  struct Student *pPtr{pListHead};
  while(pPtr != nullptr) {
    if(nSpacing < pPtr->m_sName.length() + pPtr->m_sSurname.length()) {
      nSpacing = pPtr->m_sName.length() + pPtr->m_sSurname.length();
    }
    pPtr = pPtr->m_pNext;
  }
  pPtr = pListHead;
  std::string sDivideLine(30 + nSpacing, '_');
  std::string sNameSpace(nSpacing-4, ' ');
  std::cout << std::endl << sDivideLine << std::endl;
  std::cout << "| Name " << sNameSpace << " | Birthdate  "
      "| Grades    |" << std::endl;
  while(pPtr != nullptr) {
    char cBuffer[11];
    std::strftime(cBuffer, 11, "%d.%m.%Y", &(pPtr->m_birthday));
    int nSpaceSize = nSpacing - pPtr->m_sSurname.length() - pPtr->m_sName.length();
    std::string sSpace(nSpaceSize, ' ');
    std::cout << "| " <<  pPtr->m_sSurname << " " << pPtr->m_sName << sSpace
        << " | " << cBuffer;
    std::cout << " | ";
    for(int i = 0; i < 5; i++) {
      std::cout << pPtr->m_nGrades[i] << " ";
    }
    std::cout << "|" << std::endl;
    pPtr = pPtr->m_pNext;
  }
  std::cout << sDivideLine << std::endl;
}

//-----------------------------------------------------------------------------

// Swaps two integer number
// Receives two parameters int *pNum1 and *pNum2
// Returns nothing
void swap(int *pNum1, int *pNum2) {
  int nTemp = *pNum1;
  *pNum1 = *pNum2;
  *pNum2 = nTemp;
}

//-----------------------------------------------------------------------------

// Sorts required list of students by birthdate in growing order
// Receives one parameter struct Student **ppListHead
// This parameter is a pointer on pointer of struct Student
// in order to be able to change the list
// Uses bubble sort algorithm
// Returns nothing
void sortStudents(struct Student **ppListHead) {
  if(*ppListHead == nullptr)
  {
    std::cout << "There is no students in the list" << std::endl;
    return;
  }
  int nSize{0};
  struct Student *pPtr {*ppListHead};
  while(pPtr != nullptr) {
    nSize++;
    pPtr=pPtr->m_pNext;
  }
  pPtr = *ppListHead;

  // An array that stored a sum of yeas, months and days reduced
  // to a common denominator of all students in the list
  int nExTime[nSize];

  // Calculating and filling nExTime
  for(int i{0}; i < nSize; i++) {
    nExTime[i] = pPtr->m_birthday.tm_mday + pPtr->m_birthday.tm_mon*12
        + pPtr->m_birthday.tm_year*365;
    pPtr=pPtr->m_pNext;
  }

  // Sorting nExTime by bubble sort algorithm
  for (int i = 0; i < nSize-1; i++) {
    for (int j = 0; j < nSize - i - 1; j++) {
      if (nExTime[j] < nExTime[j + 1]) {
        swap(&nExTime[j], &nExTime[j + 1]);
      }
    }
  }

  // An array that stores pointers on all students
  struct Student *pStudArr[nSize];
  pPtr = *ppListHead;
  int nCurExTime;

  // Placing students in studArr in the right place using exTime
  while(pPtr != nullptr) {
    nCurExTime = pPtr->m_birthday.tm_mday + pPtr->m_birthday.tm_mon*12
        + pPtr->m_birthday.tm_year*365;
    for(int i = 0; i < nSize; i++) {
      if(nExTime[i] == nCurExTime) {
        pStudArr[i] = pPtr;
      }
    }
    pPtr=pPtr->m_pNext;
  }

  pPtr = pStudArr[0];
  // Making first element of studArr as list head
  *ppListHead = pStudArr[0];
  // Reorganising the list using studArr
  for(int i = 1; i < nSize; i++) {
    pPtr->m_pNext=pStudArr[i];
    pPtr = pPtr->m_pNext;
  }
  pPtr->m_pNext = nullptr;
}

//-----------------------------------------------------------------------------

// Prints a table of students with average grade that lower than average
// in all list
// Receives parameter struct Student *pListHead - pointer on the head of the
// required list
// Returns nothing
void printLowerAvg(struct Student *pListHead) {
  if(pListHead == nullptr)
  {
    std::cout << "There is no students in the list" << std::endl;
    return;
  }
  int nSize{0};
  struct Student *pPtr {pListHead};
  while(pPtr != nullptr) {
    nSize++;
    pPtr=pPtr->m_pNext;
  }
  pPtr = pListHead;

  // Array for storing average grades of all student in the list
  double dAvgGrades[nSize];

  // Calculating average grades and filling avgGrades
  for(int i = 0; i < nSize; i++) {
    dAvgGrades[i] = 0;
    for(int j = 0; j < 5; j++) {
      dAvgGrades[i]+=pPtr->m_nGrades[j];
    }
    dAvgGrades[i]/=5;
    pPtr=pPtr->m_pNext;
  }

  pPtr = pListHead;

  // Number that stores average grade among all students
  double dGlobalAvg{0};

  for(int i = 0; i < nSize; i++) {
    dGlobalAvg+=dAvgGrades[i];
  }

  dGlobalAvg /= nSize;

  // Prints a formatted table of students
  int nSpacing{0};
  while(pPtr != nullptr) {
    if(nSpacing < pPtr->m_sName.length() + pPtr->m_sSurname.length()) {
      nSpacing = pPtr->m_sName.length() + pPtr->m_sSurname.length();
    }
    pPtr = pPtr->m_pNext;
  }
  pPtr = pListHead;
  while(pPtr != nullptr) {
    if(nSpacing < pPtr->m_sName.length() + pPtr->m_sSurname.length()) {
      nSpacing = pPtr->m_sName.length() + pPtr->m_sSurname.length();
    }
    pPtr = pPtr->m_pNext;
  }
  pPtr = pListHead;
  std::string sDivideLine(nSpacing + 30, '_');
  std::string sNameSpace(nSpacing-4, ' ');
  std::cout << std::endl << sDivideLine << std::endl;
  std::cout << "| Name " << sNameSpace << " | Birthdate  "
      "| Grades    |" << std::endl;
  while(pPtr != nullptr) {
    double curAvg {0};
    for(int i = 0; i < 5; i++) {
      curAvg += pPtr->m_nGrades[i];
    }
    curAvg /= 5;

    if(curAvg <=  dGlobalAvg) {
      char buffer[11];
      std::strftime(buffer, 11, "%d.%m.%Y", &(pPtr->m_birthday));
      int spaceSize = nSpacing - pPtr->m_sSurname.length() - pPtr->m_sName.length();
      std::string space(spaceSize, ' ');
      std::cout << "| " << pPtr->m_sSurname << " " << pPtr->m_sName << space
          << " | " << buffer;
      std::cout << " | ";
      for (int i = 0; i < 5; i++) {
        std::cout << pPtr->m_nGrades[i] << " ";
      }
      std::cout << "|" << std::endl;
    }
    pPtr = pPtr->m_pNext;
  }
  std::cout << sDivideLine << std::endl;
}

//-----------------------------------------------------------------------------

// Adds a new element to the list of students
// Data for a new element is inputted from keyboard
// The new element is pasted in the head of the list
// Also this function calls function for sorting list
// in order to place new element in the right place
// Returns nothing
void addNewStudent(struct Student **ppListHead) {
  // Creates a new element
  struct Student *pNewElement = new struct Student;
  pNewElement->m_pNext=*ppListHead;
  *ppListHead=pNewElement;
  // Entering data for a new element
  std::cout << "Enter the surname of the new student: " << std::endl;
  std::cin >> pNewElement->m_sSurname;
  std::cout << "Enter the name of the new student: " << std::endl;
  std::cin >> pNewElement->m_sName;
  std::cout << "Enter the day of month of birth of the new student: "
      << std::endl;
  int nDay, nMonth, nYear;
  std::cin >> nDay;
  pNewElement->m_birthday.tm_mday = nDay;
  std::cout << "Enter the month of birth of the new student: " << std::endl;
  std::cin >> nMonth;
  pNewElement->m_birthday.tm_mon = nMonth - 1;
  std::cout << "Enter the year of birth of the new student: " << std::endl;
  std::cin >> nYear;
  pNewElement->m_birthday.tm_year = nYear - 1900;
  std::cout << "Enter the grades of the new student: " << std::endl;
  for(int i = 0; i < 5; i++) {
    std::cout << "Grade " << i+1 << ": " << std::endl;
    std::cin >> pNewElement->m_nGrades[i];
  }
  // Calling function that sorts required array
  sortStudents(ppListHead);
  std::cout << "New student was added" << std::endl;
}

//-----------------------------------------------------------------------------

// Delete student with the lowest average grades
// Receives two parameters struct Student **ppListHead and int nNumToDelete
// ppListHead is a pointer on pointer of the head of the list
// in order to be able to change the list
// nNumToDelete is a number of student that we want to delete
// Returns nothing
void deleteTheLowest(struct Student **ppListHead, int nNumToDelete) {
  if(*ppListHead == nullptr)
  {
    std::cout << "There is no students in the list" << std::endl;
    return;
  }
  int nSize{0};
  struct Student *pPtr {*ppListHead};
  while(pPtr != nullptr) {
    nSize++;
    pPtr=pPtr->m_pNext;
  }
  pPtr = *ppListHead;

  // An array with size 'size' for storing average grades of all students
  double dAvgGrades[nSize];
  // An array with size 'nNumToDelete' for storing average grades of students
  // we want to delete
  double dLowestGrades[nNumToDelete];

  // Fills avgGrades with average grades from the list
  for(int i = 0; i < nSize; i++) {
    dAvgGrades[i] = pPtr->m_nGrades[0];
    for(int j = 1; j < 5; j++) {
      dAvgGrades[i] += pPtr->m_nGrades[j];
    }
    dAvgGrades[i] /= 5;
    pPtr=pPtr->m_pNext;
  }

  // Fills dLowestGrades with 6, because 6 is greater than any grade int list
  // so next cycle will be work correctly
  for(int i = 0; i < nNumToDelete; i++) {
    dLowestGrades[i] = 6;
  }

  // Cycle that calculates the lowest student grades and fills dLowestGrades
  for(int i = 0; i < nSize; i++) {
    if(dAvgGrades[i] < dLowestGrades[0]) {
      dLowestGrades[2] = dLowestGrades[1];
      dLowestGrades[1] = dLowestGrades[0];
      dLowestGrades[0] = dAvgGrades[i];
    } else if(dAvgGrades[i] < dLowestGrades[1]) {
      dLowestGrades[2] = dLowestGrades[1];
      dLowestGrades[1] = dAvgGrades[i];
    } else if(dAvgGrades[i] < dLowestGrades[2]) {
      dLowestGrades[2] = dAvgGrades[i];
    }
  }

  double dCurAvgGrade;

  pPtr = *ppListHead;

  int nGradesToSkip[nNumToDelete];

  for(int i{0}; i < nNumToDelete; i++)
  {
    nGradesToSkip[i] = -1;
  }

  int nIter {0};
  struct Student *pPrevious = pPtr;
  // Cycle that deletes students with the lowest grades stored in dLowestGrades
  while(pPtr != nullptr && nIter < nNumToDelete) {
    dCurAvgGrade = pPtr->m_nGrades[0];
    for(int i = 1; i < 5; i++) {
      dCurAvgGrade += pPtr->m_nGrades[i];
    }
    dCurAvgGrade /= 5;

    for(int i = 0; i < nNumToDelete; i++) {
      bool bSkip{false};
      for(int j{0}; j < nNumToDelete; j++) {
        if(i == nGradesToSkip[j])
        {
          bSkip = true;
        }
      }
      if(bSkip){
        continue;
      }
      if (dCurAvgGrade == dLowestGrades[i]) {
        if (pPtr == *ppListHead) {
          *ppListHead = pPtr->m_pNext;
          delete pPtr;
          pPtr = *ppListHead;
          nGradesToSkip[nIter] = i;
          nIter++;
          break;
        } else if (pPtr->m_pNext == nullptr) {
          pPrevious->m_pNext = nullptr;
          delete pPtr;
          pPtr = pPrevious;
          nGradesToSkip[nIter] = i;
          nIter++;
          break;
        } else if(pPtr == *ppListHead && pPtr->m_pNext == nullptr) {
          *ppListHead = nullptr;
          pPtr = nullptr;
          break;
        } else {
            pPrevious->m_pNext = pPtr->m_pNext;
            delete pPtr;
            pPtr = pPrevious;
            nGradesToSkip[nIter] = i;
            nIter++;
            break;
          }
        }
      }
    }
    pPrevious = pPtr;
    if(pPtr != nullptr)
    {
      pPtr = pPtr->m_pNext;
    }
  }