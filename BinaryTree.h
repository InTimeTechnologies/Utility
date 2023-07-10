#pragma once

// Forward declarations | Utility
template <typename T> class BinaryNode;
template <typename T> class BinaryTree;

// class BinaryNode 
template <typename T> class BinaryNode {
	// Friends
	friend class BinaryTree<T>;
	// Object
	private:
		// Properties
		BinaryTree<T>* binaryTree;
		BinaryNode<T>* parentNode;
		BinaryNode<T>* leftNode;
		BinaryNode<T>* rightNode;
	public:
		// Properties
		T data;

		// Constructor / Destructor
		BinaryNode();
		BinaryNode(T data);
		BinaryNode(const BinaryNode<T>& binaryNode);
		void operator = (const BinaryNode<T>& binaryNode);
		~BinaryNode();

		// Getters
		BinaryTree<T>* getBinaryTree() const;
		BinaryNode<T>* getParentNode() const;
		BinaryNode<T>* getLeftNode() const;
		BinaryNode<T>* getRightNode() const;

		// Functions
		BinaryNode<T>* addLeftNode(T data);
		BinaryNode<T>* addRightNode(T data);
		BinaryNode<T>* getLeftmostLeaf() const;
		BinaryNode<T>* getRightmostLeaf() const;

		void destroy();
};

// class BinaryTree
template <typename T> class BinaryTree {
	// Friends
	friend class BinaryNode<T>;
	// Object
	private:
		// Properties
		unsigned long long size;
		BinaryNode<T>* rootNode;
	public:
		// Constructor / Destructor
		BinaryTree();
		BinaryTree(const BinaryTree<T>& binaryTree);
		void operator = (const BinaryTree<T>& binaryTree);
		~BinaryTree();

		// Getters
		unsigned long long getSize() const;
		BinaryNode<T>* getRootNode() const;
		BinaryNode<T>* getNodeWithData(T data) const;

		// Functions
		BinaryNode<T>* add(T data);
		bool remove(T data);
		bool has(T data);
		void clear();
};

// class BinaryNode

// Object | public

// Constructor / Destructor
template <typename T> BinaryNode<T>::BinaryNode() : binaryTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr) {

}
template <typename T> BinaryNode<T>::BinaryNode(T data) : binaryTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(data) {

}
template <typename T> BinaryNode<T>::BinaryNode(const BinaryNode<T>& binaryNode) : binaryTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(binaryNode.data) {

}
template <typename T> void BinaryNode<T>::operator = (const BinaryNode<T>& binaryNode) {
	data = binaryNode.data;
}
template <typename T> BinaryNode<T>::~BinaryNode() {
	// Start destruction on left side
	BinaryNode<T>* currentNode = leftNode;

	// Destroy every binary node under currentNode
	while (currentNode != nullptr) {
		// Search for leaf
		if (currentNode->leftNode != nullptr) {
			currentNode = currentNode->leftNode;
			continue;
		}
		if (currentNode->rightNode != nullptr) {
			currentNode = currentNode->rightNode;
			continue;
		}

		// Save parent node before deletion
		BinaryNode<T>* parentNode = currentNode->parentNode;

		// Delete current node
		delete(currentNode);

		// Go up to parent node
		currentNode = parentNode;

		// If current node is this, continue destruction on right side
		if (currentNode == this)
			currentNode = currentNode->rightNode;
	}

	// Unlink this node from parent node
	if (parentNode != nullptr) {
		if (parentNode->leftNode == this)
			parentNode->leftNode = nullptr;
		else
			parentNode->rightNode = nullptr;
	}

	if (binaryTree != nullptr) {
		// Decrement tree size
		binaryTree->size--;

		// If this is tree's root node, assign it to nullptr
		if (this == binaryTree->rootNode)
			binaryTree->rootNode = nullptr;
	}
}

// Getters
template <typename T> BinaryTree<T>* BinaryNode<T>::getBinaryTree()  const {
	return binaryTree;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getParentNode()  const {
	return parentNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getLeftNode()  const {
	return leftNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getRightNode()  const {
	return rightNode;
}

// Functions
template <typename T> BinaryNode<T>* BinaryNode<T>::addLeftNode(T data) {
	if (leftNode != nullptr)
		return nullptr;

	leftNode = new BinaryNode<T>(data);
	leftNode->binaryTree = binaryTree;
	leftNode->parentNode = this;

	return leftNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::addRightNode(T data) {
	if (rightNode != nullptr)
		return nullptr;

	rightNode = new BinaryNode<T>(data);
	rightNode->binaryTree = binaryTree;
	rightNode->parentNode = this;

	return rightNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getLeftmostLeaf() const{
	if (leftNode == nullptr)
		return nullptr;

	BinaryNode<T>* currentNode = leftNode;
	while (currentNode->leftNode != nullptr)
		currentNode = leftNode->leftNode;

	return currentNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getRightmostLeaf() const {
	if (rightNode == nullptr)
		return nullptr;

	BinaryNode<T>* currentNode = rightNode;
	while (currentNode != nullptr)
		currentNode = currentNode->rightNode;

	return currentNode;
}

template <typename T> void BinaryNode<T>::destroy() {
	delete(this);
}

// class BinaryTree

// Object | public

// Constructor / Destructor
template <typename T> BinaryTree<T>::BinaryTree() : size(0ULL), rootNode(nullptr) {

}
template <typename T> BinaryTree<T>::BinaryTree(const BinaryTree<T>& binaryTree) {
	// If tree is empty, return false
	if (binaryTree.size == 0ULL)
		return;

	// Search tree for data
	BinaryNode<T>* otherCurrentNode = binaryTree.rootNode;
	BinaryNode<T>* thisCurrentNode = new BinaryNode<T>(this, otherCurrentNode->data);
	while (otherCurrentNode != nullptr) {
		// Check left branch
		if (otherCurrentNode->leftNode != nullptr) {
			otherCurrentNode = otherCurrentNode->leftNode;
			thisCurrentNode = thisCurrentNode->addLeftNode(this, otherCurrentNode->data);
			continue;
		}

		// Traverse tree upwards searching for right nodes
		while (otherCurrentNode->parentNode != nullptr) {
			otherCurrentNode = otherCurrentNode->parentNode;
			if (otherCurrentNode->rightNode != nullptr) {
				// Trigger right node's left branch check
				otherCurrentNode = otherCurrentNode->rightNode;
				thisCurrentNode = thisCurrentNode->addRightNode(this, otherCurrentNode->data);
				break;
			}
		}
	}
}
template <typename T> void BinaryTree<T>::operator = (const BinaryTree<T>& binaryTree) {
	// Clear this tree of nodes
	clear();

	// If tree is empty, return false
	if (binaryTree.size == 0ULL)
		return;

	// Search tree for data
	BinaryNode<T>* otherCurrentNode = binaryTree.rootNode;
	BinaryNode<T>* thisCurrentNode = new BinaryNode<T>(this, otherCurrentNode->data);
	while (otherCurrentNode != nullptr) {
		// Check left branch
		if (otherCurrentNode->leftNode != nullptr) {
			otherCurrentNode = otherCurrentNode->leftNode;
			thisCurrentNode = thisCurrentNode->addLeftNode(this, otherCurrentNode->data);
			continue;
		}

		// Traverse tree upwards searching for right nodes
		while (otherCurrentNode->parentNode != nullptr) {
			otherCurrentNode = otherCurrentNode->parentNode;
			if (otherCurrentNode->rightNode != nullptr) {
				// Trigger right node's left branch check
				otherCurrentNode = otherCurrentNode->rightNode;
				thisCurrentNode = thisCurrentNode->addRightNode(this, otherCurrentNode->data);
				break;
			}
		}
	}
}
template <typename T> BinaryTree<T>::~BinaryTree() {
	clear();
}

// Getters
template <typename T> unsigned long long BinaryTree<T>::getSize() const {
	return size;
}
template <typename T> BinaryNode<T>* BinaryTree<T>::getRootNode() const {
	return rootNode;
}
template <typename T> BinaryNode<T>* BinaryTree<T>::getNodeWithData(T data) const {
	// If tree is empty, return nullptr
	if (rootNode == nullptr)
		return nullptr;

	// Check root node
	if (rootNode->data == data)
		return rootNode;

	// Sentinel value
	bool visitedRootNode = false;

	// Start search on left side
	BinaryNode<T>* currentNode = rootNode->leftNode;

	while (currentNode != nullptr) {
		// If data found, return current node
		if (currentNode->data == data)
			return currentNode;

		// Search for leaf
		if (currentNode->leftNode != nullptr) {
			currentNode = currentNode->leftNode;
			continue;
		}
		if (currentNode->rightNode != nullptr) {
			currentNode = currentNode->rightNode;
			continue;
		}

		// If all nodes visisted, break from search / loop
		if (visitedRootNode)
			break;

		// Start search on left side
		BinaryNode<T>* parentNode = currentNode->parentNode;
		if (parentNode == rootNode) {
			visitedRootNode = true;
			currentNode = rootNode->rightNode;
		}
	}

	// Return nullptr
	return nullptr;
}

// Functions
template <typename T> BinaryNode<T>* BinaryTree<T>::add(T data) {
	// If tree is empty, add to tree as root node
	if (size == 0ULL) {
		rootNode = new BinaryNode<T>(data);
		rootNode->binaryTree = this;
		return rootNode;
	}


	// Add to tree based on data value (greater or equal)
	BinaryNode<T>* currentNode = rootNode;
	while (currentNode != nullptr) {
		if (data <= currentNode->data) {
			if (currentNode->leftNode == nullptr)
				return currentNode->addLeftNode(data);

			currentNode = currentNode->leftNode;
			continue;
		}
		if (data > currentNode->data) {
			if (currentNode->rightNode == nullptr)
				return currentNode->addRightNode(data);

			currentNode = currentNode->rightNode;
			continue;
		}
		break;
	}

	// Failed to add to tree somehow
	return nullptr;
}
template <typename T> bool BinaryTree<T>::remove(T data) {
	// If tree is empty, return false
	if (size == 0ULL)
		return false;

	// Check root node
	if (rootNode->data == data) {
		delete(rootNode);
		return true;
	}

	// Search tree for data
	BinaryNode<T>* currentNode = rootNode;
	while (currentNode != nullptr) {
		// If data found, return true
		if (currentNode->data == data) {
			delete(currentNode);
			return true;
		}

		// Check left branch
		if (currentNode->leftNode != nullptr) {
			currentNode = currentNode->leftNode;
			continue;
		}

		// Traverse tree upwards searching for right nodes
		while (currentNode->parentNode != nullptr) {
			currentNode = currentNode->parentNode;
			if (currentNode->rightNode != nullptr) {
				// Trigger right node's left branch check
				currentNode = currentNode->rightNode;
				break;
			}
		}
	}
}
template <typename T> bool BinaryTree<T>::has(T data) {
	// If tree is empty, return false
	if (size == 0ULL)
		return false;

	// Check root node
	if (rootNode->data == data)
		return true;

	// Search tree for data
	BinaryNode<T>* currentNode = rootNode;
	while (currentNode != nullptr) {
		// If data found, return true
		if (currentNode->data == data)
			return true;

		// Check left branch
		if (currentNode->leftNode != nullptr) {
			currentNode = currentNode->leftNode;
			continue;
		}

		// Traverse tree upwards searching for right nodes
		while (currentNode->parentNode != nullptr) {
			currentNode = currentNode->parentNode;
			if (currentNode->rightNode != nullptr) {
				// Trigger right node's left branch check
				currentNode = currentNode->rightNode;
				break;
			}
		}
	}

	// Data not found in tree
	return false;
}
template <typename T> void BinaryTree<T>::clear() {
	delete(rootNode);
}
