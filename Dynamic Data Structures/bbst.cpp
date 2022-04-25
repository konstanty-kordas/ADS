#include "bbst.h"

struct treeNode *BBSTtreeHead = nullptr;

void insertBBST(std::string firstName,std::string lastName, int index){
    struct treeNode *node = (struct treeNode*) calloc(1,sizeof(struct treeNode));
    node->firstName = firstName;
    node->lastName = lastName;
    node->indexNo = index;
    node->right = nullptr;
    node->left = nullptr;
    if (BBSTtreeHead==nullptr){
        BBSTtreeHead = node;
        return;
    }
    struct treeNode *ptr = BBSTtreeHead;
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


struct treeNode* getBalancedTreeHead(){
    return BBSTtreeHead;
}
void rebalance(struct treeNode *ptr){
    if (ptr==nullptr){
        return;
    }
    int balanceMeter = getBalanceMeter(ptr);
    struct treeNode* link ;
    if (balanceMeter>1){
        link = getInOrderSuccessorBBST(ptr->indexNo);

    }
    if (balanceMeter<-1) {
        link = getInOrderPredescessorBBST(ptr->indexNo);
    }
    if(abs(balanceMeter)>1){
        std::string fname = ptr->firstName;
        std::string lname = ptr->lastName;
        int index = ptr->indexNo;
        deleteBBST(link->indexNo);
        ptr->firstName = link->firstName;
        ptr->lastName = link->lastName;
        ptr->indexNo = link->indexNo;
        insertBBST(fname,lname,index);
    }
    rebalance(ptr->left);
    rebalance(ptr->right);


}


struct treeNode* getInOrderPredescessorBBST(int index){
    struct treeNode* ptr = findTreeIndexBBST(index);
    ptr = ptr->left;
    while(ptr!=nullptr && ptr->right!=nullptr){
        ptr=ptr->right;
    }
    return ptr;
}
struct treeNode* getInOrderSuccessorBBST(int index){
    struct treeNode* ptr;
    ptr = findTreeIndexBBST(index);
    ptr = ptr->right;
    while(ptr!=nullptr && ptr->left!=nullptr){
        ptr=ptr->left;
    }
    return ptr;
}

void deleteBBST(int index){
    if (index==BBSTtreeHead->indexNo){
        int balanceMeter= getBalanceMeter(BBSTtreeHead);
        struct treeNode * successor;
        if (balanceMeter>0){
            successor = getInOrderSuccessorBBST(index);
        }
        else{
            successor = getInOrderPredescessorBBST(index);
        }
        struct treeNode * successorParent = getBBSTNodeParent(successor->indexNo);
        if (successor->indexNo>successorParent->indexNo){
            swap(&successor,&BBSTtreeHead);
            successorParent->right = nullptr;
            return;
        }
        else{
            swap(&successor,&BBSTtreeHead);
            successorParent->left = nullptr;
            return;
        }
    }
    struct treeNode* ptr = (struct treeNode*)calloc(1,sizeof(struct treeNode*));
    ptr = findTreeIndexBBST(index);
    struct treeNode* parent = (struct treeNode*)calloc(1,sizeof(struct treeNode*));
    parent = getBBSTNodeParent(index);
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
    int balanceMeter= getBalanceMeter(ptr);
    struct treeNode * successor;
    if (balanceMeter>0){
        successor = getInOrderSuccessorBBST(index);
    }
    else{
        successor = getInOrderPredescessorBBST(index);
    }
    struct treeNode * successorParent = getBBSTNodeParent(successor->indexNo);
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
struct treeNode* findTreeIndexBBST(int index){
    struct treeNode *ptr = BBSTtreeHead;
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

struct treeNode* getBBSTNodeParent(int index){
    if (index == BBSTtreeHead->indexNo){
        return BBSTtreeHead;
    }
    struct treeNode* ptr = BBSTtreeHead;
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
