#pragma once

template <class T>
class Array {
	public:
		T* genericArray;
		unsigned int size;

		Array();
		Array(unsigned int size);
		Array(unsigned int size, T* data);
		Array(const Array& genericArray);

		void set(T element, unsigned int i);
		T get(unsigned int i);

		unsigned int getSize();

		void operator = (const Array& otherArray);

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
Array<T>::Array(const Array& genericArray) {
	genericArray = new T[genericArray.size];
	size = genericArray.size;
}

template <class T>
void Array<T>::set(T element, unsigned int i) {
	if (i >= size)
		return;
	genericArray[i] = T;
}

template <class T>
T Array<T>::get(unsigned int i) {
	return genericArray[i];
}

template <class T>
unsigned int Array<T>::getSize() {
	return size;
}

template <class T>
void Array<T>::operator = (const Array<T>& otherArray) {
	genericArray = new Array[otherArray.size];
	size = otherArray.size;
}

template <class T>
Array<T>::~Array() {
	delete[] genericArray;
}

