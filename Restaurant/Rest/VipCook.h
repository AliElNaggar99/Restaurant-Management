#pragma once
#include "Cook.h"

class VipCook :
	public Cook

{
private:
	
	static int BreakTime;
	static int CookSpeed;

public:
	
	VipCook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	static void SetBreakTime(int x);
	virtual int GetBreakTime();
	static  void SetSpeed(int x);
	int GetSpeed();

};


