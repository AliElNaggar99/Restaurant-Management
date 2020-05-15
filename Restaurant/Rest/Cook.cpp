#include "Cook.h"
#include<ctime>
#include<cstdlib>



int Cook::BreakAfterN = 0;
int Cook::InjuryRest = 0;

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


int Cook::GetID() const { return ID; }
void Cook::setID(int id) { ID = id; }


ORD_TYPE Cook::GetType() const{ return type; }
void Cook::setType(ORD_TYPE t) { type = t; }

int Cook::GetBreakTime() const { return BreakTime; }
void Cook::SetBreakTime(int min, int max) { BreakTime = min + rand() % (max - min + 1); }


int Cook::getBreakAfterN() { return BreakAfterN; }
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


int Cook::GetSpeed() const { return speed; }
void Cook::SetSpeed(int min, int max) { speed = min + rand() % (max - min + 1); }

void Cook::setInjuryRest(int n) { InjuryRest = n;  }
int Cook::getInjuryRest() { return InjuryRest;  }
//updating status as if finished orders == BreakTime

void Cook::UpdateCookStatus()
{
	NoFinishOrd++;
	if (NoFinishOrd == BreakAfterN && MakingOrder == nullptr)
	{
		SetStausOfCook(BUSY);
	}
}

void Cook::SetFinishedOrders(int x)
{
	NoFinishOrd = x;
}
int Cook::GetFinishedOrders()
{
	return NoFinishOrd;
}

int Cook::GetBreakEndTime()
{
	return BreakEndTime;
}
void Cook::SetBreakEndTime(int x)
{
	BreakEndTime = x;
}


