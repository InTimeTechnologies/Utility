#pragma once

// Dependencies | std
#include <list>
#include <utility>

class IdServer {
	// Object
	private:
		// Properties
		std::list<std::pair<int, int>> idRangeList = std::list<std::pair<int, int>>();
		int registeredIdsCount = 1;
		int idsAvailableCount = 1;

	public:
		// Constructor / Destructor
		IdServer();
		IdServer(int idCount);
		~IdServer();

		// Getters
		std::list<std::pair<int, int>> getIdRangeList() const;
		int getRegisteredIdsCount() const;
		int getIdsAvailableCount() const;

		// Functions
		bool increaseIdLimit(int idAmount);
		int requestId();
		bool submitId(int id);
};
