#include "IdServer.h"

// class IdServer

// Static | public

// Properties
int IdServer::defaultIdCount = 10;

// Object | publis

// Constructor / Destructor
IdServer::IdServer() {
	idCount = defaultIdCount == 0 ? 1 : defaultIdCount;
	idMap.addId(std::pair<int, int>(0, idCount - 1));
}
IdServer::IdServer(int idCount) {
	this->idCount = idCount == 0 ? 1 : idCount;
	idMap.addId(std::pair<int, int>(0, idCount - 1));
}
IdServer::~IdServer() {

}

// Getters
int IdServer::getIdCount() const {
	return idCount;
}

// Functions
int IdServer::requestId() {
	if (idMap.size() == 0)
		increaseSize(idCount);

	return idMap.extractLeast();
}
bool IdServer::submitId(int id) {
	return idMap.addId(id);
}

// Object | private

// Functions
void IdServer::increaseSize(int size) {
	idMap.addId(std::pair<int, int>(idCount, idCount * 2 - 1));
	idCount *= 2;
}
