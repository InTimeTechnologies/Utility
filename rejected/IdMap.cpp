#include "IdMap.h"

// class IdNode

// Object | public

// Constructor / Destructor
IdNode::IdNode() {

}
IdNode::~IdNode() {
	
}

// Functions
IdNode* IdNode::getRoot() const {
	if (m_up == nullptr)
		return nullptr;

	IdNode* currentNode = m_up;
	while (currentNode != nullptr)
		currentNode = currentNode->m_up;

	return currentNode;
}
IdNode* IdNode::getLeftmostNode() const {
	if (m_left == nullptr)
		return nullptr;

	IdNode* currentNode = m_left;
	while (currentNode->m_left != nullptr)
		currentNode = currentNode->m_left;

	return currentNode;
}
IdNode* IdNode::getRightmostNode() const {
	if (m_right == nullptr)
		return nullptr;

	IdNode* currentNode = m_right;
	while (currentNode->m_right != nullptr)
		currentNode = currentNode->m_right;

	return currentNode;
}

// class UUIDMap

// Object | public

// Constructor / Destructor
IdMap::IdMap() {

}
IdMap::~IdMap() {
	clear();
}

// Getters
IdNode* IdMap::rootNode() const {
	return m_rootNode;
}
int IdMap::size() const {
	return m_size;
}

// Functions
bool IdMap::addId(int id) {
	// If tree is empty, add id as the root node
	if (m_rootNode == nullptr) {
		IdNode* newNode = new IdNode;
		newNode->m_idRange = std::pair<int, int>(id, id);
		newNode->owner = this;

		m_rootNode = newNode;
		m_size = 1;

		// Return success
		return true;
	}

	// Add id to the tree (merge with current node or add it as a new node)
	IdNode* currentNode = m_rootNode;
	while (currentNode != nullptr) {
		// If newNode's id range overlaps with current node's id range, return fail
		if (id >= currentNode->m_idRange.first && id <= currentNode->m_idRange.second)
			return false;

		// Check if id can extend current node's id range to the left direction
		if (id == currentNode->m_idRange.first - 1) {
			// Extend current node's id range
			currentNode->m_idRange.first = id;

			// Get left node. It will be used a lot
			IdNode* leftNode = currentNode->m_left;
			
			// Check if current node can merge with left node
			if (currentNode->m_left != nullptr) {
				if (currentNode->m_idRange.first == leftNode->m_idRange.second) {
					currentNode->m_idRange.first = leftNode->m_idRange.first;
					currentNode->m_left = leftNode->m_left;
					leftNode->m_up = currentNode;
					delete(leftNode);
					m_size--;
				}
			}

			// Check if current node can merge with left's rightmost node
			IdNode* leftRightmostNode = leftNode->getRightmostNode();
			if (currentNode->m_idRange.first == leftRightmostNode->m_idRange.second - 1) {
				currentNode->m_idRange.first = leftRightmostNode->m_idRange.first;
				leftRightmostNode->m_up->m_right = nullptr;
				delete(leftRightmostNode);
				m_size--;
			}

			// Return current node
			return true;
		}

		// Check if id can extend current node's id range to the right direction
		else if (id == currentNode->m_idRange.second + 1) {
			// Extend current node's id range
			currentNode->m_idRange.second = id;

			// Get right node. It will be used a lot
			IdNode* rightNode = currentNode->m_right;

			// Check if currentNode can merge with right node
			if (currentNode->m_right != nullptr) {
				if (currentNode->m_idRange.second == rightNode->m_idRange.first) {
					currentNode->m_idRange.second = rightNode->m_idRange.second;
					currentNode->m_right = rightNode->m_right;
					rightNode->m_up = currentNode;
					delete(rightNode);
					m_size--;
				}
			}

			// Check if current node can merge with rights's leftmost node
			IdNode* rightLeftmostNode = rightNode->getLeftmostNode();
			if (rightLeftmostNode != nullptr && currentNode->m_idRange.second == rightLeftmostNode->m_idRange.first - 1) {
				currentNode->m_idRange.second = rightLeftmostNode->m_idRange.second;
				rightLeftmostNode->m_up->m_left = nullptr;
				delete(rightLeftmostNode);
				m_size--;
			}

			// Return success
			return true;
		}

		// If data is less than current node's data, add the id to the tree or traverse to left node
		if (id < currentNode->m_idRange.first) {
			// If left node is nullptr, add id to the tree
			if (currentNode->m_left == nullptr) {
				IdNode* newNode = new IdNode;
				newNode->m_idRange = std::pair(id, id);
				newNode->owner = this;
				newNode->m_up = currentNode;
				currentNode->m_left = newNode;
				m_size++;
				break;
			}

			// Traverse to left node
			currentNode = currentNode->m_left;
			continue;
		}

		// If data is greater than current node's data, add id to the tree or traverse to right node
		else if (id > currentNode->m_idRange.second) {
			// If right node is nullptr, add id to the tree
			if (currentNode->m_right == nullptr) {
				IdNode* newNode = new IdNode;
				newNode->m_idRange = std::pair<int, int>(id, id);
				newNode->owner = this;
				newNode->m_up = currentNode;
				currentNode->m_right = newNode;
				m_size++;
				break;
			}

			// Traverse to right node
			currentNode = currentNode->m_right;
			continue;
		}
	}

	// Return fail
	return false;
}
bool IdMap::addId(std::pair<int, int> idRange) {
	if (idRange.first > idRange.second) {
		int temp = idRange.first;
		idRange.first = idRange.second;
		idRange.second = temp;
	}

	// If tree is empty, add id as the root node
	if (m_rootNode == nullptr) {
		IdNode* newNode = new IdNode;
		newNode->owner = this;
		newNode->m_idRange = idRange;

		m_rootNode = newNode;
		m_size = 1;

		// Return success
		return true;
	}

	// Add id to the tree (merge with current node or add it as a new node)
	IdNode* currentNode = m_rootNode;
	while (currentNode != nullptr) {
		// If newNode's id range overlaps with current node's id range, return fail
		if (idRange.first >= currentNode->m_idRange.first && idRange.second <= currentNode->m_idRange.second)
			return false;

		// Check if uuidRange can extend current node's id range to the left direction
		if (idRange.second == currentNode->m_idRange.first - 1) {
			// Extend current node's id range
			currentNode->m_idRange.first = idRange.first;

			// Check if current node can merge with left node
			if (currentNode->m_left != nullptr) {
				// Get left node for heavy use
				IdNode* leftNode = currentNode->m_left;

				// Check if current node can merge with left's rightmost node
				IdNode* leftRightmostNode = leftNode->getRightmostNode();
				if (leftRightmostNode != nullptr && currentNode->m_idRange.first == leftRightmostNode->m_idRange.second - 1) {
					currentNode->m_idRange.first = leftRightmostNode->m_idRange.first;
					leftRightmostNode->m_up->m_right = nullptr;
					delete(leftRightmostNode);
					m_size--;
				}

				// Check if current node can merge with left node
				if (currentNode->m_idRange.first == leftNode->m_idRange.second) {
					currentNode->m_idRange.first = leftNode->m_idRange.first;
					currentNode->m_left = leftNode->m_left;
					leftNode->m_up = currentNode;
					delete(leftNode);
					m_size--;
				}
			}

			// Trigger success
			break;
		}

		// Check if id can extend current node's id range to the right direction
		else if (idRange.first == currentNode->m_idRange.second + 1) {
			// Extend current node's id range
			currentNode->m_idRange.second = idRange.second;

			// Check if currentNode can merge with right node
			if (currentNode->m_right != nullptr) {
				// Get right node. It will be used a lot
				IdNode* rightNode = currentNode->m_right;

				// Check if current node can merge with rights's leftmost node
				IdNode* rightLeftmostNode = rightNode->getLeftmostNode();
				if (rightLeftmostNode != nullptr && currentNode->m_idRange.second == rightLeftmostNode->m_idRange.first - 1) {
					currentNode->m_idRange.second = rightLeftmostNode->m_idRange.second;
					rightLeftmostNode->m_up->m_left = nullptr;
					delete(rightLeftmostNode);
					m_size--;
				}

				// Check if current node can merge with right node
				if (currentNode->m_idRange.second == rightNode->m_idRange.first) {
					currentNode->m_idRange.second = rightNode->m_idRange.second;
					currentNode->m_right = rightNode->m_right;
					rightNode->m_up = currentNode;
					delete(rightNode);
					m_size--;
				}
			}

			// Trigger success
			break;
		}

		// If uuidRange is less than current node's idRange, add the id to the tree or traverse to left node
		if (idRange.second < currentNode->m_idRange.first) {
			// If left node is nullptr, add id to the tree
			if (currentNode->m_left == nullptr) {
				IdNode* newNode = new IdNode;
				newNode->m_idRange = idRange;
				newNode->owner = this;
				newNode->m_up = currentNode;
				currentNode->m_left = newNode;
				m_size++;
				break;
			}

			// Traverse to left node
			currentNode = currentNode->m_left;
			continue;
		}

		// If uuidRange is greater than current node's data, add id to the tree or traverse to right node
		else if (idRange.first > currentNode->m_idRange.second) {
			// If right node is nullptr, add id to the tree
			if (currentNode->m_right == nullptr) {
				IdNode* newNode = new IdNode;
				newNode->m_idRange = idRange;
				newNode->owner = this;
				newNode->m_up = currentNode;
				currentNode->m_right = newNode;
				m_size++;
				break;
			}

			// Traverse to right node
			currentNode = currentNode->m_right;
			continue;
		}
	}

	// Return success
	return true;
}
bool IdMap::removeId(int id) {
	if (m_size == 0)
		return false;

	IdNode* currentNode = m_rootNode;
	while (currentNode != nullptr) {
		if (id >= currentNode->m_idRange.first && id <= currentNode->m_idRange.second) {
			// Local variables
			IdNode* leftNode = currentNode->m_left;
			IdNode* rightNode = currentNode->m_right;
			IdNode* upNode = currentNode->m_up;

			IdNode* leftHalf = nullptr;
			IdNode* rightHalf = nullptr;

			// If there is a left half leftover, create it
			if (currentNode->m_idRange.first < id) {
				leftHalf = new IdNode;
				leftHalf->m_idRange = std::pair<int, int>(currentNode->m_idRange.first, id - 1);
				leftHalf->owner = this;
				m_size++;
			}
			// If there is a right half leftover, create it
			if (currentNode->m_idRange.second > id) {
				rightHalf = new IdNode;
				rightHalf->m_idRange = std::pair<int, int>(id + 1, currentNode->m_idRange.second);
				rightHalf->owner = this;
				m_size++;
			}

			// If left half exists, link and rearrange tree accordingly: right half goes right, leftmost
			if (leftHalf != nullptr) {
				// Link left half to existing nodes
				leftHalf->m_up = upNode;
				leftHalf->m_left = leftNode;
				leftHalf->m_right = rightNode;

				// Link existing nodes to left half
				if (leftNode != nullptr)
					leftNode->m_up = leftHalf;
				if (rightNode != nullptr)
					rightNode->m_up = leftHalf;
				if (upNode != nullptr) {
					if (upNode->m_left == currentNode)
						upNode->m_left = leftHalf;
					else if (upNode->m_right == currentNode)
						upNode->m_right = leftHalf;
				}

				// Link right half to either right node or right node's leftmost node
				if (rightHalf != nullptr) {
					if (rightNode == nullptr) {
						leftHalf->m_right = rightHalf;
						rightHalf->m_up = leftHalf;
					}
					else {
						IdNode* rightLeftmostNode = rightNode->getLeftmostNode();

						if (rightLeftmostNode == nullptr) {
							rightNode->m_left = rightHalf;
							rightHalf->m_up = rightNode;
						}
						else {
							rightLeftmostNode->m_left = rightHalf;
							rightHalf->m_up = rightLeftmostNode;
						}
					}
				}
			}
			// If right half exists, rearrange tree accordingly: left half goes left, rightmost
			else if (rightHalf != nullptr) {
				// Link right half to existing nodes
				rightHalf->m_up = upNode;
				rightHalf->m_left = leftNode;
				rightHalf->m_right = rightNode;

				// Link existing nodes to right half
				if (leftNode != nullptr)
					leftNode->m_up = rightHalf;
				if (rightNode != nullptr)
					rightNode->m_up = rightHalf;
				if (upNode != nullptr) {
					if (upNode->m_left == currentNode)
						upNode->m_left = rightHalf;
					else if (upNode->m_right == currentNode)
						upNode->m_right = rightHalf;
				}

				// Link left half to either left node or left node's rightmost node
				if (leftHalf == nullptr) {
					if (leftNode == nullptr) {
						rightHalf->m_left = leftHalf;
						leftHalf->m_up = rightHalf;
					}
					else {
						IdNode* leftRightmostNode = leftNode->getRightmostNode();

						if (leftRightmostNode == nullptr) {
							leftNode->m_right = leftHalf;
							leftHalf->m_up = leftNode;
						}
						else {
							leftRightmostNode->m_right = leftHalf;
							leftHalf->m_up = leftRightmostNode;
						}
					}
				}
			}

			// Delete previously existing node
			delete(currentNode);
			m_size--;
			
			// Return success
			return true;
		}

		// If id is to the left, traverse left
		if (id < currentNode->m_idRange.first) {
			currentNode = currentNode->m_left;
		}

		// If id is to the right, traverse right
		else if (id > currentNode->m_idRange.second) {
			currentNode = currentNode->m_right;
		}
	}

	// Return fail
	return false;
}
bool IdMap::removeNode(IdNode* nodeToRemove) {
	if (nodeToRemove == nullptr || nodeToRemove->owner != this || m_size == 0)
		return false;

	if (m_size == 1) {
		delete(nodeToRemove);
		m_rootNode = nullptr;
		m_size = 0;
		return true;
	}

	IdNode* leftNode = nodeToRemove->m_left;
	IdNode* rightNode = nodeToRemove->m_right;
	IdNode* upNode = nodeToRemove->m_up;

	if (leftNode != nullptr) {
		// Link to up node
		leftNode->m_up = upNode;
		if (upNode != nullptr) {
			if (upNode->m_left == nodeToRemove)
				upNode->m_left = leftNode;
			else
				upNode->m_right = rightNode;
		}
		
		IdNode* leftRightmostNode = leftNode->getRightmostNode();
		if (leftRightmostNode == nullptr) {
			leftNode->m_right = rightNode;
			if (rightNode != nullptr)
				rightNode->m_up = leftNode;
		}
		else {
			leftRightmostNode->m_right = rightNode;
			if (rightNode != nullptr)
				rightNode->m_up = leftRightmostNode;
		}

		// If node to remove is root node, update it
		if (nodeToRemove == m_rootNode)
			m_rootNode = leftNode;

		delete(nodeToRemove);
		m_size--;
	}
	else if (rightNode != nullptr) {
		// Link to up node
		rightNode->m_up = nodeToRemove->m_up;
		if (upNode != nullptr) {
			if (upNode->m_left == nodeToRemove)
				upNode->m_left = leftNode;
			else
				upNode->m_right = rightNode;
		}

		IdNode* rightLeftmostNode = rightNode->getLeftmostNode();
		if (rightLeftmostNode == nullptr) {
			rightNode->m_left = leftNode;
			if (leftNode != nullptr)
				leftNode->m_up = rightNode;
		}
		else {
			rightLeftmostNode->m_left = leftNode;
			if (leftNode != nullptr)
				leftNode->m_up = rightLeftmostNode;
		}

		// If node to remove is root node, update it
		if (nodeToRemove != nullptr)
			m_rootNode = rightNode;

		delete(nodeToRemove);
		m_size--;
	}
	else {
		if (upNode != nullptr) {
			if (upNode->m_left == nodeToRemove)
				upNode->m_left = nullptr;
			else
				upNode->m_right = nullptr;
		}
		
		delete(nodeToRemove);
		m_size--;
	}

	// Return success
	return true;
}
int IdMap::extractLeast() {
	if (m_size == 0)
		return -1;

	IdNode* nodeToEdit = m_rootNode->getLeftmostNode();
	if (nodeToEdit == nullptr)
		nodeToEdit = m_rootNode;

	int idToReturn = nodeToEdit->m_idRange.first;
	
	if (nodeToEdit->m_idRange.second - nodeToEdit->m_idRange.first == 0)
		removeNode(nodeToEdit);
	else
		nodeToEdit->m_idRange.first++;

	return idToReturn;
}
int IdMap::extractGreatest() {
	if (m_size == 0)
		return -1;

	IdNode* nodeToEdit = m_rootNode->getRightmostNode();
	if (nodeToEdit == nullptr)
		nodeToEdit = m_rootNode;

	int idToReturn = nodeToEdit->m_idRange.second;

	if (nodeToEdit->m_idRange.second = nodeToEdit->m_idRange.first == 0)
		removeNode(nodeToEdit);
	else
		nodeToEdit->m_idRange.second--;

	return true;
}
void IdMap::clear() {
	if (m_size == 0)
		return;
	
	if (m_size == 1) {
		delete(m_rootNode);
		m_rootNode = nullptr;
		m_size = 0;
		return;
	}

	IdNode* currentNode = m_rootNode;
	while (m_size > 0) {
		IdNode* leftmostNode = currentNode->getLeftmostNode();
		if (leftmostNode != nullptr) {
			currentNode = leftmostNode;
			continue;
		}
		else {
			IdNode* rightmostNode = currentNode->getRightmostNode();
			if (rightmostNode != nullptr) {
				currentNode = rightmostNode;
				continue;
			}
		}

		IdNode* upNode = currentNode->m_up;

		if (upNode != nullptr) {
			if (upNode->m_left == currentNode)
				upNode->m_left = nullptr;
			else if (upNode->m_right == currentNode)
				upNode->m_right = nullptr;
		}

		delete(currentNode);
		m_size--;
		currentNode = upNode;
	}
}
IdNode* IdMap::getNode(int id) const {
	if (m_size == 0)
		return nullptr;

	IdNode* currentNode = m_rootNode;
	while (currentNode != nullptr) {
		if (id >= currentNode->m_idRange.first && id <= currentNode->m_idRange.second)
			return currentNode;

		if (id < currentNode->m_idRange.first)
			currentNode = currentNode->m_left;
		else if (id > currentNode->m_idRange.second)
			currentNode = currentNode->m_right;
		else
			currentNode = nullptr;
	}

	return nullptr;
}
bool IdMap::has(int id) const {
	if (getNode(id) == nullptr)
		return false;
	else
		return true;
}
