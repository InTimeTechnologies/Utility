#pragma once

#include <vector>

// DoubleLinkedNode
template <class T>
class DoublyLinkedNode {
	public:
		T data;
		DoublyLinkedNode<T>* nextNode;
		DoublyLinkedNode<T>* previousNode;

		DoublyLinkedNode(T data);
		DoublyLinkedNode(const DoublyLinkedNode<T>& otherDoublyLinkedNode);

		void operator = (const DoublyLinkedNode<T>& otherDoublyLinkedNode);

		~DoublyLinkedNode();
};

template <class T>
DoublyLinkedNode<T>::DoublyLinkedNode(T data) {
	this->data = data;
	nextNode = nullptr;
	previousNode = nullptr;
}

template <class T>
DoublyLinkedNode<T>::DoublyLinkedNode(const DoublyLinkedNode<T>& otherDoublyLinkedNode) {
	data = otherDoublyLinkedNode.data;
	nextNode = nullptr;
}

template <class T>
void DoublyLinkedNode<T>::operator = (const DoublyLinkedNode<T>& otherDoublyLinkedNode) {
	data = otherDoublyLinkedNode.data;
	nextNode = nullptr;
}

template <class T>
DoublyLinkedNode<T>::~DoublyLinkedNode() {
	nextNode = nullptr;
	previousNode = nullptr;
}

// DoublyLinkedList
template <class E>
class DoublyLinkedList {
	private:
		unsigned int size;
	public:
		DoublyLinkedNode<E>* head;
		DoublyLinkedNode<E>* tail;

		DoublyLinkedList();
		DoublyLinkedList(const DoublyLinkedList<E>& otherDoublyLinkedList);

		void operator = (const DoublyLinkedList<E>& otherDoublyLinkedList);

		DoublyLinkedNode<E>* addToHead(E data);                     // O(1)
		DoublyLinkedNode<E>* addAt(unsigned int i, E data);         // O(n)
		DoublyLinkedNode<E>* addToTail(E data);                     // O(1)

		DoublyLinkedNode<E>* insertNextOf(DoublyLinkedNode<E>* doublyLinkedNode, E data);       // O(1)
		DoublyLinkedNode<E>* insertPreviousOf(DoublyLinkedNode<E>* doublyLinkedNode, E data);   // O(1)

		DoublyLinkedNode<E>* getNodeAt(unsigned int i);             // O(n)
		DoublyLinkedNode<E>* getHeadNode();                         // O(1)
		DoublyLinkedNode<E>* getTailNode();                         // O(1)
		bool contains(DoublyLinkedNode<E>* doublyLinkedNode);       // O(1)

		E getDataAt(unsigned int i);                                // O(n)
		E getHeadData();                                            // O(1)
		E getTailData();                                            // O(1)
		bool contains(E data);                                      // O(n)

		E removeAt(unsigned int i);                                 // O(n)
		E removeHead();                                             // O(1)
		E removeTail();                                             // O(1)
		E removeNode(DoublyLinkedNode<E>* doublyLinkedNode);        // O(1)

		void clear();                                               // O(n)
		unsigned int getSize();                                     // O(1)

		~DoublyLinkedList();
};

template <class E>
DoublyLinkedList<E>::DoublyLinkedList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <class E>
DoublyLinkedList<E>::DoublyLinkedList(const DoublyLinkedList<E>& otherDoublyLinkedList) {
	DoublyLinkedNode<E>* currentDoublyLinkedNode = otherDoublyLinkedList.head;
	while (currentDoublyLinkedNode != nullptr) {
		addToTail(otherDoublyLinkedList.data);
		currentDoublyLinkedNode = currentDoublyLinkedNode->nextNode;
	}
}

template <class E>
void DoublyLinkedList<E>::operator = (const DoublyLinkedList<E>& otherDoublyLinkedList) {
	DoublyLinkedNode<E>* currentDoublyLinkedNode = otherDoublyLinkedList.head;
	while (currentDoublyLinkedNode != nullptr) {
		addToTail(otherDoublyLinkedList.data);
		currentDoublyLinkedNode = currentDoublyLinkedNode->nextNode;
	}
}

template <class E>
DoublyLinkedList<E>::~DoublyLinkedList() {
	while (head != nullptr)
		removeHead();
}

template <class E>
DoublyLinkedNode<E>* DoublyLinkedList<E>::addToHead(E data) {
	DoublyLinkedNode<E>* newNode = new DoublyLinkedNode<E>(data);

	if (size == 0) {
		head = newNode;
		tail = newNode;
		size++;
		return newNode;
	}

	newNode->nextNode = head;
	head = newNode;
	newNode->nextNode->previousNode = newNode;
	size++;
	return newNode;
}

template <class E>
DoublyLinkedNode<E>* DoublyLinkedList<E>::addAt(unsigned int i, E data) {
	if (i > size)
		return 0;
	if (i == 0)
		return addToHead(data);
	if (i == size)
		return addToTail(data);

	DoublyLinkedNode<E>* newNode = new DoublyLinkedNode<E>(data);
	DoublyLinkedNode<E>* previousNode = head;
	DoublyLinkedNode<E>* nextNode = nullptr;
	size++;

	for (unsigned int currentIndex = 0; currentIndex < (i - 1); currentIndex++)
		previousNode = previousNode->nextNode;
	nextNode = previousNode->nextNode;

	newNode->nextNode = nextNode;
	newNode->previousNode = previousNode;
	previousNode->nextNode = newNode;
	nextNode->previousNode = newNode;
	return newNode;
}

template <class E>
DoublyLinkedNode<E>* DoublyLinkedList<E>::addToTail(E data) {
	DoublyLinkedNode<E>* newNode = new DoublyLinkedNode<E>(data);

	if (size = 0) {
		head = newNode;
		tail = newNode;
		size++;
		return newNode;
	}

	newNode->previousNode = tail;
	tail = newNode;
	newNode->previousNode->nextNode = newNode;
	size++;
	return newNode;
}

template <class E>
DoublyLinkedNode<E>* DoublyLinkedList<E>::insertPreviousOf(DoublyLinkedNode<E>* doublyLinkedNode, E data) {
	DoublyLinkedNode<E>* newNode = new DoublyLinkedNode<E>(data);

	newNode->nextNode = doublyLinkedNode;
	newNode->previousNode = doublyLinkedNode->previousNode;

	doublyLinkedNode->previousNode->nextNode = newNode;
	doublyLinkedNode->previousNode = newNode;

	size++;
	return newNode;
}

template <class E>
DoublyLinkedNode<E>* DoublyLinkedList<E>::insertNextOf(DoublyLinkedNode<E>* doublyLinkedNode, E data) {
	DoublyLinkedNode<E>* newNode = new DoublyLinkedNode<E>(data);

	newNode->nextNode = doublyLinkedNode->nextNode;
	newNode->previousNode = doublyLinkedNode;

	doublyLinkedNode->nextNode->previousNode = newNode;
	doublyLinkedNode->nextNode = newNode;

	size++;
	return newNode;
}

template <class E>
DoublyLinkedNode<E>* DoublyLinkedList<E>::getNodeAt(unsigned int i) {
	if (size == 0)
		return 0;
	if (i > (size - 1))
		return 0;

	DoublyLinkedNode<E>* currentNode = head;
	for (unsigned int currentIndex = 0; currentIndex < i; currentIndex++)
		currentNode = currentNode->nextNode;

	return currentNode;
}

template <class E>
DoublyLinkedNode<E>* DoublyLinkedList<E>::getHeadNode() {
	return head;
}

template <class E>
DoublyLinkedNode<E>* DoublyLinkedList<E>::getTailNode() {
	return tail;
}

template <class E>
bool DoublyLinkedList<E>::contains(DoublyLinkedNode<E>* doublyLinkedNode) {
	DoublyLinkedNode<E>* currentNode = head;
	while (currentNode != nullptr) {
		if (currentNode == doublyLinkedNode)
			return true;
		currentNode = currentNode->nextNode;
	}
	return false;
}

template <class E>
E DoublyLinkedList<E>::getDataAt(unsigned int i) {
	if (size == 0)
		return 0;
	if (i > (size - 1))
		return 0;

	DoublyLinkedNode<E>* currentNode = head;
	DoublyLinkedNode<E>* previousNode = nullptr;
	DoublyLinkedNode<E>* nextNode = nullptr;
	for (unsigned int currentIndex = 0; currentIndex < i; currentIndex++)
		currentNode = currentNode->nextNode;

	return currentNode->data;
}

template <class E>
E DoublyLinkedList<E>::getHeadData() {
	if (head != nullptr)
		return head->data;
	return nullptr;
}

template <class E>
E DoublyLinkedList<E>::getTailData() {
	if (tail != nullptr)
		return tail->data;
	return nullptr;
}

template <class E>
bool DoublyLinkedList<E>::contains(E data) {
	DoublyLinkedNode<E>* currentNode = head;
	while (currentNode != nullptr) {
		if (currentNode->data == data)
			return true;
		currentNode = currentNode->nextNode;
	}
	return false;
}

template <class E>
E DoublyLinkedList<E>::removeAt(unsigned int i) {
	if (size == 0 || i >= size - 1)
		return 0;

	if (i == 0)
		return removeHead();
	if (i == (size - 1))
		return removeTail();

	DoublyLinkedNode<E>* currentNode = head;
	DoublyLinkedNode<E>* previousNode = nullptr;
	DoublyLinkedNode<E>* nextNode = nullptr;
	for (unsigned int currentIndex = 0; currentIndex < i; currentIndex++)
		currentNode = currentNode->nextNode;

	E* data = currentNode->data;
	previousNode = currentNode->previousNode;
	nextNode = currentNode->nextNode;
	previousNode->nextNode = nextNode;
	nextNode->previousNode = previousNode;
	delete(currentNode);
	size--;
	return data;
}

template <class E>
E DoublyLinkedList<E>::removeHead() {
	if (size == 0)
		return 0;

	DoublyLinkedNode<E>* nodeToRemove = head;
	E data = nodeToRemove->data;

	if (size == 1) {
		head = nullptr;
		tail = nullptr;
		size = 0;
		delete(nodeToRemove);
		return data;
	}
	else {
		head = head->nextNode;
		head->previousNode = nullptr;
	}

	delete(nodeToRemove);
	size--;
	return data;
}

template <class E>
E DoublyLinkedList<E>::removeTail() {
	if (size == 0)
		return 0;

	DoublyLinkedNode<E>* nodeToRemove = tail;
	E data = nodeToRemove->data;
	if (size == 1) {
		head = nullptr;
		tail = nullptr;
		size = 0;
		delete(nodeToRemove);
		return data;
	}
	else {
		tail = tail->previousNode;
		tail->nextNode = nullptr;
	}

	delete(nodeToRemove);
	size--;
	return data;
}

template <class E>
E DoublyLinkedList<E>::removeNode(DoublyLinkedNode<E>* doublyLinkedNode) {
	if (size == 0)
		return 0;

	E data = doublyLinkedNode->data;
	// If true, node is head node
	if (doublyLinkedNode->previousNode == nullptr)
		return removeHead();
	// If true, node is tail node
	if (doublyLinkedNode->nextNode == nullptr)
		return removeTail();

	DoublyLinkedNode<E>* previousNode = doublyLinkedNode->previousNode;
	DoublyLinkedNode<E>* nextNode = doublyLinkedNode->nextNode;
	previousNode->nextNode = nextNode;
	nextNode->previousNode = previousNode;
	delete(doublyLinkedNode);
	size--;
	return data;
}

template <class E>
unsigned int DoublyLinkedList<E>::getSize() {
	return size;
}

template <class E>
void DoublyLinkedList<E>::clear() {
	if (size == 0)
		return;

	while (size > 0)
		removeHead();
}

