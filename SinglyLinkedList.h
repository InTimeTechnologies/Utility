#pragma once

template <class T> class SinglyLinkedNode;
template <class T> class SinglyLinkedList;

// SinglyLinkedNode
template <class T>
class SinglyLinkedNode {
	public:
		// Properties
		SinglyLinkedList<T>* singlyLinkedList;
		SinglyLinkedNode<T>* nextNode;
		T data;

		// Constructors / Destructor
		SinglyLinkedNode();
		SinglyLinkedNode(SinglyLinkedList<T>* singlyLinkedList);
		SinglyLinkedNode(T data);
		SinglyLinkedNode(SinglyLinkedList<T>* singlyLinkedList, T data);
		SinglyLinkedNode(const SinglyLinkedNode<T>& singlyLinkedNode);
		void operator = (const SinglyLinkedNode<T>& singlyLinkedNode);
		~SinglyLinkedNode();
};

// Object| public
// Constructors / Destructor
template <class T>
SinglyLinkedNode<T>::SinglyLinkedNode() : singlyLinkedList(nullptr), nextNode(nullptr) {

}
template <class T>
SinglyLinkedNode<T>::SinglyLinkedNode(T data) : singlyLinkedList(nullptr), nextNode(nullptr), data(data) {

}
template <class T>
SinglyLinkedNode<T>::SinglyLinkedNode(SinglyLinkedList<T>* singlyLinkedList) : singlyLinkedList(singlyLinkedList), nextNode(nullptr) {

}
template <class T>
SinglyLinkedNode<T>::SinglyLinkedNode(SinglyLinkedList<T>* singlyLinkedList, T data) : singlyLinkedList(singlyLinkedList), nextNode(nullptr), data(data) {

}
template <class T>
SinglyLinkedNode<T>::SinglyLinkedNode(const SinglyLinkedNode<T>& singlyLinkedNode) {
	this->singlyLinkedList = singlyLinkedNode.singlyLinkedList;
	this->nextNode = singlyLinkedNode.nextNode;
	this->data = singlyLinkedNode.data;
}
template <class T>
void SinglyLinkedNode<T>::operator = (const SinglyLinkedNode<T>& singlyLinkedNode) {
	this->singlyLinkedList = singlyLinkedNode.singlyLinkedList;
	this->nextNode = singlyLinkedNode.nextNode;
	this->data = singlyLinkedNode.data;
}
template <class T>
SinglyLinkedNode<T>::~SinglyLinkedNode() {
	singlyLinkedList = nullptr;
	nextNode = nullptr;
}

// SinglyLinkedList
template <class T>
class SinglyLinkedList {
	private:
		// Properties
		unsigned int size;
		SinglyLinkedNode<T>* headNode;
		SinglyLinkedNode<T>* tailNode;

	public:
		// Constructors / Destructor
		SinglyLinkedList();                                                            // O(1)
		void operator = (const SinglyLinkedList<T>& singlyLinkedList);                 // O(n)
		~SinglyLinkedList();                                                           // O(n)

		// Getters
		unsigned int getSize();                                                        // O(1)
		SinglyLinkedNode<T>* getHeadNode();                                            // O(1)
		SinglyLinkedNode<T>* getTailNode();                                            // O(1)
		SinglyLinkedNode<T>* getNodeAt(unsigned int i);                                // O(n)

		// Functions
		SinglyLinkedNode<T>* add(T data);                                              // O(1)
		SinglyLinkedNode<T>* addToHead(T data);                                        // O(1)
		SinglyLinkedNode<T>* addToTail(T data);                                        // O(1)
		SinglyLinkedNode<T>* addAt(unsigned int i, T data);                            // O(n)
		SinglyLinkedNode<T>* addNextOf(SinglyLinkedNode<T>* referenceNode, T data);    // O(1)

		void remove(T data);                                                           // O(n)
		void removeAt(unsigned int i);                                                 // O(n)
		void removeNextOf(SinglyLinkedNode<T>* singlyLinkedNode);                      // O(1)
		void removeHeadNode();                                                         // O(1)
		void removeTailNode();                                                         // O(1)

		bool contains(T data);                                                         // O(n)
		bool contains(SinglyLinkedNode<T>* singlyLinkedNode);                          // O(1)

		void clear();                                                                  // O(n)
};

// Object | public
// Constructors / Destructor
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() : size(0), headNode(nullptr), tailNode(nullptr) {

}

template <class T>
void SinglyLinkedList<T>::operator = (const SinglyLinkedList<T>& singlyLinkedList) {
	clear();

	SinglyLinkedNode<T>* currentNode = singlyLinkedList.headNode;
	if (currentNode != nullptr)
		return;

	// Deep copy
	while (currentNode != nullptr) {
		addToTail(currentNode->data);
		currentNode = currentNode->nextNode;
	}
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
	clear();
}

// Getters
template <class T>
unsigned int SinglyLinkedList<T>::getSize() {
	return size;
}
template <class T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::getHeadNode() {
	return headNode;
}
template <class T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::getTailNode() {
	return tailNode;
}
template <class T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::getNodeAt(unsigned int i) {
	if (size == 0 || i >= size)
		return nullptr;

	SinglyLinkedNode<T>* currentNode = headNode;
	for (unsigned int j = 0; j != i; j++)
		currentNode = currentNode->nextNode;

	return currentNode;
}

// Functions
template <class T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::add(T data) {
	SinglyLinkedNode<T>* singlyLinkedNode = new SinglyLinkedNode<T>(this, data);

	if (size == 0) {
		headNode = singlyLinkedNode;
		tailNode = singlyLinkedNode;
		size++;
		return singlyLinkedNode;
	}

	size++;
	tailNode->nextNode = singlyLinkedNode;
	tailNode = singlyLinkedNode;

	return singlyLinkedNode;
}
template <class T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::addToHead(T data) {
	SinglyLinkedNode<T>* singlyLinkedNode = new SinglyLinkedNode<T>(this, data);

	if (size == 0) {
		size++;
		headNode = singlyLinkedNode;
		tailNode = singlyLinkedNode;
		return singlyLinkedNode;
	}

	size++;
	singlyLinkedNode->nextNode = headNode;
	headNode = singlyLinkedNode;

	return singlyLinkedNode;
}
template <class T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::addToTail(T data) {
	SinglyLinkedNode<T>* singlyLinkedNode = new SinglyLinkedNode<T>(this, data);

	if (size == 0) {
		size++;
		headNode = singlyLinkedNode;
		tailNode = singlyLinkedNode;
		return singlyLinkedNode;
	}

	size++;
	tailNode->nextNode = singlyLinkedNode;
	tailNode = singlyLinkedNode;

	return singlyLinkedNode;
}
template <class T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::addAt(unsigned int i, T data) {
	if (i > size)
		return nullptr;
	if (i == size)
		return addToTail(data);
	if (i == 0)
		return addToHead(data);

	SinglyLinkedNode<T>* currentNode = headNode;
	for (unsigned int j = 0; j != i - 1; j++)
		currentNode = currentNode->nextNode;

	SinglyLinkedNode<T>* singlyLinkedNode = new SinglyLinkedNode<T>(this, data);

	singlyLinkedNode->nextNode = currentNode->nextNode;
	currentNode->nextNode = singlyLinkedNode;
	size++;

	return singlyLinkedNode;
}
template <class T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::addNextOf(SinglyLinkedNode<T>* referenceNode, T data) {
	if (!contains(referenceNode))
		return nullptr;

	SinglyLinkedNode<T>* singlyLinkedNode = new SinglyLinkedNode<T>(this, data);

	if (referenceNode == tailNode)
		tailNode = singlyLinkedNode;

	singlyLinkedNode->nextNode = referenceNode->nextNode;
	referenceNode->nextNode = singlyLinkedNode;
	size++;

	return singlyLinkedNode;
}

template <class T>
void SinglyLinkedList<T>::remove(T data) {
	if (size == 0)
		return;
	if (size == 1) {
		delete(headNode);
		headNode = nullptr;
		tailNode = nullptr;
		size = 0;
		return;
	}
	if (headNode->data == data) {
		removeHeadNode();
		return;
	}
	if (tailNode->data == data) {
		removeTailNode();
		return;
	}

	SinglyLinkedNode<T>* currentNode = headNode;
	while (currentNode != nullptr) {
		SinglyLinkedNode<T>* nextNode = currentNode->nextNode;

		if (nextNode == nullptr)
			return;

		if (nextNode->data == data) {
			currentNode->nextNode = nextNode->nextNode;
			delete(nextNode);
			size--;
			return;
		}

		currentNode = currentNode->nextNode;
	}
}
template <class T>
void SinglyLinkedList<T>::removeAt(unsigned int i) {
	if (size == 0 || i >= size)
		return;
	if (i == 0) {
		removeHeadNode();
		return;
	}
	if (i == size - 1) {
		removeTailNode();
		return;
	}

	SinglyLinkedNode<T>* currentNode = headNode;
	for (unsigned int j = 0; j < i - 1; j++)
		currentNode = currentNode->nextNode;

	SinglyLinkedNode<T>* nodeToRemove = currentNode->nextNode;
	currentNode->nextNode = nodeToRemove->nextNode;
	delete(nodeToRemove);
	size--;
}
template <class T>
void SinglyLinkedList<T>::removeNextOf(SinglyLinkedNode<T>* singlyLinkedNode) {
	if (!contains(singlyLinkedNode) || size == 0 || singlyLinkedNode == tailNode)
		return;

	if (singlyLinkedNode->nextNode == tailNode)
		tailNode = singlyLinkedNode;

	singlyLinkedNode->nextNode = singlyLinkedNode->nextNode->nextNode;
	delete(singlyLinkedNode->nextNode);
	size--;
}
template <class T>
void SinglyLinkedList<T>::removeHeadNode() {
	if (size == 0)
		return;
	if (size == 1) {
		delete(headNode);
		headNode = nullptr;
		tailNode = nullptr;
		size = 0;
		return;
	}
	if (size == 2) {
		delete(headNode);
		headNode = tailNode;
		size--;
		return;
	}

	SinglyLinkedNode<T>* newHeadNode = headNode->nextNode;
	delete(headNode);
	headNode = newHeadNode;
}
template <class T>
void SinglyLinkedList<T>::removeTailNode() {
	if (size == 0)
		return;
	if (size == 0) {
		delete(tailNode);
		headNode = nullptr;
		tailNode = nullptr;
		size = 0;
		return;
	}
	if (size == 2) {
		delete(tailNode);
		tailNode = headNode;
		size--;
		return;
	}

	SinglyLinkedNode<T>* currentNode = headNode;
	while (currentNode->nextNode->nextNode != nullptr)
		currentNode = currentNode->nextNode;

	delete(currentNode->nextNode);
	currentNode->nextNode = nullptr;
	tailNode = currentNode;
	size--;
}

template <class T>
bool SinglyLinkedList<T>::contains(T data) {
	SinglyLinkedNode<T>* currentNode = headNode;
	while (currentNode != nullptr) {
		if (currentNode->data == data)
			return true;
		currentNode = currentNode->nextNode;
	}
	return false;
}
template <class T>
bool SinglyLinkedList<T>::contains(SinglyLinkedNode<T>* singlyLinkedNode) {
	if (singlyLinkedNode == nullptr)
		return false;
	if (singlyLinkedNode->singlyLinkedList == this)
		return true;
	return false;
}

template <class T>
void SinglyLinkedList<T>::clear() {
	SinglyLinkedNode<T>* currentNode = headNode;
	while (currentNode != nullptr) {
		SinglyLinkedNode<T>* nextNode = currentNode->nextNode;
		delete(currentNode);
		currentNode = nextNode;
		size--;
	}
	size = 0;
	headNode = nullptr;
	tailNode = nullptr;
}
