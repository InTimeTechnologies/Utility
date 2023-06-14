#pragma once

// Forward declarations | Utility
template <class T> class DoublyLinkedNode;
template <class T> class DoublyLinkedList;

// class DoublyLinkedNode
template <class T> class DoublyLinkedNode {
	// Friends
	friend class DoublyLinkedList<T>;
	// Object
	private:
		// Properties
		DoublyLinkedList<T>* doublyLinkedList;
		DoublyLinkedNode<T>* previousNode;
		DoublyLinkedNode<T>* nextNode;
	public:
		// Properties
		T data;

		// Constructors / Destructor
		DoublyLinkedNode();
		DoublyLinkedNode(DoublyLinkedList<T>* doublyLinkedList);
		DoublyLinkedNode(T data);
		DoublyLinkedNode(DoublyLinkedList<T>* doublyLinkedList, T data);
		DoublyLinkedNode(const DoublyLinkedNode<T> &doublyLinkedNode);
		void operator = (const DoublyLinkedNode<T>& doublyLinkedNode);
		~DoublyLinkedNode();

		// Getters
		DoublyLinkedList<T>* getDoublyLinkedList();
		DoublyLinkedNode<T>* getPreviousNode();
		DoublyLinkedNode<T>* getNextNode();
};

// class DoublyLinkedList
template <class T> class DoublyLinkedList {
	// Friends
	friend class DoublyLinkedNode<T>;
	// Object
	private:
		// Properties
		unsigned int size;
		DoublyLinkedNode<T>* headNode;
		DoublyLinkedNode<T>* tailNode;

	public:
		// Constructors / Destructor
		DoublyLinkedList();                                                               // O(1)
		DoublyLinkedList(const DoublyLinkedList<T>& doublyLinkedList);                    // O(n)
		void operator = (const DoublyLinkedList<T>& doublyLinkedList);                    // O(n)
		~DoublyLinkedList();                                                              // O(n)

		// Getters
		unsigned int getSize();                                                           // O(1)
		DoublyLinkedNode<T>* getHeadNode();                                               // O(1)
		DoublyLinkedNode<T>* getTailNode();                                               // O(1)
		DoublyLinkedNode<T>* getNodeAt(unsigned int i);                                   // O(n)
		DoublyLinkedNode<T>* getNodeWithData(T data);                                     // O(n)

		// Functions
		DoublyLinkedNode<T>* add(T data);                                                 // O(1)
		DoublyLinkedNode<T>* addToHead(T data);                                           // O(1)
		DoublyLinkedNode<T>* addToTail(T data);                                           // O(1)
		DoublyLinkedNode<T>* addAt(unsigned int i, T data);                               // O(n)
		DoublyLinkedNode<T>* addPreviousOf(DoublyLinkedNode<T>* referenceNode, T data);   // O(1)
		DoublyLinkedNode<T>* addNextOf(DoublyLinkedNode<T>* referenceNode, T data);       // O(1)

		void remove(T data);                                                              // O(n)
		void removeAt(unsigned int i);                                                    // O(n)
		void removeHeadNode();                                                            // O(1)
		void removeTailNode();                                                            // O(1)

		bool has(T data);                                                                 // O(n)

		void clear();                                                                     // O(n)
};

// class DoublyLinkedNode

// Object | public

// Constructor / Destructor
template <class T> DoublyLinkedNode<T>::DoublyLinkedNode() : doublyLinkedList(nullptr), previousNode(nullptr), nextNode(nullptr) {

}
template <class T> DoublyLinkedNode<T>::DoublyLinkedNode(DoublyLinkedList<T>* doublyLinkedList) : doublyLinkedList(doublyLinkedList), previousNode(nullptr), nextNode(nullptr) {

}
template <class T> DoublyLinkedNode<T>::DoublyLinkedNode(T data) : doublyLinkedList(nullptr), previousNode(nullptr), nextNode(nullptr), data(data) {

}
template <class T> DoublyLinkedNode<T>::DoublyLinkedNode(DoublyLinkedList<T>* doublyLinkedList, T data) : doublyLinkedList(doublyLinkedList), previousNode(nullptr), nextNode(nullptr), data(data) {

}
template <class T> DoublyLinkedNode<T>::DoublyLinkedNode(const DoublyLinkedNode<T>& doublyLinkedNode) {
	doublyLinkedList = doublyLinkedNode.doublyLinkedList;
	previousNode = doublyLinkedNode.previousNode;
	nextNode = doublyLinkedNode.nextNode;
	data = doublyLinkedNode.data;
}
template <class T> void DoublyLinkedNode<T>::operator = (const DoublyLinkedNode<T>& doublyLinkedNode) {
	doublyLinkedList = doublyLinkedNode.doublyLinkedList;
	previousNode = doublyLinkedNode.previousNode;
	nextNode = doublyLinkedNode.nextNode;
	data = doublyLinkedNode.data;
}
template <class T> DoublyLinkedNode<T>::~DoublyLinkedNode() {
	// If node is not associated with list, return
	if (doublyLinkedList == nullptr)
		return;

	// If list is empty, return
	if (doublyLinkedList->getSize() == 0)
		return;

	// If there is only one node in the list, reset list
	if (doublyLinkedList->getSize() == 1) {
		doublyLinkedList->size = 0;
		doublyLinkedList->headNode = nullptr;
		doublyLinkedList->tailNode = nullptr;
		return;
	}

	// Save left and right node
	DoublyLinkedNode<T>* leftNode = previousNode;
	DoublyLinkedNode<T>* rightNode = nextNode;

	// Relink list
	if (leftNode != nullptr)
		leftNode->nextNode = rightNode;
	if (rightNode != nullptr)
		rightNode->previousNode = leftNode;

	// If node is tail or head node, update list
	if (this == doublyLinkedList->getHeadNode())
		doublyLinkedList->headNode = rightNode;
	if (this == doublyLinkedList->getTailNode())
		doublyLinkedList->tailNode = leftNode;

	// Update list's size
	doublyLinkedList->size--;
}

// Getters
template <class T> DoublyLinkedList<T>* DoublyLinkedNode<T>::getDoublyLinkedList() {
	return doublyLinkedList;
}
template <class T> DoublyLinkedNode<T>* DoublyLinkedNode<T>::getPreviousNode() {
	return previousNode;
}
template <class T> DoublyLinkedNode<T>* DoublyLinkedNode<T>::getNextNode() {
	return nextNode;
}

// class DoublyLinkedList

// Object | public

// Constructors / Destructor
template <class T> DoublyLinkedList<T>::DoublyLinkedList() : size(0), headNode(nullptr), tailNode(nullptr) {

}
template <class T> DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& doublyLinkedList) : DoublyLinkedList() {
	DoublyLinkedNode<T>* currentNode = doublyLinkedList.headNode;
	if (currentNode == nullptr)
		return;

	// Deep copy
	while (currentNode != nullptr) {
		addToTail(currentNode->data);
		currentNode = currentNode->nextNode;
	}
}
template <class T> void DoublyLinkedList<T>::operator = (const DoublyLinkedList<T>& doublyLinkedList) {
	clear();

	DoublyLinkedNode<T>* currentNode = doublyLinkedList.headNode;
	if (currentNode == nullptr)
		return;

	// Deep copy
	while (currentNode != nullptr) {
		addToTail(currentNode->data);
		currentNode = currentNode->nextNode;
	}
}
template <class T> DoublyLinkedList<T>::~DoublyLinkedList() {
	clear();
}

// Getters
template <class T> unsigned int DoublyLinkedList<T>::getSize() {
	return size;
}

template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::getHeadNode() {
	return headNode;
}

template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::getTailNode() {
	return tailNode;
}

template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::getNodeAt(unsigned int i) {
	if (i >= size)
		return nullptr;
	DoublyLinkedNode<T>* currentNode = headNode;
	for (unsigned int j = 0; j < i; j++)
		currentNode = currentNode->nextNode;

	return currentNode;	
}

template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::getNodeWithData(T data) {
	if (size == 0)
		return nullptr;

	DoublyLinkedNode<T>* currentNode = headNode;
	while (currentNode != nullptr) {
		if (currentNode->data == data)
			return currentNode;

		currentNode = currentNode->nextNode;
	}

	return nullptr;
}

// Functions
template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::add(T data) {
	return addToTail(data);
}
template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::addToHead(T data) {
	DoublyLinkedNode<T>* doublyLinkedNode = new DoublyLinkedNode<T>(this, data);
	if (size == 0) {
		headNode = doublyLinkedNode;
		tailNode = doublyLinkedNode;
		size++;
		return doublyLinkedNode;
	}

	headNode->previousNode = doublyLinkedNode;
	doublyLinkedNode->nextNode = headNode;
	headNode = doublyLinkedNode;
	size++;

	return doublyLinkedNode;
}
template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::addToTail(T data) {
	DoublyLinkedNode<T>* doublyLinkedNode = new DoublyLinkedNode<T>(this, data);
	if (size == 0) {
		headNode = doublyLinkedNode;
		tailNode = doublyLinkedNode;
		size++;
		return doublyLinkedNode;
	}

	tailNode->nextNode = doublyLinkedNode;
	doublyLinkedNode->previousNode = tailNode;
	tailNode = doublyLinkedNode;
	size++;

	return doublyLinkedNode;
}
template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::addAt(unsigned int i, T data) {
	if (i > size)
		return;
	if (i == 0)
		return addToHead(data);
	if (i == size)
		return addToTail(data);

	DoublyLinkedNode<T>* doublyLinkedNode = new DoublyLinkedNode<T>(this, data);

	DoublyLinkedNode<T>* currentNode = headNode;
	for (unsigned int j = 0; j < i; j++)
		currentNode = currentNode->nextNode;

	DoublyLinkedNode<T>* leftNode = currentNode->previousNode;
	DoublyLinkedNode<T>* rightNode = currentNode;

	leftNode->nextNode = doublyLinkedNode;
	rightNode->previousNode = doublyLinkedNode;

	doublyLinkedNode->previousNode = leftNode;
	doublyLinkedNode->nextNode = rightNode;

	size++;

	return doublyLinkedNode;
}
template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::addPreviousOf(DoublyLinkedNode<T>* referenceNode, T data) {
	if (referenceNode == nullptr || size == 0 || !has(referenceNode))
		return nullptr;
	if (referenceNode == headNode)
		return addToHead(data);

	DoublyLinkedNode<T>* doublyLinkedNode = new DoublyLinkedNode<T>(this, data);
	
	DoublyLinkedNode<T>* leftNode = referenceNode->previousNode;
	DoublyLinkedNode<T>* rightNode = referenceNode;

	leftNode->nextNode = doublyLinkedNode;
	rightNode->previousNode = doublyLinkedNode;

	doublyLinkedNode->previousNode = leftNode;
	doublyLinkedNode->nextNode = rightNode;

	size++;

	return doublyLinkedNode;
	
}
template <class T> DoublyLinkedNode<T>* DoublyLinkedList<T>::addNextOf(DoublyLinkedNode<T>* referenceNode, T data) {
	if (referenceNode == nullptr || size == 0 || !has(referenceNode))
		return nullptr;
	if (referenceNode == tailNode)
		return addToTail(data);

	DoublyLinkedNode<T>* doublyLinkedNode = new DoublyLinkedNode<T>(this, data);

	DoublyLinkedNode<T>* leftNode = referenceNode;
	DoublyLinkedNode<T>* rightNode = referenceNode->nextNode;

	leftNode->nextNode = doublyLinkedNode;
	rightNode->previousNode = doublyLinkedNode;

	doublyLinkedNode->previousNode = leftNode;
	doublyLinkedNode->nextNode = rightNode;

	size++;

	return doublyLinkedNode;
}


template <class T> void DoublyLinkedList<T>::remove(T data) {
	if (size == 0)
		return;
	if (size == 1 || headNode->data == data) {
		removeHeadNode();
		return;
	}
	if (tailNode->data == data) {
		removeTailNode();
		return;
	}

	DoublyLinkedNode<T>* currentNode = headNode;
	while (currentNode != nullptr) {
		if (currentNode->data == data) {
			remove(currentNode);
			return;
		}

		currentNode = currentNode->nextNode;
	}
}
template <class T> void DoublyLinkedList<T>::removeAt(unsigned int i) {
	// If list is empty, return
	if (size == 0)
		return;
	
	// Search for node at index == i and delete / remove it
	DoublyLinkedNode<T>* currentNode = headNode;
	for (unsigned int j = 0; j < i; j++)
		currentNode = currentNode->nextNode;
	delete(currentNode);
}
template <class T>
void DoublyLinkedList<T>::removeHeadNode() {
	// If list is empty, return
	if (size == 0)
		return;
	
	// Delete / remove head node
	if (headNode != nullptr)
		delete(headNode);
}
template <class T> void DoublyLinkedList<T>::removeTailNode() {
	// If list is empty, return
	if (size == 0)
		return;
	
	// Delete / remove tail node
	if (tailNode != nullptr)
		delete(tailNode);
}

template <class T> bool DoublyLinkedList<T>::has(T data) {
	if (size == 0)
		return false;

	DoublyLinkedNode<T>* currentNode = headNode;
	while (currentNode != nullptr) {
		if (currentNode->data == data)
			return true;

		currentNode = currentNode->nextNode;
	}

	return false;
}

template <class T> void DoublyLinkedList<T>::clear() {
	DoublyLinkedNode<T>* currentNode = headNode;
	while (currentNode != nullptr) {
		DoublyLinkedNode<T>* nextNode = currentNode->nextNode;
		delete(currentNode);
		currentNode = nextNode;
		size--;
	}
	size = 0;
	headNode = nullptr;
	tailNode = nullptr;
}
