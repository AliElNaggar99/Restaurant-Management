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
public:
	BaseList() {
		First = nullptr;
		Last = nullptr;
	}

	bool isEmpty() const {
		if (First == nullptr) return true;
		return false;
	}
	bool enqueue(const T& newEntry) {
		Node<T>* newNodePtr = new Node<T>(newEntry);
		if (isEmpty())
			First = newNodePtr;
		else
			Last->setNext(newNodePtr);
		Last = newNodePtr;
		return true;
	}
	bool dequeue(T& frntEntry) {

		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = First;
		frntEntry = First->getItem();
		First = First->getNext();

		if (nodeToDeletePtr == Last)
			Last = nullptr;

		delete nodeToDeletePtr;


		return true;
	}
	bool peekFront(T& frntEntry)  const {
		if (isEmpty())
			return false;

		frntEntry = First->getItem();
		return true;
	}



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
	while (TravPtr->getNext() != nullptr) {

		if (TravPtr->getNext()->getItem()->GetID() == id) return TravPtr;

		TravPtr = TravPtr->getNext();

	}


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
		return TEMP;
	}

	Node<Order*>* Prev = SearchandReturnPrev(id);

	if (Prev != nullptr) {

		Node<Order*>* TEMP = Prev->getNext();
		Prev->setNext(TEMP->getNext());
		if (TEMP == Last && First == TEMP) Last = nullptr;
		return TEMP;


	}



}




#endif // !_LIST_H_
















