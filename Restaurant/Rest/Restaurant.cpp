#include <cstdlib>
#include <time.h>
#include <iostream>
#include<regex>

using namespace std;

#include "Restaurant.h"
#include"../Events/ArrivalEvent.h"
#include"../Events/CancellationEvent.h"
#include"../Events/PromotionEvent.h"
#include"NormalCook.h"
#include"VeganCook.h"
#include"VipCook.h"

//The Priority Equation Function Ps: might need to be editted
int Restaurant::PriorityEquation(Order* Ord)
{
	return 0.8 * Ord->GetTotalMoney() + 0.6 * Ord->GetNumberOfDishes() + 0.3 * Ord->GetArrivalTime();
}


Restaurant::Restaurant() 
{
	pGUI = NULL;
}


void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		//Phase II test not actually ALI
		TestPHII();
		break;
	case MODE_DEMO:
		//Just_A_Demo();
		Test();
		break;
	};

}

std::vector<std::string> Restaurant::split_line(const std::string & line,std::string delimeter) {
  std::vector<std::string> StringVector;
  std::size_t start = 0, end = 0;
  while ((end = line.find(delimeter, start)) != std::string::npos) {
    StringVector.push_back(line.substr(start, end - start));
    start = end + 1;
  }
  StringVector.push_back(line.substr(start));
  return StringVector;
}


void Restaurant::ReadFromFile()
{


//making Cooks ID

	int cID = 1;

this->pGUI->PrintMessage("Enter the name of the file to be read : ");
std::string FileName = pGUI->GetString();

fstream toBeReadFile ;

toBeReadFile.open(FileName,ios::in);

if(! toBeReadFile.is_open()){

	// We could make the function a bool and close the program if file name is wrong or put this in a while loop that exits when you etner -1

	pGUI->PrintMessage("File doesn't exist or can't be opened");
		return;

}


std::vector<std::string> Lines(7);
int Counter = 0 ;
while (getline(toBeReadFile,Lines[Counter]) && Counter++ != 6);


regex MoreThanTwoSpace("\\s{2,}");
regex Tabs("\t");
const std::string oneWhiteSpace = " ";

{
	std::vector<std::string> Container, CookSpdCont, BreakTimeCont;


	// makes string only have 1 consecutive whitespace
	// L1 no of cooks from each type
	Lines[0] = regex_replace(Lines[0], Tabs, oneWhiteSpace);
	Lines[0] = regex_replace(Lines[0], MoreThanTwoSpace, oneWhiteSpace);
	Container = split_line(Lines[0], oneWhiteSpace);

	//L2 cook speed for ea
	Lines[1] = regex_replace(Lines[1], Tabs, oneWhiteSpace);
	Lines[1] = regex_replace(Lines[1], MoreThanTwoSpace, oneWhiteSpace);
	CookSpdCont = split_line(Lines[1], oneWhiteSpace);

	//L3 (BreakAfter n orders) BreakDuration
	Lines[2] = regex_replace(Lines[2], Tabs, oneWhiteSpace);
	Lines[2] = regex_replace(Lines[2], MoreThanTwoSpace, oneWhiteSpace);

	BreakTimeCont = split_line(Lines[2], oneWhiteSpace);


	//Remeber to delete Cooks in destructor of Restaurant

	Cook::setBreakAfterN(std::stoi(BreakTimeCont[0]));

	for (int i = 0; i < TYPE_CNT; i++) {
		for (int j = 0; j < std::stoi(Container[i]); j++) {

			if (i == TYPE_NORMAL) {

				//Creating ID for Cooks
				cID += (rand() % 15 + 1);
				NormalCook* TEMP = new NormalCook(cID, std::stoi(CookSpdCont[0]), std::stoi(CookSpdCont[1]), std::stoi(BreakTimeCont[1]), std::stoi(BreakTimeCont[2]));
				NormCookList.enqueue(TEMP);    //Inserting at the end O(n) InsertingBeg O(1) ???
				NumberOfNormalCooks++;

			}
			else if (i == TYPE_VEGAN) {
				VeganCook* TEMP = new VeganCook(cID, std::stoi(CookSpdCont[2]), std::stoi(CookSpdCont[3]), std::stoi(BreakTimeCont[3]), std::stoi(BreakTimeCont[4]));
				//Creating ID for Cooks
				cID += (rand() % 15 + 1);
				TEMP->setID(cID);
				VegCookList.enqueue(TEMP);
				NumberOfVeganCooks++;

			}
			else {
				VipCook* TEMP = new VipCook(cID, std::stoi(CookSpdCont[4]), std::stoi(CookSpdCont[5]), std::stoi(BreakTimeCont[5]), std::stoi(BreakTimeCont[6]));
				//Creating ID for Cooks
				cID += (rand() % 15 + 1);
				TEMP->setID(cID);
				VipCookList.enqueue(TEMP);
				NumberOfVipCooks++;

			}


		}
	}




	//L4 Injury Chance Thingy
	
	Lines[3] = regex_replace(Lines[3], Tabs, oneWhiteSpace);
	Lines[3] = regex_replace(Lines[3], MoreThanTwoSpace, oneWhiteSpace);
	Container = split_line(Lines[3], oneWhiteSpace);

	//string to float not int 
	InjuryProb = std::stof(Container[0]);
	Cook::setInjuryRest(std::stoi(Container[1]));


	//L5 Promotion Variable
	Lines[4] = regex_replace(Lines[4], Tabs, oneWhiteSpace);
	Lines[4] = regex_replace(Lines[4], MoreThanTwoSpace, oneWhiteSpace);
	Container = split_line(Lines[4], oneWhiteSpace);


	PromotionVariable = std::stoi(Container[0]);
	UrgentVariable = std::stoi(Container[1]); 
}


//L6 No of events in file
int numEvents = std::stoi(Lines[5]);


//Resizing vector
Lines.resize(6+numEvents);
while (getline(toBeReadFile,Lines[Counter]) && Counter++ != 5+numEvents) ;

for(int i = 6; i < (6+numEvents);i++){
	Lines[i] = regex_replace(Lines[i], Tabs, oneWhiteSpace);
	Lines[i] = regex_replace(Lines[i], MoreThanTwoSpace, oneWhiteSpace);
	std::vector<std::string> SplitString = split_line(Lines[i]," ");
	char FirstLetter = *std::begin(SplitString[0]);

	if (FirstLetter == 'R') {
		//Arrival Event
		char SecondLetter = *std::begin(SplitString[1]);
		ORD_TYPE oType;
		switch (SecondLetter)
		{
		case 'N':
			oType = TYPE_NORMAL;
			break;
		case 'V':
			oType = TYPE_VIP;
			break;
		case 'G':
			oType = TYPE_VEGAN;
			break;
		default:
			break;
		}
		// making a pointer of Event to add it to Queue dynamically so it doesn't remvoe after deqeueing
		Event* A = new ArrivalEvent(std::stoi(SplitString[2]), std::stoi(SplitString[3]), oType, std::stoi(SplitString[4]), std::stod(SplitString[5]));

		// enqueue the event
		EventsQueue.enqueue(A);

	}
	else if (FirstLetter == 'X') {
		//Cancellation event
		// making a pointer of Event to add it to Queue dynamically so it doesn't remvoe after deqeueing
		//swaped between Splitstring 1 and 2 as 1 is ID not 2
		Event* C = new CancellationEvent(std::stoi(SplitString[1]), std::stoi(SplitString[2]));
	
		// enqueue the event
		EventsQueue.enqueue(C);

	}
	else{
		// making a pointer of Event to add it to Queue dynamically so it doesn't remvoe after deqeueing
		Event* P = new PromotionEvent(std::stoi(SplitString[1]), std::stoi(SplitString[2]),std::stoi(SplitString[3]));
		// enqueue the event
		EventsQueue.enqueue(P);
		
	}



}

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		if (pGUI)
			delete pGUI;
}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);

	//Size will be used as Size to print
	int size = 0;
	//Filling the drawing list with Cooks
	VipCook** VICList = VipCookList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(VICList[i]);
	}
	delete []VICList;

	VeganCook** VegCock = VegCookList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(VegCock[i]);
	}
	delete[]VegCock;


	NormalCook** NormCoList = NormCookList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(NormCoList[i]);
	}
	delete[]NormCoList;


	//Now Printing Waiting Order first we print Vip then Vegan then Normal Just like cooks
	Order** pOrd = Vip_Order.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrd[i]);
	}
	delete[]pOrd;
	
	pOrd = VeganOrder.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrd[i]);
	}
	delete[]pOrd;

	pOrd = NormalOrder.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrd[i]);
	}
	delete[]pOrd;

	//Now Printing The serving according to assement time
	pOrd = OrdersServing.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrd[i]);
	}
	delete[]pOrd;

	//Now Printing Done Orders
	pOrd = OrdersAllDone.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrd[i]);
	}
	delete[]pOrd;

}



// Simple Stimulation for Phase I to test Ali:
void Restaurant::Test()
{
	//reading File from user

	ReadFromFile();

	//all lists are filled by cocks and events


	//Check Event list 
	int CurrentTimeStep = 0;
	string* S = new string[3];
	int* NumberOfCooks = new int[4];
	int* NumberOfOrders = new int[3];
	//condition of Events and Waiting and Serving
	while (!EventsQueue.isEmpty() || !Vip_Order.isEmpty() || !NormalOrder.isEmpty() || !VeganOrder.isEmpty() ||!OrdersServing.isEmpty())
		{
			//print current timestep
			//char timestep[10];
			//itoa(CurrentTimeStep,timestep,10);	
			//pGUI->PrintMessage("TS: " + to_string(CurrentTimeStep));

	
	     	//The next line may add new orders to the Queue waiting
			ExecuteEvents(CurrentTimeStep);	//execute all events at current time step

			//Moving Orders form Waiting to Serves
			Order* pOrd;
			//Checking of Free Cocks from each type
			if (Vip_Order.dequeue(pOrd))
			{
				pOrd->setStatus(SRV);
				OrdersServing.dequeue(pOrd);
		    }
			if (VeganOrder.dequeue(pOrd))
			{
				pOrd->setStatus(SRV);
				OrdersServing.dequeue(pOrd);
			}
			if (NormalOrder.RemoveFirst(pOrd))
			{
				pOrd->setStatus(SRV);
				OrdersServing.dequeue(pOrd);
			}

			//moving from in Srv to done
			if (CurrentTimeStep % 5 == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					if (OrdersServing.dequeue(pOrd))
					{
						pOrd->setStatus(DONE);
						OrdersAllDone.enqueue(pOrd);
						pOrd->SetServingTime(CurrentTimeStep);
				   }
				}
			}
			
        //////////////////////////////////////////////////////////////////////////////////////////
			FillDrawingList();
  
		///////////////////////////////////////////////////////////////////////////////////////////
	   // interactive Mode
			S[0] = "TS: " + to_string(CurrentTimeStep);
			S[1] = "Number of Waiting Orders: Vip: " + to_string(NumberOfOrders[2]) + " Vegan : " + to_string(NumberOfOrders[1]) + " Normal : " + to_string(NumberOfOrders[0]);
			//this acts like index so first element is Zero
			S[2] = "Number of available cooks: Vip: " + to_string(NumberOfCooks[3]) + " Vegan: " + to_string(NumberOfCooks[2]) + " Normal: " + to_string(NumberOfCooks[1]);
			pGUI->PrintMessageML(S, 3);

			pGUI->UpdateInterface();
			pGUI->waitForClick();
			CurrentTimeStep++;	//advance timestep
			pGUI->ResetDrawingList();
		}
	pGUI->PrintMessage("Simulation is Done");
	pGUI->waitForClick();
	delete[]S;
	delete[]NumberOfCooks;
	delete[]NumberOfOrders;


}


//Simulation for Phase II

void Restaurant::TestPHII()
{
	//reading File from user

	ReadFromFile();

	//all lists are filled by cocks and events


	pGUI->PrintMessage("Hello, this is demo");
	pGUI->waitForClick();


	pGUI->waitForClick();
	//Check Event list 
	int CurrentTimeStep = 0;
	float Injury;
	
	//condition of Events and Waiting and Serving
	while (!EventsQueue.isEmpty() || !Vip_Order.isEmpty() || !NormalOrder.isEmpty() || !VeganOrder.isEmpty() || !OrdersServing.isEmpty())
	{
		//print current timestep

		pGUI->PrintMessage("TS: " + to_string(CurrentTimeStep));


		//The next line may add new orders to the Queue waiting
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step

		//Creating an Order and cook Pointer to use them in simulation
		AssigningOrders(CurrentTimeStep);
		//Checking the Injury
		Injury = rand() % 100 / 100.0;
		if (Injury <= InjuryProb)
		    CheckInjuredCooks(CurrentTimeStep);

		CheckUrgency(CurrentTimeStep);
		CheckAutoProm(CurrentTimeStep);
		UpdateCooksandOrdersstatus(CurrentTimeStep);
		PrintInfoCurrentTime(CurrentTimeStep);
		
		
		//////////////////////////////////////////////////////////////////////////////////////////
		FillDrawingList();
		
		pGUI->UpdateInterface();
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
		//add check urgent later


		//////////////////////////////////////////////////////////////////////////////////////////
	   // interactive Mode
		pGUI->ResetDrawingList();
	}
	SaveFile();
	pGUI->PrintMessage("Simulation is Done");
	pGUI->waitForClick();
	FillDrawingList();
	
}



void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

// add order to the right Queue
void Restaurant::AddtoOrderQueue(Order* pOrd)
{
	ORD_TYPE type =	pOrd->GetType();

	switch (type)
	{
	case TYPE_NORMAL:
		NormalOrder.InsertLast(pOrd);
		break;
	case TYPE_VIP:
		Vip_Order.enqueue(pOrd, PriorityEquation(pOrd));
		break;
	case TYPE_VEGAN:
		VeganOrder.enqueue(pOrd);
		break;
	default:
		break;
	}
}


//Cancel Function using the Queue
void Restaurant::CancelOrder(int CID)
{
	// Remove it from  List 
	Node<Order*>* Ord = NormalOrder.RemoveOrderFromList(CID);
	if (Ord == nullptr) return;
	delete Ord;

}



//Promotion Function (I think it is finished)
void Restaurant::PromOrder(int CID , int ExtraMoney)
{
	//Not sure how will this be done
	Node<Order*> * Ord = NormalOrder.RemoveOrderFromList(CID);
	if (Ord == nullptr || Ord->getItem() == nullptr) return; //Check for errors
	
	Order* OrderToBePromoted = Ord->getItem();  //get Order from Node then deletes the node



	OrderToBePromoted->SetTotalMoney(OrderToBePromoted->GetTotalMoney() + ExtraMoney);
	OrderToBePromoted->setType(TYPE_VIP);

	//Later On Priority for order will be set according to the equation
	Vip_Order.enqueue(OrderToBePromoted,PriorityEquation(OrderToBePromoted));
	delete Ord;
}

void Restaurant::AssigningOrders(int CurrentTimeStep)////////////////////////afifiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
{
	//Temp Storage for Orders
	Order* pOrd;
	//Cook temp for drawing information of Current Time Step
	Cook* CookTemp;
	//Serveing all Vip Orders if there is an available Cook
	while ((Vip_Order.peekFront(pOrd)) && (!VipCookList.isEmpty() || !VegCookList.isEmpty() || !NormCookList.isEmpty()))
	{
		//First Dequeue the Order
		Vip_Order.dequeue(pOrd);
		//If there is a vip Cook
		if (!VipCookList.isEmpty())
		{
			VipCook* Cook1;
			VipCookList.dequeue(Cook1);
			AssignOrder(Cook1, pOrd, CurrentTimeStep);
		}
		//If there is an NormalCook
		else if (!NormCookList.isEmpty())
		{
			NormalCook* Cook1;
			NormCookList.dequeue(Cook1);
			AssignOrder(Cook1, pOrd, CurrentTimeStep);
		}
		//If there is an Vegan Cook
		else if (!VegCookList.isEmpty())
		{
			VeganCook* Cook1;
			VegCookList.dequeue(Cook1);
			AssignOrder(Cook1, pOrd, CurrentTimeStep);
		}
	}

	//Finishing all Vegan Orders if there is a Free Vegan Cook
	while (VeganOrder.peekFront(pOrd) && (!VegCookList.isEmpty()))
	{
		VeganOrder.dequeue(pOrd);
		VeganCook* Cook1;
		VegCookList.dequeue(Cook1);
		AssignOrder(Cook1, pOrd, CurrentTimeStep);
	}

	//Finishing all Normal Orders if there is a free Normal or a vip Cook
	while (NormalOrder.ReturnFirst(pOrd) && (!VipCookList.isEmpty() || !NormCookList.isEmpty()))
	{
		NormalOrder.RemoveFirst(pOrd);
		if (!NormCookList.isEmpty())
		{
			NormalCook* Cook1;
			NormCookList.dequeue(Cook1);
			AssignOrder(Cook1, pOrd, CurrentTimeStep);
		}
		//If there is an NormalCook
		else if (!VipCookList.isEmpty())
		{
			VipCook* Cook1;
			VipCookList.dequeue(Cook1);
			AssignOrder(Cook1, pOrd, CurrentTimeStep);
		}
	}
}

void Restaurant::UpdateCooksandOrdersstatus(int CurrentTimeStep)/////afifiiiiiiiiiiiiiiiiiiiiiiiii
{
	//Checking if A cook Finished his Order
	Cook* Temp;
	//Working Cook List
	while (Working_Cook.peekFront(Temp) && Temp->getMakingOrder()->GetFinishTime() == CurrentTimeStep)
	{
		//SO that Cook Finished his Order
		Working_Cook.dequeue(Temp);
		UpdateCook(Temp, CurrentTimeStep);
	}

	//Checking the InjuredCooks List // He will go the relative list
	while (Injured_Cooks.peekFront(Temp) && Temp->getMakingOrder()->GetFinishTime() == CurrentTimeStep)
	{
		Injured_Cooks.dequeue(Temp);
		UpdateCook(Temp , CurrentTimeStep);
	}


	//Check Break List
	while (Break_Cooks.peekFront(Temp) && Temp->GetBreakEndTime() == CurrentTimeStep)
	{
		//His break Ended Return it to the Right List
		Temp = nullptr;
		Break_Cooks.dequeue(Temp);
		ReturnCookToRightList(Temp);
	}
	//Check Rest List
	while (Rest_Cooks.peekFront(Temp) && Temp->GetBreakEndTime() == CurrentTimeStep)
	{
		Rest_Cooks.dequeue(Temp);
		ReturnCookToRightList(Temp);
	}
}

void Restaurant::CheckAutoProm(int CurrentTimestep) 
{

	while (true) 
	{
		Order* TEMP = nullptr; 
		if (!NormalOrder.ReturnFirst(TEMP)) 
			break;
		if ((CurrentTimestep - TEMP->GetArrivalTime()) > PromotionVariable) {

			NormalOrder.RemoveFirst(TEMP);
			TEMP->setType(TYPE_VIP);
			Vip_Order.enqueue(TEMP , PriorityEquation(TEMP));
			NumberOfAutoProm++;
			TEMP->setAutoPromoted(true);
		}
		else
			break;
	}
}

void Restaurant::CheckUrgency(int CurrentTimestep) {


		List<Order*> TempStore;
		
		while (Vip_Order.GetCount()) 
		{

			if (Break_Cooks.isEmpty() && Rest_Cooks.isEmpty())
				break;

			Order* TempOrder = nullptr;
			Vip_Order.dequeue(TempOrder);

			if ((CurrentTimestep - TempOrder->GetArrivalTime()) > UrgentVariable) {

				//this will later be modified as to have rest and break in different queues
				Cook* TempCook = nullptr;
				Cook_Status CookStat = URG_BRK;
				Break_Cooks.dequeue(TempCook);
				if (TempCook == nullptr) {
					Rest_Cooks.dequeue(TempCook);
					CookStat = URG_INJ;
				}
				AssignOrder(TempCook, TempOrder, CurrentTimestep, CookStat);
				TempCook->SetBreakEndTime(TempCook->GetBreakEndTime() - CurrentTimestep + TempOrder->GetFinishTime());// set end break time = old end break time + time taken to finish order
				NumberOfUrgentOrders++;
			}
			else
				//to work as the Same Order as a Queue
				TempStore.InsertLast(TempOrder);
		}
		while (TempStore.GetCount())
		{
			Order* TempOrder = nullptr;
			TempStore.RemoveFirst(TempOrder);
			Vip_Order.enqueue(TempOrder,PriorityEquation(TempOrder));
		}
}

void Restaurant::CheckInjuredCooks(int CurrentTimeStep)
{
	Cook* BusyCook;
	Order* order;
	int RemainingDishes, NewServingTime, TimeStepOfServing, WorkedhowManyTimesteps, NumberofDoneDishes;
	float NewSpeed;
	int oldServing;
	int oldFinishing;
	if (Working_Cook.dequeue(BusyCook))
	{
		NumOfInjCooks++;
		order = BusyCook->getMakingOrder();
		oldServing = order->GetServingTime();
		oldFinishing = order->GetFinishTime();
		TimeStepOfServing = order->GetArrivalTime() + order->GetWaitTime();
		if (CurrentTimeStep == 1)
			WorkedhowManyTimesteps = 0;
		else
			WorkedhowManyTimesteps = CurrentTimeStep - TimeStepOfServing - 1;
		NumberofDoneDishes = WorkedhowManyTimesteps * (BusyCook->GetSpeed());
		RemainingDishes = order->GetNumberOfDishes() - NumberofDoneDishes;
		NewSpeed = ((float)BusyCook->GetSpeed()) / 2;
		NewServingTime = WorkedhowManyTimesteps + ceil((float)RemainingDishes / NewSpeed);
		order->SetServingTime(NewServingTime);
		order->SetFinishTime(order->GetArrivalTime() + order->GetServingTime() + order->GetWaitTime());
		BusyCook->SetStausOfCook(INJURED);
		Injured_Cooks.enqueue(BusyCook, order->GetFinishTime());
		//Changing Position of the the Order
		OrdersServing.dequeue(order);
		OrdersServing.enqueue(order, order->GetFinishTime());
	}
}



void Restaurant::UpdateCook(Cook* pCook, int CurrentTimeStep)
{
	Order* pOrd = pCook->getMakingOrder();
	pOrd->setStatus(DONE);
	OrdersAllDone.enqueue(pOrd);
	OrdersServing.dequeue(pOrd);
	pCook->setMakingOrder(nullptr);
	pCook->SetFinishedOrders(pCook->GetFinishedOrders() + 1);

	//Check if the Cook would Take a break or No
	if (pCook->GetFinishedOrders() == pCook->getBreakAfterN())
	{
		pCook->SetFinishedOrders(0);
		pCook->SetBreakEndTime(pCook->GetBreakTime() + CurrentTimeStep);
		pCook->SetStausOfCook(BREAK);
		//Put it in the Break List
		Break_Cooks.enqueue(pCook, pCook->GetBreakEndTime());
	}
	//Return it to the list
	else
	{
		ReturnCookToRightList(pCook);
	}
}

void Restaurant::ReturnCookToRightList(Cook* pCook)
{
	pCook->SetStausOfCook(AVAILABLE);
	if (pCook->GetType() == TYPE_VEGAN)
	{
		VeganCook* Cook1 = (VeganCook*)pCook;
		VegCookList.enqueue(Cook1);
	}
	else if (pCook->GetType() == TYPE_NORMAL)
	{
		NormalCook* Cook1 = (NormalCook*)pCook;
		NormCookList.enqueue(Cook1);
	}
	else if (pCook->GetType() == TYPE_VIP)
	{
		VipCook* Cook1 = (VipCook*)pCook;
		VipCookList.enqueue(Cook1);
	}
}

void Restaurant::AssignOrder(Cook* pCook, Order* pOrder,int CurrentTimeStep,Cook_Status CookStat ) {


	pCook->setMakingOrder(pOrder); // Link Cook and order together 
	pCook->SetStausOfCook(CookStat);// set status to URG_BRK or URG_INJ Or BUSY
	int InjuryFactor = 1;
	if (CookStat == URG_INJ) 
		InjuryFactor = 2;
	pOrder->SetWaitTime(CurrentTimeStep - pOrder->GetArrivalTime());
	pOrder->SetServingTime(ceil((float)pOrder->GetNumberOfDishes() / ((float)pCook->GetSpeed() / InjuryFactor)));
	pOrder->SetFinishTime(pOrder->GetArrivalTime()+pOrder->GetWaitTime()+pOrder->GetServingTime());
	pOrder->setStatus(SRV);
	if (CookStat == URG_INJ)
		Injured_Cooks.enqueue(pCook, pOrder->GetFinishTime());
	else
		Working_Cook.enqueue(pCook, pOrder->GetFinishTime());// move cook to working and order to serving and check other shit that ali needs for printing
	Assigned.enqueue(pCook);
	OrdersServing.enqueue(pOrder, pOrder->GetFinishTime());
}


void Restaurant::SaveFile()
{
	pGUI->PrintMessage("Enter the file name please: ");
	string FileName = pGUI->GetString();
	pGUI->UpdateInterface();
	ofstream OutputFile;
	OutputFile.open(FileName, ios::out);
	int count = 0;
	if (OutputFile.is_open()) {
		OutputFile << "FT" << "  " << "ID" << "  " << "AT" << "  " << "WT" << "  " << "ST" << endl;
		Order** Doneorder = OrdersAllDone.toArray(count);
		int* id = new int[count];
		int* ft = new int[count];
		int* at = new int[count];
		int* wt = new int[count];
		int* st = new int[count];
		int NumOfVegOrders = 0;
		int NumOfNormOrders = 0;
		int NumOfVipOrders = 0;
		int TotalWaitTime = 0;
		int TotalServTime = 0;
		int cooksCount = NumberOfNormalCooks + NumberOfVeganCooks + NumberOfVipCooks;
		for (int i = 0; i < count; i++)
		{
			at[i] = Doneorder[i]->GetArrivalTime();
			ft[i] = Doneorder[i]->GetFinishTime();
			id[i] = Doneorder[i]->GetID();
			st[i] = Doneorder[i]->GetServingTime();
			wt[i] = Doneorder[i]->GetWaitTime();
			TotalServTime = TotalServTime + st[i];
			TotalWaitTime = TotalWaitTime + wt[i];
			OutputFile << ft[i] << "   " << id[i] << "   " << at[i] << "   " << wt[i] << "   " << st[i] << endl;
		}

		for (int i = 0; i < count; i++)
		{
			if (Doneorder[i]->GetType() == TYPE_NORMAL || (Doneorder[i]->GetType() == TYPE_VIP && Doneorder[i]->getAutoPromted() == true))
			{
				NumOfNormOrders++;
			}
			else if (Doneorder[i]->GetType() == TYPE_VIP && Doneorder[i]->getAutoPromted() == false)
			{
				NumOfVipOrders++;
			}
			else if (Doneorder[i]->GetType() == TYPE_VEGAN) 
			{
				NumOfVegOrders++;
			}
		}
		OutputFile << "................................................" << endl;
		OutputFile << "Orders: " << count << " [Norm: " << NumOfNormOrders << ", Veg: " << NumOfVegOrders << ", VIP: " << NumOfVipOrders << "]" << endl;
		OutputFile << "Cooks: " << cooksCount << " [Norm: " << NumberOfNormalCooks << ", Veg: " << NumberOfVeganCooks << ", VIP: " << NumberOfVipCooks << ", injured: " << NumOfInjCooks << "]" << endl;
		OutputFile << "Avg Wait = " << (float)TotalWaitTime / count << ", Avg Serv = " << (float)TotalServTime / count << endl;
		OutputFile << "Urgent orders: " << NumberOfUrgentOrders << ", Auto-promoted: " << (float)NumberOfAutoProm/ NumOfNormOrders*100 <<"%"<< endl; 
		OutputFile.close();
		delete[]at;  delete[] ft;  delete[] id; delete[] st; delete[]wt;
	}
}


void Restaurant::PrintInfoCurrentTime(int CurrentTimeStep)
{
	//Making Arrays To get Information From Restuartant
	string* S = new string[5];
	int* NumberOfOrdersDone = new int[3];
	CalculatingNumberofOrdersDone(NumberOfOrdersDone);
	S[0] = "TS: " + to_string(CurrentTimeStep);
	S[1] = "Number of Waiting Orders: Vip: " + to_string(Vip_Order.GetCount()) + " Vegan : " + to_string(VeganOrder.GetCount()) + " Normal : " + to_string(NormalOrder.GetCount());
	S[2] = "Number of available cooks: Vip: " + to_string(VipCookList.GetCount()) + " Vegan: " + to_string(VegCookList.GetCount()) + " Normal: " + to_string(NormCookList.GetCount())+",InJured: "+to_string(Injured_Cooks.GetCount());
	//Temp Storage to Get Cooks and Orders
	S[3] = "";
	Cook* Temp;
	while (Assigned.dequeue(Temp))
	{
		//Type of Cook
		if (Temp->GetType() == TYPE_VIP)
		{
			S[3] = S[3] + "V" + to_string(Temp->GetID());
		}
		else if ((Temp->GetType() == TYPE_NORMAL))
		{
			S[3] = S[3] + "N" + to_string(Temp->GetID());
		}
		else if ((Temp->GetType() == TYPE_VEGAN))
		{
			S[3] = S[3] + "G" + to_string(Temp->GetID());
		}
		//Type Of Order
		if (Temp->getMakingOrder()->GetType() == TYPE_VIP)
		{
			S[3] = S[3] + "(V" + to_string(Temp->getMakingOrder()->GetID()) + ")";
		}
		else if ((Temp->getMakingOrder()->GetType() == TYPE_NORMAL))
		{
			S[3] = S[3] + "(N" + to_string(Temp->getMakingOrder()->GetID()) + ")";
		}
		else if ((Temp->getMakingOrder()->GetType() == TYPE_VEGAN))
		{
			S[3] = S[3] + "(G" + to_string(Temp->getMakingOrder()->GetID()) + ")";
		}
		//Add Space in the End Of each Assigend
		S[3] = S[3] + "  ";
	}

	S[4] = "Number of Orders Served So Far : Vip: " + to_string(NumberOfOrdersDone[2]) + " Vegan : " + to_string(NumberOfOrdersDone[1]) + " Normal : " + to_string(NumberOfOrdersDone[0]);

	pGUI->PrintMessageML(S, 5);

	delete[]S;
	delete[]NumberOfOrdersDone;
}


void Restaurant::CalculatingNumberofOrdersDone(int* Arrayofnumber)
{
	int numberofvip = 0;
	int numberofvegan = 0;
	int numberofnormal = 0;
	//Making a temp Queue for  Order and Empty it in A queue
	Queue<Order*> temp;
	Order* temp1;
	while (OrdersAllDone.dequeue((temp1)))
	{
		temp.enqueue(temp1);
		if (temp1->GetType() == TYPE_VIP)
		{
			numberofvip++;
		}
		else if (temp1->GetType() == TYPE_NORMAL)
		{
			numberofnormal++;
		}
		else if (temp1->GetType() == TYPE_VEGAN)
		{
			numberofvegan++;
		}
	}
	while (temp.dequeue(temp1))
	{
		OrdersAllDone.enqueue(temp1);
	}

	Arrayofnumber[0] = numberofnormal;
	Arrayofnumber[1] = numberofvegan;
	Arrayofnumber[2] = numberofvip;
}








