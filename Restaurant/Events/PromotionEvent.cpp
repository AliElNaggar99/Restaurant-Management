#include"PromotionEvent.h"



PromotionEvent::PromotionEvent(int EventTime,int OrderTime,int ExtraMoney): Event(EventTime,OrderID)
{
    this->ExtraMoney = ExtraMoney;
}


int PromotionEvent::getExtraMoney(){return ExtraMoney;}

void PromotionEvent::Execute(Restaurant * pRest){

    // Accesses The order from the ID

    // Adds the Extra money

    // Moves it to VIP

    // Order it is moved in and key depend on the way the priority queue is made
    

    return;
    
}
