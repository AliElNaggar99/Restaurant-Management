#include "VeganCook.h"


//adjust Constructor for VeganCook
VeganCook::VeganCook(int ID, int minSpd, int maxSpd, int minBrk, int maxBrk):Cook(ID,minSpd,maxSpd,minBrk,maxBrk)
{
	type = TYPE_VEGAN;
}
