#include "Cook.h"

int Cook::BreakAfterN = 0;

Cook::Cook()
{
}


Cook::~Cook()
{
}
bool Cook::isAssigned()
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


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}




void Cook::setBreakAfterN(int n) { BreakAfterN = n; }

void Cook::SetStausOfCook(Cook_Status stat) {

	CurrentStatus = stat; 

}

Cook_Status Cook::GetCookStatus() { return CurrentStatus; }

// setters and gettings for the MakingOrder
void Cook::setMakingOrder(Order* pOrd)
{
	MakingOrder = pOrd;
	CurrentStatus = BSY;

}
Order* Cook::getMakingOrder()
{
	return MakingOrder;
}

//updating status as if finished orders == BreakTime
void Cook::UpdateCookStatus()
{
	NoFinishOrd++;
	if (NoFinishOrd == BreakAfterN && MakingOrder == nullptr)
	{
		SetStausOfCook(BSY);
	}
}

