#pragma once
#include "Cook.h"

class NormalCook :
	public Cook
{

	
public:
	static int BreakTime;
	NormalCook();
	
	int GetID() const;
	ORD_TYPE GetType() const;
	virtual void setID(int x);
	virtual void setType(ORD_TYPE);
	virtual void SetBreakTime(int x);
	 int GetBreakTime();
	 void SetStatusOfCook(Cook_Status x);
	Cook_Status GetCookStatus();
	virtual  void SetSpeed(int x);
	virtual int GetSpeed();

};


