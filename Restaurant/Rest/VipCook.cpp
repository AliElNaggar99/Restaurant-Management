#include "VipCook.h"


VipCook::VipCook(int ID, int minSpd, int maxSpd, int minBrk, int maxBrk) :Cook(ID, minSpd, maxSpd, minBrk, maxBrk)
{
	type = TYPE_VIP;
}

