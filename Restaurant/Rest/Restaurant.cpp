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

// L1 no of cooks from each type

regex MoreThanTwoSpace("\\s{2,}");
regex Tabs("\t");
const std::string oneWhiteSpace = " ";

{
	std::vector<std::string> Container, CookSpdCont, BreakTimeCont;


	// makes string only have 1 consecutive whitespace
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
				NormCookList.InsertFirst(TEMP);    //Inserting at the end O(n) InsertingBeg O(1) ???

			}
			else if (i == TYPE_VEGAN) {
				VeganCook* TEMP = new VeganCook(cID, std::stoi(CookSpdCont[2]), std::stoi(CookSpdCont[3]), std::stoi(BreakTimeCont[3]), std::stoi(BreakTimeCont[4]));
				//Creating ID for Cooks
				cID += (rand() % 15 + 1);
				TEMP->setID(cID);
				VegCookList.InsertFirst(TEMP);

			}
			else {
				VipCook* TEMP = new VipCook(cID, std::stoi(CookSpdCont[4]), std::stoi(CookSpdCont[5]), std::stoi(BreakTimeCont[5]), std::stoi(BreakTimeCont[6]));
				//Creating ID for Cooks
				cID += (rand() % 15 + 1);
				TEMP->setID(cID);
				VipCookList.InsertFirst(TEMP);

			}


		}
	}




	//L4 Injury Chance Thingy
	
	Lines[3] = regex_replace(Lines[3], Tabs, oneWhiteSpace);
	Lines[3] = regex_replace(Lines[3], MoreThanTwoSpace, oneWhiteSpace);
	Container = split_line(Lines[3], oneWhiteSpace);


	InjuryProb = std::stoi(Container[0]);
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
				OrdersServing.RemoveFirst(pOrd);
		    }
			if (VeganOrder.RemoveFirst(pOrd))
			{
				pOrd->setStatus(SRV);
				OrdersServing.RemoveFirst(pOrd);
			}
			if (NormalOrder.RemoveFirst(pOrd))
			{
				pOrd->setStatus(SRV);
				OrdersServing.RemoveFirst(pOrd);
			}

			//moving from in Srv to done
			if (CurrentTimeStep % 5 == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					if (OrdersServing.RemoveFirst(pOrd))
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
			S[1] = "Number of Waiting Orders: Vip: " + to_string(Vip_Order.GetCount()) + " Vegan : " + to_string(VeganOrder.GetCount()) + " Normal : " + to_string(NormalOrder.GetCount());
			//this acts like index so first element is Zero
			S[2] = "Number of available cooks: Vip: " + to_string(VipCookList.GetCount() + 1) + " Vegan: " + to_string(VegCookList.GetCount() + 1) + " Normal: " + to_string(NormCookList.GetCount() + 1);
			pGUI->PrintMessageML(S, 3);

			pGUI->UpdateInterface();
			pGUI->waitForClick();
			CurrentTimeStep++;	//advance timestep
			pGUI->ResetDrawingList();
		}
	pGUI->PrintMessage("Simulation is Done");
	pGUI->waitForClick();

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
	string* S = new string[3];
	//condition of Events and Waiting and Serving
	while (!EventsQueue.isEmpty() || !Vip_Order.isEmpty() || !NormalOrder.isEmpty() || !VeganOrder.isEmpty() || !OrdersServing.isEmpty())
	{
		//print current timestep
		//char timestep[10];
		//itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage("TS: " + to_string(CurrentTimeStep));


		//The next line may add new orders to the Queue waiting
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step

		//Creating an Order and cook Pointer to use them in stimulation
		assigningorders(CurrentTimeStep);
		UpdateCooksandOrdersstatus(CurrentTimeStep);
		

		//////////////////////////////////////////////////////////////////////////////////////////
		FillDrawingList();
		S[0] = "TS: " + to_string(CurrentTimeStep);
		S[1] = "Number of Waiting Orders: Vip: " + to_string(Vip_Order.GetCount()) + " Vegan : " + to_string(VeganOrder.GetCount()) + " Normal : " + to_string(NormalOrder.GetCount());
		//this acts like index so first element is Zero
		S[2] = "Number of available cooks: Vip: " + to_string(VipCookList.GetCount() + 1) + " Vegan: " + to_string(VegCookList.GetCount() + 1) + " Normal: " + to_string(NormCookList.GetCount() + 1);
		pGUI->PrintMessageML(S, 3);

		pGUI->UpdateInterface();
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
		

		//////////////////////////////////////////////////////////////////////////////////////////
	   // interactive Mode
		pGUI->ResetDrawingList();
	}
	pGUI->PrintMessage("Simulation is Done");
	pGUI->waitForClick();
}


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
		NormalOrder.InsertLast(pOrd);
		break;
	case TYPE_VIP:
		Vip_Order.enqueue(pOrd);
		break;
	case TYPE_VEGAN:
		VeganOrder.InsertLast(pOrd);
		break;
	default:
		break;
	}

	OrdersAll.InsertLast(pOrd);


}


//Cancel Function using the Queue
void Restaurant::CancelOrder(int CID)
{
	// Remove it from printing List 
	Node<Order*>* Ord = OrdersAll.RemoveOrderFromList(CID);
	if (Ord == nullptr) return;
	delete Ord;
	//Removing it From the Actual List
     Ord = NormalOrder.RemoveOrderFromList(CID);
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
	Vip_Order.enqueue(OrderToBePromoted);
	delete Ord;



}

void Restaurant::assigningorders(int CurrentTimeStep)////////////////////////afifiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
{
	//Temp Storage for Orders
	Order* pOrd;
	//Serveing all Vip Orders if there is an available Cook
	while ((Vip_Order.peekFront(pOrd)) && (!VipCookList.isEmpty() || !VegCookList.isEmpty() || !NormCookList.isEmpty()))
	{
		//First Dequeue the Order
		Vip_Order.dequeue(pOrd);
		//If there is a vip Cook
		if (!VipCookList.isEmpty())
		{
			VipCook* Cook1;
			VipCookList.RemoveFirst(Cook1);
			Cook1->setMakingOrder(pOrd);
			Cook1->SetStausOfCook(BUSY);
			pOrd->SetWaitTime(CurrentTimeStep - pOrd->GetArrivalTime());
			pOrd->SetServingTime(ceil(pOrd->GetNumberOfDishes() / Cook1->GetSpeed()));
			pOrd->SetFinishTime(pOrd->GetArrivalTime() + pOrd->GetWaitTime() + pOrd->GetServingTime());
			Working_Cook.InsertFirst(Cook1);
			//Update
			pOrd->setStatus(SRV);
			OrdersServing.InsertLast(pOrd);
		}
		//If there is an NormalCook
		else if (!NormCookList.isEmpty())
		{
			NormalCook* Cook1;
			NormCookList.RemoveFirst(Cook1);
			Cook1->setMakingOrder(pOrd);
			Cook1->SetStausOfCook(BUSY);
			pOrd->SetWaitTime(CurrentTimeStep - pOrd->GetArrivalTime());
			pOrd->SetServingTime(ceil(pOrd->GetNumberOfDishes() / Cook1->GetSpeed()));
			pOrd->SetFinishTime(pOrd->GetArrivalTime() + pOrd->GetWaitTime() + pOrd->GetServingTime());
			Working_Cook.InsertFirst(Cook1);
			//Update
			pOrd->setStatus(SRV);
			OrdersServing.InsertLast(pOrd);
		}
		//If there is an Vegan Cook
		else if (!VegCookList.isEmpty())
		{
			VeganCook* Cook1;
			VegCookList.RemoveFirst(Cook1);
			Cook1->setMakingOrder(pOrd);
			Cook1->SetStausOfCook(BUSY);
			pOrd->SetWaitTime(CurrentTimeStep - pOrd->GetArrivalTime());
			pOrd->SetServingTime(ceil(pOrd->GetNumberOfDishes() / Cook1->GetSpeed()));
			pOrd->SetFinishTime(pOrd->GetArrivalTime() + pOrd->GetWaitTime() + pOrd->GetServingTime());
			Working_Cook.InsertFirst(Cook1);
			//Update
			pOrd->setStatus(SRV);
			OrdersServing.InsertLast(pOrd);
		}
	}

	//Finishing all Vegan Orders if there is a Free Vegan Cook
	while (VeganOrder.ReturnFirst(pOrd) && (!VegCookList.isEmpty()))
	{
		VeganOrder.RemoveFirst(pOrd);
		VeganCook* Cook1;
		VegCookList.RemoveFirst(Cook1);
		Cook1->setMakingOrder(pOrd);
		Cook1->SetStausOfCook(BUSY);
		pOrd->SetWaitTime(CurrentTimeStep - pOrd->GetArrivalTime());
		pOrd->SetServingTime(ceil(pOrd->GetNumberOfDishes() / Cook1->GetSpeed()));
		pOrd->SetFinishTime(pOrd->GetArrivalTime() + pOrd->GetWaitTime() + pOrd->GetServingTime());
		Working_Cook.InsertFirst(Cook1);
		//Update
		pOrd->setStatus(SRV);
		OrdersServing.InsertLast(pOrd);
	}

	//Finishing all Normal Orders if there is a free Normal or a vip Cook
	while (NormalOrder.ReturnFirst(pOrd) && (!VipCookList.isEmpty() || !NormCookList.isEmpty()))
	{
		NormalOrder.RemoveFirst(pOrd);
		if (!NormCookList.isEmpty())
		{
			NormalCook* Cook1;
			NormCookList.RemoveFirst(Cook1);
			Cook1->setMakingOrder(pOrd);
			Cook1->SetStausOfCook(BUSY);
			pOrd->SetWaitTime(CurrentTimeStep - pOrd->GetArrivalTime());
			pOrd->SetServingTime(ceil(pOrd->GetNumberOfDishes() / Cook1->GetSpeed()));
			pOrd->SetFinishTime(pOrd->GetArrivalTime() + pOrd->GetWaitTime() + pOrd->GetServingTime());
			Working_Cook.InsertFirst(Cook1);
			//Update
			pOrd->setStatus(SRV);
			OrdersServing.InsertLast(pOrd);
		}
		//If there is an NormalCook
		else if (!VipCookList.isEmpty())
		{
			VipCook* Cook1;
			VipCookList.RemoveFirst(Cook1);
			Cook1->setMakingOrder(pOrd);
			Cook1->SetStausOfCook(BUSY);
			pOrd->SetWaitTime(CurrentTimeStep - pOrd->GetArrivalTime());
			pOrd->SetServingTime(ceil(pOrd->GetNumberOfDishes() / Cook1->GetSpeed()));
			pOrd->SetFinishTime(pOrd->GetArrivalTime() + pOrd->GetWaitTime() + pOrd->GetServingTime());
			Working_Cook.InsertFirst(Cook1);
			//Update
			pOrd->setStatus(SRV);
			OrdersServing.InsertLast(pOrd);
		}
	}
}


void Restaurant:: UpdateCooksandOrdersstatus(int CurrentTimeStep)/////afifiiiiiiiiiiiiiiiiiiiiiiiii
{
	//Making List of Cooks to array to Check Status of each one
	int size;
	Cook** WorkOrBusyCook = Working_Cook.toArray(size);
	for (int i = 0; i < size; i++)
	{
		//Check if the Cook is Busy and Its Order is finished
		if (WorkOrBusyCook[i]->GetCookStatus() == BUSY  && WorkOrBusyCook[i]->getMakingOrder()->GetFinishTime() == CurrentTimeStep)
		{
			//Get a pointer to that Order
			Order* pOrd = WorkOrBusyCook[i]->getMakingOrder();
			pOrd->setStatus(DONE);
			OrdersAllDone.enqueue(pOrd);
			OrdersServing.DeleteNode(pOrd);
			WorkOrBusyCook[i]->setMakingOrder(nullptr);
			WorkOrBusyCook[i]->SetStausOfCook(AVAILABLE);
			WorkOrBusyCook[i]->SetFinishedOrders(WorkOrBusyCook[i]->GetFinishedOrders() + 1);
			//Check if the Cook would Take a break or No
			if (WorkOrBusyCook[i]->GetFinishedOrders() == WorkOrBusyCook[i]->getBreakAfterN())
			{
				WorkOrBusyCook[i]->SetFinishedOrders(0);
				WorkOrBusyCook[i]->SetRemainingBreak(WorkOrBusyCook[i]->GetBreakTime());
				WorkOrBusyCook[i]->SetStausOfCook(BREAK);
			}
			//Return it to the list
			else
			{
				Working_Cook.DeleteNode(WorkOrBusyCook[i]);
				if (WorkOrBusyCook[i]->GetType() == TYPE_VEGAN)
				{
					VeganCook* Cook1 = (VeganCook*)WorkOrBusyCook[i];
					VegCookList.InsertFirst(Cook1);
				}
				else if (WorkOrBusyCook[i]->GetType() == TYPE_NORMAL)
				{
					NormalCook* Cook1 = (NormalCook*)WorkOrBusyCook[i];
					NormCookList.InsertFirst(Cook1);
				}
				else if (WorkOrBusyCook[i]->GetType() == TYPE_VIP)
				{
					VipCook* Cook1 = (VipCook*)WorkOrBusyCook[i];
					VipCookList.InsertFirst(Cook1);
				}
			}
		}
		//Check if cook is in break
		else if (WorkOrBusyCook[i]->GetCookStatus() == BREAK)
		{
			//Either he finishes or decrease remaining time
			if (WorkOrBusyCook[i]->GetRemainingBreak() == 0)
			{
				//Make it avaiable then add it to the List
				WorkOrBusyCook[i]->SetStausOfCook(AVAILABLE);
				Working_Cook.DeleteNode(WorkOrBusyCook[i]);
				if (WorkOrBusyCook[i]->GetType() == TYPE_VEGAN)
				{
					VeganCook* Cook1 = (VeganCook*)WorkOrBusyCook[i];
					VegCookList.InsertFirst(Cook1);
				}
				else if (WorkOrBusyCook[i]->GetType() == TYPE_NORMAL)
				{
					NormalCook* Cook1 = (NormalCook*)WorkOrBusyCook[i];
					NormCookList.InsertFirst(Cook1);
				}
				else if (WorkOrBusyCook[i]->GetType() == TYPE_VIP)
				{
					VipCook* Cook1 = (VipCook*)WorkOrBusyCook[i];
					VipCookList.InsertFirst(Cook1);
				}

			}
			else if (WorkOrBusyCook[i]->GetBreakTime() != 0)
			{
				WorkOrBusyCook[i]->setBreakAfterN(WorkOrBusyCook[i]->GetBreakTime() - 1);
			}
		}

	}
	//deallcoate the Memory 
	delete[]WorkOrBusyCook;
}







/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////

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


