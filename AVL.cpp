#include "AVL.h"

//Item Class implementation
Item ::Item(){
    name = "";
    category = "";
    price = 0;
}
Item ::Item(string name, string category, int price){
    this->name = name;
    this->category = category;
    this->price = price;
}

int Item:: getPrice(){
    return price;
}
bool Item :: operator<(const Item item) {
    return name < item.name;
}

bool Item :: operator>(const Item item) {
    return name > item.name;
}




void Item:: print(){
    cout << "******************"<<endl;
    cout << "* Name: " << name<<endl;
    cout << "* Category: " << category<<endl;
    cout << "* Price: "<< price<<endl;
}



// AVL Tree Class implementation

AVLTree :: AVLTree(){
    Root = NULL;
}
AVLNode* AVLTree:: getRoot(){
    return Root;
}
int AVLTree::getTreeHeight() {
    return Height(Root);
}



/* Height of NULL node -> 0
 * Height of lead node -> 1
 * Height of parent node -> max of [it's right subtree, it's left subtree] + 1
*/
int AVLTree:: Height(AVLNode* node){
    // Base case where the node is an empty subtree, hence it's height is 0
    if (node == nullptr){
        return 0;
    }
        //Recursive call for the function if the node is not an empty tree hence it's height will be the max of it's left subtree
        // and it's right subtree
    else{
        return max(Height(node->llink),Height(node->rlink))+1;
    }
}


// Balance Factor =  Height of the right subtree - Height of the left subtree
int AVLTree:: BalanceFactor(AVLNode* node){
    //If tree is empty then it's height is zero, hence 0-0 = 0
    if(node == nullptr){
        return 0;
    }
        //Calculate the height of the left subtree and right subtree and subtract them
    else {
        return Height(node->llink) - Height(node->rlink);
    }
}

// Function to only take the new node and call the function that will insert the node into the tree
void AVLTree:: addNode(AVLNode* node){
    // The first call starts from the Root of the tree
    // It also will update the Root to the value of the root that the insertTHeNode() returned after any needed adjustment
    Root = insertTHeNode(Root, node);
}

AVLNode* AVLTree:: insertTHeNode(AVLNode* root, AVLNode* newNode) {

    // The cases of the insertion
    if (root == nullptr) {
        return newNode;
    }
    if (root->data < newNode->data) {
        AVLNode* rChild = insertTHeNode(root->rlink,newNode);
        root->rlink = rChild;
        rChild->parentlink = root;

    } else if (newNode->data < root->data) {
        AVLNode *lChild = insertTHeNode(root->llink, newNode);
        root->llink = lChild;
        lChild->parentlink = root;

    }

 /*                                          *** Balancing the tree ***                                                                                  */

   // If the balance Factor > 1 that indicates last insertion was in the left subtree so a right rotation is needed
    if (BalanceFactor(root) > 1) {
        //It's a left-left insertion ->  Single Rotation:[Right rotation] is needed
        if (root->data < newNode->data) {
            return singleRightRotation(root);
        }
        // It's left-right rotation -> Double Rotation:[left rotation followed by right rotation]
        else {
            root->llink = singleLeftRotation(root->llink);
            return singleRightRotation(root);
        }

    }


    // If the balance Factor < -1 that indicates last insertion was in the right subtree so a left rotation is needed
     if (BalanceFactor(root) < -1) {
         // It's a right-right rotation -> Single Rotation:[left rotation] is needed
        if (root->data < newNode->data) {
            return singleLeftRotation(root);
        }
        // It's right-left rotation -> Double Rotation:[right rotation followed by left rotation]
        else  {
            root->rlink = singleRightRotation(root->rlink);
            return singleLeftRotation(root);
        }
    }

    Height(root);

    return root;
}

AVLNode* AVLTree:: getSuccessor(AVLNode* node){
    AVLNode* succsesor = node->rlink;
    if(succsesor->llink !=  nullptr){
        succsesor= getSuccessor(succsesor->llink);
        }
    return succsesor;
}


AVLNode* AVLTree:: removeNode(AVLNode* root,AVLNode* nodeToRemove) {
    //Locating the node in the tree
    if (root == nullptr) {
        return root;
    }
    if (root->data < nodeToRemove->data) {
        root->rlink = removeNode(root->rlink,nodeToRemove);

    } else if (nodeToRemove->data < root->data) {
        root->llink = removeNode(root->llink, nodeToRemove);

        // When we found the place of the node in the tree
    }else {
        //First case where the node is a leafe (with zero children)
        if(root->llink == nullptr || root->rlink == nullptr ) {
            //Store the non-NULL child into temp
            AVLNode* temp= root->llink ? root->llink : root->rlink;
            //Both left and right children are null -> First case [Leaf Deletion]
            if (temp == nullptr) {
                root = nullptr;
            }
            //Only one of the children is null -> Second Case [Node with one child]
            else{
                root = temp;
            }
        // Both left and right children aren't null -> Third case [node has two children]
        }else{
           AVLNode* temp = getSuccessor(root);
           root->data = temp->data;
           root->rlink = removeNode(root->rlink,temp);
         }
        }

/*                                          *** Balancing the tree ***                                                                                  */

    // If the balance Factor > 1 that indicates last insertion was in the left subtree so a right rotation is needed
    if (BalanceFactor(root) > 1) {
        //It's a left-left insertion ->  Single Rotation:[Right rotation] is needed
        if (root->data < nodeToRemove->data) {
            return singleRightRotation(root);
        }
            // It's left-right rotation -> Double Rotation:[left rotation followed by right rotation]
        else {
            root->llink = singleLeftRotation(root->llink);
            return singleRightRotation(root);
        }

    }


    // If the balance Factor < -1 that indicates last insertion was in the right subtree so a left rotation is needed
    if (BalanceFactor(root) < -1) {
        // It's a right-right rotation -> Single Rotation:[left rotation] is needed
        if (root->data < nodeToRemove->data) {
            return singleLeftRotation(root);
        }
            // It's right-left rotation -> Double Rotation:[right rotation followed by left rotation]
        else  {
            root->rlink = singleRightRotation(root->rlink);
            return singleLeftRotation(root);
        }
    }

    Height(root);
    return root;
    }


// Calling the remove Node starting from the Root
void AVLTree:: deleteNode(AVLNode* nodeToRemove){
   Root =  removeNode(Root, nodeToRemove);
}

//Rotate a node to the right and return the new parent
AVLNode* AVLTree::singleRightRotation(AVLNode* nodeToRotate) {
    AVLNode* parent = nodeToRotate->llink;
    nodeToRotate->llink = parent->rlink; // Corrected assignment
    parent->rlink = nodeToRotate;

    // Update heights
    Height(nodeToRotate);
    Height(parent);

    // Update balance factors
    BalanceFactor(nodeToRotate);
    BalanceFactor(parent);

    return parent;
}

//Rotate a node to the left and return the new parent
AVLNode* AVLTree:: singleLeftRotation(AVLNode* nodeToRotate){
    AVLNode* parent = nodeToRotate->rlink;
    nodeToRotate->rlink = parent->llink;
    parent->llink = nodeToRotate;

    //Updating height after rotation
    Height(nodeToRotate);
    Height(parent);

    //Updating Balance Factor
    BalanceFactor(nodeToRotate);
    BalanceFactor(parent);
    return parent;
}

// Print the left subtree -> Root -> Right subtree
void AVLTree:: inorderTravers(AVLNode* node){
    if (node != nullptr){
        inorderTravers(node->llink);
        node->data.print();
        inorderTravers(node->rlink);
    }
}

// Calling the inorder cause it prints the trees nodes in ascending order
void AVLTree:: diplayOrderdByNameAsc(){
    inorderTravers(Root);
}


// Creating a reversed inorder to visit: right subtree-> root -> left subtree
void AVLTree:: inorderReversdTravers(AVLNode* node){
    if(node != nullptr){
        inorderReversdTravers(node->rlink);
        node->data.print();
        inorderReversdTravers(node->llink);
    }
}


// Calling the reversed inorder cause it gets the node order in desceding order
void AVLTree:: diplayOrderdByNameDesc(){
    inorderReversdTravers(Root);
}


// Storing the nodes data in a vector to display sorted by price
vector<Item>  AVLTree:: inorderTraversPrice(AVLNode* node){
    vector <Item> items;
    if(node != nullptr){
        // Traverse left subtree first
        vector<Item> leftItems = inorderTraversPrice(node->llink);
        items.insert(items.end(), leftItems.begin(), leftItems.end());

        // Append current node's data
        items.push_back(node->data);

        // Traverse right subtree
        vector<Item> rightItems = inorderTraversPrice(node->rlink);
        items.insert(items.end(), rightItems.begin(), rightItems.end());
    }

    return items;
}


// Sorting the itmes by prices Asc and printing the items
void AVLTree:: diplayOrderdByPricAsc() {
    vector<Item> items = inorderTraversPrice(Root);

    int n = items.size();
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (items[j].getPrice() > items[i].getPrice()) {
                swap(items[i], items[j]);
            }
        }
    }

    for (Item i: items) {
        i.print();
    }

}


// Sorting the items by prices Desc and printing the items
void AVLTree:: diplayOrderdByPricDesc(){
    vector<Item> items = inorderTraversPrice(Root);
    int n = items.size();
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (items[j].getPrice() < items[i].getPrice()) {
                swap(items[i], items[j]);
            }
        }
    }

    for (Item i: items) {
        i.print();
    }
}




















