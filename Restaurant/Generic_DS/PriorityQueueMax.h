#pragma once
#pragma once
#include "Node.h"

template <typename T>
class PriorityQueueMax
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count;
public:
	PriorityQueueMax();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, int Pri);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	~PriorityQueueMax();
	int GetCount();
};
/////////////////////////////////////////////////////////////////////////////////////////


/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
PriorityQueueMax<T>::PriorityQueueMax()
{
	frontPtr = nullptr;
	backPtr = nullptr;
	count = 0;

}
/////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
bool PriorityQueueMax<T>::isEmpty() const
{
	if (frontPtr == nullptr )
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
bool PriorityQueueMax<T>::enqueue(const T& newEntry, int p) // rakam lee value w priority bta3o 
//byhot awel rakam fl list el 3ndo priority a2al
{
	Node<T>* P1 = new Node<T>(newEntry);
	P1->setPriority(p);

	if (frontPtr == nullptr)
	{
		frontPtr = P1;
		P1->setNext(nullptr);

	}
	else if (p > frontPtr->getPriority())
	{
		Node<T>* P2 = new Node<T>;
		P2 = frontPtr;
		frontPtr = P1;
		P1->setNext(P2);
	}
	else
	{
		Node<T>* P3 = new Node<T>;
		P3 = frontPtr;
		while (P3->getNext() && P3->getNext()->getPriority() > p)
		{
			P3 = P3->getNext();
		}

		Node<T>* temp = new Node<T>;
		temp = P3->getNext();
		P3->setNext(P1);
		P1->setNext(temp);
	}
	count++;
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
bool PriorityQueueMax<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;


	frntEntry = frontPtr->getItem();
	Node<T>* temp = new Node<T>;
	temp = frontPtr;
	frontPtr = frontPtr->getNext();
	delete temp;
	count--;
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
bool PriorityQueueMax<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueueMax<T>::~PriorityQueueMax()
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
T* PriorityQueueMax<T>::toArray(int& count)
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
template <typename T>
int PriorityQueueMax<T>::GetCount()
{
	return count;
}



