#pragma once

// Dependencies | std
#include <iterator>

// Forward declarations | Utility
template <typename T> class SinglyLinkedNode;
template <typename T> class SinglyLinkedList;
template <typename T> class SinglyLinkedNodeIterator;

// SinglyLinkedNode
template <typename T> class SinglyLinkedNode {
	// Friends
	friend class SinglyLinkedList<T>;
	friend class SinglyLinkedNodeIterator<T>;

	// Object
	private:
		// Properties
		SinglyLinkedList<T>* singlyLinkedList;
		SinglyLinkedNode<T>* nextNode;

		// Constructors / Destructor
		SinglyLinkedNode();
		SinglyLinkedNode(T data);
		SinglyLinkedNode(const SinglyLinkedNode<T>& singlyLinkedNode);
	public:
		// Constructor / Destructor
		void operator = (const SinglyLinkedNode<T>& singlyLinkedNode);
		~SinglyLinkedNode();

		// Properties
		T data;

		// Getters
		SinglyLinkedList<T>* getSinglyLinkedList();
		SinglyLinkedNode<T>* getNextNode();

		// Functions
		SinglyLinkedNode<T>* addNextNode(T data);
};

// SinglyLinkedList
template <typename T> class SinglyLinkedList {
	// Friends
	friend class SinglyLinkedNode<T>;

	// Object
	private:
		// Properties
		unsigned long long size;
		SinglyLinkedNode<T>* firstNode;
		SinglyLinkedNode<T>* lastNode;
	public:
		// Constructors / Destructor
		SinglyLinkedList();                                                         // O(1)
		void operator = (const SinglyLinkedList<T>& singlyLinkedList);              // O(n)
		~SinglyLinkedList();                                                        // O(n)

		// Getters
		unsigned long long getSize();                                               // O(1)
		SinglyLinkedNode<T>* getFirstNode();                                        // O(1)
		SinglyLinkedNode<T>* getLastNode();                                         // O(1)
		SinglyLinkedNode<T>* getNodeAt(unsigned long long i);                       // O(n)

		// Functions
		SinglyLinkedNode<T>* add(T data);                                           // O(1)
		SinglyLinkedNode<T>* addFirstNode(T data);                                  // O(1)
		SinglyLinkedNode<T>* addLastNode(T data);                                   // O(1)
		SinglyLinkedNode<T>* addAt(unsigned long long i, T data);                   // O(n)
		SinglyLinkedNode<T>* addNextOf(SinglyLinkedNode<T>* referenceNode, T data); // O(1)

		void removeFirstNode();                                                     // O(1)
		void removeLastNode();                                                      // O(1)

		bool contains(T data);                                                      // O(n)
		bool contains(SinglyLinkedNode<T>* singlyLinkedNode);                       // O(1)

		void clear();                                                               // O(n)

		SinglyLinkedNodeIterator<T> begin();
		SinglyLinkedNodeIterator<T> end();
};

// SinglyLinkedNodeIterator
template <typename T> class SinglyLinkedNodeIterator {
	private:
		// Properties
		SinglyLinkedNode<T>* currentNode;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		// Constructor / Destructor
		SinglyLinkedNodeIterator(SinglyLinkedNode<T>* singlyLinkedNode);
		~SinglyLinkedNodeIterator();

		// Operators
		T& operator*() const;
		SinglyLinkedNodeIterator<T>& operator++();
		SinglyLinkedNodeIterator<T> operator++(int);
		bool operator==(const SinglyLinkedNodeIterator<T>& other) const;
		bool operator!=(const SinglyLinkedNodeIterator<T>& other) const;
};

// class SinglyLinkedNode

// Object| private

// Constructors / Destructor
template <typename T> SinglyLinkedNode<T>::SinglyLinkedNode() : singlyLinkedList(nullptr), nextNode(nullptr) {

}
template <typename T> SinglyLinkedNode<T>::SinglyLinkedNode(T data) : singlyLinkedList(nullptr), nextNode(nullptr), data(data) {

}
template <typename T> SinglyLinkedNode<T>::SinglyLinkedNode(const SinglyLinkedNode<T>& singlyLinkedNode) {
	this->singlyLinkedList = singlyLinkedNode.singlyLinkedList;
	this->nextNode = singlyLinkedNode.nextNode;
	this->data = singlyLinkedNode.data;
}
template <typename T> void SinglyLinkedNode<T>::operator = (const SinglyLinkedNode<T>& singlyLinkedNode) {
	this->singlyLinkedList = singlyLinkedNode.singlyLinkedList;
	this->nextNode = singlyLinkedNode.nextNode;
	this->data = singlyLinkedNode.data;
}

// Object| public

// Constructors / Destructor
template <typename T> SinglyLinkedNode<T>::~SinglyLinkedNode() {
	// If node not attached to a list, return
	if (singlyLinkedList == nullptr)
		return;

	// If list is empty, return
	if (singlyLinkedList->getSize() == 0ULL)
		return;

	// If there is only one node in the list, reset list
	if (singlyLinkedList->getSize() == 1ULL) {
		singlyLinkedList->size = 0ULL;
		singlyLinkedList->firstNode = nullptr;
		singlyLinkedList->lastNode = nullptr;
		return;
	}

	// Search for node to remove
	SinglyLinkedNode<T>* previousNode = nullptr;
	SinglyLinkedNode<T>* currentNode = singlyLinkedList->getFirstNode();
	while (currentNode != nullptr) {
		// If node to remove found
		if (currentNode == this) {
			// Relink list
			if (previousNode != nullptr)
				previousNode->nextNode = currentNode->nextNode;
			
			// If node is last or first node, update list
			if (singlyLinkedList->firstNode == this)
				singlyLinkedList->firstNode = currentNode->nextNode;
			if (singlyLinkedList->lastNode == this)
				singlyLinkedList->lastNode = previousNode;

			// Update list's size
			singlyLinkedList->size--;

			// Stop loop
			break;
		}

		// Save previous node and current node
		previousNode = currentNode;
		currentNode = currentNode->nextNode;
	}
}

// Getters
template <typename T> SinglyLinkedList<T>* SinglyLinkedNode<T>::getSinglyLinkedList() {
	return singlyLinkedList;
}
template <typename T> SinglyLinkedNode<T>* SinglyLinkedNode<T>::getNextNode() {
	return nextNode;
}

// Functions
template <typename T> SinglyLinkedNode<T>* SinglyLinkedNode<T>::addNextNode(T data) {
	SinglyLinkedNode<T>* newNode = new SinglyLinkedNode<T>(data);
	newNode->singlyLinkedList = singlyLinkedList;
	newNode->nextNode = nextNode;
	nextNode = newNode;

	if (singlyLinkedList != nullptr) {
		if (this == singlyLinkedList->lastNode)
			singlyLinkedList->lastNode = newNode;
		singlyLinkedList->size++;
	}

	return newNode;
}

// class SinglyLinkedList

// Object | public

// Constructors / Destructor
template <typename T> SinglyLinkedList<T>::SinglyLinkedList() : size(0ULL), firstNode(nullptr), lastNode(nullptr) {

}

template <typename T> void SinglyLinkedList<T>::operator = (const SinglyLinkedList<T>& singlyLinkedList) {
	clear();

	SinglyLinkedNode<T>* currentNode = singlyLinkedList.firstNode;
	if (currentNode != nullptr)
		return;

	// Deep copy
	while (currentNode != nullptr) {
		addLastNode(currentNode->data);
		currentNode = currentNode->nextNode;
	}
}

template <typename T> SinglyLinkedList<T>::~SinglyLinkedList() {
	clear();
}

// Getters
template <typename T> unsigned long long SinglyLinkedList<T>::getSize() {
	return size;
}
template <typename T> SinglyLinkedNode<T>* SinglyLinkedList<T>::getFirstNode() {
	return firstNode;
}
template <typename T> SinglyLinkedNode<T>* SinglyLinkedList<T>::getLastNode() {
	return lastNode;
}
template <typename T> SinglyLinkedNode<T>* SinglyLinkedList<T>::getNodeAt(unsigned long long i) {
	if (size == 0ULL || i >= size)
		return nullptr;

	SinglyLinkedNode<T>* currentNode = firstNode;
	for (unsigned long long j = 0ULL; j != i; j++)
		currentNode = currentNode->nextNode;

	return currentNode;
}

// Functions
template <typename T> SinglyLinkedNode<T>* SinglyLinkedList<T>::add(T data) {
	SinglyLinkedNode<T>* newNode = new SinglyLinkedNode<T>(data);
	newNode->singlyLinkedList = this;

	if (size == 0ULL) {
		firstNode = newNode;
		lastNode = newNode;
		size++;
		return newNode;
	}

	size++;
	lastNode->nextNode = newNode;
	lastNode = newNode;

	return newNode;
}
template <typename T> SinglyLinkedNode<T>* SinglyLinkedList<T>::addFirstNode(T data) {
	SinglyLinkedNode<T>* newNode = new SinglyLinkedNode<T>( data);
	newNode->singlyLinkedList = this;

	if (size == 0ULL) {
		size++;
		firstNode = newNode;
		lastNode = newNode;
		return newNode;
	}

	size++;
	newNode->nextNode = firstNode;
	firstNode = newNode;

	return newNode;
}
template <typename T> SinglyLinkedNode<T>* SinglyLinkedList<T>::addLastNode(T data) {
	SinglyLinkedNode<T>* newNode = new SinglyLinkedNode<T>(data);
	newNode->singlyLinkedList = this;

	if (size == 0ULL) {
		size++;
		firstNode = newNode;
		lastNode = newNode;
		return newNode;
	}

	size++;
	lastNode->nextNode = newNode;
	lastNode = newNode;

	return newNode;
}
template <typename T> SinglyLinkedNode<T>* SinglyLinkedList<T>::addAt(unsigned long long i, T data) {
	if (i > size)
		return nullptr;
	if (i == size)
		return addLastNode(data);
	if (i == 0ULL)
		return addFirstNode(data);

	SinglyLinkedNode<T>* currentNode = firstNode;
	for (unsigned long long j = 0ULL; j != i - 1ULL; j++)
		currentNode = currentNode->nextNode;

	SinglyLinkedNode<T>* newNode = new SinglyLinkedNode<T>(data);
	newNode->singlyLinkedList = this;

	newNode->nextNode = currentNode->nextNode;
	currentNode->nextNode = newNode;
	size++;

	return newNode;
}
template <typename T> SinglyLinkedNode<T>* SinglyLinkedList<T>::addNextOf(SinglyLinkedNode<T>* referenceNode, T data) {
	if (!contains(referenceNode))
		return nullptr;

	SinglyLinkedNode<T>* newNode = new SinglyLinkedNode<T>(data);
	newNode->singlyLinkedList = this;

	if (referenceNode == lastNode)
		lastNode = newNode;

	newNode->nextNode = referenceNode->nextNode;
	referenceNode->nextNode = newNode;
	size++;

	return newNode;
}

template <typename T> void SinglyLinkedList<T>::removeFirstNode() {
	delete(firstNode);
}
template <typename T> void SinglyLinkedList<T>::removeLastNode() {
	delete(lastNode);
}

template <typename T> bool SinglyLinkedList<T>::contains(T data) {
	SinglyLinkedNode<T>* currentNode = firstNode;
	while (currentNode != nullptr) {
		if (currentNode->data == data)
			return true;
		currentNode = currentNode->nextNode;
	}
	return false;
}
template <typename T> bool SinglyLinkedList<T>::contains(SinglyLinkedNode<T>* singlyLinkedNode) {
	if (singlyLinkedNode == nullptr)
		return false;
	if (singlyLinkedNode->singlyLinkedList == this)
		return true;
	return false;
}

template <typename T> void SinglyLinkedList<T>::clear() {
	SinglyLinkedNode<T>* currentNode = firstNode;
	while (currentNode != nullptr) {
		SinglyLinkedNode<T>* nextNode = currentNode->nextNode;
		delete(currentNode);
		currentNode = nextNode;
	}
	size = 0ULL;
	firstNode = nullptr;
	lastNode = nullptr;
}

// Container functions
template <typename T> SinglyLinkedNodeIterator<T> SinglyLinkedList<T>::begin() {
	return SinglyLinkedNodeIterator<T>(firstNode);
}
template<typename T> SinglyLinkedNodeIterator<T> SinglyLinkedList<T>::end() {
	return SinglyLinkedNodeIterator<T>(nullptr);
}

// class SinglyLinkedNodeIterator

// Object | public

// Constructor / Destructor
template <typename T> SinglyLinkedNodeIterator<T>::SinglyLinkedNodeIterator(SinglyLinkedNode<T>* singlyLinkedNode) : currentNode(singlyLinkedNode) {

}
template <typename T> SinglyLinkedNodeIterator<T>::~SinglyLinkedNodeIterator() {

}

// Operator overload
template <typename T> T& SinglyLinkedNodeIterator<T>::operator*() const {
	return currentNode->data;
}
template <typename T> SinglyLinkedNodeIterator<T>& SinglyLinkedNodeIterator<T>::operator++() {
	currentNode = currentNode->nextNode;
	return *this;
}
template <typename T> SinglyLinkedNodeIterator<T> SinglyLinkedNodeIterator<T>::operator++(int) {
	SinglyLinkedNodeIterator temp = *this;
	++(*this);
	return temp;
}
template <typename T> bool SinglyLinkedNodeIterator<T>::operator==(const SinglyLinkedNodeIterator<T>& other) const {
	return currentNode == other.currentNode;
}
template <typename T> bool SinglyLinkedNodeIterator<T>::operator!=(const SinglyLinkedNodeIterator<T>& other) const {
	return !(*this == other);
}
