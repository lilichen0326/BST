//Lili Chen
using namespace std;

template<class T>
BST<T>::BST()
{
	root = nullptr;
}

template<class T>
BST<T>::~BST()
{
	deleteNode(root);
}

template<class T>
void BST<T>::deleteNode(Node<T>* node)
{
	if (node != nullptr)
	{
		deleteNode(node->left);
		deleteNode(node->right);
		delete node;
	}
}

template<class T>
void BST<T>::Insert(const T& newObj)
{
	Insert(root, newObj);
}

template<class T>
void BST<T>::Insert(Node<T>*& node, const T& newObj)
{
	if (node == nullptr)
	{
		node = newNode(newObj);
	}
	else if (node->self > newObj)
	{
		Insert(node->left, newObj);
		UpdateHeightByChildren(node);
	}
	else
	{
		Insert(node->right, newObj);
		UpdateHeightByChildren(node);
	}
}

template<class T>
Node<T>* BST<T>::newNode(const T& newObj)
{
	Node<T>* node = new Node<T>;
	node->self = newObj;
	node->height = 0;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

template<class T>
void BST<T>::Remove(const T& obj)
{
	Remove(root, obj);
}

template<class T>
void BST<T>::Remove(Node<T>*& node, const T& obj)
{
	if (node != nullptr)
	{
		if (node->self == obj)
		{
			Node<T>* deleted = node;
			if (numOfChildren(node) == 0)
				node = nullptr;
			else if (numOfChildren(node) == 1)
			{
				node = avaiableChild(node);
			}
			else
			{
				Node<T>* sNode = successor(node->right);
				sNode->left = node->left;
				sNode->right = node->right;
				node = sNode;
			}
			delete deleted;
		}
		else if (node->self > obj)
			Remove(node->left, obj);
		else
			Remove(node->right, obj);
		UpdateHeightByChildren(node);
	}
}

template<class T>
int BST<T>::numOfChildren(Node<T>*& node)
{
	return (node->left == nullptr ? 0 : 1) + (node->right == nullptr ? 0 : 1);
}

template<class T>
Node<T>* BST<T>::successor(Node<T>*& node)
{
	if (node->left != nullptr)
	{
		Node<T>* sNode = successor(node->left);
		UpdateHeightByChildren(node);
		return sNode;
	}
	else
	{
		Node<T>* sNode = node;
		node = node->right;
		return sNode;
	}
}

template<class T>
T& BST<T>::operator[] (const int index)
{
	Node<T>* result;
	find(root, result, index, new int(0));
	return result->self;
}

template<class T>
void BST<T>::find(Node<T>* node, Node<T>*& result, const int index, int* i)
{
	if (node != nullptr && *i <= index)
	{
		find(node->left, result, index, i);
		if (index == *i)
		{
			result = node;
			(*i)++;
			return;
		}
		else (*i)++;
		find(node->right, result, index, i);
	}
}

template<class T>
int BST<T>::Size()
{
	return Size(root);
}

template<class T>
int BST<T>::Size(Node<T>* node)
{
	return node == nullptr ? 0 : (Size(node->left) + Size(node->right) + 1);
}

template<class T>
int BST<T>::Height()
{
	return root == nullptr ? -1 : root->height;
}

template<class T>
BST<T>& BST<T>::operator = (const BST & otherBST)
{
	root = otherBST.root;
	return *this;
}

template<class T>
void BST<T>::Print()
{
	Print(root);
}

template<class T>
void BST<T>::Print(Node<T>* node)
{
	if (node != nullptr)
	{
		Print(node->left);
		cout << node->self;
		Print(node->right);
	}
}

template<class T>
void BST<T>::UpdateHeightByChildren(Node<T>* node)
{
	if (node != nullptr)
	{
		int maxChildHeight = -1;
		if (node->left != nullptr)	maxChildHeight = node->left->height;
		if (node->right != nullptr)	maxChildHeight = max(maxChildHeight, node->right->height);
		node->height = maxChildHeight + 1;
	}
}

template<class T>
Node<T>* BST<T>::avaiableChild(Node<T>* node)
{
	if (node->left != nullptr) return node->left;
	else return node->right;
}

template<class T>
void AVL<T>::Insert(const T& newObj)
{
	Insert(BST<T>::root, newObj);
}

// return true if x is left child
template<class T>
bool AVL<T>::Insert(Node<T>*& node, const T& newObj)
{
	if (node == nullptr)
	{
		node = BST<T>::newNode(newObj);
		return false;
	}
	else if (node->self > newObj)
	{
		bool leftX = Insert(node->left, newObj);
		reBalance(node, leftX, true);
		BST<T>::UpdateHeightByChildren(node);
		return true;
	}
	else
	{
		bool leftX = Insert(node->right, newObj);
		reBalance(node, leftX, false);
		BST<T>::UpdateHeightByChildren(node);
		return false;
	}
}


template<class T>
void AVL<T>::reBalance(Node<T>*& node, bool leftX, bool leftY)
{
	if (node != nullptr && !isBalance(node))
	{
		if (leftX && leftY)
			rightRotate(node);
		else if (!leftX && leftY)
		{
			leftRotate(node->left);
			rightRotate(node);
		}
		else if (!leftX && !leftY)
			leftRotate(node);
		else
		{
			rightRotate(node->right);
			leftRotate(node);
		}
		BST<T>::UpdateHeightByChildren(node->left);
		BST<T>::UpdateHeightByChildren(node->right);
		BST<T>::UpdateHeightByChildren(node);
	}
}

template<class T>
void AVL<T>::leftRotate(Node<T>*& node)
{
	Node<T>* nodeX = node->right;
	node->right = nodeX->left;
	nodeX->left = node;
	node = nodeX;
}

template<class T>
void AVL<T>::rightRotate(Node<T>*& node)
{
	Node<T>* nodeY = node->left;
	node->left = nodeY->right;
	nodeY->right = node;
	node = nodeY;
}

template<class T>
bool AVL<T>::isBalance(Node<T>* node)
{
	int left = node->left == nullptr ? -1 : node->left->height;
	int right = node->right == nullptr ? -1 : node->right->height;
	return (abs(left - right) < 2);
}

template<class T>
void AVL<T>::Remove(const T& obj)
{
	Remove(BST<T>::root, obj);
}

template<class T>
void AVL<T>::Remove(Node<T>*& node, const T& obj)
{
	if (node != nullptr)
	{
		if (node->self == obj)
		{
			Node<T>* deleted = node;
			if (BST<T>::numOfChildren(node) == 0)
				node = nullptr;
			else if (BST<T>::numOfChildren(node) == 1)
			{
				node = BST<T>::avaiableChild(node);
			}
			else
			{
				Node<T>* sNode = BST<T>::successor(node->right);
				sNode->left = node->left;
				sNode->right = node->right;
				node = sNode;
			}
			delete deleted;
		}
		else if (node->self > obj)
			Remove(node->left, obj);
		else
			Remove(node->right, obj);
		BST<T>::UpdateHeightByChildren(node);
		reBalance(node);
	}
}

template<class T>
void AVL<T>::reBalance(Node<T>*& node)
{
	if (node != nullptr && !isBalance(node))
	{
		bool leftY = isLeftChildHigher(node);
		bool leftX;
		if(leftY)
			leftX = isLeftChildHigher(node->left);
		else
			leftX = isLeftChildHigher(node->right);
		if (leftX && leftY)
			rightRotate(node);
		else if (!leftX && leftY)
		{
			leftRotate(node->left);
			rightRotate(node);
		}
		else if (!leftX && !leftY)
			leftRotate(node);
		else
		{
			rightRotate(node->right);
			leftRotate(node);
		}
		BST<T>::UpdateHeightByChildren(node->left);
		BST<T>::UpdateHeightByChildren(node->right);
		BST<T>::UpdateHeightByChildren(node);
	}
}

template<class T>
bool AVL<T>::isLeftChildHigher(Node<T>* node)
{
	return ((node->left == nullptr ? -1 : node->left->height) >= (node->right == nullptr ? -1 : node->right->height));
}