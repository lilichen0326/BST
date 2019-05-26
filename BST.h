//Lili Chen
#ifndef BST_H
#define BST_H
#include <iostream> 
#include <string>
#include <math.h> 
#include <algorithm> 

template<typename T>
struct Node
{
	T self;
	int height;
	Node* left;
	Node* right;
};

template<class T>
class BST
{
public:
	BST();
	~BST();
	void Insert(const T& newObj);
	void Remove(const T& obj);
	void Print();
	T& operator[] (const int index);
	int Size();
	int Height();
	BST<T>& operator = (const BST & otherBST);

protected:

	Node<T>* root;
	void deleteNode(Node<T>* node);
	void Insert(Node<T>*& node, const T& newObj);
	Node<T>* newNode(const T& newObj);
	void Remove(Node<T>*& node, const T& obj);
	int numOfChildren(Node<T>*& node);
	void Print(Node<T>* node);
	void find(Node<T>* node, Node<T>*& result, const int index, int* i);
	int Size(Node<T>* node);
	void UpdateHeightByChildren(Node<T>* node);
	Node<T>* avaiableChild(Node<T>* node);
	Node<T>* successor(Node<T>*& node);

};


template<class T>
class AVL : public BST<T>
{
public:
	void Insert(const T& newObj);
	void Remove(const T& obj);
protected:
	bool Insert(Node<T>*& node, const T& newObj);
	void reBalance(Node<T>*& node, bool leftX, bool leftY);
	bool isBalance(Node<T>* node);
	void leftRotate(Node<T>*& node);
	void rightRotate(Node<T>*& node);
	void Remove(Node<T>*& node, const T& obj);
	void reBalance(Node<T>*& node);
	bool isLeftChildHigher(Node<T>* node);
};

#include "BST.cpp"
#endif 
