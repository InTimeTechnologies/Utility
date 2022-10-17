#pragma once

class BaseArrayList {
	// Static
	protected:
		// Properties
		static const unsigned int MINIMUM_CAPACITY;
		static unsigned int defaultCapacity;
	public:
		// Setters
		static void setDefaultCapacity(unsigned int capacity);

		// Getters
		unsigned int getMinimumCapacity();
		unsigned int getDefaultCapacity();
};