#include <iostream>
#include "Tree.h"

template<typename T>
void Tree<T>::addRec(T value, TreeNode<T>* parent) {
    if (value > parent->getValue()) {
        if (parent->getRightChild() != nullptr) {
            this->addRec(value, parent->getRightChild());
        } else {
            parent->setRightChild(value);
        }
    } else {
        if (parent->getLeftChild() != nullptr) {
            this->addRec(value, parent->getLeftChild());
        } else {
            parent->setLeftChild(value);
        }
    }
}

template<typename T>
void Tree<T>::showInOrderRec(TreeNode<T>* TreeNode) {
    if (TreeNode->getRightChild() != nullptr) {
        showInOrderRec(TreeNode->getRightChild());
    }
    std::cout << TreeNode->getValue() << std::endl;

    if (TreeNode->getLeftChild() != nullptr) {
        showInOrderRec(TreeNode->getLeftChild());
    }
}

template<typename T>
bool Tree<T>::findRec(T value, TreeNode <T>* TreeNode) {
    if (TreeNode == nullptr) {
        return false;
    } else if (TreeNode->getValue() < value) {
        return findRec(value, TreeNode->getRightChild());
    } else if (TreeNode->getValue() > value) {
        return findRec(value, TreeNode->getLeftChild());
    } else {
        return true;
    }
}

template<typename T>
Tree<T>::Tree() {
    root = nullptr;
};


template<typename T>
void Tree<T>::insert(T value) {
    if (root == nullptr) {
        root = new TreeNode<T>(value, nullptr);
    } else {
        this->addRec(value, root);
    }
}

template<typename T>
void Tree<T>::inorder() {
    //TODO:    if(root == nullptr) throw new exception;
    showInOrderRec(root);
}

template<typename T>
bool Tree<T>::find(T value) {
    return this->findRec(value, root);
}

template<typename T>
int Tree<T>::min() {
    TreeNode<T>* TreeNode = root;
//TODO:    if(TreeNode == nullptr) throw new exception;
    while (TreeNode->getLeftChild() != nullptr) {
        TreeNode = TreeNode->getLeftChild();
    }

    return TreeNode->getValue();
}

template<typename T>
int Tree<T>::max() {
    TreeNode<T>* TreeNode = root;
//TODO:   if(TreeNode == nullptr) throw new exception;
    while (TreeNode->getRightChild() != nullptr) {
        TreeNode = TreeNode->getRightChild();
    }

    return TreeNode->getValue();
}

template
class Tree<int>;