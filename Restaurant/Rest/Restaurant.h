#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\PriorityQueue.h"
#include"../Generic_DS/List.h"
#include "..\Generic_DS\PriorityQueueMax.h"
#include "..\Generic_DS\PriorityQueueMin.h"

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
	Queue <VeganCook*> VegCookList;
	Queue <NormalCook*> NormCookList;
	Queue <VipCook*> VipCookList;
	PriorityQueueMin<Cook*> Working_Cook;	//Working Cooks Busy
	PriorityQueueMin <Cook*> Break_Cooks; //Cooks in Break

	//Queue Assigned for drawing information of Current Time Step
	Queue <Cook*> Assigned;

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>


	//List of orders
	List<Order*> NormalOrder;
	Queue <Order*> VeganOrder;
	PriorityQueueMax <Order*> Vip_Order;
 

	//Our Orders that are in Servicing
	PriorityQueueMin <Order*> OrdersServing;
	//OurOrdersDone
	Queue <Order*> OrdersAllDone;
	
	int PromotionVariable , UrgentVariable ,InjuryProb ;


public:
	
	Restaurant();
	~Restaurant();
	
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

	// for testing
	void Test();
	void TestPHII();

/// ================================================================================================== 

	//Queuing in the Restaurant
	void AddtoOrderQueue(Order* pOrd);


	// Cancel an order if it is waiting
	void CancelOrder(int CID);

	//promo the order 
	void PromOrder(int CID , int ExtraMoney);


	//Functions for Simulatiom
	void assigningorders(int timeStep);
	void UpdateCooksandOrdersstatus(int timeStep);
	void CalculatingNumberofCooks(int* Arrayofnumber);
	void CalculatingNumberofOrders(int* Arrayofnumber);
	void CalculatingNumberofOrdersDone(int* Arrayofnumber);
	void PrintInfoCurrentTime(int CurrentTimeStep);
};

#endif