#pragma once

// Dependencies | std
#include <utility>

// Forwward declarations | Utility
template <typename T> class BinaryRangeNode;
template <typename T> class BinaryRangeTree;

// class BinaryRangeDirection
enum class BinaryRangeDirection {
	LEFT,
	RIGHT
};

// class BinaryRangeNode
template <typename T> class BinaryRangeNode {
	// Friends
	friend class BinaryRangeTree<T>;

	// Static
	public:
		// Properties
		static BinaryRangeDirection nodeDirectionAscendsOnDeletion;

	// Object
	private:
		// Properties
		BinaryRangeTree<T>* binaryRangeTree;
		BinaryRangeNode<T>* parentNode;
		BinaryRangeNode<T>* leftNode;
		BinaryRangeNode<T>* rightNode;
		std::pair<T, T> data;
	public:
		// Constructor / Destructur
		BinaryRangeNode();
		BinaryRangeNode(std::pair<T, T> data);
		BinaryRangeNode(const BinaryRangeNode<T>& binaryRangeNode);
		void operator = (const BinaryRangeNode<T>& binaryRangeNode);
		~BinaryRangeNode();

		// Getters
		BinaryRangeTree<T>* getBinaryRangeTree() const;
		BinaryRangeNode<T>* getParentNode() const;
		BinaryRangeNode<T>* getLeftNode() const;
		BinaryRangeNode<T>* getRightNode() const;
		std::pair<T, T> getData() const;

		// Functions
		BinaryRangeNode<T>* getLeftmostNode();
		BinaryRangeNode<T>* getRightmostNode();
		BinaryRangeNode<T>* add(const std::pair<T, T>& data);
		BinaryRangeNode<T>* add(const T& data);
		BinaryRangeNode<T>* get(const std::pair<T, T>& data);
		bool has(const std::pair<T, T>& data);
		bool remove(const std::pair<T, T>& data);
		bool extract(const T& data);
		void destroy();
};

// class BinaryRangeTree
template <typename T> class BinaryRangeTree {
	// Friends
	friend class BinaryRangeNode<T>;

	// Object
	private:
		// Properties
		unsigned long long size;
		BinaryRangeNode<T>* rootNode;
	public:
		// Constructor / Destructor
		BinaryRangeTree();
		~BinaryRangeTree();

		// Getters
		unsigned long long getSize() const;
		BinaryRangeNode<T>* getRootNode() const;

		// Functions
		BinaryRangeNode<T>* add(const std::pair<T, T>& data);
		BinaryRangeNode<T>* add(const T& data);
		BinaryRangeNode<T>* get(const std::pair<T, T>& data) const;
		BinaryRangeNode<T>* get(const T& data) const;
		bool has(const std::pair<T, T>& data) const;
		bool remove(const std::pair<T, T>& data);
		bool extract(const T& data);
		void clear();
};

// class BinaryRangeNode

// Static | public

// Properties
template <typename T> BinaryRangeDirection BinaryRangeNode<T>::nodeDirectionAscendsOnDeletion = BinaryRangeDirection::LEFT;

// Object | public

// Constructor / Destructor
template <typename T> BinaryRangeNode<T>::BinaryRangeNode() : binaryRangeTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr) {

}
template <typename T> BinaryRangeNode<T>::BinaryRangeNode(std::pair<T, T> data) : binaryRangeTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(data) {

}
template <typename T> BinaryRangeNode<T>::BinaryRangeNode(const BinaryRangeNode<T>& binaryRangeNode) : parentNode(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(binaryRangeNode->data) {

}
template <typename T> void BinaryRangeNode<T>::operator = (const BinaryRangeNode<T>& binaryRangeNode) {
	data = binaryRangeNode->data;
}
template <typename T> BinaryRangeNode<T>::~BinaryRangeNode() {
	BinaryRangeNode<T>* ascendingNode = nullptr;
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
		BinaryRangeNode<T>* descendingNode = nullptr;
		if (nodeDirectionAscendsOnDeletion == BinaryRangeDirection::LEFT) {
			ascendingNode = leftNode;
			descendingNode = rightNode;
		}
		else {
			ascendingNode = rightNode;
			descendingNode = leftNode;
		}
		ascendingNode->parentNode = parentNode;

		// Link descendingNode to ascendingNode
		if (ascendingNode != nullptr && descendingNode != nullptr) {
			if (nodeDirectionAscendsOnDeletion == BinaryRangeDirection::LEFT) {
				BinaryRangeNode<T>* upperLinkingNode = ascendingNode->getRightmostNode();
				if (upperLinkingNode == nullptr)
					upperLinkingNode = ascendingNode;
				upperLinkingNode->rightNode = descendingNode;
			}
			else {
				BinaryRangeNode<T>* upperLinkingNode = ascendingNode->getLeftmostNode();
				if (upperLinkingNode == nullptr)
					upperLinkingNode = ascendingNode;
				upperLinkingNode->leftNode = descendingNode;
			}
			descendingNode->parentNode = ascendingNode;
		}
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

	// If this node belongs to a binary tree, decrease its size
	if (binaryRangeTree != nullptr) {
		binaryRangeTree->size--;
		if (binaryRangeTree->size == 0ULL)
			binaryRangeTree->rootNode = nullptr;
		else if (ascendingNode != nullptr && ascendingNode->parentNode == nullptr)
			binaryRangeTree->rootNode = ascendingNode;
	}
}

// Getters
template <typename T> BinaryRangeTree<T>* BinaryRangeNode<T>::getBinaryRangeTree() const {
	return binaryRangeTree;
}
template <typename T> BinaryRangeNode<T>* BinaryRangeNode<T>::getParentNode() const {
	return parentNode;
}
template <typename T> BinaryRangeNode<T>* BinaryRangeNode<T>::getLeftNode() const {
	return leftNode;
}
template <typename T> BinaryRangeNode<T>* BinaryRangeNode<T>::getRightNode() const {
	return rightNode;
}
template <typename T> std::pair<T, T> BinaryRangeNode<T>::getData() const {
	return data;
}

// Functions
template <typename T> BinaryRangeNode<T>* BinaryRangeNode<T>::getLeftmostNode() {
	// If left node is nullptr, return nullptr
	if (leftNode == nullptr)
		return nullptr;

	// Traverse tree until leftmost node is reached
	BinaryRangeNode<T>* currentNode = leftNode;
	while (currentNode->leftNode != nullptr)
		currentNode = currentNode->leftNode;

	// Return currentNode (leftmost node)
	return currentNode;
}
template <typename T> BinaryRangeNode<T>* BinaryRangeNode<T>::getRightmostNode() {
	// If right node is nullptr, return nullptr
	if (rightNode == nullptr)
		return nullptr;

	// Traverse tree until rightmost node is reached
	BinaryRangeNode<T>* currentNode = rightNode;
	while (currentNode->rightNode != nullptr)
		currentNode = currentNode->rightNode;

	// Return currentNode (rightmost node)
	return currentNode;
}
template <typename T> BinaryRangeNode<T>* BinaryRangeNode<T>::add(const std::pair<T, T>& data) {
	// Error check
	if (parentNode != nullptr)
		return nullptr;

	// If first is greater than second, swap them to keep data integrity in tree
	if (data.first > data.second)
		return nullptr;

	// Traverse tree and add node to corresponding position
	BinaryRangeNode<T>* currentNode = this;
	while (currentNode != nullptr) {
		// If data overlaps with current node's data, return nullptr to leep data integrity in tree
		if (data.first >= currentNode->data.first && data.second <= currentNode->data.second)
			return nullptr;

		// Check if data can extend current node's data to the left direction
		if (data.first == currentNode->data.first - T(1)) {
			// Extend current node's data
			currentNode->data.first = data.first;

			// If left node is not nullptr, check if current node can merge with left node, or left node's rightmost node
			if (currentNode->leftNode != nullptr) {
				// Check if current node can merge with left node
				if (leftNode->data.second + (T)1 == currentNode->data.first) {
					currentNode->data.first = leftNode->data.first;
					delete(leftNode);
					return currentNode;
				}
								
				// Check if current node can merge with left node's rightmost node
				BinaryRangeNode<T>* leftRightmostNode = currentNode->leftNode->getRightmostNode();
				if (leftRightmostNode != nullptr) {
					if ((data.second + (T)1) == leftRightmostNode->data.second) {
						currentNode->data.first = leftRightmostNode->data.first;
						delete(leftRightmostNode);
						return currentNode;
					}
				}
			}

			// Return current node
			return currentNode;
		}

		// Check if data can extend current node's data to the right direction
		else if (data.second == currentNode->data.second + (T)1) {
			// Extend current node's data
			currentNode->data.second = data.second;

			// If right node is not nullptr, check if current node can merge with right node, or right node's leftmost node
			if (currentNode->rightNode != nullptr) {
				// Check if current node can merge with right node
				if (rightNode->data.first + (T)1 == currentNode->data.second) {
					currentNode->data.second = rightNode->data.second;
					delete(rightNode);
					return currentNode;
				}

				// Check if current node can merge with left node's rightmost node
				BinaryRangeNode<T>* rightLeftmostNode = currentNode->rightNode->getLeftmostNode();
				if (rightLeftmostNode != nullptr) {
					currentNode->data.second = rightLeftmostNode->data.second;
					delete(rightLeftmostNode);
					return currentNode;
				}
			}

			// Return current node
			return currentNode;
		}

		// If data is less than current node's data, add or traverse to left node
		if (data.first < currentNode->data.first) {
			// If left node is nullptr, add data to the tree as a node
			if (currentNode->leftNode == nullptr) {
				BinaryRangeNode<T>* newNode = new BinaryRangeNode<T>(data);
				newNode->binaryRangeTree = binaryRangeTree;
				newNode->parentNode = currentNode;
				currentNode->leftNode = newNode;
				if (binaryRangeTree != nullptr)
					binaryRangeTree->size++;
				return newNode;
			}

			// Traverse to the left node
			currentNode = currentNode->leftNode;
			continue;
		}
		// If data is greater than current node's data, add or traverse to right node
		else if (data.second > currentNode->data.second) {
			// If right node is nullptr, add data to the tree as node
			if (currentNode->rightNode == nullptr) {
				BinaryRangeNode<T>* newNode = new BinaryRangeNode<T>(data);
				newNode->binaryRangeTree = binaryRangeTree;
				newNode->parentNode = this;
				currentNode->rightNode = newNode;
				if (binaryRangeTree != nullptr)
					binaryRangeTree->size++;
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
template <typename T> BinaryRangeNode<T>* BinaryRangeNode<T>::add(const T& data) {
	return add(std::pair<T, T>(data, data));
}
template <typename T> BinaryRangeNode<T>* BinaryRangeNode<T>::get(const std::pair<T, T>& data) {
	// If there are no nodes to search for, return nullptr
	if (leftNode == nullptr && rightNode == nullptr)
		return nullptr;

	// If first is greater than second, swap them to keep data integrity in tree
	if (data.first > data.second)
		return nullptr;

	// Traverse tree in search of node that was data equal to data provided
	BinaryRangeNode<T>* currentNode = this;
	while (currentNode != nullptr) {
		// If current node's data is equal to data provided, return current node
		if (currentNode->data == data)
			return currentNode;

		// Traverse left if less than
		if (data.first < currentNode->data.first) {
			currentNode = currentNode->leftNode;
			continue;
		}
		// Traverse right if greater than
		else if (data.second > currentNode->data.second) {
			currentNode = currentNode->rightNode;
			continue;
		}

		// Set currentNode to nullptr to trigger loop break
		currentNode = nullptr;
	}

	// Return fail
	return nullptr;
}
template <typename T> bool BinaryRangeNode<T>::has(const std::pair<T, T>& data) {
	BinaryRangeNode<T>* searchResult = get(data);
	if (searchResult == nullptr)
		return false;
	return true;
}
template <typename T> bool BinaryRangeNode<T>::remove(const std::pair<T, T>& data) {
	BinaryRangeNode<T>* nodeToDelete = get(data);
	if (nodeToDelete == nullptr)
		return false;
	delete(nodeToDelete);
	return true;
}
template <typename T> bool BinaryRangeNode<T>::extract(const T& data) {
	// Error check
	if (parentNode != nullptr)
		return false;

	// If first is greater than second, swap them to keep data integrity in tree
	if (data.first > data.second)
		return nullptr;

	BinaryRangeNode<T>* currentNode = this;
	while (currentNode != nullptr) {
		if (data == currentNode->data.first) {
			// Edit current node data. Delete node if overlap detected.
			currentNode->data.first++;
			if (currentNode->data.first > currentNode->data.second)
				delete(currentNode);
			return true;
		}
		if (data == currentNode->data.second) {
			// Edit current node data. Delete node if overlap detected.
			currentNode->data.second--;
			if (currentNode->data.second < currentNode->data.first)
				delete(currentNode);
			return true;
		}
		if (data > currentNode->data.first && data < currentNode->data.second) {
			// Split node into two nodes and organize tree
			BinaryRangeNode<T>* leftBranch = new BinaryRangeNode<T>(std::pair(currentNode->data.first, data - (T)1));
			leftBranch->binaryRangeTree = binaryRangeTree;
			BinaryRangeNode<T>* rightBranch = new BinaryRangeNode<T>(std::pair(data + (T)1, currentNode->data.second));
			rightBranch->binaryRangeTree = binaryRangeTree;

			if (nodeDirectionAscendsOnDeletion == BinaryRangeDirection::LEFT) {
				// Left branch does up, right branch goes down
				leftBranch->leftNode = currentNode->leftNode;
				leftBranch->rightNode = rightBranch;
				leftBranch->parentNode = currentNode->parentNode;

				rightBranch->rightNode = currentNode->rightNode;
				rightBranch->parentNode = leftBranch;

				if (currentNode->parentNode != nullptr)
					if (currentNode->parentNode->leftNode == currentNode)
						currentNode->parentNode->leftNode = leftBranch;
					else if (currentNode->parentNode->rightNode == currentNode)
						currentNode->parentNode->rightNode = leftBranch;

				// If current node == root node, update root node
				if (currentNode->binaryRangeTree != nullptr && currentNode->binaryRangeTree->rootNode == currentNode->binaryRangeTree->rootNode)
					currentNode->binaryRangeTree->rootNode = leftBranch;
			}
			else {
				// Right branch goes up, left branch goes down
				rightBranch->leftNode = leftBranch;
				rightBranch->rightNode = currentNode->rightNode;
				rightBranch->parentNode = currentNode->parentNode;

				leftBranch->leftNode = currentNode->leftNode;
				leftBranch->parentNode = rightBranch;

				if (currentNode->parentNode != nullptr)
					if (currentNode->parentNode->leftNode == currentNode)
						currentNode->parentNode->leftNode = leftBranch;
					else if (currentNode->parentNode->rightNode == currentNode)
						currentNode->parentNode->rightNode = leftBranch;

				// If current node == root node, update root node
				if (currentNode->binaryRangeTree != nullptr && currentNode->binaryRangeTree->rootNode == currentNode->binaryRangeTree->rootNode)
					currentNode->binaryRangeTree->rootNode = rightBranch;
			}

			// Increase size by one because of node split
			binaryRangeTree->size++;

			// Delete current node because it is now invalid
			currentNode->binaryRangeTree = nullptr;
			currentNode->binaryRangeTree = nullptr;
			currentNode->leftNode = nullptr;
			currentNode->rightNode = nullptr;
			delete(currentNode);

			return true;
		}

		// Try to move to left node
		if (data < currentNode->data.first && leftNode != nullptr) {
			currentNode = leftNode;
			continue;
		}

		// Try to move to right node
		if (data > currentNode->data.second && rightNode != nullptr) {
			currentNode = rightNode;
			continue;
		}

		// Could not find data to extract. Trigger loop termination.
		currentNode = nullptr;
	}

	return false;
}
template <typename T> void BinaryRangeNode<T>::destroy() {
	delete(this);
}

// class BinaryRangeTree

// Object | public

// Constructor / Destructor
template <typename T> BinaryRangeTree<T>::BinaryRangeTree() : size(0ULL), rootNode(nullptr) {

}
template <typename T> BinaryRangeTree<T>::~BinaryRangeTree() {
	clear();
}

// Getters
template <typename T> unsigned long long BinaryRangeTree<T>::getSize() const {
	return size;
}
template <typename T> BinaryRangeNode<T>* BinaryRangeTree<T>::getRootNode() const {
	return rootNode;
}

// Functions
template <typename T> BinaryRangeNode<T>* BinaryRangeTree<T>::add(const std::pair<T, T>& data) {
	if (size == 0ULL) {
		BinaryRangeNode<T>* newNode = new BinaryRangeNode<T>(data);
		newNode->binaryRangeTree = this;
		rootNode = newNode;
		size++;
		return newNode;
	}
	return rootNode->add(data);
}
template <typename T> BinaryRangeNode<T>* BinaryRangeTree<T>::add(const T& data) {
	if (size == 0) {
		BinaryRangeNode<T>* newNode = new BinaryRangeNode<T>(std::pair<T, T>(data, data));
		newNode->binaryRangeTree = this;
		rootNode = newNode;
		size++;
		return newNode;
	}
	return rootNode->add(data);
}
template <typename T> BinaryRangeNode<T>* BinaryRangeTree<T>::get(const std::pair<T, T>& data) const {
	if (size == 0ULL)
		return nullptr;
	return rootNode->get(data);
}
template <typename T> BinaryRangeNode<T>* BinaryRangeTree<T>::get(const T& data) const {
	if (size == 0ULL)
		return nullptr;
	return rootNode->get(data);
}
template <typename T> bool BinaryRangeTree<T>::has(const std::pair<T, T>& data) const {
	if (size == 0ULL)
		return false;
	return rootNode->has(data);
}
template <typename T> bool BinaryRangeTree<T>::remove(const std::pair<T, T>& data) {
	if (size == 0ULL)
		return false;
	return rootNode->remove(data);
}
template <typename T> bool BinaryRangeTree<T>::extract(const T& data) {
	if (size == 0ULL)
		return false;
	return rootNode->extract(data);
}
template <typename T> void BinaryRangeTree<T>::clear() {
	while (size > 0ULL)
		delete(rootNode);
}
