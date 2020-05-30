#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
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
	PriorityQueueMin<Cook*> Working_Cook;	//Cook with lowest time remaining until he finishes the order is first
	PriorityQueueMin <Cook*> Break_Cooks,Rest_Cooks;  //Cook with lowest time remaining on break goes out first
	PriorityQueueMin <Cook*> Injured_Cooks; // Injured Cooks

	//Queue Assigned for drawing information of Current Time Step
	Queue <Cook*> Assigned;

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>

	//Assigning a single order to a cook
	void AssignOrder(Cook*, Order*,int,Cook_Status = BUSY);

	//List of orders
	List<Order*> NormalOrder;
	Queue <Order*> VeganOrder;
	PriorityQueueMax <Order*> Vip_Order;	   //According to the highest value of priority equation 
 

	//Our Orders that are in Servicing
	PriorityQueueMin <Order*> OrdersServing;  //Order that will finish in lowest time step has highest priority
	//Our OrdersDone
	Queue <Order*> OrdersAllDone;

	//Variables for the Number of Cooks
	int NumberOfNormalCooks=0;
	int NumberOfVeganCooks=0;
	int NumberOfVipCooks=0;
	
	//specific Details for the Restaurant 
	int PromotionVariable, UrgentVariable;
	float InjuryProb;

	int NumberOfAutoProm=0;
	int NumOfInjCooks=0;
	int NumberOfUrgentOrders = 0;

	//Function that returns the Priority of the Orders with request to its Details
	int PriorityEquation(Order*);


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

	//promote the order 
	void PromOrder(int CID , int ExtraMoney);


	//Functions for Simulatiom
	void AssigningOrders(int timeStep);
	void UpdateCooksandOrdersstatus(int timeStep);
	void CalculatingNumberofOrdersDone(int* Arrayofnumber);
	void PrintInfoCurrentTime(int CurrentTimeStep);

	//Promotion & Urgency

	void CheckAutoProm(int);
	void CheckUrgency(int);
	void CheckInjuredCooks(int CurrentTimeStep);

	void SaveFile();

};

#endif