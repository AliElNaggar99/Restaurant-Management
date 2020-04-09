#pragma once
#include "Generic_DS/Node.h"
template <typename T>
class LinkedList
{
private:
	Node<T>* Head;
public:
	// hena functions Delete be koll ashkalo w Insert be koll ashkalo 

	LinkedList()
	{
		Head = nullptr;
	}


	~LinkedList()
	{
		DeleteAll();
	}

	void InsertEnd(const T& data)
	{

		Node<T>* P1 = new Node<T>();
		P1 = Head;
		Node<T>* pnew = new Node<T>(data);
		if (Head == nullptr)
		{
			Head = pnew;
			return;
		}
		while (P1->getNext())
		{
			P1 = P1->getNext();
		}
		P1->setNext(pnew);



	}


	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}

	void InsertEnd(const T& data)
	{

		Node<T>* p = new Node<T>();
		p = Head;
		Node<T>* pnew = new Node<T>(data);
		if (Head == nullptr)
		{
			Head = pnew;
			return;
		}
		while (p->getNext())
		{
			p = p->getNext();
		}
		p->setNext(pnew);

	}

	void insertPos(T data, int Pos)
	{
		Node<T>* P1 = new Node <T>;
		P1->setItem(data); P1->setNext(nullptr);
		if (Pos == 1) {
			P1->setNext(Head);
			Head = P1;
			return;
		}
		Node<T>* P2 = Head;
		for (int i = 0; i < Pos - 2; i++) {
			P2 = P2->getNext();
		}
		P1->setNext(P2->getNext());
		P2->setNext(P1);
	}

	void DeleteFirst()
	{
		if (Head)
		{
			Node<T>* temp = Head;
			Head = Head->getNext();
			delete temp;
		}

	}

	bool DeleteNode(const T& value)
	{
		{
			int c = -1;
			Node<T>* temp = Head;
			while (temp->getNext())
			{
				if (temp->getNext()->getItem() == value)
				{
					Node<T>* p = temp->getNext();
					temp->setNext(p->getNext());
					delete p;c = 1;
				}

				else
					temp = temp->getNext();


			}
			if (c == 1)
				return true;
		}

	}

	void DeleteAll()
	{
		Node<T>* P1 = Head;
		while (Head)
		{
			P1 = Head->getNext();
			delete Head;
			Head = P1;
		}
	}




};



