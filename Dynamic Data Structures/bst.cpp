#include "bst.h"

struct treeNode *BSTtreeHead = nullptr;

void insertBST(std::string firstName,std::string lastName, int index){
    struct treeNode *node = (struct treeNode*) calloc(1,sizeof(struct treeNode));
    node->firstName = firstName;
    node->lastName = lastName;
    node->indexNo = index;
    node->right = nullptr;
    node->left = nullptr;
    if (BSTtreeHead==nullptr){
        BSTtreeHead = node;
        return;
    }
    struct treeNode *ptr = BSTtreeHead;
    while(1){
        if (index < ptr->indexNo){ //go left
            if (ptr->left==nullptr){
                ptr->left = node;
                return;
            }
            ptr = ptr->left;
        }
        else{
            if (ptr->right==nullptr){
                ptr->right = node;
                return;
            }
            ptr = ptr->right;
        }
    }
}


struct treeNode* findTreeIndex(int index){
    struct treeNode *ptr = BSTtreeHead;
    while(ptr!=nullptr){
        if (index==ptr->indexNo){
            return ptr;
        }
        if (index<ptr->indexNo){
            ptr= ptr->left;
        }
        else{
            ptr= ptr->right;
        }
    }
    return nullptr;
}

struct treeNode* getTreeHead(){
    return BSTtreeHead;
}

void BSTPreOrder(struct treeNode *ptr){
    if (ptr==nullptr){
        return;
    }
    printBSTNode(ptr);
    BSTPreOrder(ptr->left);
    BSTPreOrder(ptr->right);
}


void BSTPostOrder(struct treeNode *ptr){
    if (ptr==nullptr){
        return;
    }
    BSTPostOrder(ptr->left);
    BSTPostOrder(ptr->right);
    printBSTNode(ptr);
}


void BSTInOrder(struct treeNode *ptr){
    if (ptr==nullptr){
        return;
    }
    BSTInOrder(ptr->left);
    printBSTNode(ptr);
    BSTInOrder(ptr->right);
}

struct treeNode* getInOrderPredescessor(int index){
    struct treeNode* ptr = findTreeIndex(index);
    ptr = ptr->left;
    while(ptr!=nullptr && ptr->right!=nullptr){
        ptr=ptr->right;
    }
    return ptr;
}
struct treeNode* getInOrderSuccessor(int index){
    struct treeNode* ptr = findTreeIndex(index);
    ptr = ptr->right;
    while(ptr!=nullptr && ptr->left!=nullptr){
        ptr=ptr->left;
    }
    return ptr;
}
void printBSTNode(struct treeNode *ptr){
    std::cout<<"("<<ptr->firstName<< " "<<ptr->lastName<<": "<<ptr->indexNo<<")"<<std::endl;
}

struct treeNode* getBSTNodeParent(int index){
    if (index == BSTtreeHead->indexNo){
        return BSTtreeHead;
    }
    struct treeNode* ptr = BSTtreeHead;
    while (1){
        if (index<ptr->indexNo){
            if (ptr->left->indexNo==index){
                return ptr;
            }
            ptr = ptr->left;
        }
        else{
            if (ptr->right->indexNo==index){
                return ptr;
            }
            ptr = ptr->right;
        }
    }
}

void swap(struct treeNode **a,struct treeNode **b){
    int temp = (*a)->indexNo;
    std::string Fname = (*a)->firstName;
    std::string Lname = (*a)->lastName;
    (*a)->firstName = (*b)->firstName;
    (*a)->lastName = (*b)->lastName;
    (*a)->indexNo = (*b)->indexNo;
    (*b)->firstName = Fname;
    (*b)->lastName = Lname;
    (*b)->indexNo = temp;
}

int getBalanceMeter(struct treeNode *ptr){
    int l = getHeight(ptr->left);
    int r = getHeight(ptr->right);
    return r-l;
}
int getHeight(struct treeNode *ptr){
    if (ptr==nullptr){
        return 0;
    }
    int l = getHeight(ptr->left);
    int r = getHeight(ptr->right);
    return 1+((l>r)?l:r);
}

void deleteBST(int index){
    if (index==BSTtreeHead->indexNo){
      int balanceMeter= getBalanceMeter(BSTtreeHead);
        struct treeNode * successor;
        if (balanceMeter>0){
            successor = getInOrderSuccessor(index);
        }
        else{
            successor = getInOrderPredescessor(index);
        }
        struct treeNode * successorParent = getBSTNodeParent(successor->indexNo);
        if (successor->indexNo>successorParent->indexNo){
            swap(&successor,&BSTtreeHead);
            successorParent->right = nullptr;
            return;
        }
        else{
            swap(&successor,&BSTtreeHead);
            successorParent->left = nullptr;
            return;
        }
    }
    struct treeNode* ptr = findTreeIndex(index);
    struct treeNode* parent = getBSTNodeParent(index);
    bool left = (ptr->left==nullptr);
    bool right = (ptr->right==nullptr);
    if (left && right){ //NO CHILDREN
        if (index > parent->indexNo){
            parent->right=nullptr;
            return;
        }
        else{
            parent->left=nullptr;
            return;
        }
    }
    if (!left&&right){
        if (index > parent->indexNo){
            parent->right=ptr->left;
            return;
        }
        else{
            parent->left=ptr->left;
            return;
        }
    } 
    if(left&&!right){
        if (index > parent->indexNo){
            parent->right=ptr->right;
            return;
        }
        else{
            parent->left=ptr->right;
            return;
        }
    }
    struct treeNode * successor = getInOrderSuccessor(index);
    struct treeNode * successorParent = getBSTNodeParent(successor->indexNo);
    if (successor->indexNo>successorParent->indexNo){
        swap(&successor,&ptr);
        successorParent->right = nullptr;
        return;
    }
    else{
        swap(&successor,&ptr);
        successorParent->left = nullptr;
        return;
    }
}
