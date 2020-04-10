#pragma once
#include "Cook.h"

class VipCook :
	public Cook

{
private:
	
public:
	static int BreakTime;
	VipCook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	virtual void SetBreakTime(int x);
	virtual int GetBreakTime();
	void SetStatusofCook(Cook_Status x);
	Cook_Status GetStatus();
	virtual  void SetSpeed(int x);
	virtual int GetSpeed();

};


