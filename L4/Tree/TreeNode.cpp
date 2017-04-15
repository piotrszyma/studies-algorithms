//
// Created by thomp on 12.04.2017.
//

#include "TreeNode.h"


//template<typename T>
//TreeNode<T>* TreeNode<T>::parentPointer;
//template<typename T>
//TreeNode<T>* TreeNode<T>::leftChildPointer;
//template<typename T>
//TreeNode<T>* TreeNode<T>::rightChildPointer;
//template<typename T>
//T TreeNode<T>::value;

template<typename T>
TreeNode<T>::TreeNode(T value, TreeNode* parent) {
    this->value = value;
    this->leftChildPointer = nullptr;
    this->rightChildPointer = nullptr;
    this->parentPointer = parent;
}

template<typename T>
TreeNode<T>* TreeNode<T>::getParent() {
    return this->parentPointer;
}

template<typename T>
TreeNode<T>* TreeNode<T>::getLeftChild() {
    return this->leftChildPointer;
}

template<typename T>
TreeNode<T>* TreeNode<T>::getRightChild() {
    return this->rightChildPointer;
}

template<typename T>
T TreeNode<T>::getValue() {
    return this->value;
}

template<typename T>
TreeNode<T>* TreeNode<T>::setRightChild(T value) {
    rightChildPointer = new TreeNode(value, this);
}

template<typename T>
TreeNode<T>* TreeNode<T>::setLeftChild(T value) {
    leftChildPointer = new TreeNode(value, this);
}

template<typename T>
TreeNode<T>::~TreeNode() {};


template
class TreeNode<int>;