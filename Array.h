#pragma once

template <class T>
class Array {
	private:
		// Properties
		unsigned int size;
		T* genericArray;
	public:
		// Constructors / Destructor
		Array();
		Array(unsigned int size);                           // O(1)
		Array(unsigned int size, T* data);                  // O(n)
		Array(const Array& otherArray);                     // O(n)
		void operator = (const Array& otherArray);          // O(n)
		~Array();

		// Getters
		unsigned int getSize();                             // O(1)
		T* getArray();                                      // O(1)
		T get(unsigned int i);                              // O(1)

		// Setters
		void set(T element, unsigned int i);                // O(1)
};

// Constructors / Destructor
template <class T>
Array<T>::Array() {
	size = 2;
	genericArray = new T[size];
}
template <class T>
Array<T>::Array(unsigned int size) {
	if (size == 0) {
		this->size = 0;
		genericArray = nullptr;
		return;
	}

	this->size = size;
	this->genericArray = new T[size];
}
template <class T>
Array<T>::Array(unsigned int size, T* data) {
	if (size == 0 || data == nullptr) {
		genericArray = nullptr;
		size = 0;
		return;
	}

	this->size = size;
	this->genericArray = new T[size];

	for (unsigned int i = 0; i < size; i++)
		genericArray[i] = data[i];
}
template <class T>
Array<T>::Array(const Array<T>& otherArray) {
	if (otherArray.size == 0 || otherArray.genericArray == nullptr) {
		genericArray = nullptr;
		size = 0;
		return;
	}

	this->size = otherArray.size;
	this->genericArray = new T[otherArray.size];

	for (unsigned int i = 0; i < otherArray.size; i++)
		genericArray[i] = otherArray.genericArray[i];
}
template <class T>
void Array<T>::operator = (const Array<T>& otherArray) {
	if (otherArray.size == 0 || otherArray.genericArray == nullptr) {
		genericArray = nullptr;
		size = 0;
		return;
	}

	this->size = otherArray.size;
	this->genericArray = new T[otherArray.size];

	for (unsigned int i = 0; i < otherArray.size; i++)
		genericArray[i] = otherArray.genericArray[i];
}
template <class T>
Array<T>::~Array() {
	delete[] genericArray;
}

// Getters
template <class T>
unsigned int Array<T>::getSize() {
	return size;
}
template <class T>
T* Array<T>::getArray() {
	return genericArray;
}
template <class T>
T Array<T>::get(unsigned int i) {
	return genericArray[i];
}


// Setters
template <class T>
void Array<T>::set(T element, unsigned int i) {
	if (i >= size)
		return;
	genericArray[i] = element;
}
