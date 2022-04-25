#pragma once
#include <iostream>
#include "bst.h"
void insertBBST(std::string firstName,std::string lastName, int index);


struct treeNode* getBalancedTreeHead();


void deleteBBST(int index);

void rebalance(struct treeNode *ptr);

struct treeNode* findTreeIndexBBST(int index);

struct treeNode* getInOrderPredescessorBBST(int index);

struct treeNode* getInOrderSuccessorBBST(int index);

struct treeNode* getBBSTNodeParent(int index);
