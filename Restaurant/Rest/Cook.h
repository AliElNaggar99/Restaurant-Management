#pragma once

#include "..\Defs.h"

#pragma once
class Cook
{  protected:
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	Cook_Status CurrentStatus;
public:
	Cook();
	virtual ~Cook();
	
	virtual int GetID() const;
	virtual ORD_TYPE GetType() const;
	virtual void setID(int);
	virtual void setType(ORD_TYPE) ;
	virtual void SetStausOfCook() = 0;
    virtual Cook_Status GetCookStatus()=0;
	virtual  void SetSpeed(int x);
	virtual int GetSpeed();
	virtual int GetBreakTime()=0;
	virtual void SetBreakTime()=0;



};
