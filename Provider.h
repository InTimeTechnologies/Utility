#pragma once

// Dependencies | std
#include <vector>

// Dependencies | datautil
#include "DoublyLinkedList.h"
#include "ProviderInterface.h"

// Forward declarations | Dependant
class Dependant;

class Provider {
	// Friends
	friend class Dependant;
	public:
		// Properties
		ProviderInterface* providerInterface;
		DoublyLinkedList<Dependant*> dependants;

		// Constructor / Destructor
		Provider();
		Provider(ProviderInterface* providerInterface);
		virtual ~Provider();
		
		// Getters
		std::vector<Dependant*> getDependants();

		// Functions
		void clearDependants();
};
