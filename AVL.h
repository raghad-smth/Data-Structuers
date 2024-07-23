#ifndef AVL_H
#define AVL_H

#include "AVLNode.h"
#include "Item.h"
#include <vector>

class AVLTree {
private:
    AVLNode* Root;

    int Height(AVLNode* node);
    int BalanceFactor(AVLNode* node);

    AVLNode* insertTheNode(AVLNode* root, AVLNode* newNode);
    AVLNode* removeNode(AVLNode* root, AVLNode* nodeToRemove);
    AVLNode* getSuccessor(AVLNode* node);

    AVLNode* singleRightRotation(AVLNode* nodeToRotate);
    AVLNode* singleLeftRotation(AVLNode* nodeToRotate);

    void inorderTravers(AVLNode* node);
    void inorderReversedTravers(AVLNode* node);
    std::vector<Item> inorderTraversPrice(AVLNode* node);

public:
    AVLTree();
    AVLNode* getRoot();
    int getTreeHeight();
    void addNode(AVLNode* node);
    void deleteNode(AVLNode* nodeToRemove);
    void displayOrderedByNameAsc();
    void displayOrderedByNameDesc();
    void displayOrderedByPriceAsc();
    void displayOrderedByPriceDesc();
};

#endif // AVL_H

