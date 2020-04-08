#include "NormalCook.h"

int NormalCook::BreakTime = 0;
NormalCook::NormalCook()
{
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
void NormalCook::SetStatusOfCook(Cook_Status x)
{
	CurrentStatus = x;


}
Cook_Status NormalCook::GetCookStatus()
{
	return CurrentStatus;

}
int NormalCook::GetSpeed()
{
	return speed;

}
void NormalCook::SetSpeed(int x)
{
	speed = x;

}