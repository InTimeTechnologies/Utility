#pragma once

template <class T>
class Array {
	private:
		T* genericArray;
		unsigned int size;
	public:
		Array();
		Array(unsigned int size);
		Array(unsigned int size, T* data);
		Array(const Array& otherArray);                     // O(n)
		
		void operator = (const Array& otherArray);          // O(n)

		void set(T element, unsigned int i);                // O(1)
		T get(unsigned int i);                              // O(1)
		T* getArray();                                      // O(1)
		unsigned int getSize();                             // O(1)

		~Array();
};

template <class T>
Array<T>::Array() {
	genericArray = nullptr;
	size = 0;
}

template <class T>
Array<T>::Array(unsigned int size) {
	if (size == 0) {
		genericArray = nullptr;
		this->size = 0;
		return;
	}
	genericArray = new T[size];
	this->size = size;
}

template <class T>
Array<T>::Array(unsigned int size, T* data) {
	if (size == 0 || data == nullptr) {
		genericArray = nullptr;
		size = 0;
		return;
	}
	genericArray = new T[size];
	this->size = size;
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
	genericArray = new T[otherArray.size];
	this->size = otherArray.size;
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
	genericArray = new T[otherArray.size];
	for (unsigned int i = 0; i < otherArray.size; i++)
		genericArray = otherArray.genericArray[i];
	size = otherArray.size;
}

template <class T>
void Array<T>::set(T element, unsigned int i) {
	if (i >= size)
		return;
	genericArray[i] = element;
}

template <class T>
T Array<T>::get(unsigned int i) {
	return genericArray[i];
}

template <class T>
T* Array<T>::getArray() {
	return genericArray;
}

template <class T>
unsigned int Array<T>::getSize() {
	return size;
}

template <class T>
Array<T>::~Array() {
	delete[] genericArray;
}

