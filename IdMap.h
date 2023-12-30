#pragma once

// Dependencies | std
#include <utility>

// Forward declarations | utility
class IdNode;
class IdMap;

class IdNode {
	// Object
	public:
		// Properties
		std::pair<int, int> m_idRange = std::pair<int, int>(0, 0);
		IdMap* owner = nullptr;
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
	private:
		// Properties
		IdNode* m_rootNode = nullptr;
		int m_size = 0;

	public:
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
		bool removeNode(IdNode* idNode);
		int extractLeast();
		int extractGreatest();
		void clear();
		IdNode* getNode(int id) const;
		bool has(int id) const;
};
