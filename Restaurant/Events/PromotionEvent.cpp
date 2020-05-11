#include"PromotionEvent.h"
#include "..\Rest\Restaurant.h"


// adjusting constructor to save elements
PromotionEvent::PromotionEvent(int EventTime, int OrderID, int ExtraMoney): Event(EventTime,OrderID)
{
    this->ExtraMoney = ExtraMoney;
}



void PromotionEvent::Execute(Restaurant * pRest){

    // Accesses The order from the ID

    // Adds the Extra money

    // Moves it to VIP

    // Order(as in position not order itself) it is moved in and key depend on the way the priority queue is made
    

    pRest->PromOrder(OrderID , ExtraMoney);

    return;
    
}

