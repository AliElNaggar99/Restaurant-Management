#pragma once

#include "..\Defs.h"

#pragma once
class Cook
{  protected:
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	Cook_Status CurrentStatus;
	static int BreakAfterN;
public:
	Cook();
	virtual ~Cook();
	
	virtual int GetID() const;
	virtual ORD_TYPE GetType() const;
	virtual void setID(int);
	virtual void setType(ORD_TYPE) ;
	void SetStausOfCook(Cook_Status);
    Cook_Status GetCookStatus();
	virtual int GetBreakTime()=0;
	static void setBreakAfterN(int n); // somebody should add a getter for this 
	



};
