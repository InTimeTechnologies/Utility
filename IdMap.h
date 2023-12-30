#pragma once

// Dependencies | std
#include <utility>

class IdNode {
	// Object
	public:
		// Properties
		std::pair<int, int> m_idRange = std::pair<int, int>(0, 0);
		IdNode* m_up = nullptr;
		IdNode* m_left = nullptr;
		IdNode* m_right = nullptr;

		// Constructor / Destructor
		IdNode();
		~IdNode();

		// Functions
		IdNode* getRoot() const;
		IdNode* getLeftmostNode() const;
		IdNode* getRightmostNode() const;
};

class IdMap {
	// Object
	public:
		// Properties
		IdNode* m_rootNode = nullptr;
		int m_size = 0;

		// Constructor / Destructor
		IdMap();
		~IdMap();

		// Getters
		IdNode* rootNode() const;
		int size() const;

		// Functions
		bool addId(int id);
		bool addId(std::pair<int, int> idRange);
		bool removeId(int id);
		void removeNode(IdNode* idNode);
		void clear();
		IdNode* getNode(int id) const;
		bool has(int id) const;
};
