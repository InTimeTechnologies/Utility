#pragma once

// SinglyLinkedNode
template <class T>
class SinglyLinkedNode {
	public:
		T data;
		SinglyLinkedNode<T>* nextNode;

		SinglyLinkedNode(T data);
		SinglyLinkedNode(const SinglyLinkedNode& singlyLinkedNode);
		
		void operator = (const SinglyLinkedNode& singlyLinkedNode);

		~SinglyLinkedNode();
};

template <class T>
SinglyLinkedNode<T>::SinglyLinkedNode(T data) {
	this->data = data;
	nextNode = nullptr;
}

template <class T>
SinglyLinkedNode<T>::SinglyLinkedNode(const SinglyLinkedNode& singlyLinkedNode) {
	this->data = singlyLinkedNode.data;
	nextNode = nullptr;
}

template <class T>
void SinglyLinkedNode<T>::operator = (const SinglyLinkedNode& singlyLinkedNode) {
	this->data = singlyLinkedNode.data;
	nextNode = nullptr;
}

template <class T>
SinglyLinkedNode<T>::~SinglyLinkedNode() {
	nextNode = nullptr;
}

// SinglyLinkedList
template <class E>
class SinglyLinkedList {
	private:
		unsigned int size;
	public:
		SinglyLinkedNode<E>* head;
		SinglyLinkedNode<E>* tail;

		SinglyLinkedList();
		SinglyLinkedList(const SinglyLinkedList& singlyLinkedList);

		void operator = (const SinglyLinkedList<E> singlyLinkedList);

		SinglyLinkedNode<E>* add(E data);                       // O(1)
		SinglyLinkedNode<E>* addAt(unsigned int i, E data);     // O(n)
		SinglyLinkedNode<E>* addToHead(E data);                 // O(1)
		SinglyLinkedNode<E>* addToTail(E data);                 // O(n)

		SinglyLinkedNode<E>* getNodeAt(unsigned int i);         // O(n)
		SinglyLinkedNode<E>* getHeadNode();                     // O(1)
		SinglyLinkedNode<E>* getTailNode();                     // O(1)
		bool contains(SinglyLinkedNode<E>* singlyLinkedNode);   // O(n)

		E getDataAt(unsigned int i);                            // O(n)
		E getHeadData();                                        // O(1)
		E getTailData();                                        // O(1)
		bool contains(E data);                                  // O(n)

		E remove(E data);                                       // O(n)
		E removeAt(unsigned int i);                             // O(n)
		E removeHead();                                         // O(1)
		E removeTail();                                         // O(size)

		void clear();                                           // O(size)
		bool isEmpty();                                         // O(1)
		unsigned int getSize();                                 // O(1)

		~SinglyLinkedList();
};

template <class E>
SinglyLinkedList<E>::SinglyLinkedList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <class E>
SinglyLinkedList<E>::SinglyLinkedList(const SinglyLinkedList<E>& singlyLinkedList) {
	head = nullptr;
	tail = nullptr;
	size = 0;

	SinglyLinkedNode<E>* currentNode = singlyLinkedList.head;
	while (currentNode != nullptr) {
		addToTail(currentNode->data);
		currentNode = currentNode->nextNode;
	}
}

template <class E>
void SinglyLinkedList<E>::operator = (const SinglyLinkedList<E> singlyLinkedList) {
	head = nullptr;
	tail = nullptr;
	size = 0;

	SinglyLinkedNode<E>* currentNode = singlyLinkedList.head;
	while (currentNode != nullptr) {
		addToTail(currentNode->data);
		currentNode = currentNode->nextNode;
	}
}

template <class E>
SinglyLinkedNode<E>* SinglyLinkedList<E>::add(E data) {
	return addToTail(data);
}

template <class E>
SinglyLinkedNode<E>* SinglyLinkedList<E>::addAt(unsigned int i, E data) {
	if (i > size)
		return nullptr;
	SinglyLinkedNode<E>* singlyLinkedNode = new SinglyLinkedNode<E>(data);
	if (size == 0) {
		head = singlyLinkedNode;
		tail = singlyLinkedNode;
		size++;
		return singlyLinkedNode;
	}
	if (i == 0) {
		singlyLinkedNode->nextNode = head;
		head = singlyLinkedNode;
		size++;
		return singlyLinkedNode;
	}
	SinglyLinkedNode<E>* currentNode = head;
	for (unsigned int j = 1; j < i; j++)
		currentNode = currentNode->nextNode;
	singlyLinkedNode->nextNode = currentNode->nextNode;
	currentNode->nextNode = singlyLinkedNode;
	size++;
	return singlyLinkedNode;
}

template <class E>
SinglyLinkedNode<E>* SinglyLinkedList<E>::addToHead(E data) {
	SinglyLinkedNode<E>* singlyLinkedNode = new SinglyLinkedNode<E>(data);
	if (size == 0) {
		head = singlyLinkedNode;
		tail = singlyLinkedNode;
		size++;
		return singlyLinkedNode;
	}
	singlyLinkedNode->nextNode = head;
	head = singlyLinkedNode;
	size++;
	return singlyLinkedNode;
}

template <class E>
SinglyLinkedNode<E>* SinglyLinkedList<E>::addToTail(E data) {
	SinglyLinkedNode<E>* singlyLinkedNode = new SinglyLinkedNode<E>(data);
	if (size == 0) {
		head = singlyLinkedNode;
		tail = singlyLinkedNode;
		size++;
		return singlyLinkedNode;
	}
	tail->nextNode = new SinglyLinkedNode<E>(data);
	tail = tail->nextNode;
	size++;
	return singlyLinkedNode;
}

template <class E>
SinglyLinkedNode<E>* SinglyLinkedList<E>::getNodeAt(unsigned int i) {
	if (size == 0 || i >= size)
		return nullptr;
	SinglyLinkedNode<E>* currentNode = head;
	for (unsigned int j = 0; j < i; j++)
		currentNode = currentNode->nextNode;
	return currentNode;
}

template <class E>
SinglyLinkedNode<E>* SinglyLinkedList<E>::getHeadNode() {
	return head;
}

template <class E>
SinglyLinkedNode<E>* SinglyLinkedList<E>::getTailNode() {
	return tail;
}

template <class E>
bool SinglyLinkedList<E>::contains(SinglyLinkedNode<E>* singlyLinkedNode) {
	SinglyLinkedList<E>* currentNode = head;
	while (currentNode != nullptr)
		if (currentNode == singlyLinkedNode)
			return true;
	return false;
}

template <class E>
E SinglyLinkedList<E>::getDataAt(unsigned int i) {
	SinglyLinkedNode<E>* singlyLinkedNode = getNodeAt(i);
	if (singlyLinkedNode == nullptr)
		return 0;
	return singlyLinkedNode->data;
}

template <class E>
E SinglyLinkedList<E>::getHeadData() {
	if (head == nullptr)
		return 0;
	return head->data;
}

template <class E>
E SinglyLinkedList<E>::getTailData() {
	if (tail == nullptr)
		return 0;
	return tail->data;
}

template <class E>
bool SinglyLinkedList<E>::contains(E data) {
	if (size == 0)
		return false;
	SinglyLinkedNode<E>* currentNode = head;
	while (currentNode != nullptr) {
		if (currentNode->data == data)
			return true;
		currentNode = currentNode->nextNode;
	}
	return false;
}

template <class E>
E SinglyLinkedList<E>::remove(E data) {
	if (size == 0)
		return 0;
	if (head->data == data)
		return removeHead();
	if (size > 1) {
		SinglyLinkedNode<E>* currentNode = head;
		while (currentNode->nextNode != nullptr) {
			if (currentNode->nextNode->data == data) {
				E data = currentNode->nextNode->data;
				SinglyLinkedNode<E>* nodeToDelete = currentNode->nextNode;
				if (nodeToDelete == tail)
					tail = currentNode;
				currentNode->nextNode = currentNode->nextNode->nextNode;
				delete(nodeToDelete);
				size--;
				return data;
			}
			currentNode = currentNode->nextNode;
		}
	}
	return 0;
}

template <class E>
E SinglyLinkedList<E>::removeAt(unsigned int i) {
	if (size == 0 || i >= size)
		return 0;
	if (i == 0)
		return removeHead();
	if (i == (size - 1))
		return removeTail();

	SinglyLinkedNode<E>* currentNode = head;
	for (unsigned int j = 1; j < i; j++)
		currentNode = currentNode->nextNode;
	E data = currentNode->nextNode->data;
	SinglyLinkedNode<E>* nodeToDelete = currentNode->nextNode;
	currentNode->nextNode = currentNode->nextNode->nextNode;
	delete(nodeToDelete);
	size--;
	return data;
}

template <class E>
E SinglyLinkedList<E>::removeHead() {
	if (size == 0)
		return 0;
	if (size == 1) {
		E data = head->data;
		delete(head);
		size--;
		return data;
	}
	if (size == 2) {
		E data = head->data;
		SinglyLinkedNode<E>* newHead = head->nextNode;
		delete(head);
		head = newHead;
		tail = newHead;
		size--;
	}
	SinglyLinkedNode<E>* newHead = head->nextNode;
	E data = head->data;
	delete head;
	head = newHead;
	size--;
	return data;
}

template <class E>
E SinglyLinkedList<E>::removeTail() {
	if (size == 0)
		return 0;
	if (size == 1)
		return removeHead();
	if (size == 2) {
		E data = tail->data;
		delete(tail);
		tail = head;
		size--;
		return data;
	}

	SinglyLinkedNode<E>* currentNode = head;
	while (currentNode->nextNode->nextNode != nullptr)
		currentNode = currentNode->nextNode;
	E data = tail->data;
	delete(tail);
	currentNode->nextNode = nullptr;
	tail = currentNode;
	size--;
	return data;
}

template <class E>
void SinglyLinkedList<E>::clear() {
	while (size > 0)
		removeHead();
}

template <class E>
bool SinglyLinkedList<E>::isEmpty() {
	if (size == 0)
		return true;
}

template <class E>
unsigned int SinglyLinkedList<E>::getSize() {
	return size;
}

template <class E>
SinglyLinkedList<E>::~SinglyLinkedList() {
	clear();
}
