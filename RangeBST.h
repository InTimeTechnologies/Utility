#pragma once

#include "Range.h"

// Forward declarations
class RangeBSTNode;
class RangeBST;

class RangeBSTNode {
	public:
		RangeBST* rangeBST;
		RangeBSTNode* parentNode;
		RangeBSTNode* leftNode;
		RangeBSTNode* rightNode;
		Range<unsigned int> data;
	
		RangeBSTNode(const Range<unsigned int>& data);
		~RangeBSTNode();

		// Functions
		RangeBSTNode* getLeastNode();
		RangeBSTNode* getGreatestNode();
		RangeBSTNode* getRootNode();
};

class RangeBST {
	private:
		RangeBSTNode* rootNode;
		unsigned int size;
	public:
		RangeBST();
		~RangeBST();
	
		// Getters
		RangeBSTNode* getRootNode() const;
		unsigned int getSize() const;
		RangeBSTNode* getNodeWithData(unsigned int data) const;
		RangeBSTNode* getNodeWithRange(const Range<unsigned int>& range) const;
		RangeBSTNode* getLeast() const;
		RangeBSTNode* getGreatest() const;
	
		// Functions
		RangeBSTNode* add(unsigned int data);
		RangeBSTNode* add(const Range<unsigned int>& range);
	
		bool remove(unsigned int data);
		bool remove(const Range<unsigned int>& range);
		bool remove(RangeBSTNode* node);
	
		bool contains(unsigned int data) const;
		bool contains(const Range<unsigned int>& range) const;
		bool contains(RangeBSTNode* node) const;
	
		bool isEmpty() const;
	
		void clear();
};
