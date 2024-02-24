#include "IdServer.h"

// class IdServer

// Object | public

// Consturctor / Destructor
IdServer::IdServer() {
	idRangeList.push_back(std::pair<int, int>(0, 0));
	registeredIdsCount = 1;
	idsAvailableCount = 1;
}
IdServer::IdServer(int idCount) {
	if (idCount <= 0)
		idCount = 1;

	idRangeList.push_back(std::pair<int, int>(0, idCount - 1));
	registeredIdsCount = idCount;
	idsAvailableCount = idCount;
}
IdServer::~IdServer() {

}

// Getters
std::list<std::pair<int, int>> IdServer::getIdRangeList() const {
	return idRangeList;
}
int IdServer::getRegisteredIdsCount() const {
	return registeredIdsCount;
}
int IdServer::getIdsAvailableCount() const {
	return idsAvailableCount;
}


// Functions
bool IdServer::increaseIdLimit(int idAmount) {
	// Error check
	if (idAmount <= 0)
		return false;

	// New id range to be adding to the list
	std::pair<int, int> newIdRange = std::pair<int, int>(registeredIdsCount, registeredIdsCount + idAmount - 1);

	// If the list is empty, add this range as a new node
	if (idRangeList.size() == 0)
		idRangeList.push_back(newIdRange);
	// Check if to add to the last node or to edit the last node
	else {
		std::pair<int, int> lastIdRange = *std::prev(idRangeList.end());
		if (lastIdRange.second == registeredIdsCount - 1)
			// Edit last node by extending its range
			lastIdRange.second = newIdRange.second;
		else
			// Add new range as a new ndoe
			idRangeList.push_back(newIdRange);
	}
	
	// Increase size of availabled ids and registered ids
	registeredIdsCount += idAmount;
	idsAvailableCount += idAmount;


	return true;
}
int IdServer::requestId() {
	// If idRangeList is empty, double the limit of ids it can hold
	if (idRangeList.size() == 0)
		increaseIdLimit(registeredIdsCount);

	// Get the least id from the leftmost node
	std::list<std::pair<int, int>>::iterator leastNode = idRangeList.begin();
	std::pair<int, int> leastIdRange = *leastNode;
	int leastId = leastIdRange.first;

	// Edit the leftmostnode to reflect that the id was removed
	(*leastNode).first++;
	if ((*leastNode).first > (*leastNode).second)
		idRangeList.pop_front();

	// Update idsAvailable
	idsAvailableCount--;

	// Return the least id
	return leastId;
}
bool IdServer::submitId(int id) {
	// Error check
	if (id < 0 || id >= registeredIdsCount)
		return false;

	// Check if idRangeList is empty
	if (idsAvailableCount == 0) {
		// Add id to the list (anywhere because the list is empty)
		idRangeList.push_back(std::pair<int, int>(id, id));
		idsAvailableCount++;
		return true;
	}

	// Current node
	std::list<std::pair<int, int>>::iterator currentNode = idRangeList.begin();

	while (currentNode != idRangeList.end()) {
		// Current id range at hand
		std::pair<int, int> currentIdRange = *currentNode;
		
		// Error check
		if (id >= currentIdRange.first && id <= currentIdRange.second)
			return false;

		// Check if this id can extend the current node's range to the left
		if (id + 1 == currentIdRange.first) {
			// Extend this id range's lower end
			currentIdRange.first = id;
			*currentNode = currentIdRange;

			// Check if you can move to the left
			if (currentNode != idRangeList.begin()) {
				// Check if this new id range can merge with the left nodes's range
				std::list<std::pair<int, int>>::iterator leftNode = std::prev(currentNode);
				std::pair<int, int> leftIdRange = *leftNode;
				if (leftIdRange.second == currentIdRange.first - 1) {
					// Merge this node to left node
					std::pair<int, int> newIdRange = std::pair<int, int>(0, 0);
					newIdRange.first = leftIdRange.first;
					newIdRange.second = currentIdRange.second;
					*currentNode = newIdRange;
					idRangeList.erase(leftNode);

					// Check if there is still a node to the left of the current node
					if (currentNode != idRangeList.begin()) {
						leftNode = std::prev(currentNode);
						leftIdRange = *leftNode;
						
						// Check if this node can merge with the left node now that it's bigger in range
						if (newIdRange.first - 1 == leftIdRange.second) {
							// Extend current node to the left and remove the node to its left
							newIdRange.first = leftIdRange.first;
							*currentNode = newIdRange;
							idRangeList.erase(leftNode);
						}
					}
				}
			}

			// Return success
			return true;
		}
		// Check if this id can extend the current node's range to the right
		else if (id - 1 == currentIdRange.second) {
			// Extend this id range's higher end
			currentIdRange.second = id;
			*currentNode = currentIdRange;

			// Check if you can move to the right
			if (currentNode != std::prev(idRangeList.end())) {
				// Check if this new id range can merge with the right nodes's range
				std::list<std::pair<int, int>>::iterator rightNode = std::next(currentNode);
				std::pair<int, int> rightIdRange = *rightNode;
				if (rightIdRange.first == currentIdRange.second + 1) {
					// Merge this node to the right node
					std::pair<int, int> newIdRange = std::pair<int, int>(0, 0);
					newIdRange.first = currentIdRange.first;
					newIdRange.second = rightIdRange.second;
					*currentNode = newIdRange;
					idRangeList.erase(rightNode);

					// Check if there is still a node to the right of the current node
					if (currentNode != std::prev(idRangeList.end())) {
						rightNode = std::next(currentNode);
						rightIdRange = *rightNode;
						
						// Check if this node can merge with the right node now that it's bigger in range
						if (newIdRange.second + 1 == rightIdRange.first) {
							// Extend current node to the right and remove the node to its right
							newIdRange.second = rightIdRange.second;
							*currentNode = newIdRange;
							idRangeList.erase(rightNode);
						}
					}
				}
			}

			// Return success
			return true;
		}
		// Check if this id can be added to the left of this node as a new node
		else if (id < currentIdRange.first) {
			idRangeList.insert(currentNode, std::pair<int, int>(id, id));
			return true;
		}

		// Traverse to the next node
		currentNode++;
	}

	// Check if you can add this id to the end of the list a new node
	std::pair<int, int> lastIdRange = *std::prev(idRangeList.end());
	if (id > lastIdRange.second && id < registeredIdsCount) {
		// Add this id to the end of the list
		idRangeList.push_back(std::pair<int, int>(id, id));
		return true;
	}

	// Return fail
	return false;
}
