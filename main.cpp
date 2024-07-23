#include "AVL.h"

using namespace std;


int main() {

    Item itemZero("C", "Drink", 459000);
    Item itemOne("A", "Fruit", 1400);
    Item itemTwo("B", "Brakey", 20);
    Item itemThree("D", "HARAM", 1000);
    Item itemFour("E", "HARAM", 1000);
    Item itemFive("F", "HARAM", 1000);




    AVLNode nodeZero = {itemZero , nullptr, nullptr};
    AVLNode nodeOne = {itemOne , nullptr, nullptr};
    AVLNode nodeTwo= {itemTwo , nullptr, nullptr};
    AVLNode nodeThree= {itemThree , nullptr, nullptr};
    AVLNode nodeFour= {itemFour , nullptr, nullptr};
    AVLNode nodeFive= {itemFive , nullptr, nullptr};



    AVLTree Tree;
    Tree.addNode(&nodeZero);
    Tree.addNode(&nodeOne);
    Tree.addNode(&nodeTwo);
    Tree.addNode(&nodeThree);
    Tree.addNode(&nodeFour);
    Tree.addNode(&nodeFive);


    cout << "Height of the tree: " << Tree.getTreeHeight() << endl;

    //Tree.diplayOrderdByNameDesc();
   //Tree.diplayOrderdByPricAsc();

    //Tree.inorderTravers(Tree.getRoot());

    Tree.deleteNode(&nodeTwo);
    //Tree.diplayOrderdByNameAsc();
    Tree.diplayOrderdByPricDesc();

    return 0;
}
