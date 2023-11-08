#include "Dependant.h"

// Dependencies | provider
#include "Provider.h"

// class Dependant

// Object | public

// Constructor / Destructor
Dependant::Dependant() : Dependant(nullptr) {}
Dependant::Dependant(DependantInterface* owner) : dependantInterface(owner), provider(nullptr), dependantNode(nullptr) {}
Dependant::~Dependant() {
	// If dependant is not assigned to a provider, return
	if (dependantNode == nullptr)
		return;
	
	// Remove node from provider's list
	delete(dependantNode);
	dependantNode = nullptr;
}

// Getters
DependantInterface* Dependant::getOwner() {
	return dependantInterface;
}
Provider* Dependant::getProvider() {
	return provider;
}

// Setters
void Dependant::setProvider(Provider* provider) {
	// If provider == nullptr, remove from list if assigned to a list
	this->provider = provider;
	if (provider == nullptr) {
		if (dependantNode != nullptr) {
			delete(dependantNode);
			dependantNode = nullptr;
			if (dependantInterface != nullptr)
				dependantInterface->onProviderUnset();
		}
		return;
	}

	// Add to provider's list of dependants
	dependantNode = provider->dependants.addRightmostNode(this);
	if (dependantInterface != nullptr)
		dependantInterface->onProviderSet();
}
