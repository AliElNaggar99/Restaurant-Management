#pragma once
#include "Cook.h"

class VeganCook :
	public Cook
{ private:
	

	static int Breaktime;
	static int CookSpeed;

public:
	
	VeganCook();
	
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	static void SetBreakTime(int x);
	virtual int GetBreakTime();
	static  void SetSpeed(int x);
	int GetSpeed();



};



