#include "VipCook.h"
int VipCook::BreakTime = 0;
int VipCook::CookSpeed = 0;


VipCook::VipCook()
{
}



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

int VipCook::GetBreakTime()
{
	return BreakTime;
}
int VipCook::GetSpeed()
{
	return VipCook::CookSpeed;

}
void VipCook::SetSpeed(int x)
{
	VipCook::CookSpeed = x;

}