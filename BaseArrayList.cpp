#include "BaseArrayList.h"

// Static | protected
// Properties
const unsigned int BaseArrayList::MINIMUM_CAPACITY = 2;
unsigned int BaseArrayList::defaultCapacity = 2;

// Static | public
// Setters
void BaseArrayList::setDefaultCapacity(unsigned int capacity) {
	if (capacity >= BaseArrayList::MINIMUM_CAPACITY)
		return;
	BaseArrayList::defaultCapacity = capacity;
}

// Getters
unsigned int BaseArrayList::getMinimumCapacity() {
	return MINIMUM_CAPACITY;
}
unsigned int BaseArrayList::getDefaultCapacity() {
	return defaultCapacity;
}
