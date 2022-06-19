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
		Array(const Array& otherArrayObject);               // O(n)
		
		void operator = (const Array& otherArrayObject);    // O(n)

		void set(T element, unsigned int i);                // O(1)
		T get(unsigned int i);                              // O(1)
		T* getArray();                                      // O(1)
		unsigned int getSize();                             // O(1)

		~Array();
};

template <class T>
Array<T>::Array() {
	genericArray = new T[1];
	size = 1;
}

template <class T>
Array<T>::Array(unsigned int size) {
	genericArray = new T[size];
	this->size = size;
}

template <class T>
Array<T>::Array(unsigned int size, T* data) : Array<T>(size) {
	for (unsigned int i = 0; i < size; i++)
		genericArray[i] = data[i];
}

template <class T>
Array<T>::Array(const Array<T>& otherArrayObject) : Array<T>(otherArrayObject.size, otherArrayObject.genericArray) {
	
}

template <class T>
void Array<T>::operator = (const Array<T>& otherArrayObject) {
	this->genericArray = new T[otherArrayObject.size];
	size = otherArrayObject.size;
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

