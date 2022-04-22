#include "func.h"

int main() {
    //Creating list of students
    struct Student *listHead = createListOfStudents("D:\\Work\\University\\C1S2"
                                          "\\Introduction to Software Engineering\\Lab02\\students.txt");

    //Variable for storing chosen operation
    char operation {};

    std::string divideLine(80, '_');
    //Infinite cycle from which user can exit with printing 'x' or 'X' in console
    while(true) {
      //Printing a table of operations that user can call
      std::cout << std::endl << divideLine << std::endl << "Operations list:" << std::endl;
      std::cout << "Enter 'p' to print table of students" << std::endl;
      std::cout << "Enter 's' to sort students" << std::endl;
      std::cout << "Enter 'a' to add new element" << std::endl;
      std::cout << "Enter 'd' to delete 3 elements with lowest grades" << std::endl;
      std::cout << "Enter 'l' to print table with students that have grades lower than average" << std::endl;
      std::cout << "Enter 'x' to exit" << std::endl;
      std::cout << divideLine << std::endl;

      std::cin >> operation;

      if(operation == 'p' || operation == 'P') {
        printStudents(listHead);
        } else if(operation == 's' || operation == 'S') {
        sortStudents(&listHead);
        } else if(operation == 'a' || operation == 'A') {
        addNewStudent(&listHead);
        } else if(operation == 'd' || operation == 'D') {
        deleteTheLowest(&listHead, 3);
        } else if(operation == 'l' || operation == 'L') {
        printLowerAvg(listHead);
        } else if(operation == 'x' || operation == 'X') {
        break;
        } else {
        std::cout << std::endl << "Such operation doesn't exist" << std::endl;
        }
    }

    return 0;
}
