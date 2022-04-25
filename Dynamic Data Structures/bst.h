#pragma once
#include <iostream>

struct treeNode {
    std::string firstName;
    std::string lastName;
    int indexNo;
    struct treeNode* left;
    struct treeNode* right;
};
void insertBST(std::string firstName,std::string lastName, int index);

struct treeNode* findTreeIndex(int index);

struct treeNode* getTreeHead();
int getHeight(struct treeNode *ptr);
int getBalanceMeter(struct treeNode *ptr);

void BSTPreOrder(struct treeNode *ptr);

void BSTPostOrder(struct treeNode *ptr);

void BSTInOrder(struct treeNode *ptr);

struct treeNode* getInOrderPredescessor(int index);

struct treeNode* getInOrderSuccessor(int index);

void printBSTNode(struct treeNode *ptr);

struct treeNode* getBSTNodeParent(int index);

void swap(struct treeNode **a,struct treeNode **b);

void deleteBST(int index);