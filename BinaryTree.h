#pragma once

// Forward declarations
template <typename T> class BinaryNode;
template <typename T> class BinaryTree;

// class BinaryDirection
enum class BinaryDirection {
	NONE,
	LEFT,
	RIGHT
};

// class BinaryNode
template <typename T> class BinaryNode {
	// Friends
	friend class BinaryTree<T>;

	// Object
	public:
		// Properties
		T data;

	private:
		// Properties
		BinaryNode<T>* parentNode = nullptr;
		BinaryNode<T>* leftNode = nullptr;
		BinaryNode<T>* rightNode = nullptr;
		BinaryTree<T>* tree = nullptr;

	public:
		// Constructor / Destructor
		BinaryNode();
		BinaryNode(const T& data);
		~BinaryNode();

		// Getters
		BinaryNode<T>* getParentNode() const;
		BinaryNode<T>* getLeftNode() const;
		BinaryNode<T>* getRightNode() const;
		BinaryTree<T>* getTree() const;

		// Functions
		BinaryNode<T>* getRootNode() const;
		BinaryNode<T>* getLeftmostNode() const;
		BinaryNode<T>* getRightmostNode() const;
		BinaryNode<T>* get(const T& data) const;
		bool has(const T& data) const;
		BinaryDirection getDirection() const;

		BinaryNode<T>* addParentNode(const T& data, BinaryDirection parentNodeDirection);
		BinaryNode<T>* addLeftNode(const T& data);
		BinaryNode<T>* addRightNode(const T& data);
		BinaryNode<T>* add(const T& data);
		BinaryNode<T>* add(const T& data, BinaryDirection directionIfEqual);
		bool erase(const T& data);
		void clearNodes();
};

// class BinaryTree
template <typename T> class BinaryTree {
	// Friends
	friend class BinaryNode<T>;

	// Object
	private:
		// Properties
		int size = 0;
		BinaryNode<T>* rootNode = nullptr;

	public:
		// Constructor / Destructor
		BinaryTree();
		BinaryTree(const BinaryTree<T>& tree);
		void operator = (const BinaryTree<T>& tree);
		~BinaryTree();

		// Getters
		int getSize() const;
		BinaryNode<T>* getRootNode() const;

		// Functions
		BinaryNode<T>* add(const T& data);
		void clear();
};

// class BinaryNode

// Object | public

// Constructor / Destructor
template <typename T> BinaryNode<T>::BinaryNode() {
	
}
template <typename T> BinaryNode<T>::BinaryNode(const T& data) : data(data) {

}
template <typename T> BinaryNode<T>::~BinaryNode() {
	clearNodes();

	// Unlink this node from parent node
	if (parentNode != nullptr) {
		if (parentNode->leftNode == this)
			parentNode->leftNode = nullptr;
		else
			parentNode->rightNode = nullptr;
	}

	if (tree != nullptr)
		tree->size--;
}

// Getters
template <typename T> BinaryNode<T>* BinaryNode<T>::getParentNode() const {
	return parentNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getLeftNode() const {
	return leftNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getRightNode() const {
	return rightNode;
}
template <typename T> BinaryTree<T>* BinaryNode<T>::getTree() const {
	return tree;
}

// Functions
template <typename T> BinaryNode<T>* BinaryNode<T>::getRootNode() const {
	if (parentNode == nullptr)
		return nullptr;

	BinaryNode<T>* currentNode = this;
	while (currentNode->parentNode != nullptr)
		currentNode = currentNode->parentNode;

	return currentNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getLeftmostNode() const {
	if (leftNode == nullptr)
		return nullptr;

	BinaryNode<T>* currentNode = leftNode;
	while (currentNode->leftNode != nullptr)
		currentNode = leftNode->leftNode;

	return currentNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::getRightmostNode() const {
	if (rightNode == nullptr)
		return nullptr;

	BinaryNode<T>* currentNode = rightNode;
	while (currentNode->rightNode != nullptr)
		currentNode = rightNode->rightNode;

	return currentNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::get(const T& data) const {
	BinaryNode<T>* currentNode = this;
	while (currentNode != nullptr) {
		// If current node's data is equal to data provided, return current node
		if (currentNode->data == data)
			return currentNode;

		// Check left branch
		if (currentNode->leftNode != nullptr) {
			currentNode = currentNode->leftNode;
			continue;
		}

		// Traverse tree up searching for right nodes
		while (currentNode->parentNode != nullptr) {
			currentNode = currentNode->parentNode;
			if (currentNode->rightNode != nullptr) {
				// Trigger nodes's left branch check
				currentNode = currentNode->rightNode;
				break;
			}
		}
	}

	return nullptr;
}
template <typename T> bool BinaryNode<T>::has(const T& data) const {
	return get(data) == nullptr ? false : true;
}
template <typename T> BinaryDirection BinaryNode<T>::getDirection() const {
	if (parentNode == nullptr)
		return BinaryDirection::NONE;

	if (parentNode->leftNode == this)
		return BinaryDirection::LEFT;
	else if (parentNode->rightNode == this)
		return BinaryDirection::RIGHT;

	return BinaryDirection::NONE;
}

template <typename T> BinaryNode<T>* BinaryNode<T>::addParentNode(const T& data, BinaryDirection parentNodeDirection) {
	// If this node already has a parent node, return false
	if (parentNode != nullptr)
		return nullptr;

	// Link new node to this
	BinaryNode<T>* newNode = new BinaryNode<T>();
	newNode->data = data;
	if (parentNodeDirection == BinaryDirection::LEFT)
		newNode->rightNode = this;
	else
		newNode->leftNode = this;

	// Edit tree
	if (tree != nullptr) {
		newNode->tree = tree;
		tree->size++;
		tree->rootNode = this;
	}

	// Link this to new node
	parentNode = newNode;

	// Return true
	return newNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::addLeftNode(const T& data) {
	// If this node already has a node to the left, return false
	if (leftNode != nullptr)
		return nullptr;

	// Link new node to this
	BinaryNode<T>* newNode = new BinaryNode<T>(data);
	newNode->parentNode = this;
	
	// Edit tree
	if (tree != nullptr) {
		newNode->tree = tree;
		tree->size++;
	}

	// Link this to new node
	leftNode = newNode;

	// Return true
	return newNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::addRightNode(const T& data) {
	// If this node already has a node to the right, return false
	if (rightNode != nullptr)
		return nullptr;

	// Link new node to this
	BinaryNode<T>* newNode = new BinaryNode<T>(data);
	newNode->parentNode = this;

	// Edit tree
	if (tree != nullptr) {
		newNode->tree = tree;
		tree->size++;
	}
	
	// Link this to new node
	rightNode = newNode;

	// Return true
	return newNode;
}
template <typename T> BinaryNode<T>* BinaryNode<T>::add(const T& data) {
	BinaryNode<T>* newNode = new BinaryNode<T>(data);

	BinaryNode<T>* currentNode = this;
	while (currentNode != nullptr) {
		if (data <= currentNode->data) {
			if (currentNode->leftNode == nullptr)
				return currentNode->addLeftNode(data);
			
			currentNode = currentNode->leftNode;
			continue;
		}
		else if (data > currentNode->data) {
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
template <typename T> BinaryNode<T>* BinaryNode<T>::add(const T& data, BinaryDirection directionIfEqual) {
	BinaryNode<T>* newNode = new BinaryNode<T>(data);

	BinaryNode<T>* currentNode = this;
	while (currentNode != nullptr) {
		if (data < currentNode->data || (data == currentNode->data && directionIfEqual == BinaryDirection::LEFT)) {
			if (currentNode->leftNode == nullptr)
				return currentNode->addLeftNode(data);

			currentNode = currentNode->leftNode;
			continue;
		}
		else if (data > currentNode->data || (data == currentNode->data && directionIfEqual == BinaryDirection::RIGHT)) {
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
template <typename T> bool BinaryNode<T>::erase(const T& data) {
	BinaryNode<T>* nodeToErase = get(data);
	
	if (nodeToErase == nullptr)
		return false;

	delete(nodeToErase);
	return true;
}
template <typename T> void BinaryNode<T>::clearNodes() {
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
}

// class BinaryTree

// Object | public

// Constructor / Destructor
template <typename T> BinaryTree<T>::BinaryTree() {

}
template <typename T> BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree) {
	// If tree is empty, return false
	if (tree.size == 0ULL)
		return;

	// Search tree for data
	BinaryNode<T>* otherCurrentNode = tree.rootNode;
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
template <typename T> void BinaryTree<T>::operator = (const BinaryTree<T>& tree) {
	// Clear this tree of nodes
	clear();

	// If tree is empty, return false
	if (tree.size == 0ULL)
		return;

	// Search tree for data
	BinaryNode<T>* otherCurrentNode = tree.rootNode;
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
template <typename T> int BinaryTree<T>::getSize() const {
	return size;
}
template <typename T> BinaryNode<T>* BinaryTree<T>::getRootNode() const {
	return rootNode;
}

// Functions
template <typename T> BinaryNode<T>* BinaryTree<T>::add(const T& data) {
	if (size == 0) {
		rootNode = new BinaryNode<T>(data);
		rootNode->tree = this;
		size++;
		return rootNode;
	}

	return rootNode->add(data);
}
template <typename T> void BinaryTree<T>::clear() {
	delete(rootNode);
}
