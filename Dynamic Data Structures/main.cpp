#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <functional>
#include <sstream>

#include "list.h"
#include "bbst.h"



void readFile(std::string fn){
    std::fstream fs;
    std::string line;
    std::string comma = ",";
    fs.open(fn);
    while(getline(fs,line)){
        size_t pos;
        int c = 0;
        int index;
        std::string firstName, lastName;
        while ((pos = line.find(comma)) != std::string::npos) {
            std::string temp = line.substr(0, pos);
            if (c==0){
                firstName = temp;
            }
            if (c==1){
                lastName = temp;
            }
            c++;
            line.erase(0, pos + 1);
        }
        index = stoi(line);
        insertSortedList(firstName,lastName,index);
        insertBST(firstName,lastName,index);
        insertBBST(firstName,lastName,index);
        rebalance(getBalancedTreeHead());
        line = "";
    }
    fs.close();
}

int main(int argc,char * argv[]){
    int ELEMENTS = atoi(argv[1])*10000;
    ELEMENTS = 10;
    std::ostringstream stream;
    stream << "example_" <<ELEMENTS<<".csv";
    std::string FILENAME = stream.str();
    FILENAME = "e.csv";
    readFile(FILENAME);
    srand(time(0));
    std::cout<<"InOrder"<<std::endl;
    BSTInOrder(getTreeHead());
    std::cout<<"PreOrder"<<std::endl;
    BSTPreOrder(getTreeHead());
    std::cout<<"PostOrder"<<std::endl;
    BSTPostOrder(getTreeHead());
    std::cout<<getHeight(getTreeHead());
    // return 0;
    // int r;
    // for (int i =0;i<10;i++){
    //     r = rand()%ELEMENTS+1;
    //     auto start = std::chrono::high_resolution_clock::now();
    //     struct listNode * l = findListIndex(r);
    //     std::string fname = l->firstName;
    //     std::string lname = l->lastName;
    //     auto stop = std::chrono::high_resolution_clock::now();
    //     auto search = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     start = std::chrono::high_resolution_clock::now();
    //     deleteList(r);
    //     stop = std::chrono::high_resolution_clock::now();
    //     auto del = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     start = std::chrono::high_resolution_clock::now();
    //     insertSortedList(fname,lname,r);
    //     stop = std::chrono::high_resolution_clock::now();
    //     auto insert = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     std::ofstream file;
    //     file.open("out.csv",std::ios::app);
    //     file<<"LIST"<<','<<"SEARCH"<<","<<search.count()<<","<<ELEMENTS<<std::endl;
    //     file<<"LIST"<<','<<"REMOVE"<<","<<del.count()<<","<<ELEMENTS<<std::endl;
    //     file<<"LIST"<<','<<"INSERT"<<","<<insert.count()<<","<<ELEMENTS<<std::endl;
    //     file.close();
    // }
    // // printList();
    // for (int i =0;i<10;i++){
    //     r = rand()%ELEMENTS+1;
    //     auto start = std::chrono::high_resolution_clock::now();
    //     struct treeNode * l = findTreeIndexBBST(r);
    //     std::string fname = l->firstName;
    //     std::string lname = l->lastName;
    //     auto stop = std::chrono::high_resolution_clock::now();
    //     auto search = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     start = std::chrono::high_resolution_clock::now();
    //     deleteBBST(r);
    //     stop = std::chrono::high_resolution_clock::now();
    //     auto del = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     start = std::chrono::high_resolution_clock::now();
    //     insertBBST(fname,lname,r);
    //     stop = std::chrono::high_resolution_clock::now();
    //     auto insert = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     std::ofstream file;
    //     file.open("out.csv",std::ios::app);
    //     file<<"BBST"<<','<<"SEARCH"<<","<<search.count()<<","<<ELEMENTS<<std::endl;
    //     file<<"BBST"<<','<<"REMOVE"<<","<<del.count()<<","<<ELEMENTS<<std::endl;
    //     file<<"BBST"<<','<<"INSERT"<<","<<insert.count()<<","<<ELEMENTS<<std::endl;
    //     file.close();
    // }
    // // BSTInOrder(getBalancedTreeHead());
    // for (int i =0;i<10;i++){
    //     r = rand()%ELEMENTS+1;
    //     auto start = std::chrono::high_resolution_clock::now();
    //     struct treeNode * l = findTreeIndex(r);
    //     std::string fname = l->firstName;
    //     std::string lname = l->lastName;
    //     auto stop = std::chrono::high_resolution_clock::now();
    //     auto search = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     start = std::chrono::high_resolution_clock::now();
    //     deleteBST(r);
    //     stop = std::chrono::high_resolution_clock::now();
    //     auto del = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     start = std::chrono::high_resolution_clock::now();
    //     insertBST(fname,lname,r);
    //     stop = std::chrono::high_resolution_clock::now();
    //     auto insert = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     std::ofstream file;
    //     file.open("out.csv",std::ios::app);
    //     file<<"BST"<<','<<"SEARCH"<<","<<search.count()<<","<<ELEMENTS<<std::endl;
    //     file<<"BST"<<','<<"REMOVE"<<","<<del.count()<<","<<ELEMENTS<<std::endl;
    //     file<<"BST"<<','<<"INSERT"<<","<<insert.count()<<","<<ELEMENTS<<std::endl;
    //     file.close();
    // }
}
