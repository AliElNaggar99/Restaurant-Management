#ifndef __LIST_H_
#define __LIST_H_

#include"Node.h"
#include"../Rest/Order.h"

template <typename T>
class BaseList
{
protected:
	Node<T>* First;
	Node<T>* Last;
	int count = 0;
public:
	BaseList() {
		First = nullptr;
		Last = nullptr;
	}
	//Destructor
	~BaseList()
	{
	   DeleteAll();
	}

	bool isEmpty() const {
		if (First == nullptr) return true;
		return false;
	}

	bool InsertFirst(const T& newEntry)
	{
		Node<T>* temp = new Node<T>(newEntry);
		temp->setNext(First);
		First = temp;
		count++;
		return true;
	}


	// insert in last of the List
	bool InsertLast(const T& newEntry) {
		Node<T>* newNodePtr = new Node<T>(newEntry);
		if (isEmpty())
			First = newNodePtr;
		else
			Last->setNext(newNodePtr);
		Last = newNodePtr;
		count++;
		return true;
	}
	// Remove First of the list
	bool RemoveFirst(T& frntEntry) {

		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = First;
		frntEntry = First->getItem();
		First = First->getNext();

		if (nodeToDeletePtr == Last)
			Last = nullptr;

		delete nodeToDeletePtr;

		count--;
		return true;
	}
	bool ReturnFirst(T& frntEntry)  const {
		if (isEmpty())
			return false;

		frntEntry = First->getItem();
		return true;
	}
	
	//inserting in a specific Pos
	void insertPos(T data, int Pos)
	{
		Node<T>* P1 = new Node <T>;
		P1->setItem(data); P1->setNext(nullptr);
		if (Pos == 1) {
			P1->setNext(First);
			First = P1;
			count++;
			return;
		}
		Node<T>* P2 = First;
		for (int i = 0; i < Pos - 2; i++) {
			P2 = P2->getNext();
		}
		P1->setNext(P2->getNext());
		P2->setNext(P1);
	}
	//Adjusting the DeleteFirst to return Delete Node
	bool DeleteFirst()
	{
		if (First)
		{
			Node<T>* temp = First;
			First = First->getNext();
			delete temp;
			count--;
			return true;
		}
		else
			return false;

	}

	//Delete a node from a list
	bool DeleteNode(const T& value)
	{
		Node <T>* temp = First;
		while (temp)
		{
			if (temp->getItem() == value)
			{
				First = temp->getNext();
				delete temp;
				count--;
				return true;

			}
			if (temp->getNext() && temp->getNext()->getItem() == value)
			{
				Node <T>* temp2 = temp->getNext();
				temp->setNext(temp->getNext()->getNext());
				delete temp2;
				count--;
				return true;
			}
			temp = temp->getNext();
		}
		return false;
	}
	void DeleteAll()
	{
		Node<T>* P1 = First;
		while (First)
		{
			P1 = First->getNext();
			delete First;
			First = P1;
		}
		count = 0;
	}

	int GetCount()
	{
		return count;
	}

	//For Printing
	T* toArray(int& count)
	{
		count = 0;

		if (!First)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = First;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = First;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}

	//to find an element in the List

	/*bool findPos(T& data, int i)
	{
		Node<T>* temp = First;
		int inital = 0;

		if (i >= count)
			return false;

		while (inital != i)
		{
			inital++;
			temp = temp->getNext();

		}
		data = temp->getItem();

		return true;

	}*/

};

template< class T >
class List : public BaseList<T> {
	//List that works for all Data type

};


template<>
class List<Order*> :public  BaseList<Order*> {
	// List that is partially specialized for the order data type


	Node<Order*>* SearchandReturnPrev(int OrderID);
public:


	Node<Order*>* SearchForOrder(int OrderID);
	Node<Order*>* RemoveOrderFromList(int OrderID);

};



inline Node<Order*>* List<Order*>::SearchandReturnPrev(int id)
{
	// Doesnt work on 1st node so have to be done manually as 1st doesnt have previous
	if (First == nullptr) return nullptr;
	Node<Order*>* TravPtr = First;
	while (TravPtr->getNext() != nullptr) 
	{

		if (TravPtr->getNext()->getItem()->GetID() == id) 
			return TravPtr;

		TravPtr = TravPtr->getNext();

	}
	return nullptr;

}


inline Node<Order*>* List<Order*>::SearchForOrder(int id) {
	if (First->getItem()->GetID() == id) return First;

	Node<Order*>* Prev = SearchandReturnPrev(id);
	return (Prev != nullptr) ? Prev->getNext() : nullptr;

}



inline Node<Order*>* List<Order*>::RemoveOrderFromList(int id) {
	if (isEmpty()) return nullptr;
	
	if (First->getItem()->GetID() == id) {

		Node<Order*>* TEMP = First;
		First = First->getNext();
		if (TEMP == Last) Last = nullptr;
		count = count - 1;
		return TEMP;
	}

	Node<Order*>* Prev = SearchandReturnPrev(id);

	if (Prev != nullptr) 
	{

		Node<Order*>* TEMP = Prev->getNext();
		Prev->setNext(TEMP->getNext());

		if (TEMP == Last && First == TEMP)
			Last = nullptr;
		else if (TEMP == Last)
			Last = Prev;

		count = count - 1;
		return TEMP;


	}
	return nullptr;
}




#endif // !_LIST_H_
















