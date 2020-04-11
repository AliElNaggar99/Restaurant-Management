#include "NormalCook.h"

int NormalCook::BreakTime = 0;
int NormalCook::CookSpeed = 0;
//adjusting Default construtor 
NormalCook::NormalCook()
{
	type = TYPE_NORMAL;
	CurrentStatus = Availabe;
}




int NormalCook::GetID() const
{
	return ID;
}


ORD_TYPE NormalCook::GetType() const
{
	return type;
}


void NormalCook::setID(int id)
{
	ID = id;
}

void NormalCook::setType(ORD_TYPE t)
{
	type = t;
}
void NormalCook::SetBreakTime(int x)
{
	
	BreakTime = x;

}
int NormalCook::GetBreakTime()
{
	return BreakTime;
}

int NormalCook::GetSpeed()
{
	return NormalCook::CookSpeed;

}
void NormalCook::SetSpeed(int x)
{
	NormalCook::CookSpeed = x;

}