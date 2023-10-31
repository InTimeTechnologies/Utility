#pragma once

// Dependencies | datautil
#include "DoublyLinkedList.h"
#include "DependantInterface.h"

// Forward declarations
class Provider;

class Dependant {
	// Friends
	friend class Provider;
	public:
		// Properties
		DependantInterface* dependantInterface;
		Provider* provider;
		DoublyLinkedNode<Dependant*>* dependantNode;

		// Constructor / Destructor
		Dependant();
		Dependant(DependantInterface* owner);
		virtual ~Dependant();

		// Getters
		DependantInterface* getOwner();
		Provider* getProvider();

		// Setters
		void setProvider(Provider* provider);
};
