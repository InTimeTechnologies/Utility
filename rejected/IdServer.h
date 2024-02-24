#pragma once

// Dependencies | utility
#include "IdMap.h"

class IdServer {
	// Static
	public:
		// Properties
		static int defaultIdCount;

	// Object
	private:
		// Properties
		IdMap idMap = IdMap();
		int idCount = 0;

	public:
		// Constructor / Destructor
		IdServer();
		IdServer(int idCount);
		~IdServer();

		// Getters
		int getIdCount() const;

		// Functions
		int requestId();
		bool submitId(int id);

	private:
		// Functions
		void increaseSize(int size);
};
