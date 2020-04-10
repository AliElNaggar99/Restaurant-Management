#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}
void Order::SetNumberOfDishes(int x)
{
	NumberOfDishes = x;
}

int Order::GetNumberOfDishes()
{
	return NumberOfDishes;
}
void Order::SetTotalMoney(double x)
{
	totalMoney = x;
}
void Order::SetArrivalTime(int x)
{
	ArrTime = x;

}
void Order::SetServingTime(int x)
{
	ServTime = x;

}
void Order::SetFinishTime(int x)
{
	FinishTime = x;

}
double Order::GetTotalMoney( )
{
	return totalMoney;

}
int  Order::GetArrivalTime( )
{
	return ArrTime;

}
int Order::GetFinishTime( )
{
	return FinishTime;

}
int Order::GetServingTime( )
{
	return ServTime;
	

}
