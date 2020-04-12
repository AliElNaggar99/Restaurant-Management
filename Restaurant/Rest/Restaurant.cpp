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


std::vector<std::string> Lines(5);
int Counter = 0 ;
while (getline(toBeReadFile,Lines[Counter]) && Counter++ != 4);

// L1 no of cooks from each type

regex MoreThanTwoSpace("\\s{2,}");
const std::string oneWhiteSpace = " ";
std::vector<std::string> Container;


// makes string only have 1 consecutive whitespace
Lines[0] = regex_replace(Lines[0],MoreThanTwoSpace,oneWhiteSpace);
Container = split_line(Lines[0],oneWhiteSpace);
//Remeber to delete Cooks in destructor of Restaurant

for (int i = 0; i < TYPE_CNT; i++) {
	for (int j = 0; j < std::stoi(Container[i]); j++) {

		if (i == TYPE_NORMAL) {
			NormalCook* TEMP = new NormalCook;
			//Creating ID for Cooks
			cID += (rand() % 15 + 1);
			TEMP->setID(cID);
			NormCookList.InsertEnd(TEMP);
			//Creating a pointer to the Cook to add in Cook list
			Cook* CookPointer = TEMP;
			Free_Cook.InsertEnd(TEMP);
		}
		else if (i == TYPE_VEGAN) {
			VeganCook* TEMP = new VeganCook;
			//Creating ID for Cooks
			cID += (rand() % 15 + 1);
			TEMP->setID(cID);
			VegCookList.InsertEnd(TEMP);
			//Creating a pointer to the Cook to add in Cook list
			Cook* CookPointer = TEMP;
			Free_Cook.InsertEnd(TEMP);
		}
		else{
			VipCook* TEMP = new VipCook;
			//Creating ID for Cooks
			cID += (rand() % 15 + 1);
			TEMP->setID(cID);
			VipCookList.InsertEnd(TEMP);
			//Creating a pointer to the Cook to add in Cook list
			Cook* CookPointer = TEMP;
			Free_Cook.InsertEnd(TEMP);
			
		}


	}
}



//L2 cook speed for ea
Lines[1] = regex_replace(Lines[1],MoreThanTwoSpace,oneWhiteSpace);
Container = split_line(Lines[1],oneWhiteSpace);
NormalCook::SetSpeed(std::stoi(Container[0]));
VeganCook::SetSpeed(std::stoi(Container[1]));
VipCook::SetSpeed(std::stoi(Container[2]));





//L3 (BreakAfter n orders) BreakDuration
Lines[2] = regex_replace(Lines[2],MoreThanTwoSpace,oneWhiteSpace);

Container = split_line(Lines[2],oneWhiteSpace);

Cook::setBreakAfterN(std::stoi(Container[0]));
VipCook::SetBreakTime(std::stoi(Container[3]));
NormalCook::SetBreakTime(std::stoi(Container[1]));
VeganCook::SetBreakTime(std::stoi(Container[2]));


//L4 Promotion Variable
PromotionVariable = std::stoi(Lines[3]);

//L5 No of events in file
int numEvents = std::stoi(Lines[4]);


//Resizing vector
Lines.resize(5+numEvents);
// test that this reads from the begining not from the line you stopped at
while (getline(toBeReadFile,Lines[Counter]) && Counter++ != 4+numEvents) ;

for(int i = 5; i < (5+numEvents);i++){
	Lines[i] = regex_replace(Lines[i], MoreThanTwoSpace, oneWhiteSpace);
	std::vector<std::string> SplitString = split_line(Lines[i]," ");
	char FirstLetter = *std::begin(SplitString[0]); // test that conversion works

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
		//swaped between Splitstring 3 and 2 as 2 is ID not 3
		Event* A = new ArrivalEvent(std::stoi(SplitString[3]), std::stoi(SplitString[2]), oType, std::stoi(SplitString[4]), std::stod(SplitString[5]));

		// enqueue the event
		EventsQueue.enqueue(A);

	}
	else if (FirstLetter == 'X') {
		//Cancellation event
		// making a pointer of Event to add it to Queue dynamically so it doesn't remvoe after deqeueing
		//swaped between Splitstring 1 and 2 as 1 is ID not 2
		Event* C = new CancellationEvent(std::stoi(SplitString[2]), std::stoi(SplitString[1]));
	
		// enqueue the event
		EventsQueue.enqueue(C);

	}
	else{
		// making a pointer of Event to add it to Queue dynamically so it doesn't remvoe after deqeueing
		Event* P = new PromotionEvent(std::stoi(SplitString[2]), std::stoi(SplitString[1]),std::stoi(SplitString[3]));
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

	//filling cook list
	int i = 0;
	//temp storage for cook
	Cook* Pc;
	while (Free_Cook.findPos(Pc, i))
	{
		pGUI->AddToDrawingList(Pc);	
		i++;
	}

	/*filling the Orders list
	int size = 0;
	Order* pOrd;
	Order** Orders_Array = OrdersAll.toArray(size);
		
	  for(int i=0; i<size; i++)
	  {
		  pOrd = Orders_Array[i];
		  pGUI->AddToDrawingList(pOrd);
	  }*/

	  //filling the waiting - Orders
	  int size = 0;
	  Order* pOrd;
	  Order** Orders_Array = OrdersAll.toArray(size);

	  for (int i = 0; i < size; i++)
	  {
		  pOrd = Orders_Array[i];
		  //if it is not waiting don't print
		  if(pOrd->getStatus() == WAIT)
		     pGUI->AddToDrawingList(pOrd);
	  }

	  //filling the In - Serve Orders
	   size = 0;
	  Orders_Array = OrdersServing.toArray(size);

	  for (int i = 0; i < size; i++)
	  {
		  pOrd = Orders_Array[i];
		  pGUI->AddToDrawingList(pOrd);
	  }
	  //filling the DoneOrders
	   size = 0;
	  Orders_Array = OrdersAllDone.toArray(size);

	  for (int i = 0; i < size; i++)
	  {
		  pOrd = Orders_Array[i];
		  pGUI->AddToDrawingList(pOrd);
	  }

}



// Simple Stimulation for Phase I to test Ali:
void Restaurant::Test()
{
	//reading File from user

	ReadFromFile();

	//all lists are filled by cocks and events


	pGUI->PrintMessage("Hello, u sexyyy");
	pGUI->waitForClick();
	//Check Event list 
	int CurrentTimeStep = 0;

	while (!EventsQueue.isEmpty() || !OrdersAll.isEmpty())
		{
			//print current timestep
			//char timestep[10];
			//itoa(CurrentTimeStep,timestep,10);	
			pGUI->PrintMessage("TS: " + to_string(CurrentTimeStep));
	
	
	     	//The next line may add new orders to the Queue
			ExecuteEvents(CurrentTimeStep);	//execute all events at current time step

			//Moving Orders form Waiting to Serves
			Order* pOrd;
			if (Vip_Order.dequeue(pOrd))
			{
				pOrd->setStatus(SRV);
				OrdersServing.enqueue(pOrd);
		    }
			if (VeganOrder.dequeue(pOrd))
			{
				pOrd->setStatus(SRV);
				OrdersServing.enqueue(pOrd);
			}
			if (NormalOrder.dequeue(pOrd))
			{
				pOrd->setStatus(SRV);
				OrdersServing.enqueue(pOrd);
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
			pGUI->UpdateInterface();
			pGUI->waitForClick();
			CurrentTimeStep++;	//advance timestep
			pGUI->ResetDrawingList();
		}

}



////////////////////////////////////////////////////////////////////////////////////////////////
///// ==> 
/////  DEMO-related functions. Should be removed in phases 1&2
//
////Begin of DEMO-related functions
//
////This is just a demo function for project introductory phase
////It should be removed starting phase 1
//void Restaurant::Just_A_Demo()
//{
//	
//	//
//	// THIS IS JUST A DEMO FUNCTION
//	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
//	
//	int EventCnt;	
//	Order* pOrd;
//	Event* pEv;
//	srand(time(NULL));
//
//	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
//	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer
//
//	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
//	pGUI->waitForClick();
//		
//	//Just for sake of demo, generate some cooks and add them to the drawing list
//	//In next phases, Cooks info should be loaded from input file
//	int C_count = 12;	
//
//	Cook **arrayOfCookPointers = new Cook*[C_count];
//
//	Cook **pC = new Cook*[C_count];
//
//	int cID = 1;
//
//	for(int i=0; i<C_count; i++)
//	{
//		cID+= (rand()%15+1);	
//		arrayOfCookPointers[i]->setID(cID);
//		arrayOfCookPointers[i]->setType((ORD_TYPE)(rand()%TYPE_CNT));
//	}	
//
//		
//	int EvTime = 0;
//
//	int O_id = 1;
//	
//	//Create Random events and fill them into EventsQueue
//	//All generated event will be "ArrivalEvents" for the demo
//	for(int i=0; i<EventCnt; i++)
//	{
//		O_id += (rand()%4+1);		
//		int OType = rand()%TYPE_CNT;	//Randomize order type		
//		EvTime += (rand()%5+1);			//Randomize event time
//		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType);
//		EventsQueue.enqueue(pEv);
//
//	}	
//
//	// --->   In next phases, no random generation is done
//	// --->       EventsQueue should be filled from actual events loaded from input file
//
//	
//	
//	
//	
//	//Now We have filled EventsQueue (randomly)
//	int CurrentTimeStep = 1;
//	
//
//	//as long as events queue is not empty yet
//	while(!EventsQueue.isEmpty())
//	{
//		//print current timestep
//		char timestep[10];
//		itoa(CurrentTimeStep,timestep,10);	
//		pGUI->PrintMessage(timestep);
//
//
//		//The next line may add new orders to the DEMO_Queue
//		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
//		
//
///////////////////////////////////////////////////////////////////////////////////////////
//		/// The next code section should be done through function "FillDrawingList()" once you
//		/// decide the appropriate list type for Orders and Cooks
//		
//		//Let's add ALL randomly generated Cooks to GUI::DrawingList
//		for(int i=0; i<C_count; i++)
//			pGUI->AddToDrawingList(arrayOfCookPointers[i]);
//		
//		//Let's add ALL randomly generated Ordes to GUI::DrawingList
//		int size = 0;
//		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);
//		
//		for(int i=0; i<size; i++)
//		{
//			pOrd = Demo_Orders_Array[i];
//			pGUI->AddToDrawingList(pOrd);
//		}
///////////////////////////////////////////////////////////////////////////////////////////
//
//		pGUI->UpdateInterface();
//		Sleep(1000);
//		CurrentTimeStep++;	//advance timestep
//		pGUI->ResetDrawingList();
//	}
//
//	delete []arrayOfCookPointers;
//
//
//	pGUI->PrintMessage("generation done, click to END program");
//	pGUI->waitForClick();
//
//	
//}
////////////////



int* Restaurant::CalculatingNumberofCooks(Cook** ArrayOfcook, int totalcooks)
{
	int numberofvipcooks = 0;
	int numberofvegancooks = 0;
	int numberofnormalcooks = 0;
	for(int i=0;i<totalcooks;i++)
	{
		if (dynamic_cast <VipCook*> (ArrayOfcook[i]))
		{
			numberofvipcooks++;
		}
		if (dynamic_cast <NormalCook*> (ArrayOfcook[i]))
		{

			numberofnormalcooks++;
		}
		if (dynamic_cast <VeganCook*> (ArrayOfcook[i]))
		{

			numberofvegancooks++;
		}
	}
	int* Arrayofnumber = new int[4];
		Arrayofnumber[0] = totalcooks;
		Arrayofnumber[1] = numberofnormalcooks;
		Arrayofnumber[2] = numberofvegancooks;
		Arrayofnumber[3] = numberofvipcooks;
		return Arrayofnumber;
}



void Restaurant::SaveFile(Order** ArrayofOrders, int NumberOfOrders,Cook**arrayofCooks,int NumberofCooks)
{
	ofstream OutputFile;
	OutputFile.open("OutPut", ios::out);
	OutputFile << "FT" << "     " << "ID" << "     " << "AT" << "     " << "WT" << "    " << "ST" << endl;
	int numberofveganorders =0;
	int numberofnormalorders =0;
	int numberofviporders = 0;
	int totalwaitingtime = 0;
	int totalservingtime = 0;
	for (int i = 0; i < NumberOfOrders; i++)
	{   
		int ft= ArrayofOrders[i]->GetFinishTime();
		int id= ArrayofOrders[i]->GetID();
		int at = ArrayofOrders[i]->GetArrivalTime();
		int st =  ArrayofOrders[i]->GetFinishTime();
		int wt=ft-at-st;
		totalwaitingtime += wt;
		totalservingtime += st;

		OutputFile << ft << "     " << id << "     " << id << "     " << at << "     " << wt << "     " << st << endl;


	}
	for (int i = 0; i < NumberOfOrders ; i++)
	{
		if (ArrayofOrders[i]->GetType() == TYPE_VIP)
		{
			numberofviporders++;
		}
		if (ArrayofOrders[i]->GetType() == TYPE_VEGAN)
		{
			numberofveganorders++;
		}
		if (ArrayofOrders[i]->GetType() == TYPE_NORMAL)
		{
			numberofnormalorders++;
		}
		
	}
	int* arrofnumbers = CalculatingNumberofCooks(arrayofCooks, NumberofCooks);
	OutputFile << "Orders: [Norm" << numberofnormalorders << ", Veg:" << numberofveganorders << ", VIP;" << numberofviporders <<"]" <<endl;
	OutputFile << "Cooks:" << arrofnumbers[0] << "    [" << arrofnumbers[1] << arrofnumbers[2] << arrofnumbers[3] << "]" << endl;
	OutputFile << "Avg Wait = " << totalwaitingtime / NumberOfOrders << "Avg Serv " << totalwaitingtime / NumberOfOrders << "" << endl;
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
		NormalOrder.enqueue(pOrd);
		break;
	case TYPE_VIP:
		Vip_Order.enqueue(pOrd);
		break;
	case TYPE_VEGAN:
		VeganOrder.enqueue(pOrd);
		break;
	default:
		break;
	}

	OrdersAll.enqueue(pOrd);


}


//Cancel Function using the Queue
void Restaurant::CancelOrder(int CID)
{
	//taking a pointers to the queue
	int size = 0;
	Order* pOrd= nullptr;
	Order** Orders_Array = OrdersAll.toArray(size);
	//index of order that we want to delete
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		//searching for order in the queue where same id and it is normal and it is waitting
		if (CID == Orders_Array[i]->GetID() && Orders_Array[i]->GetType() == TYPE_NORMAL && Orders_Array[i]->getStatus() == WAIT)
		{
			pOrd = Orders_Array[i];
			index++;
		}
	}
	if (pOrd == nullptr)
		return;
	//temp for dequeuing
	Order* pOrdTemp = nullptr;
	//Deqeueing the whole arrays and it is saved in Orders_array
	while (OrdersAll.dequeue(pOrdTemp))
	{}

	//filling the queue again but without that order
	for (int i = 0; i < size; i++)
	{
		if (i != index)
		{
			OrdersAll.enqueue(Orders_Array[i]);
		}
	}
 	delete pOrd;
	return;

}



//Promotion Function (I think it is finished)
void Restaurant::PromOrder(int CID , int ExtraMoney)
{
	//taking a pointers to the queue
	int size = 0;
	Order* pOrd = nullptr;
	Order** Orders_Array = OrdersAll.toArray(size);


	for (int i = 0; i < size; i++)
	{
		//searching for order in the queue where same id and it is normal and it is waitting
		if (CID == Orders_Array[i]->GetID() && Orders_Array[i]->GetType() == TYPE_NORMAL && Orders_Array[i]->getStatus() == WAIT)
		{
			pOrd = Orders_Array[i];
		}
	}
	if (pOrd == nullptr)
		return;
	//Changing type to vip and adding extra Money
	pOrd->setType(TYPE_VIP);
	pOrd->SetTotalMoney(pOrd->GetTotalMoney() + ExtraMoney);


	return;

}


/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////



