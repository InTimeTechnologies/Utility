#include "Provider.h"

// Dependencies | Dependant
#include "Dependant.h"

// class Provider

// Object | public

// Constructor / Destructor
Provider::Provider() : Provider(nullptr) {

}
Provider::Provider(ProviderInterface* providerInterface) : providerInterface(providerInterface), dependants(DoublyLinkedList<Dependant*>()) {

}
Provider::~Provider() {
	clearDependants();
}

// Getters
std::vector<Dependant*> Provider::getDependants() {
	std::vector<Dependant*> dependants = std::vector<Dependant*>(this->dependants.getSize());
	DoublyLinkedNode<Dependant*>* currentNode = this->dependants.getHeadNode();
	for (unsigned int i = 0U; currentNode != nullptr; i++) {
		Dependant* dependant = currentNode->data;
		dependants[i] = dependant;

		currentNode = currentNode->nextNode;
	}
	return dependants;
}

// Functions
void Provider::clearDependants() {
	while (dependants.getSize() > 0) {
		DoublyLinkedNode<Dependant*>* dependantNode = dependants.getHeadNode();
		Dependant* dependant = dependantNode->data;
		dependant->setProvider(nullptr);
	}
}
