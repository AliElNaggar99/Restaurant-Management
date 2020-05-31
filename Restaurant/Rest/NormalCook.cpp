#include "NormalCook.h"

//adjusting Default construtor 
NormalCook::NormalCook(int ID, int minSpd, int maxSpd, int minBrk, int maxBrk) :Cook(ID, minSpd, maxSpd, minBrk, maxBrk)
{
	type = TYPE_NORMAL;
}




