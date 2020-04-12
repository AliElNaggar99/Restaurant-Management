#pragma once
#include"Generic_DS/Node.h"

#include"../Restaurant/Rest/Order.h"
template <typename T>
class List
{
private:
	Node<T>* First;
	Node<T>* Last;
public:





	List();
	void Add(Node<T>*n);
	void Remove();
	void SearchandDelete(int x);

};
template<typename T>
List<T>::List()
{
		First = nullptr;
		Last = nullptr;



}


template<typename T>

void List<T>::Add(Node<T>*InsertedNode)
	
{
		if (First == Last == nullptr)
		{
			First = Last = InsertedNode;
			First->setNext(nullptr);
			Last->setNext(nullptr);

		}
		else
		{
			Node<T>* Temp = new Node<T>;
			Temp = Last;
			Temp->setNext(InsertedNode);
			Last = InsertedNode;





		}
	
	
	
	}
template <typename T>
void List<T>::Remove()
{
	if (!First)
	{
		return;
	}
	if (First == Last)
	{
		First = nullptr;
		Last = nullptr;

	}


	else {
		Node<T>* Temp = new Node<T>;
		Temp = First;
		while (Temp->getNext() != Last)
		{
			Temp = Temp->getNext();

		}
		Node<T>* Temp2 = new Node<T>;
		Temp2 = Last;
		Temp->setNext(nullptr);
		Last = Temp;
		delete Temp2;

	}



}
template<>
void List<Order*>::SearchandDelete(int x)
{
	if (First == nullptr)
	{
		return;

	}
	else if (First==Last&&First->getItem()->GetID()==x)
	{
		Node<Order*>* Temp = new Node<Order*>;
		First = Last = nullptr;
		delete Temp;
	}
	else if (First->getItem()->GetID()==x)
	{
		Node<Order*>* Temp = new Node<Order*>;
		Temp = First;
		First = First->getNext();
		delete Temp;
	}
	else if (Last->getItem()->GetID() == x)
	{
		Remove();
	}
	else
	{
		Node<Order*>* Temp = new Node<Order*>;
		while (Temp->getNext() && Temp->getNext()->getItem()->GetID()==x)
		{
			Temp = Temp->getNext();

		}
		Node<Order*>* Temp2 = new Node<Order*>;
		Temp2 = Temp->getNext();
		Temp->setNext(Temp2->getNext());
		delete Temp2;





	}


}















