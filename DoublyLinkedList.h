#pragma once

// Dependencies | std
#include <iterator>

// Forward declarations | Utility
template <typename T> class DoublyLinkedNode;
template <typename T> class DoublyLinkedList;
template <typename T> class DoublyLinkedNodeIterator;

// class DoublyLinkedNode
template <typename T> class DoublyLinkedNode {
	// Friends
	friend class DoublyLinkedList<T>;
	friend class DoublyLinkedNodeIterator<T>;
	// Object
	private:
		// Properties
		DoublyLinkedList<T>* doublyLinkedList;
		DoublyLinkedNode<T>* leftNode;
		DoublyLinkedNode<T>* rightNode;
	public:
		// Properties
		T data;

		// Constructors / Destructor
		DoublyLinkedNode();
		DoublyLinkedNode(T data);
		DoublyLinkedNode(const DoublyLinkedNode<T>& doublyLinkedNode);
		void operator = (const DoublyLinkedNode<T>& doublyLinkedNode);
		~DoublyLinkedNode();

		// Getters
		DoublyLinkedList<T>* getDoublyLinkedList() const;
		DoublyLinkedNode<T>* getLeftNode() const;
		DoublyLinkedNode<T>* getRightNode() const;

		// Setters
		DoublyLinkedNode<T>* setRightNode(T data);
		DoublyLinkedNode<T>* setLeftNode(T data);

		void destroy();
};

// class DoublyLinkedList
template <typename T> class DoublyLinkedList {
	// Friends
	friend class DoublyLinkedNode<T>;
	// Object
	private:
		// Properties
		unsigned long long size;
		DoublyLinkedNode<T>* leftmostNode;
		DoublyLinkedNode<T>* rightmostNode;
	public:
		// Constructors / Destructor
		DoublyLinkedList();                                                                // O(1)
		DoublyLinkedList(const DoublyLinkedList<T>& doublyLinkedList);                     // O(n)
		void operator = (const DoublyLinkedList<T>& doublyLinkedList);                     // O(n)
		~DoublyLinkedList();                                                               // O(n)

		// Getters
		unsigned long long getSize() const;                                                // O(1)
		DoublyLinkedNode<T>* getLeftmostNode() const;                                      // O(1)
		DoublyLinkedNode<T>* getRightmostNode() const;                                     // O(1)

		// Functions
		DoublyLinkedNode<T>* getNodeAt(unsigned long long i) const;                        // O(n)
		DoublyLinkedNode<T>* getNodeWithData(T data) const;                                // O(n)
		DoublyLinkedNode<T>* add(T data);                                                  // O(1)
		DoublyLinkedNode<T>* addLeftmostNode(T data);                                      // O(1)
		DoublyLinkedNode<T>* addRightmostNode(T data);                                     // O(1)
		DoublyLinkedNode<T>* addAt(unsigned long long i, T data);                          // O(n)

		bool remove(T data);                                                               // O(n)
		bool removeAt(unsigned long long i);                                               // O(n)
		bool removeLeftmostNode();                                                         // O(1)
		bool removeRightmostNode();                                                        // O(1)
		bool has(T data) const;                                                            // O(n)
		void clear();                                                                      // O(n)

		// Container functions
		DoublyLinkedNodeIterator<T> begin();
		DoublyLinkedNodeIterator<T> end();
};

// DoublyLinkedNodeIterator
template <typename T> class DoublyLinkedNodeIterator {
	private:
		// PropertiesS
		DoublyLinkedNode<T>* currentNode;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		// Constructor / Destructor
		DoublyLinkedNodeIterator(DoublyLinkedNode<T>* doublyLinkedNode);
		~DoublyLinkedNodeIterator();

		// Operators
		T& operator*() const;
		DoublyLinkedNodeIterator<T>& operator++();
		DoublyLinkedNodeIterator<T> operator++(int);
		DoublyLinkedNodeIterator<T>& operator--();
		DoublyLinkedNodeIterator<T> operator--(int);
		bool operator==(const DoublyLinkedNodeIterator<T>& other) const;
		bool operator!=(const DoublyLinkedNodeIterator<T>& other) const;
};

// class DoublyLinkedNode

// Object | public

// Constructor / Destructor
template <typename T> DoublyLinkedNode<T>::DoublyLinkedNode() : doublyLinkedList(nullptr), leftNode(nullptr), rightNode(nullptr) {

}
template <typename T> DoublyLinkedNode<T>::DoublyLinkedNode(T data) : doublyLinkedList(nullptr), leftNode(nullptr), rightNode(nullptr), data(data) {

}
template <typename T> DoublyLinkedNode<T>::DoublyLinkedNode(const DoublyLinkedNode<T>& doublyLinkedNode) : doublyLinkedList(nullptr), leftNode(nullptr), rightNode(nullptr), data(doublyLinkedNode->data) {

}
template <typename T> void DoublyLinkedNode<T>::operator = (const DoublyLinkedNode<T>& doublyLinkedNode) {
	data = doublyLinkedNode.data;
}
template <typename T> DoublyLinkedNode<T>::~DoublyLinkedNode() {
	// If node is not associated with list, return
	if (doublyLinkedList == nullptr || doublyLinkedList->size == 0ULL)
		return;

	// If this is the last node in the list, reset list
	if (doublyLinkedList->size == 1ULL) {
		doublyLinkedList->size = 0ULL;
		doublyLinkedList->leftmostNode = nullptr;
		doublyLinkedList->rightmostNode = nullptr;
		return;
	}

	// Save left and right node
	DoublyLinkedNode<T>* leftNode = this->leftNode;
	DoublyLinkedNode<T>* rightNode = this->rightNode;

	// Relink list
	if (leftNode != nullptr)
		leftNode->rightNode = rightNode;
	if (rightNode != nullptr)
		rightNode->leftNode = leftNode;

	// If node is tail or head node, update list
	if (this == doublyLinkedList->leftmostNode)
		doublyLinkedList->leftmostNode = rightNode;
	if (this == doublyLinkedList->rightmostNode)
		doublyLinkedList->rightmostNode = leftNode;

	// Update list's size
	if (doublyLinkedList != nullptr)
		doublyLinkedList->size--;
}

// Getters
template <typename T> DoublyLinkedList<T>* DoublyLinkedNode<T>::getDoublyLinkedList() const {
	return doublyLinkedList;
}
template <typename T> DoublyLinkedNode<T>* DoublyLinkedNode<T>::getLeftNode() const {
	return leftNode;
}
template <typename T> DoublyLinkedNode<T>* DoublyLinkedNode<T>::getRightNode() const {
	return rightNode;
}

// Functions
template <typename T> DoublyLinkedNode<T>* DoublyLinkedNode<T>::setRightNode(T data) {
	// Link new node to doubly linked node chain
	DoublyLinkedNode<T>* newNode = new DoublyLinkedNode<T>(data);
	newNode->doublyLinkedList = doublyLinkedList;
	newNode->leftNode = this;
	newNode->rightNode = rightNode;

	// Link old nodes to new node
	DoublyLinkedNode<T>* rightNode = this->rightNode;
	this->rightNode = newNode;
	if (rightNode != nullptr)
		rightNode->leftNode = newNode;

	// If this is head node
	if (doublyLinkedList != nullptr && this == doublyLinkedList->rightmostNode)
		doublyLinkedList->rightmostNode = newNode;

	// Return new node
	return newNode;
}
template <typename T> DoublyLinkedNode<T>* DoublyLinkedNode<T>::setLeftNode(T data) {
	// Link new node to doubly linked node chain
	DoublyLinkedNode<T>* newNode = new DoublyLinkedNode<T>(data);
	newNode->doublyLinkedList = doublyLinkedList;
	newNode->leftNode = leftNode;
	newNode->rightNode = this;

	// Link old nodes to new node
	DoublyLinkedNode<T>* leftNode = this->leftNode;
	this->leftNode = newNode;
	if (leftNode != nullptr)
		leftNode->rightNode = leftNode;

	// If this is tail node
	if (doublyLinkedList != nullptr && this == doublyLinkedList->rightmostNode)
		doublyLinkedList->tailNode = newNode;

	// Return new node
	return newNode;
}

template <typename T> void DoublyLinkedNode<T>::destroy() {
	delete(this);
}

// class DoublyLinkedList

// Object | public

// Constructors / Destructor
template <typename T> DoublyLinkedList<T>::DoublyLinkedList() : size(0ULL), leftmostNode(nullptr), rightmostNode(nullptr) {

}
template <typename T> DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& doublyLinkedList) : DoublyLinkedList() {
	DoublyLinkedNode<T>* currentNode = doublyLinkedList.leftmostNode;
	if (currentNode == nullptr)
		return;

	// Deep copy
	for (T data : doublyLinkedList)
		addRightmostNode(data);
}
template <typename T> void DoublyLinkedList<T>::operator = (const DoublyLinkedList<T>& doublyLinkedList) {
	clear();

	DoublyLinkedNode<T>* currentNode = doublyLinkedList.leftmostNode;
	if (currentNode == nullptr)
		return;

	// Deep copy
	for (T data : doublyLinkedList)
		addRightmostNode(data);
}
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() {
	clear();
}

// Getters
template <typename T> unsigned long long DoublyLinkedList<T>::getSize() const {
	return size;
}

template <typename T> DoublyLinkedNode<T>* DoublyLinkedList<T>::getLeftmostNode() const {
	return leftmostNode;
}

template <typename T> DoublyLinkedNode<T>* DoublyLinkedList<T>::getRightmostNode() const {
	return rightmostNode;
}

// Functions
template <typename T> DoublyLinkedNode<T>* DoublyLinkedList<T>::getNodeAt(unsigned long long i) const {
	// If list is ampty, return nullptr
	if (i >= size)
		return nullptr;

	// Search for nod at index i
	DoublyLinkedNode<T>* currentNode = leftmostNode;
	for (unsigned long long j = 0ULL; j < i; j++)
		currentNode = currentNode->rightNode;

	// Return node
	return currentNode;	
}

template <typename T> DoublyLinkedNode<T>* DoublyLinkedList<T>::getNodeWithData(T data) const {
	// If list is empty, return nullptr
	if (size == 0ULL)
		return nullptr;

	// Search for node with data provided
	DoublyLinkedNode<T>* currentNode = leftmostNode;
	while (currentNode != nullptr) {
		// If nodes's data is equal to data provided, return current node
		if (currentNode->data == data)
			return currentNode;

		currentNode = currentNode->rightNode;
	}

	// Did not find node with data provided. Return nullptr
	return nullptr;
}
template <typename T> DoublyLinkedNode<T>* DoublyLinkedList<T>::add(T data) {
	return addRightmostNode(data);
}
template <typename T> DoublyLinkedNode<T>* DoublyLinkedList<T>::addLeftmostNode(T data) {
	if (size == 0ULL) {
		DoublyLinkedNode<T>* newNode = new DoublyLinkedNode<T>(data);
		newNode->doublyLinkedList = this;
		leftmostNode = newNode;
		rightmostNode = newNode;
		size++;
		return newNode;
	}
	return leftmostNode->setLeftNode(data);
}
template <typename T> DoublyLinkedNode<T>* DoublyLinkedList<T>::addRightmostNode(T data) {
	if (size == 0ULL) {
		DoublyLinkedNode<T>* newNode = new DoublyLinkedNode<T>(data);
		newNode->doublyLinkedList = this;
		leftmostNode = newNode;
		rightmostNode = newNode;
		size++;
		return newNode;
	}
	return rightmostNode->setRightNode(data);
}
template <typename T> DoublyLinkedNode<T>* DoublyLinkedList<T>::addAt(unsigned long long i, T data) {
	// Error check
	if (i > size)
		return nullptr;

	// If list is empty, add to list as leftmost and rightmost node
	if (i == 0ULL)
		return new DoublyLinkedNode<T>(this, data);

	// If index is equal to the size, add ass rightmost node
	if (i == size)
		return addRightmostNode(data);

	// Travers list until i node is reached
	DoublyLinkedNode<T>* currentNode = leftmostNode;
	for (unsigned long long j = 0ULL; j < i; j++)
		currentNode = currentNode->rightNode;

	// Add node to list
	DoublyLinkedNode<T>* newNode = currentNode->setLeftNode(data);
	size++;
	
	// Return new node
	return newNode;
}

template <typename T> bool DoublyLinkedList<T>::remove(T data) {
	//  If list is empty, return false
	if (size == 0ULL)
		return false;

	// If leftmost node has data provided, remove leftmost node and return success
	if (leftmostNode->data == data) {
		removeLeftmostNode();
		return true;
	}

	// If rightmost node has data provided, remove rightmost node and return success
	if (rightmostNode->data == data) {
		removeRightmostNode();
		return;
	}

	// Search for node with data provided
	DoublyLinkedNode<T>* currentNode = leftmostNode;
	while (currentNode != nullptr) {
		// If current node has data provided, delete it and return success
		if (currentNode->data == data) {
			delete(currentNode);
			return true;
		}

		currentNode = currentNode->rightNode;
	}

	// Return fail
	return false;
}
template <typename T> bool DoublyLinkedList<T>::removeAt(unsigned long long i) {
	// If list is empty, return fail
	if (size == 0ULL)
		return false;
	
	// Search for node at index == i and delete / remove it
	DoublyLinkedNode<T>* currentNode = leftmostNode;
	for (unsigned long long j = 0ULL; j < i; j++)
		currentNode = currentNode->rightNode;
	delete(currentNode);

	// Return success
	return true;
}
template <typename T> bool DoublyLinkedList<T>::removeLeftmostNode() {
	// If list is empty, return fail
	if (size == 0ULL)
		return false;
	
	// Delete / remove head node
	if (leftmostNode != nullptr)
		delete(leftmostNode);

	// Return success
	return true;
}
template <typename T> bool DoublyLinkedList<T>::removeRightmostNode() {
	// If list is empty, return fail
	if (size == 0ULL)
		return;
	
	// Delete / remove tail node
	if (rightmostNode != nullptr)
		delete(rightmostNode);

	// Return success
	return true;
}
template <typename T> bool DoublyLinkedList<T>::has(T data) const {
	// If list is empty, return false
	if (size == 0ULL)
		return false;

	// Search for node that was data provided
	DoublyLinkedNode<T>* currentNode = leftmostNode;
	while (currentNode != nullptr) {
		// If node has data provided, return current true
		if (currentNode->data == data)
			return true;

		currentNode = currentNode->rightNode;
	}

	// Did not find node
	return false;
}
template <typename T> void DoublyLinkedList<T>::clear() {
	// Delete each node from leftmost to rightmost
	DoublyLinkedNode<T>* currentNode = leftmostNode;
	while (currentNode != nullptr) {
		DoublyLinkedNode<T>* nextNode = currentNode->rightNode;
		delete(currentNode);
		currentNode = nextNode;
	}
}

// Container functions
template <typename T> DoublyLinkedNodeIterator<T> DoublyLinkedList<T>::begin() {
	return DoublyLinkedNodeIterator<T>(leftmostNode);
}
template<typename T> DoublyLinkedNodeIterator<T> DoublyLinkedList<T>::end() {
	return DoublyLinkedNodeIterator<T>(nullptr);
}

// class DoublyLinkedNodeIterator

// Object | public

// Constructor / Destructor
template <typename T> DoublyLinkedNodeIterator<T>::DoublyLinkedNodeIterator(DoublyLinkedNode<T>* doublyLinkedNode) : currentNode(doublyLinkedNode) {

}
template <typename T> DoublyLinkedNodeIterator<T>::~DoublyLinkedNodeIterator() {

}

// Operator overload
template <typename T> T& DoublyLinkedNodeIterator<T>::operator*() const {
	return currentNode->data;
}
template <typename T> DoublyLinkedNodeIterator<T>& DoublyLinkedNodeIterator<T>::operator++() {
	currentNode = currentNode->rightNode;
	return *this;
}
template <typename T> DoublyLinkedNodeIterator<T> DoublyLinkedNodeIterator<T>::operator++(int) {
	DoublyLinkedNodeIterator temp = *this;
	++(*this);
	return temp;
}
template <typename T> DoublyLinkedNodeIterator<T>& DoublyLinkedNodeIterator<T>::operator--() {
	currentNode = currentNode->leftNode;
	return *this;
}
template <typename T> DoublyLinkedNodeIterator<T> DoublyLinkedNodeIterator<T>::operator--(int) {
	DoublyLinkedNodeIterator tmp = *this;
	--(*this);
	return tmp;
}
template <typename T> bool DoublyLinkedNodeIterator<T>::operator==(const DoublyLinkedNodeIterator<T>& other) const {
	return currentNode == other.currentNode;
}
template <typename T> bool DoublyLinkedNodeIterator<T>::operator!=(const DoublyLinkedNodeIterator<T>& other) const {
	return !(*this == other);
}
