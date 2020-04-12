#include "VeganCook.h"
int VeganCook::Breaktime = 0;
int VeganCook::CookSpeed = 0;
//adjust Constructor for VeganCook
VeganCook::VeganCook()
{
	type = TYPE_VEGAN;
	CurrentStatus = AVA;
}




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

int VeganCook::GetSpeed()
{
	return VeganCook::CookSpeed;

}
void VeganCook::SetSpeed(int x)
{
	VeganCook::CookSpeed = x;

}