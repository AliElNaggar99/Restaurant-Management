#include "VipCook.h"
int VipCook::BreakTime = 0;
int VipCook::GetID() const
{
	return ID;
}


ORD_TYPE VipCook::GetType() const
{
	return type;
}


void VipCook::setID(int id)
{
	ID = id;
}

void VipCook::setType(ORD_TYPE t)
{
	type = t;
}
void VipCook::SetBreakTime(int x)
{
	BreakTime = x;




}
void VipCook::SetStatusofCook(Cook_Status t )
{
	CurrentStatus = t;


}
int VipCook::GetBreakTime()
{
	return BreakTime;
}
Cook_Status VipCook::GetStatus()
{
	return CurrentStatus;

}
int VipCook::GetSpeed()
{
	return speed;

}
void VipCook::SetSpeed(int x)
{
	speed = x;

}