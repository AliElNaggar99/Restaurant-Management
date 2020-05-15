#pragma once

#include "..\Defs.h"
#include "Order.h"

// Make Speed and Break time depend on each cook not static memmbers


class Cook
{  
protected:
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	Cook_Status CurrentStatus;
	int ID,speed ,  NoFinishOrd , BreakTime; //number of Finished Orders before taking Breaking
	Order* MakingOrder;
	static int BreakAfterN , InjuryRest ;
	int BreakEndTime;



public:
	Cook(int, int,int ,int,int);
	virtual ~Cook()=0;

	virtual void setID(int);
	virtual int GetID() const;
	
	virtual ORD_TYPE GetType() const;
	virtual void setType(ORD_TYPE) ;

	virtual void SetStausOfCook(Cook_Status);
    virtual Cook_Status GetCookStatus() const;
	

	virtual int GetBreakTime() const;
	virtual void SetBreakTime(int,int);

	static void setBreakAfterN(int n); 
	static int getBreakAfterN();

	static void setInjuryRest(int n);
	static int getInjuryRest();


	int GetSpeed() const;
	void SetSpeed( int, int);


	virtual bool isAssigned()const;  //checking if making an order

	// setters and gettings for the MakingOrder
	void setMakingOrder(Order*);
	Order* getMakingOrder() const ;

	//updating status as if finished orders == BreakTime
	void UpdateCookStatus();

	int GetBreakEndTime();
	void SetBreakEndTime(int x);


	void SetFinishedOrders(int x);
	int GetFinishedOrders();

};
