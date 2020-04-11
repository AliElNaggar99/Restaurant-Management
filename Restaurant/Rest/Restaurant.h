#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Events\Event.h"

#include<fstream>
#include "Order.h"
#include<vector>
//
//what i am doing
// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	LinkedList<VeganCook*> VegCookList;
	LinkedList<NormalCook*> NormCookList;
	LinkedList<VipCook*> VipCookList;
	LinkedList<Cook*> Busy_Break_Cooks;

	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	int PromotionVariable;

public:
	
	void SaveFile(Order** Array, int Numberoftotalorders, Cook** Arrayoofcooks,int NumberOfcooks);
	Restaurant();
	~Restaurant();
	int* CalculatingNumberofCooks(Cook** ArrayOfcook, int totalcooks);
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	
	


	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//
	void ReadFromFile(); //Hosny
	std::vector<std::string> split_line(const std::string & line , std::string delimeter); //Honsy

/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	//void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ================================================================================================== 



};

#endif