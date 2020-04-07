#ifndef  __PROMOTIONEVENT_H
#define __PROMOTIONEVENT_H

#include"Event.h"

class PromotionEvent:public Event{

private:

int ExtraMoney;

public:

PromotionEvent(int EventTime,int OrderID,int ExtraMoney);
int getExtraMoney();

virtual void Execute(Restaurant* pRest);

}



#endif