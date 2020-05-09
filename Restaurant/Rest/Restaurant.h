#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_
#include<cmath>
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include"..\PQueueLinkedList.h"
#include"..\LinkedList.h"
#include "Order.h"
#include"Motorcycle.h"
#include"..\ArrayList.h"
// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	int AutoProm;
	/// ==>
	//Types of Active Orders Queues

	//1)FROZEN Orders
	Queue<Order*> ActiveFROZENOrder[4];
	//2)VIP Orders
	PQueueLinkedList<Order*,int>ActiveVIPOrder[4];
	//3)NORMAL Orders
	LinkedList<Order*> ActiveNORMALOrder[4] ;

	/// ==>
	//Assighned Orders Lists

	//1)FROZEN Orders
	PQueueLinkedList<Order*,int> AssighnedFROZENOrder[4];
	//2)VIP Orders
	PQueueLinkedList<Order*,int>AssighnedVIPOrder[4];
	//3)NORMAL Orders
	PQueueLinkedList<Order*,int> AssighnedNORMALOrder[4] ;

	/// ==>
	//Available Motors Queues for regions

	//1)Frozen Motors
	PQueueLinkedList<Motorcycle*,int> FrozMotors[4];
	//2)Normal Motors
	PQueueLinkedList<Motorcycle*,int> NormalMotors[4];
	//3)Fast Motors
	PQueueLinkedList<Motorcycle*,int> FastMotors[4];

	/// ==>
	//Inservise Motors Lists

	//1)Frozen Motors
	PQueueLinkedList<Motorcycle*,int> InserviseFrozMotors[4];
	//2)Normal Motors
	PQueueLinkedList<Motorcycle*,int> InserviseNormalMotors[4];
	//3)Fast Motors
	PQueueLinkedList<Motorcycle*,int> InserviseFastMotors[4];

	/// ==>
	//Servised Orders
	Queue<Order*> ServicedOrders;
	  int ServicedVIPOrders[4];
	 int ServicedFROZENOrders[4];
	 int ServicedNORMALOrders[4];

	 /// ==>
	//Damaged Motors Lists

	//1)Frozen Motors
	PQueueLinkedList<Motorcycle*,int> DamagedFrozMotors[4];
	//2)Normal Motors
	PQueueLinkedList<Motorcycle*,int> DamagedNormalMotors[4];
	//3)Fast Motors
	PQueueLinkedList<Motorcycle*,int> DamagedFastMotors[4];


public:
	void Reset();
	Restaurant();
	~Restaurant();
	void AddEvent(Event*pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	/// ==> 
	//Dealing with the Queues and lists of Orders functions

	//1)Normal Queue
	void AddtoFROZENOrders(Order* po,int i);	
	Order* getFROZENOrders(int i);			

	//2)VIP Queue
	void AddtoVipOrders(Order* po,int i);	
	Order* getVipOrders(int i);			

	//3)Normal Linkedlist
	void AddtoNormalOrders(Order* po,int i);	
	Order* getNormalOrders(int i);			

	/// ==>
	//For Cancelation Event
	Order* GetNormalOederWithId(int Id,int &Position);
	void RemoveFromNORMALOrdersList(int Position,int i);

	/// ==>
	//For RunSimulation Functions
	void Interactive_Mode();
	void Step_Mode();
	void Silent_Mode();
	/// ==>
	//For Window Updating Functions
	void ResetPQueueWindow(PQueueLinkedList<Order*,int> &Rhs);
	void ResetQueueWindow (Queue<Order*> &Rhs );
	void ResetListWindow(LinkedList<Order*>&Rhs);
	void ResetWindowALL();
	void printOutput(string(&s)[4]);

	/// ==>
	//For Assigning Order to Motors Functions
	void AssighnOrdersToMotors(int TimeStep,string(&s)[4]);
	void AssighnOrder_PQueue(int TimeStep,PQueueLinkedList<Order*,int>& WaitingOrders,PQueueLinkedList<Order*,int>& InServiceOrders,PQueueLinkedList<Motorcycle*,int>& AvailableMotors,PQueueLinkedList<Motorcycle*,int>& InServiceeMotors,string&s);
	void AssighnOrder_Queue(int TimeStep,Queue<Order*>& WaitingOrders,PQueueLinkedList<Order*,int>& InServiceOrders,PQueueLinkedList<Motorcycle*,int>& AvailableMotors,PQueueLinkedList<Motorcycle*,int>& InServiceeMotors,string&s);
	void AssighnOrder_List(int TimeStep,LinkedList<Order*>& WaitingOrders,PQueueLinkedList<Order*,int>& InServiceOrders,PQueueLinkedList<Motorcycle*,int>& AvailableMotors,PQueueLinkedList<Motorcycle*,int>& InServiceeMotors,string&s);

	/// ==>
	//For Loading Function
	void Load();
	void Output();
	char Region(int m);

	void Finishing(int CurrentTimeStep);
	void Repair(int);
	void DeleteActiveOrders();
	bool AllOrdersAREserved();
	bool AllMotorsCameBack();
	bool ALLMotorsAreRepaird();
	
};
#endif