#pragma once

// Forward declaractions | Utility
template <typename T> class BinarySearchNode;
template <typename T> class BinarySearchTree;

// class BinarySearchNodeDirection
enum class BinarySearchNodeDirection {
	LEFT,
	RIGHT
};

// class BinarySearchNode
template <typename T> class BinarySearchNode {
	// Friends
	friend class BinarySearchTree<T>;

	// Static
	public:
		// Properties
		static BinarySearchNodeDirection nodeDirectionAscendsOnDeletion;

		// Functions
		static bool linkBranches(BinarySearchNode<T>* ascendingNode, BinarySearchNode<T>* descendingNode);
	// Object
	private:
		// Properties
		BinarySearchTree<T>* binarySearchTree;
		BinarySearchNode<T>* parentNode;
		BinarySearchNode<T>* leftNode;
		BinarySearchNode<T>* rightNode;
	public:
		// Properties
		T data;

		// Constructor / Destructur
		BinarySearchNode();
		BinarySearchNode(T data);
		BinarySearchNode(const BinarySearchNode<T>& binarySearchNode);
		void operator = (const BinarySearchNode<T>& binarySearchNode);
		~BinarySearchNode();

		// Getters
		BinarySearchTree<T>* getBinarySearchTree();
		BinarySearchNode<T>* getParentNode();
		BinarySearchNode<T>* getLeftNode();
		BinarySearchNode<T>* getRightNode();

		// Functions
		BinarySearchNode<T>* getLeftmostNode();
		BinarySearchNode<T>* getRightmostNode();
		BinarySearchNode<T>* add(T data);
		BinarySearchNode<T>* get(T data);
		bool has(T data);
		bool remove(T data);
		void destroy();
};

// class BinarySearchTree
template <typename T> class BinarySearchTree {
	// Friends
	friend class BinarySearchNode<T>;
	// Object
	private:
		// Properties
		unsigned long long size;
		BinarySearchNode<T>* rootNode;
	public:
		// Constructore / Destructor
		BinarySearchTree();
		~BinarySearchTree();

		// Getters
		unsigned long long getSize() const;
		BinarySearchNode<T>* getRootNode() const;

		// Functions
		BinarySearchNode<T>* add(T data);
		BinarySearchNode<T>* get(T data) const;
		bool has(T data) const;
		void clear();
};

// class BinarySearchNode

// Static | public

// Properties
template <typename T> BinarySearchNodeDirection BinarySearchNode<T>::nodeDirectionAscendsOnDeletion = BinarySearchNodeDirection::LEFT;

// Functions
template <typename T> bool BinarySearchNode<T>::linkBranches(BinarySearchNode<T>* ascendingNode, BinarySearchNode<T>* descendingNode) {
	if (ascendingNode == nullptr || descendingNode == nullptr)
		return false;
	
	if (nodeDirectionAscendsOnDeletion == BinarySearchNodeDirection::LEFT) {
		BinarySearchNode<T>* upperLinkingNode = ascendingNode->getRightmostNode();
		if (upperLinkingNode == nullptr)
			upperLinkingNode = ascendingNode;
		upperLinkingNode->rightNode = descendingNode;
	}
	else {
		BinarySearchNode<T>* upperLinkingNode = ascendingNode->getLeftmostNode();
		if (upperLinkingNode == nullptr)
			upperLinkingNode = ascendingNode;
		upperLinkingNode->leftNode = descendingNode;
	}
	descendingNode->parentNode = ascendingNode;

	return true;
}

// Object | public

// Constructor / Destructor
template <typename T> BinarySearchNode<T>::BinarySearchNode() : binarySearchTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr) {
	
}
template <typename T> BinarySearchNode<T>::BinarySearchNode(T data) : binarySearchTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(data) {

}
template <typename T> BinarySearchNode<T>::BinarySearchNode(const BinarySearchNode<T>& binarySearchNode) : binarySearchTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(binarySearchNode.data) {

}
template <typename T> void BinarySearchNode<T>::operator = (const BinarySearchNode<T>& binarySearchNode) {
	data = binarySearchNode->data;
}
template <typename T> BinarySearchNode<T>::~BinarySearchNode() {
	BinarySearchNode<T>* ascendingNode = nullptr;
	// If node to delete does not have a left nor right node, just unlink parent from this
	if (leftNode == nullptr && rightNode == nullptr) {
		if (parentNode != nullptr) {
			if (parentNode->leftNode == this)
				parentNode->leftNode = nullptr;
			else
				parentNode->rightNode = nullptr;
		}
	}
	// If node has a left and a right node, relink accordingly
	else if (leftNode != nullptr && rightNode != nullptr) {
		BinarySearchNode<T>* descendingNode = nullptr;
		if (nodeDirectionAscendsOnDeletion == BinarySearchNodeDirection::LEFT) {
			ascendingNode = leftNode;
			descendingNode = rightNode;
		}
		else {
			ascendingNode = rightNode;
			descendingNode = leftNode;
		}
		ascendingNode->parentNode = parentNode;

		// Link descendingNode to ascendingNode
		linkBranches(ascendingNode, descendingNode);
	}
	// If node only has one node below, relink accordingly
	else {
		// Link node below to parentNode
		if (leftNode == nullptr) // If left node is nullptr, right node is the ascending node
			ascendingNode = rightNode;
		else // If right node is nullptr, left node is the ascending node
			ascendingNode = leftNode;
		ascendingNode->parentNode = parentNode;
		
		// Relink parent node to node below
		if (parentNode != nullptr) {
			if (parentNode->leftNode == this) // If this node is left node of parent's node, relink parent's left node to ascending node
				parentNode->leftNode = this;
			else // If this node is right node of parent's node, relink parent's right node to ascending node
				parentNode->rightNode = this;
		}
	}

	// If this node belongs to a binary tree, descres its size
	if (binarySearchTree != nullptr) {
		binarySearchTree->size--;
		if (binarySearchTree->size == 0ULL)
			binarySearchTree->rootNode = nullptr;
		else if (ascendingNode != nullptr && ascendingNode->parentNode == nullptr)
			binarySearchTree->rootNode = ascendingNode;
	}
}

// Getters
template <typename T> BinarySearchTree<T>* BinarySearchNode<T>::getBinarySearchTree() {
	return binarySearchTree;
}
template <typename T> BinarySearchNode<T>* BinarySearchNode<T>::getParentNode() {
	return parentNode;
}
template <typename T> BinarySearchNode<T>* BinarySearchNode<T>::getLeftNode() {
	return leftNode;
}
template <typename T> BinarySearchNode<T>* BinarySearchNode<T>::getRightNode() {
	return rightNode;
}

// Functions
template <typename T> BinarySearchNode<T>* BinarySearchNode<T>::getLeftmostNode() {
	// If left node is nullptr, return nullptr
	if (leftNode == nullptr)
		return nullptr;
		
	// Traverse tree until leftmost node is reached
	BinarySearchNode<T>* currentNode = leftNode;
	while (currentNode->leftNode != nullptr)
		currentNode = currentNode->leftNode;

	// Return currentNode (leftmost node)
	return currentNode;
}
template <typename T> BinarySearchNode<T>* BinarySearchNode<T>::getRightmostNode() {
	// If right node is nullptr, return nullptr
	if (rightNode == nullptr)
		return nullptr;

	// Traverse tree until rightmost node is reached
	BinarySearchNode<T>* currentNode = rightNode;
	while (currentNode->rightNode != nullptr)
		currentNode = currentNode->rightNode;

	// Return currentNode (rightmost node)
	return currentNode;
}
template <typename T> BinarySearchNode<T>* BinarySearchNode<T>::add(T data) {
	// If this node has a parent node, retrun nullptr (Reason: it would corrupt the tree otherwise)
	if (parentNode != nullptr)
		return nullptr;

	// Traverse tree and add node to corresponding position
	BinarySearchNode<T>* currentNode = this;
	while (currentNode != nullptr) {
		// If data is less than current node's data, add or traverse to left node
		if (data < currentNode->data) {
			// If left node is nullptr, add data to the tree as a node
			if (currentNode->leftNode == nullptr) {
				BinarySearchNode<T>* newNode = new BinarySearchNode<T>(data);
				newNode->binarySearchTree = binarySearchTree;
				newNode->parentNode = currentNode;
				currentNode->leftNode = newNode;
				return newNode;
			}

			// Traverse to the left node
			currentNode = currentNode->leftNode;
			continue;
		}
		// If data is greater than current node's data, add or traverse to right node
		else {
			// If right node is nullptr, add data to the tree as node
			if (currentNode->rightNode == nullptr) {
				BinarySearchNode<T>* newNode = new BinarySearchNode<T>(data);
				newNode->binarySearchTree = binarySearchTree;
				newNode->parentNode = this;
				currentNode->rightNode = newNode;
				return newNode;
			}

			// Traverse to the right node
			currentNode = currentNode->rightNode;
			continue;
		}

		// Set currentNode to nullptr to trigger loop break
		currentNode = nullptr;
	}

	// Return fail
	return nullptr;
}
template <typename T> BinarySearchNode<T>* BinarySearchNode<T>::get(T data) {
	// If there are no nodes to search for, return nullptr
	if (leftNode == nullptr && rightNode == nullptr)
		return nullptr;

	// Traverse tree in search of node that was data equal to data provided
	BinarySearchNode<T>* currentNode = this;
	while (currentNode != nullptr) {
		// If current node's data is equal to data provided, return current node
		if (currentNode->data == data)
			return currentNode;

		// Traverse left if less than
		if (data < currentNode->data) {
			currentNode = currentNode->leftNode;
			continue;
		}
		// Traverse right if greater than
		else {
			currentNode = currentNode->rightNode;
			continue;
		}

		// Set currentNode to nullptr to trigger loop break
		currentNode = nullptr;
	}

	// Return fail
	return nullptr;
}
template <typename T> bool BinarySearchNode<T>::has(T data) {
	BinarySearchNode<T>* searchResult = get(data);
	if (searchResult == nullptr)
		return false;
	return true;
}
template <typename T> bool BinarySearchNode<T>::remove(T data) {
	BinarySearchNode<T>* nodeToDelete = get(data);
	if (nodeToDelete == nullptr)
		return false;
	delete(nodeToDelete);
	return true;
}
template <typename T> void BinarySearchNode<T>::destroy() {
	delete(this);
}

// class BinarySearchTree

// Object | public

// Constructor / Destructor
template <typename T> BinarySearchTree<T>::BinarySearchTree() : size(0ULL), rootNode(nullptr) {

}
template <typename T> BinarySearchTree<T>::~BinarySearchTree() {
	clear();
}

// Getters
template <typename T> unsigned long long BinarySearchTree<T>::getSize() const {
	return size;
}
template <typename T> BinarySearchNode<T>* BinarySearchTree<T>::getRootNode() const {
	return rootNode;
}

// Functions
template <typename T> BinarySearchNode<T>* BinarySearchTree<T>::add(T data) {
	if (size == 0ULL) {
		rootNode = new BinarySearchNode<T>(data);
		rootNode->binarySearchTree = this;
		size++;
		return rootNode;
	}

	BinarySearchNode<T>* newNode = rootNode->add(data);
	if (newNode == nullptr)
		return nullptr;
	size++;
	return newNode;
}
template <typename T> BinarySearchNode<T>* BinarySearchTree<T>::get(T data) const {
	return rootNode->get(data);
}
template <typename T> bool BinarySearchTree<T>::has(T data) const {
	return rootNode->has(data);
}
template <typename T> void BinarySearchTree<T>::clear() {
	while (size > 0ULL)
		delete(rootNode);
}
