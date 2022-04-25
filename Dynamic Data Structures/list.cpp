#include "list.h"

struct listNode *listHead = nullptr;


struct listNode* findListIndex(int index){
    struct listNode *ptr = listHead;
    while(ptr->indexNo!=index){
        if (index<ptr->indexNo){
            return nullptr;
        }
        ptr = ptr->NEXT;
    }   
    return ptr;
}


void printList() { 
    struct listNode *ptr = listHead;
	int counter = 0;
    while(ptr != NULL) {
        std::cout<<"("<<ptr->firstName<< " "<<ptr->lastName<<": "<<ptr->indexNo<<")"<<std::endl;
        ptr = ptr->NEXT;
        counter++;
    }
    std::cout<<"Num of nodes: "<<counter<<std::endl; 	
}


void insertSortedList(std::string firstName,std::string lastName, int index){
    struct listNode *link = (struct listNode*) calloc(1,sizeof(struct listNode));
    link->indexNo = index;
    link->lastName = lastName;
    link->firstName = firstName;
    struct listNode *ptr = listHead;
    if (listHead == nullptr){    //FIRST!!!
        link->NEXT = nullptr;
        listHead = link;
        return;
    }
    if (ptr->NEXT==nullptr){
        if (index>(ptr->indexNo)){
            ptr->NEXT = link;
            link->NEXT = nullptr;
            return;
        }
        else{
            link->NEXT = ptr;
            listHead = link;
            return;
        }
    }
    if(index<=listHead->indexNo){
        link->NEXT = listHead;
        listHead = link;
        return;
    }
    while(index>(ptr->NEXT->indexNo)){
        ptr=ptr->NEXT;
        if (ptr->NEXT==nullptr){
            break;
        }
    }
    link->NEXT = ptr->NEXT;
    ptr->NEXT = link;
}

void deleteList(int index){
    if (listHead->indexNo==index){
        listHead = listHead->NEXT;
        return;
    }
    struct listNode* ptr = listHead;
    while (ptr->NEXT!=nullptr){
        if ((ptr->NEXT->indexNo)==index){
            ptr->NEXT = ptr->NEXT->NEXT;
            // free(ptr->NEXT);
            return;
        }
        ptr = ptr->NEXT;
    }
}
