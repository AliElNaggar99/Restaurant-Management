#include "VeganCook.h"
int VeganCook::Breaktime = 0;
int VeganCook::GetID() const
{
	return ID;
}


ORD_TYPE VeganCook::GetType() const
{
	return type;
}


void VeganCook::setID(int id)
{
	ID = id;
}

void VeganCook::setType(ORD_TYPE t)
{
	type = t;
}
void VeganCook::SetBreakTime(int x)
{
	Breaktime = x;
	



}
int VeganCook::GetBreakTime()
{
	return Breaktime;
}

Cook_Status VeganCook::GetCookStatus()
{
	return CurrentStatus;

}
void VeganCook::SetStatusOfCook(Cook_Status t)
{
	CurrentStatus = t;

}
int VeganCook::GetSpeed()
{
	return speed;

}
void VeganCook::SetSpeed(int x)
{
	speed = x;

}