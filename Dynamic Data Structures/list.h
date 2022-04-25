#include <iostream>


struct listNode {
    std::string firstName;
    std::string lastName;
    int indexNo;
    struct listNode* NEXT;
};

struct listNode* findListIndex(int index);

void printList();

void insertSortedList(std::string firstName,std::string lastName, int index);

void deleteList(int index);