#include "RangeBST.h"

// class RangeBSTNode
// Object | public
// Constructor / Destructor
RangeBSTNode::RangeBSTNode(const Range<unsigned int>& data) : rangeBST(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(data) {

}
RangeBSTNode::~RangeBSTNode() {

}

// Functions
RangeBSTNode* RangeBSTNode::getLeastNode() {
	RangeBSTNode* currentNode = this;
	while (currentNode->leftNode != nullptr)
		currentNode = currentNode->leftNode;
	return currentNode;
}
RangeBSTNode* RangeBSTNode::getGreatestNode() {
	RangeBSTNode* currentNode = this;
	while (currentNode->rightNode != nullptr)
		currentNode = currentNode->rightNode;
	return currentNode;
}
RangeBSTNode* RangeBSTNode::getRootNode() {
	RangeBSTNode* currentNode = this;
	while (currentNode->parentNode != nullptr)
		currentNode = currentNode->parentNode;
	return currentNode;
}

// class RangeBST
// Object / public
// Constructor / Destructor
RangeBST::RangeBST() {
	rootNode = nullptr;
	size = 0;
}
RangeBST::~RangeBST() {
	clear();
}

// Getters
RangeBSTNode* RangeBST::getRootNode() const {
	return rootNode;
}
unsigned int RangeBST::getSize() const {
	return size;
}
RangeBSTNode* RangeBST::getNodeWithData(unsigned int data) const {
	RangeBSTNode* currentNode = rootNode;

	while (currentNode != nullptr) {
		if (currentNode->data.contains(data))
			return currentNode;

		if (data < currentNode->data.getLower())
			currentNode = currentNode->leftNode;
		else
			currentNode = currentNode->rightNode;
	}

	return nullptr;
}
RangeBSTNode* RangeBST::getNodeWithRange(const Range<unsigned int>& range) const {
	RangeBSTNode* currentNode = rootNode;

	while (currentNode != nullptr) {
		if (range.equals(currentNode->data))
			return currentNode;

		if (range.getUpper() < currentNode->data.getLower())
			currentNode = currentNode->leftNode;
		else
			currentNode = currentNode->rightNode;
	}

	return nullptr;
}
RangeBSTNode* RangeBST::getLeast() const {
	if (isEmpty())
		return nullptr;
	return rootNode->getLeastNode();
}
RangeBSTNode* RangeBST::getGreatest() const {
	if (isEmpty())
		return nullptr;
	return rootNode->getGreatestNode();
}

// Functions
RangeBSTNode* RangeBST::add(unsigned int data) {
	if (isEmpty()) {
		rootNode = new RangeBSTNode(Range<unsigned int>(data));
		rootNode->rangeBST = this;
		size = 1;
		return rootNode;
	}

	RangeBSTNode* currentNode = rootNode;
	while (currentNode != nullptr) {
		if (currentNode->data.contains(data))
			break;

		if (data < currentNode->data.getLower()) {
			if (currentNode->data.getLower() - data == 1) {
				currentNode->data.setLower(data);
				if (currentNode->leftNode != nullptr) {
					RangeBSTNode* lowerRangeNode = currentNode->leftNode->getGreatestNode();
					if (currentNode->data.getLower() - lowerRangeNode->data.getUpper()) {
						currentNode->data.setLower(lowerRangeNode->data.getLower());
						remove(lowerRangeNode);
					}
				}
				return currentNode;
			}

			if (currentNode->leftNode == nullptr) {
				RangeBSTNode* newNode = new RangeBSTNode(Range<unsigned int>(data));
				newNode->rangeBST = this;

				currentNode->leftNode = newNode;
				newNode->parentNode = currentNode;
				size++;

				return newNode;
			}

			currentNode = currentNode->leftNode;
		}
		else {
			if (data - currentNode->data.getUpper() == 1) {
				currentNode->data.setUpper(data);
				if (currentNode->rightNode != nullptr) {
					RangeBSTNode* upperRangeNode = currentNode->rightNode->getLeastNode();
					if (currentNode->data.getUpper() - upperRangeNode->data.getUpper()) {
						currentNode->data.setUpper(upperRangeNode->data.getUpper());
						remove(upperRangeNode);
					}
				}
				return currentNode;
			}

			if (currentNode->rightNode == nullptr) {
				RangeBSTNode* newNode = new RangeBSTNode(Range<unsigned int>(data));
				newNode->rangeBST = this;

				currentNode->rightNode = newNode;
				newNode->parentNode = currentNode;
				size++;
				return newNode;
			}

			currentNode = currentNode->rightNode;
		}
	}
}
RangeBSTNode* RangeBST::add(const Range<unsigned int>& range) {
	if (isEmpty()) {
		rootNode = new RangeBSTNode(range);
		rootNode->rangeBST = this;
		size = 1;
		return rootNode;
	}

	RangeBSTNode* currentNode = rootNode;
	while (currentNode != nullptr) {
		if (Range<unsigned int>::overlap(range, currentNode->data))
			break;

		if (range.getUpper() < currentNode->data.getLower()) {
			if (currentNode->data.getLower() - range.getUpper() == 1) {
				currentNode->data.setLower(range.getLower());
				if (currentNode->leftNode != nullptr) {
					RangeBSTNode* lowerRangeNode = currentNode->leftNode->getGreatestNode();
					if (currentNode->data.getLower() - lowerRangeNode->data.getUpper()) {
						currentNode->data.setLower(lowerRangeNode->data.getLower());
						remove(lowerRangeNode);
					}
				}
				return currentNode;
			}
			
			if (currentNode->leftNode == nullptr) {
				RangeBSTNode* newNode = new RangeBSTNode(range);
				newNode->rangeBST = this;

				currentNode->leftNode = newNode;
				newNode->parentNode = currentNode;
				size++;

				return newNode;
			}

			currentNode = currentNode->leftNode;
		}
		else {
			if (range.getLower() - currentNode->data.getUpper() == 1) {
				currentNode->data.setUpper(range.getUpper());
				if (currentNode->rightNode != nullptr) {
					RangeBSTNode* upperRangeNode = currentNode->rightNode->getLeastNode();
					if (currentNode->data.getUpper() - upperRangeNode->data.getUpper()) {
						currentNode->data.setUpper(upperRangeNode->data.getUpper());
						remove(upperRangeNode);
					}
				}
				return currentNode;
			}

			if (currentNode->rightNode == nullptr) {
				RangeBSTNode* newNode = new RangeBSTNode(range);
				newNode->rangeBST = this;

				currentNode->rightNode = newNode;
				newNode->parentNode = currentNode;
				size++;
				return newNode;
			}

			currentNode = currentNode->rightNode;
		}
	}

	return nullptr;
}

bool RangeBST::remove(unsigned int data) {
	RangeBSTNode* nodeToSplit = getNodeWithData(data);
	if (nodeToSplit == nullptr)
		return false;

	// Save neighboring nodes and parent node before deleting currentNode
	RangeBSTNode* parent = nodeToSplit->parentNode;
	RangeBSTNode* leftBranch = nodeToSplit->leftNode;
	RangeBSTNode* rightBranch = nodeToSplit->rightNode;

	// Unlink nodes pointing to currentNode address
	if (parent != nullptr)
		if (parent->leftNode == nodeToSplit)
			parent->leftNode = nullptr;
		else
			parent->rightNode = nullptr;
	if (leftBranch != nullptr)
		leftBranch->parentNode = nullptr;
	if (rightBranch != nullptr)
		rightBranch->parentNode = nullptr;
	if (nodeToSplit == rootNode)
		rootNode = nullptr;
	
	Range<unsigned int> leftRange = nodeToSplit->data;
	Range<unsigned int> rightRange = nodeToSplit->data;

	leftRange.moveUpper(data - 1);
	rightRange.moveLower(data + 1);

	// delete nodeToSplit (currentNode cotains data to remove)
	delete(nodeToSplit);
	size--;

	// Left half of split node, become part of left branch
	// Right hald of split node, become part of right branch
	if (leftRange.getUpper() < data) {
		RangeBSTNode* leftNode = new RangeBSTNode(leftRange);
		leftNode->rangeBST = this;
		size++;

		leftNode->leftNode = leftBranch;
		if (leftBranch != nullptr)
			leftBranch->parentNode = leftNode;
		leftBranch = leftNode;
	}
	if (rightRange.getLower() > data) {
		RangeBSTNode* rightNode = new RangeBSTNode(rightRange);
		rightNode->rangeBST = this;
		size++;

		rightNode->rightNode = rightBranch;
		if (rightBranch != nullptr)
			rightBranch->parentNode = rightNode;
		rightBranch = rightNode;
	}

	// Relink binary search tree while keeping binary search tree integrity
	if (leftBranch != nullptr) {
		if (parent == nullptr) {
			parent = leftBranch;
			rootNode = leftBranch;
		}
		else {
			leftBranch->parentNode = parent;
			if (leftBranch->data.getUpper() < parent->data.getLower())
				parent->leftNode = leftBranch;
			else
				parent->rightNode = leftBranch;
		}

		if (rightBranch != nullptr) {
			RangeBSTNode* leftBranchGreatestNode = leftBranch->getGreatestNode();
			leftBranchGreatestNode->rightNode = rightBranch;
			rightBranch->parentNode = leftBranchGreatestNode;
		}
	}
	else if (rightBranch != nullptr) {
		if (parent == nullptr) {
			parent = rightBranch;
			rootNode = rightBranch;
		}
		else {
			rightBranch->parentNode = parent;
			if (rightBranch->data.getLower() < parent->data.getUpper())
				parent->leftNode = rightBranch;
			else
				parent->rightNode = rightBranch;
		}
	}

	return true;
}
bool RangeBST::remove(const Range<unsigned int>& range) {
	return remove(getNodeWithRange(range));
}
bool RangeBST::remove(RangeBSTNode* node) {
	// abort if node is not in binary search tree
	if (!contains(node))
		return false;

	// remove root node if that is the target value to remove
	if (size == 1) {
		if (rootNode == node) {
			delete(rootNode);
			size = 0;
			return true;
		}
		else {
			return false;
		}
	}

	// Save neighboring nodes and parent node before deleting currentNode
	RangeBSTNode* parent = node->parentNode;
	RangeBSTNode* leftBranch = node->leftNode;
	RangeBSTNode* rightBranch = node->rightNode;

	// nullify properties / nodes pointing to currentNode address
	if (parent != nullptr)
		if (parent->leftNode == node)
			parent->leftNode = nullptr;
		else
			parent->rightNode = nullptr;
	if (leftBranch != nullptr)
		leftBranch->parentNode = nullptr;
	if (rightBranch != nullptr)
		rightBranch->parentNode = nullptr;
	if (node == rootNode)
		rootNode = nullptr;

	// delete currentNode (currentNode cotains data to remove)
	delete(node);
	size--;

	// Relink binary search tree while keeping binary search tree integrity
	if (leftBranch != nullptr) {
		if (parent == nullptr) {
			parent = leftBranch;
			rootNode = leftBranch;
		}
		else {
			leftBranch->parentNode = parent;
			if (leftBranch->data.getUpper() < parent->data.getLower())
				parent->leftNode = leftBranch;
			else
				parent->rightNode = leftBranch;
		}

		if (rightBranch != nullptr) {
			RangeBSTNode* leftBranchGreatestNode = leftBranch->getGreatestNode();
			leftBranchGreatestNode->rightNode = rightBranch;
			rightBranch->parentNode = leftBranchGreatestNode;
		}
	}
	else if (rightBranch != nullptr) {
		if (parent == nullptr) {
			parent = rightBranch;
			rootNode = rightBranch;
		}
		else {
			rightBranch->parentNode = parent;
			if (rightBranch->data.getLower() < parent->data.getUpper())
				parent->leftNode = rightBranch;
			else
				parent->rightNode = rightBranch;
		}
	}

	// Return true for success notification
	return true;
}

bool RangeBST::contains(unsigned int data) const {
	RangeBSTNode* currentNode = rootNode;

	while (currentNode != nullptr) {
		if (currentNode->data.contains(data))
			return true;

		if (data < currentNode->data.getLower())
			currentNode = currentNode->leftNode;
		else
			currentNode = currentNode->rightNode;
	}

	return false;
}
bool RangeBST::contains(const Range<unsigned int>& range) const {
	RangeBSTNode* currentNode = rootNode;

	while (currentNode != nullptr) {
		if (range.equals(currentNode->data))
			return true;

		if (range.getUpper() < currentNode->data.getLower())
			currentNode = currentNode->leftNode;
		else
			currentNode = currentNode->rightNode;
	}
}
bool RangeBST::contains(RangeBSTNode* node) const {
	if (node == nullptr)
		return false;

	if (node->rangeBST == this)
		return true;
	return false;
}

bool RangeBST::isEmpty() const {
	if (size == 0)
		return true;
	return false;
}

void RangeBST::clear() {
	RangeBSTNode* currentNode = rootNode;
	
	while (size > 0) {
		currentNode = currentNode->getGreatestNode();

		if (currentNode->leftNode != nullptr)
			currentNode = currentNode->leftNode;
		else {
			RangeBSTNode* parentNode = currentNode->parentNode;

			if (parentNode != nullptr)
				if (parentNode->leftNode == currentNode)
					parentNode->leftNode = nullptr;
				else
					parentNode->rightNode = nullptr;

			delete(currentNode);
			size--;

			currentNode = parentNode;
		}
	}

	rootNode = nullptr;
}
