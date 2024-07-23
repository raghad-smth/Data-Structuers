#include <iostream>
#include <vector>
using namespace std;

// The class that represents the items of the supermarket
class Item
{
    string name;
    string category;
    int price;
public:
    Item();
    Item(string name, string category, int price);
    int getPrice();
    bool operator<(const Item item);
    bool operator>(const Item item);
    void print();
};

//AVLNode class that represents the AVL Tree Node

struct AVLNode{
    Item data;
    AVLNode* llink;
    AVLNode* rlink;
    AVLNode* parentlink;
};

class AVLTree{
private:
  AVLNode*  Root;
  int Height(AVLNode* node);
  int BalanceFactor(AVLNode* node);



public:
    AVLTree();
    AVLNode* getRoot();
    int getTreeHeight();
    void addNode(AVLNode* node);
    AVLNode* insertTHeNode(AVLNode* node, AVLNode* newNode);
    AVLNode* singleRightRotation(AVLNode* nodeToRotate);
    AVLNode* singleLeftRotation(AVLNode* nodeToRotate);
    AVLNode* getSuccessor(AVLNode* node );
    void deleteNode(AVLNode* nodeToRemove);
    AVLNode* removeNode(AVLNode* node,AVLNode* nodeToRemove);
    void inorderTravers(AVLNode* node);
    void inorderReversdTravers(AVLNode* node);
    vector<Item>  inorderTraversPrice(AVLNode* node);
    void diplayOrderdByNameAsc();
    void diplayOrderdByNameDesc();
    void diplayOrderdByPricAsc();
    void diplayOrderdByPricDesc();
};

