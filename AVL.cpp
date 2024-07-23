#include "AVL.h"

AVLTree::AVLTree() {
    Root = nullptr;
}

AVLNode* AVLTree::getRoot() {
    return Root;
}

int AVLTree::getTreeHeight() {
    return Height(Root);
}

int AVLTree::Height(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return std::max(Height(node->llink), Height(node->rlink)) + 1;
    }
}

int AVLTree::BalanceFactor(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return Height(node->llink) - Height(node->rlink);
    }
}

void AVLTree::addNode(AVLNode* node) {
    Root = insertTheNode(Root, node);
}

AVLNode* AVLTree::insertTheNode(AVLNode* root, AVLNode* newNode) {
    if (root == nullptr) {
        return newNode;
    }

    if (root->data < newNode->data) {
        root->rlink = insertTheNode(root->rlink, newNode);
        root->rlink->parentlink = root;
    } else if (newNode->data < root->data) {
        root->llink = insertTheNode(root->llink, newNode);
        root->llink->parentlink = root;
    }

    if (BalanceFactor(root) > 1) {
        if (root->data < newNode->data) {
            return singleRightRotation(root);
        } else {
            root->llink = singleLeftRotation(root->llink);
            return singleRightRotation(root);
        }
    }

    if (BalanceFactor(root) < -1) {
        if (root->data > newNode->data) {
            return singleLeftRotation(root);
        } else {
            root->rlink = singleRightRotation(root->rlink);
            return singleLeftRotation(root);
        }
    }

    return root;
}

AVLNode* AVLTree::getSuccessor(AVLNode* node) {
    AVLNode* successor = node->rlink;
    while (successor->llink != nullptr) {
        successor = successor->llink;
    }
    return successor;
}

AVLNode* AVLTree::removeNode(AVLNode* root, AVLNode* nodeToRemove) {
    if (root == nullptr) {
        return root;
    }

    if (root->data < nodeToRemove->data) {
        root->rlink = removeNode(root->rlink, nodeToRemove);
    } else if (nodeToRemove->data < root->data) {
        root->llink = removeNode(root->llink, nodeToRemove);
    } else {
        if (root->llink == nullptr || root->rlink == nullptr) {
            AVLNode* temp = root->llink ? root->llink : root->rlink;
            if (temp == nullptr) {
                root = nullptr;
            } else {
                root = temp;
            }
        } else {
            AVLNode* temp = getSuccessor(root);
            root->data = temp->data;
            root->rlink = removeNode(root->rlink, temp);
        }
    }

    if (BalanceFactor(root) > 1) {
        if (root->data < nodeToRemove->data) {
            return singleRightRotation(root);
        } else {
            root->llink = singleLeftRotation(root->llink);
            return singleRightRotation(root);
        }
    }

    if (BalanceFactor(root) < -1) {
        if (root->data > nodeToRemove->data) {
            return singleLeftRotation(root);
        } else {
            root->rlink = singleRightRotation(root->rlink);
            return singleLeftRotation(root);
        }
    }

    return root;
}

AVLNode* AVLTree::singleRightRotation(AVLNode* nodeToRotate) {
    AVLNode* parent = nodeToRotate->llink;
    nodeToRotate->llink = parent->rlink;
    parent->rlink = nodeToRotate;

    Height(nodeToRotate);
    Height(parent);

    return parent;
}

AVLNode* AVLTree::singleLeftRotation(AVLNode* nodeToRotate) {
    AVLNode* parent = nodeToRotate->rlink;
    nodeToRotate->rlink = parent->llink;
    parent->llink = nodeToRotate;

    Height(nodeToRotate);
    Height(parent);

    return parent;
}

void AVLTree::inorderTravers(AVLNode* node) {
    if (node != nullptr) {
        inorderTravers(node->llink);
        node->data.print();
        inorderTravers(node->rlink);
    }
}

void AVLTree::inorderReversedTravers(AVLNode* node) {
    if (node != nullptr) {
        inorderReversedTravers(node->rlink);
        node->data.print();
        inorderReversedTravers(node->llink);
    }
}

std::vector<Item> AVLTree::inorderTraversPrice(AVLNode* node) {
    std::vector<Item> items;
    if (node != nullptr) {
        std::vector<Item> leftItems = inorderTraversPrice(node->llink);
        items.insert(items.end(), leftItems.begin(), leftItems.end());

        items.push_back(node->data);

        std::vector<Item> rightItems = inorderTraversPrice(node->rlink);
        items.insert(items.end(), rightItems.begin(), rightItems.end());
    }

    return items;
}

void AVLTree::displayOrderedByNameAsc() {
    inorderTravers(Root);
}

void AVLTree::displayOrderedByNameDesc() {
    inorderReversedTravers(Root);
}

void AVLTree::displayOrderedByPriceAsc() {
    std::vector<Item> items = inorderTraversPrice(Root);
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.getPrice() < b.getPrice();
    });

    for (const auto& item : items) {
        item.print();
    }
}

void AVLTree::displayOrderedByPriceDesc() {
    std::vector<Item> items = inorderTraversPrice(Root);
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.getPrice() > b.getPrice();
    });

    for (const auto& item : items) {
        item.print();
    }
}
