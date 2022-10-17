#pragma once

#include "BaseArrayList.h"

template <class T>
class ArrayList : public BaseArrayList {
	// Object
	private:
		// Properties
		unsigned int capacity;
		unsigned int size;
		T* genericArray;
	public:
		// Constructors / Destructor
		ArrayList();
		ArrayList(unsigned int capacity);
		ArrayList(unsigned int capacity, unsigned int size, T* elements);
		void operator = (const ArrayList& otherArrayList);
		~ArrayList();

		// Setters
		void setCapacity(unsigned int capacity);
		void setSize(unsigned int size);
		void set(unsigned int i, T element);

		// Getters
		unsigned int getCapacity();
		unsigned int getSize();
		T* getGenericArray();
		T get(unsigned int i);

		// Functions
		void add(T element);
		void addAt(unsigned int i, T element);

		void remove(T element);
		void removeAt(unsigned int i);

		void rebuildArray();
};

// Object | public
// Constructors / Destructors
template <class T>
ArrayList<T>::ArrayList() {
	capacity = defaultCapacity;
	size = 0;
	genericArray = new T[capacity];
}
template <class T>
ArrayList<T>::ArrayList(unsigned int capacity) {
	if (capacity < defaultCapacity)
		capacity = defaultCapacity;
	this->capacity = capacity;
	size = 0;
	genericArray = new T[capacity];
}

template <class T>
ArrayList<T>::ArrayList(unsigned int capacity, unsigned int size, T* elements) {
	if (capacity < defaultCapacity)
		capacity = defaultCapacity;
	if (size < capacity)
		size = capacity;
	this->capacity = capacity;
	this->size = size;
	genericArray = new T[capacity];

	if (elements == nullptr)
		return;

	for (unsigned int i = 0; i < size; i++)
		genericArray[i] = elements[i];
}

template <class T>
void ArrayList<T>::operator = (const ArrayList<T>& otherArrayList) {
	capacity = otherArrayList.capacity;
	size = otherArrayList.size;
	if (genericArray != nullptr)
		delete(genericArray);
	genericArray = new T[capacity];

	for (unsigned int i = 0; i < size; i++)
		genericArray[i] = otherArrayList.genericArray[i];
}

template <class T>
ArrayList<T>::~ArrayList() {
	delete[] genericArray;
}

// Setters
template <class T>
void ArrayList<T>::setCapacity(unsigned int capacity) {
	if (capacity < defaultCapacity)
		capacity = defaultCapacity;
	this->capacity = capacity;
	if (size > capacity)
		size = capacity;

	T* tempGenericArray = new T[capacity];
	for (unsigned int i = 0; i < size; i++)
		tempGenericArray[i] = genericArray[i];

	delete[] genericArray;
	genericArray = tempGenericArray;
}

template <class T>
void ArrayList<T>::setSize(unsigned int size) {
	if (size > capacity)
		return;
	this->size = size;
}

template <class T>
void ArrayList<T>::set(unsigned int i, T element) {
	if (i > size)
		return;
	genericArray[i] = element;
}

// Getters
template <class T>
unsigned int ArrayList<T>::getCapacity() {
	return capacity;
}

template <class T>
unsigned int ArrayList<T>::getSize() {
	return size;
}

template <class T>
T* ArrayList<T>::getGenericArray() {
	return genericArray;
}

template <class T>
T ArrayList<T>::get(unsigned int i) {
	if (i > size)
		size = 0;
	return genericArray[i];
}

// Functions
template <class T>
void ArrayList<T>::add(T element) {
	if (size == capacity)
		setCapacity(capacity * 2);
	genericArray[size++] = element;
}

template <class T>
void ArrayList<T>::addAt(unsigned int i, T element) {
	if (size == capacity)
		setCapacity(capacity * 2);
	if (size == 0) {
		genericArray[0] = element;
		return;
	}
	if (i == size) {
		genericArray[size++];
		return;
	}
	
	// Shift elements, then add element to i
	for (unsigned int j = size; j >= i; j--)
		genericArray[j] = genericArray[j - 1];
	genericArray[i] = element;
	size++;
}

template <class T>
void ArrayList<T>::remove(T element) {
	if (size == 0)
		return;
	if (size == 1) {
		size--;
		return;
	}

	// Search for element, then shift leftover elements one index towards it
	for (unsigned int i = 0; i < size; i++)
		if (element == genericArray[i])
			for (; i < size - 1; i++)
				genericArray[i] = genericArray[i + 1];
	size--;
}

template <class T>
void ArrayList<T>::removeAt(unsigned int i) {
	if (size == 0)
		return;
	if (size == 1) {
		size--;
		return;
	}

	// Search for element, then shift leftover elements one index towards it
	for (; i < size - 1; i++)
		genericArray[i] = genericArray[i + 1];
	size--;
}

template <class T>
void ArrayList<T>::rebuildArray() {
	T* newGenericArray = new T[capacity];
	for (unsigned int i = 0; i < size; i++)
		newGenericArray[i] = genericArray[i];
	delete[] genericArray;
	genericArray = newGenericArray;
}
