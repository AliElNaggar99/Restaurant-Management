#include "Cook.h"
#include<ctime>
#include<cstdlib>


Cook::Cook(int ID,int minSpd,int maxSpd,int minBrk,int maxBrk)
{
	this->ID = ID;
	srand(time(NULL));
	SetSpeed(minSpd, maxSpd);
	SetBreakTime(minBrk, maxBrk);
	CurrentStatus =  AVAILABLE;
	NoFinishOrd = 0;
	MakingOrder = nullptr;
	
}

void Cook::SetBreakTime(int min , int max) {
	BreakTime = min + rand() % (max - min);
}

int Cook::getBreakAfterN() const {
	return BreakAfterN;
}

Cook::~Cook()
{
}

bool Cook::isAssigned() const
{
	if (MakingOrder == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}

int Cook::GetBreakTime() const { return BreakTime; }

void Cook::setID(int id){ ID = id; }

void Cook::setType(ORD_TYPE t)
{
	type = t;
}




void Cook::setBreakAfterN(int n) { BreakAfterN = n; }


void Cook::SetStausOfCook(Cook_Status stat) { CurrentStatus = stat;  }

Cook_Status Cook::GetCookStatus() const { return CurrentStatus; }

// setters and gettings for the MakingOrder
void Cook::setMakingOrder(Order* pOrd)
{
	MakingOrder = pOrd;
	CurrentStatus = BUSY;

}
Order* Cook::getMakingOrder() const
{
	return MakingOrder;
}

int Cook::GetSpeed() const {
	return speed; 
}

void Cook::SetSpeed(int min, int max) {

	speed = min + rand() % (max - min);
}
//updating status as if finished orders == BreakTime
void Cook::UpdateCookStatus()
{
	NoFinishOrd++;
	if (NoFinishOrd == BreakAfterN && MakingOrder == nullptr)
	{
		SetStausOfCook(BUSY);
	}
}

