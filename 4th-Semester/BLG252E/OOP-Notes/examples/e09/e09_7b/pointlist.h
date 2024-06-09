// pointlist.h for e07_19
// Definition of PointList class

// You don’t need to create your own classes for linked lists. std::list is already defined in the standard library.
// <list>
// We provide this example for educational purposes.

#pragma once

#include "node.h"

// *** The list consists of nodes
class PointList{
public:
	PointList();					// Default constructor creates an empty list
	~PointList();                   // Destructor deletes all nodes of the list
	void append(Point *);			// Add a point to the end of the list
	void printAll() const;			// Print all elements (points) in the list
private:
	Node* m_head{};					// The pointer to the first node in the list
};