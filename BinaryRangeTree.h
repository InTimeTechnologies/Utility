#pragma once

// Dependencies | std
#include <utility>

// Forwward declarations | Utility
template <typename T> class BinaryRangeNode;
template <typename T> class BinaryRangeTree;

// class BinaryRangeNode
template <typename T> class BinaryRangeNode {
	// Object
	private:
		// Properties
		BinaryRangeTree<T>* binaryRangeTree;
		BinaryRangeNode<T>* parentNode;
		BinaryRangeNode<T>* leftNode;
		BinaryRangeNode<T>* rightNode;
		std::pair<T, T> data;
	public:
		// Constructor / Destructur
		BinaryRangeNode();
		BinaryRangeNode(std::pair<T, T> data);
		BinaryRangeNode(const BinaryRangeNode<T>& binaryRangeNode);
		void operator = (const BinaryRangeNode<T>& binaryRangeNode);
		~BinaryRangeNode();

		// Getters
		BinaryRangeTree<T>* getBinarySearchTree();
		BinaryRangeNode<T>* getParentNode();
		BinaryRangeNode<T>* getLeftNode();
		BinaryRangeNode<T>* getRightNode();
		std::pair<T, T> getData();

		// Setters
		bool setData(std::pair<T, T> data);

		// Functions
		BinaryRangeNode<T>* getLeftmostNode();
		BinaryRangeNode<T>* getRightmostNode();
		BinaryRangeNode<T>* add(std::pair<T, T> data);
		BinaryRangeNode<T>* get(std::pair<T, T> data);
		bool has(std::pair<T, T> data);
		bool remove(std::pair<T, T> data);
		void destroy();
};

// class BinaryRangeTree
template <typename T> class BinaryRangeTree {
	// Object
	private:
		// Properties
		unsigned long long size;
		BinaryRangeNode<T>* rootNode;
	public:
		// Constructor / Destructor
		BinaryRangeTree();
		~BinaryRangeTree();

		// Getters
		unsigned long long getSize();
		BinaryRangeNode<T>* getRootNode();

		// Functions
		BinaryRangeNode<T>* add(std::pair<T, T> data);
		BinaryRangeNode<T>* add(T data);
		BinaryRangeNode<T>* add(BinaryRangeNode<T>* binaryRangeNode);
		BinaryRangeNode<T>* get(std::pair<T, T> data) const;
		BinaryRangeNode<T>* get(T data) const;
		bool has(std::pair<T, T> data) const;
		bool has(T data) const;
		void clear();
};

// class BinaryRangeNode

// Object | public

// Constructor / Destructor
template <typename T> BinaryRangeNode<T>::BinaryRangeNode() : binaryRangeTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr) {

}
template <typename T> BinaryRangeNode<T>::BinaryRangeNode(std::pair<T, T> data) : binaryRangeTree(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(data) {

}
template <typename T> BinaryRangeNode<T>::BinaryRangeNode(const BinaryRangeNode<T>& binaryRangeNode) : parentNode(nullptr), parentNode(nullptr), leftNode(nullptr), rightNode(nullptr), data(binaryRangeNode->data) {

}
template <typename T> void BinaryRangeNode<T>::operator = (const BinaryRangeNode<T>& binaryRangeNode) {
	data = binaryRangeNode->data;
}
template <typename T> BinaryRangeNode<T>::~BinaryRangeNode() {

}
