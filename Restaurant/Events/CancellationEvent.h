#ifndef  __CANCELLATIONEVENT_H
#define  __CANCELLATIONEVENT_H

#include"Event.h"

class CancellationEvent : public Event {

	CancellationEvent(int EventTime, int OrderID);


	virtual void Execute(Restaurant* pRest);


};




#endif