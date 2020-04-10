#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

				//ServTime & Finish time depend on the cook 
	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	int NumberOfDishes;

	
public:
	Order(int ID, ORD_TYPE r_Type,int ArrivalTime,int numDishes,double totMoney);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	void SetNumberOfDishes(int x);
	int GetNumberOfDishes();
	double GetTotalMoney();
	int GetArrivalTime();
	int GetServingTime();
	int GetFinishTime();
	void SetTotalMoney(double x);
	void SetArrivalTime(int x);
	void SetServingTime(int x);
	void SetFinishTime(int x);
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif