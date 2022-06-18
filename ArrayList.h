#pragma once

template <class T>
class ArrayList {
	public:
		T* genericArray;
		unsigned int size;
		unsigned int capacity;
		
		ArrayList();
		ArrayList(unsigned int capacity);
		ArrayList(T* data, unsigned int size, unsigned int capacity);
		ArrayList(const ArrayList& arrayList);

		void operator = (const ArrayList& otherArrayList);

		void set(T element, unsigned int i);
		void add(T element);
		T get(unsigned int i);
		void resizeCapacity(unsigned int capacity);

		unsigned int getSize();
		unsigned int getCapacity();

		~ArrayList();
};

template <class T>
ArrayList<T>::ArrayList() {
	genericArray = new T[1];
	size = 0;
	capacity = 1;
}

template <class T>
ArrayList<T>::ArrayList(unsigned int capacity) {
	genericArray = new T[capacity];
	size = 0;
	this->capacity = capacity;
}

template <class T>
ArrayList<T>::ArrayList(T* data, unsigned int size, unsigned int capacity) {
	if (capacity < size)
		capacity = size;
	genericArray = new T[capacity];
	this->size = size;
	this->capacity = capacity;

	for (unsigned int i = 0; i < size; i++)
		genericArray[i] = data[i];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList& arrayList) {
	genericArray = new T[arrayList.capacity];
	for (unsigned int i = 0; i < arrayList.size; i++)
		genericArray[i] = arrayList.genericArray[i];
	size = arrayList.size;
	capacity = arrayList.capacity;
}

template <class T>
void ArrayList<T>::operator = (const ArrayList<T>& otherArrayList) {
	genericArray = new T[capacity];
	for (unsigned int i = 0; i < size; i++)
		genericArray[i] = otherArrayList.genericArray[i];
	size = otherArrayList.size;
	capacity = otherArrayList.size;
}

template <class T>
void ArrayList<T>::set(T element, unsigned int i) {
	if (i >= size)
		return;
	genericArray[i] = element;
}

template <class T>
unsigned int ArrayList<T>::getSize() {
	return size;
}

template <class T>
unsigned int ArrayList<T>::getCapacity() {
	return capacity;
}

template <class T>
void ArrayList<T>::add(T element) {
	if (size == capacity)
		resizeCapacity(capacity * 2);
	set(element, size++);
}

template <class T>
T ArrayList<T>::get(unsigned int i) {
	if (i >= size)
		return 0;
	return genericArray[i];
}

template <class T>
void ArrayList<T>::resizeCapacity(unsigned int capacity) {
	T* oldGenericArray = genericArray;
	unsigned int oldSize = size;
	unsigned int oldCapacity = this->capacity;

	if (capacity == 0)
		capacity = 1;

	genericArray = new T[capacity];
	for (unsigned int i = 0; i < capacity; i++)
		genericArray[i] = oldGenericArray[i];
	if (oldSize > capacity)
		size = capacity;
	this->capacity = capacity;

	delete[] oldGenericArray;
}

template <class T>
ArrayList<T>::~ArrayList() {
	delete[] genericArray;
}
