#pragma once
#include "Cook.h"

class VeganCook :
	public Cook
{ private:
	

	
public:
	static int Breaktime;
	VeganCook();
	
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	virtual void SetBreakTime(int x);
	virtual int GetBreakTime();
	void SetStatusOfCook(Cook_Status x);
	Cook_Status GetCookStatus();
	virtual  void SetSpeed(int x);
	virtual int GetSpeed();



};



