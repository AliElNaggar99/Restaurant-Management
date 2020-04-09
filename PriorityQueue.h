#pragma once
#include "Generic_DS/Node.h"

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
bool PriorityQueue<T>::enqueue(const T& newEntry, int pri = 0) // rakam lee value w priority bta3o 
//byhot awel rakam fl list el 3ndo priority a2al
{
	Node<T>*P1 = new Node<T>(newEntry); // A pointer and a value for a new node 
	P1->setPriority(pri);
	if (frontPtr == nullptr || pri < frontPtr->getPriority()) // de lw el linked fadya aw el condition el tany b2a 
	{
		P1->setNext(frontPtr); frontPtr = P1;
	}
	else {
		Node<T>* P2 = frontPtr; // 
		while (P2->getNext() != nullptr && P2->getNext()->getPriority() <= pri)
		{
			P2 = P2->getNext();
		}
		P1->setNext(P2->getNext());
		P2->setNext(P1);

	}
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
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = frontPtr = nullptr;

	// Free memory reserved by the dequeued node
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
