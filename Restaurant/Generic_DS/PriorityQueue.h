#pragma once
#include "Node.h"

template <typename T>
class PriorityQueue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, int Pri = 0);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	~PriorityQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////


/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	frontPtr = nullptr;
	backPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr || backPtr == nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, int pri) // rakam lee value w priority bta3o 
//byhot awel rakam fl list el 3ndo priority a2al
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	newNodePtr->setPriority(pri);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	return true;

} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	Node<T>* temp = frontPtr;
	//Search for node with highest Priority 
	while (temp)
	{
		if (nodeToDeletePtr->getPriority() < temp->getPriority())
		{
			nodeToDeletePtr = temp;
		}
		temp = temp->getNext();
	}
	//if nodetoDeletePtr is FrontPtr
	if (nodeToDeletePtr == frontPtr)
	{
		frontPtr = frontPtr->getNext();
		frntEntry = nodeToDeletePtr->getItem();
		delete nodeToDeletePtr;
		return true;
	}

	// Here you have the node to DeletePtr
	// you reset the pointer
	//Search for  node before this node 
	temp = frontPtr;
	while (temp->getNext() != nodeToDeletePtr)
	{
		temp = temp->getNext();
	}
	temp->setNext(nodeToDeletePtr->getNext());

	frntEntry = nodeToDeletePtr->getItem();
	delete nodeToDeletePtr;

	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PriorityQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/

template <typename T>
T* PriorityQueue<T>::toArray(int& count)
{
	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

