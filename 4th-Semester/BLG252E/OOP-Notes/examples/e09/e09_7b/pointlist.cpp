// pointlist.cpp for e07_19
// Methods of the List class

// You don’t need to create your own classes for linked lists. std::list is already defined in the standard library.
// <list>
// We provide this example for educational purposes.

#include <iostream>
using std::cout;
using std::endl;
#include "pointlist.h"

// Default constructor creates an empty list
PointList::PointList() : m_head{ nullptr }
{
	cout << "PointList Constructor" << endl;
}

// Add a point to the end of the list
void PointList::append(Point* in_point)
{			
	Node *new_node = new Node{ in_point };			// A new node that point to the given point object
	Node *previous, *current;						// Pointers to move in the list
	if (m_head)        // if the list is not empty
	{
		previous = m_head;
		current = m_head->getNext();
		while (current)             // searh for the end of the list
		{
			previous = current;
			current = current->getNext();
		}
		previous->setNext(new_node);			// Put the new node to the end of the list
	}
	else             // if the list is empty
	{
		m_head = new_node;						// The new node is the first element in the list.
	}
}

// Print all elements (points) in the list
void PointList::printAll() const {
	if (m_head)							// if the list is not empty
	{
		Node* tempPtr{ m_head };		// A temporary pointer points to the first node of the list
		while (tempPtr)
		{
			tempPtr->getPoint()->print();		// POLYMORPHISM. Get a point from the node and call its print method
			tempPtr = tempPtr->getNext();		// go to the next node
			cout << "---------------" << endl;  // print a line break
		}
	}
	else
		cout << "The list is empty" << endl;
}

// Destructor
// deletes all nodes of the list
PointList::~PointList()
{
	Node* temp;
	while (m_head)        // if the list is not empty
	{
		temp = m_head;
		m_head = m_head->getNext();
		delete temp;
	}
}
// Other methods if any .............