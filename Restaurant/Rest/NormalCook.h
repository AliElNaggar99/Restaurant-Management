#pragma once
#include "Cook.h"

class NormalCook :
	public Cook
{

	static int BreakTime;
	static int CookSpeed;
	
public:
	
	NormalCook();
	
	int GetID() const;
	ORD_TYPE GetType() const;
	virtual void setID(int x);
	virtual void setType(ORD_TYPE);
	static void SetBreakTime(int x);
	int GetBreakTime();
	static  void SetSpeed(int x);
	int GetSpeed();

};


