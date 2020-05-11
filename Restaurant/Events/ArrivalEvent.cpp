#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType,int numDishes,double totMoney):Event(eTime, oID)
{
	OrdType = oType;
	this->numDishes = numDishes;
	this->OrdMoney = totMoney;
	this->OrderID = oID;
	this->ArrTime = eTime;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	Order* pOrd = new Order(OrderID,OrdType,ArrTime,numDishes,OrdMoney);
	//pRest->AddtoDemoQueue(pOrd);

	pRest->AddtoOrderQueue(pOrd);
}
