#ifndef  __PROMOTIONEVENT_H
#define __PROMOTIONEVENT_H

#include"Event.h"

class PromotionEvent :public Event {

private:

	int ExtraMoney;

public:

	PromotionEvent(int EventTime, int OrderID, int ExtraMoney);

	virtual void Execute(Restaurant* pRest);

};



#endif