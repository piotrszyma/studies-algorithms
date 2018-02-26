#include <iostream>
#include <stdexcept>
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
    if (TreeNode->getLeftChild() != nullptr) {
        showInOrderRec(TreeNode->getLeftChild());
    }
    std::cout << TreeNode->getValue() << " ";

    if (TreeNode->getRightChild() != nullptr) {
        showInOrderRec(TreeNode->getRightChild());
    }
}

template<typename T>
bool Tree<T>::findRec(T value, TreeNode <T>* TreeNode) {
    if (TreeNode == nullptr) {
        numberOfOperationsInFind++;
        return false;
    } else if (TreeNode->getValue() < value) {
        numberOfOperationsInFind++;
        return findRec(value, TreeNode->getRightChild());
    } else if (TreeNode->getValue() > value) {
        numberOfOperationsInFind++;
        return findRec(value, TreeNode->getLeftChild());
    } else {
        return true;
    }
}

template<typename T>
Tree<T>::Tree() {
    root = nullptr;
    treeSize = 0;
    numberOfOperationsInFind = 0;
};


template<typename T>
void Tree<T>::insert(T value) {
    treeSize++;
    if (root == nullptr) {
        root = new TreeNode<T>(value, nullptr);
    } else {
        this->addRec(value, root);
    }
}

template<typename T>
void Tree<T>::inorder() {
    if (root == nullptr) throw std::runtime_error("Tree is empty");
    showInOrderRec(root);
}

template<typename T>
bool Tree<T>::find(T value) {
    return this->findRec(value, root);
}

template<typename T>
int Tree<T>::min() {
    if (root == nullptr) throw std::runtime_error("Tree is empty");
    TreeNode<T>* minimalNode = findMinimum(root);
    return minimalNode->getValue();
}

template<typename T>
int Tree<T>::max() {
    if (root == nullptr) throw std::runtime_error("Tree is empty");
    TreeNode<T>* TreeNode = root;
    while (TreeNode->getRightChild() != nullptr) {
        TreeNode = TreeNode->getRightChild();
    }

    return TreeNode->getValue();
}

template<typename T>
int Tree<T>::size() {
    return treeSize;
}

template<typename T>
void Tree<T>::remove(T value) {
    treeSize--;
    deleteRec(value, root);
}

template<typename T>
void Tree<T>::deleteRec(T value, TreeNode <T>* treeNode) {
    if (treeNode == nullptr) {
        return;
    } else if (treeNode->getValue() < value) {
        deleteRec(value, treeNode->getRightChild());
    } else if (treeNode->getValue() > value) {
        deleteRec(value, treeNode->getLeftChild());
    } else {
        deleteOperation(treeNode);
    }
}

template<typename T>
void Tree<T>::deleteOperation(TreeNode <T>* treeNode) {
    if (treeNode == root) {
        if (treeNode->getRightChild() == nullptr && treeNode->getLeftChild() == nullptr) {
            root = nullptr;
            delete treeNode;
        } else if (treeNode->getRightChild() == nullptr) {
            root = treeNode->getLeftChild();
            delete treeNode;

        } else if (treeNode->getLeftChild() == nullptr) {
            root = treeNode->getRightChild();
            delete treeNode;

        } else {
            TreeNode<T>* smallestInRightSubTree = findMinimum(treeNode->getRightChild());
            changeParentsChildren(smallestInRightSubTree, nullptr);
            treeNode->setValue(smallestInRightSubTree->getValue());
            delete smallestInRightSubTree;
        }
        return;
    } else if (treeNode->getRightChild() == nullptr && treeNode->getLeftChild() == nullptr) {
        changeParentsChildren(treeNode, nullptr);
    } else if (treeNode->getRightChild() == nullptr) {
        changeParentsChildren(treeNode, treeNode->getLeftChild());
    } else if (treeNode->getLeftChild() == nullptr) {
        changeParentsChildren(treeNode, treeNode->getRightChild());
    } else {
        TreeNode<T>* smallestInRightSubTree = findMinimum(treeNode->getRightChild());
        changeParentsChildren(smallestInRightSubTree, nullptr);
        treeNode->setValue(smallestInRightSubTree->getValue());
        delete smallestInRightSubTree;
    }
    delete treeNode;
}

template<typename T>
void Tree<T>::changeParentsChildren(TreeNode <T>* treeNode, TreeNode <T>* newChildren) {
    if (treeNode->getParent()->getValue() <= treeNode->getValue()) {
        treeNode->getParent()->changeRightChild(newChildren);
    } else {
        treeNode->getParent()->changeLeftChild(newChildren);
    }
}

template<typename T>
TreeNode<T>* Tree<T>::findMinimum(TreeNode <T>* treeRoot) {
    TreeNode<T>* minimumNode = treeRoot;
    while (minimumNode->getLeftChild() != nullptr) {
        minimumNode = minimumNode->getLeftChild();
    }
    return minimumNode;
}

template<typename T>
int Tree<T>::getNumberOfOperationsInFind() {
    return numberOfOperationsInFind;
}

template<typename T>
void Tree<T>::resetNumberOfOperationsInFind() {
    numberOfOperationsInFind = 0;
}

template
class Tree<int>;