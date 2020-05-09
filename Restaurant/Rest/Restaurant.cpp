#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"..\CancelEvent.h"
#include"..\PromotionEvent.h"
#include"..\Rest\Order.h"
Restaurant::Restaurant() 
{
	pGUI = NULL;
	for (int i = 0; i < 4; i++)
	{
		ServicedVIPOrders[i]=0;
	}

	for (int i = 0; i < 4; i++)
	{
		ServicedFROZENOrders[i]=0;
	}
	for (int i = 0; i < 4; i++)
	{
		ServicedNORMALOrders[i]=0;
	}
}

//////////////////////////////////////////////

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	pGUI->ResetDrawingList();	
	switch (mode)	
	{
	case MODE_INTR:
		Interactive_Mode();
		break;
	case MODE_STEP:
		Step_Mode();
		break;
	case MODE_SLNT:
		Silent_Mode();
		break;
	case MODE_DEMO:
		break;

	};

}

//////////////////////////////////////////////

Order* Restaurant::GetNormalOederWithId(int Id,int& Position)
{
	for(int i=0;i<ActiveNORMALOrder[0].getSize();i++)
	{
		Order*ptr=ActiveNORMALOrder[0].getEntry(i+1);
		if(ptr->GetID()==Id)
		{
			Position=i+1;
			return ptr;
		}
	}
	for(int i=0;i<ActiveNORMALOrder[1].getSize();i++)
	{
		Order*ptr=ActiveNORMALOrder[1].getEntry(i+1);
		if(ptr->GetID()==Id)
		{
			Position=i+1;
			return ptr;
		}
	}
	for(int i=0;i<ActiveNORMALOrder[2].getSize();i++)
	{
		Order*ptr=ActiveNORMALOrder[2].getEntry(i+1);
		if(ptr->GetID()==Id)
		{
			Position=i+1;
			return ptr;
		}
	}
	for(int i=0;i<ActiveNORMALOrder[3].getSize();i++)
	{
		Order*ptr=ActiveNORMALOrder[3].getEntry(i+1);
		if(ptr->GetID()==Id)
		{
			Position=i+1;
			return ptr;
		}
	}
	return NULL;
}

//////////////////////////////////////////////

//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//////////////////////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

//////////////////////////////////////////////

Restaurant::~Restaurant()
{
	delete pGUI;
}

//////////////////////////////////////////////

void Restaurant::AddtoVipOrders(Order* pOrd,int i)
{
	ActiveVIPOrder[i].enqueue(pOrd,pOrd->GetPriority());
}	
Order* Restaurant::getVipOrders(int i)
{
	Order* pOrd;
	ActiveVIPOrder[i].dequeue(pOrd);
	return pOrd;
}

//////////////////////////////////////////////

void Restaurant::AddtoNormalOrders(Order* pOrd,int i)
{
	ActiveNORMALOrder[i].InsertBeg(pOrd);
}	
Order* Restaurant::getNormalOrders(int i)
{
	Order* pOrd;
	ActiveNORMALOrder[i].DeleteLast(pOrd);
	return pOrd;
}

//////////////////////////////////////////////

void Restaurant::AddtoFROZENOrders(Order* pOrd,int i)
{
	ActiveFROZENOrder[i].enqueue(pOrd);
}	

Order* Restaurant::getFROZENOrders(int i)
{
	Order* pOrd;
	ActiveFROZENOrder[i].dequeue(pOrd);
	return pOrd;
}
void Restaurant::RemoveFromNORMALOrdersList(int Position,int i)
{
	ActiveNORMALOrder[i].remove(Position);
}

//////////////////////////////////////////////

void Restaurant::Interactive_Mode()
{
	string AssignOrdersToMotor[4];
	pGUI->PrintMessage("Enter file name ^_^");
	Load();
	int CurrentTimeStep = 1;
	pGUI->PrintMessage("Click on the mouse to deliver the order ^_^");
	pGUI->waitForClick();

	while(!EventsQueue.isEmpty()|| !AllOrdersAREserved() || !AllMotorsCameBack()||!ALLMotorsAreRepaird())
	{   
		for (int i = 0; i < 4; i++)
		{
			AssignOrdersToMotor[i]="";
		}
		ExecuteEvents(CurrentTimeStep);
		Finishing(CurrentTimeStep);
		Repair(CurrentTimeStep);
		AssighnOrdersToMotors(CurrentTimeStep,AssignOrdersToMotor);
		ResetWindowALL();
		pGUI->PrintMessage("Click on the mouse to deliver the next order  "+to_string(CurrentTimeStep));
		printOutput(AssignOrdersToMotor);
		CurrentTimeStep++;
		pGUI->waitForClick();
	}
	Output();
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}
void Restaurant::Step_Mode()
{
	string AssignOrdersToMotor[4];
	pGUI->PrintMessage("Enter file name ^_^");
	Load();
	int CurrentTimeStep = 1;
	pGUI->PrintMessage("Click on the mouse to start delivering ^_^");
	pGUI->waitForClick();
	while(!EventsQueue.isEmpty()|| !AllOrdersAREserved() || !AllMotorsCameBack()||!ALLMotorsAreRepaird())
	{   
		for (int i = 0; i < 4; i++)
		{
			AssignOrdersToMotor[i]="";
		}
		ExecuteEvents(CurrentTimeStep);
		Finishing(CurrentTimeStep);
		Repair(CurrentTimeStep);
		AssighnOrdersToMotors(CurrentTimeStep,AssignOrdersToMotor);
		ResetWindowALL();
			pGUI->PrintMessage(" ");
		printOutput(AssignOrdersToMotor);
		CurrentTimeStep++;
		Sleep(1000);
	}
	Output();
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}
void Restaurant::Silent_Mode()
{
	string AssignOrdersToMotor[4];
	pGUI->PrintMessage("Enter file name ^_^");
	Load();
	int CurrentTimeStep = 1;
	pGUI->PrintMessage("Click on the mouse to start delivering ^_^");
	pGUI->waitForClick();
	while(!EventsQueue.isEmpty()|| !AllOrdersAREserved() || !AllMotorsCameBack()||!ALLMotorsAreRepaird())
	{   
		for (int i = 0; i < 4; i++)
		{
			AssignOrdersToMotor[i]="";
		}
		ExecuteEvents(CurrentTimeStep);
		Finishing(CurrentTimeStep);
		Repair(CurrentTimeStep);
		AssighnOrdersToMotors(CurrentTimeStep,AssignOrdersToMotor);
			pGUI->PrintMessage(" ");
		CurrentTimeStep++;
	}
	Output();
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}
void Restaurant::ResetQueueWindow (Queue<Order*>& Rhs )
{  
	Order**arr;
	arr=NULL;
	Rhs.toArray(arr);

	for(int i=0;i<Rhs.getSize();i++)
	{
		pGUI->AddOrderForDrawing(arr[i]);
	}
}
void Restaurant::ResetPQueueWindow(PQueueLinkedList<Order*,int> &Rhs)
{  
	Order**arr;
	arr=NULL;
	Rhs.toArray(arr);
	for(int i=0;i<Rhs.getSize();i++)
	{
		pGUI->AddOrderForDrawing(arr[i]);
	}
}
void Restaurant::ResetListWindow(LinkedList<Order*>& Rhs )
{  
	Order**arr;
	arr=NULL;
	Rhs.toArray(arr);

	for(int i=(Rhs.getSize())-1;i>-1;i--)
	{
		pGUI->AddOrderForDrawing(arr[i]);
	}
}
void Restaurant::ResetWindowALL( )
{
	pGUI->ResetDrawingList();

	if(!ActiveVIPOrder[0].isEmpty())
		ResetPQueueWindow(ActiveVIPOrder[0]);
	if(!ActiveFROZENOrder[0].isEmpty())
		ResetQueueWindow(ActiveFROZENOrder[0]);
	if(ActiveNORMALOrder[0].getSize()!=0)
		ResetListWindow(ActiveNORMALOrder[0]);

	if(!ActiveVIPOrder[1].isEmpty())
		ResetPQueueWindow(ActiveVIPOrder[1]);
	if(!ActiveFROZENOrder[1].isEmpty())
		ResetQueueWindow(ActiveFROZENOrder[1]);
	if(ActiveNORMALOrder[1].getSize()!=0)
		ResetListWindow(ActiveNORMALOrder[1]);

	if(!ActiveVIPOrder[2].isEmpty())
		ResetPQueueWindow(ActiveVIPOrder[2]);
	if(!ActiveFROZENOrder[2].isEmpty())
		ResetQueueWindow(ActiveFROZENOrder[2]);
	if(ActiveNORMALOrder[2].getSize()!=0)
		ResetListWindow(ActiveNORMALOrder[2]);


	if(!ActiveVIPOrder[3].isEmpty())
		ResetPQueueWindow(ActiveVIPOrder[3]);
	if(!ActiveFROZENOrder[3].isEmpty())
		ResetQueueWindow(ActiveFROZENOrder[3]);
	if(ActiveNORMALOrder[3].getSize()!=0)
		ResetListWindow(ActiveNORMALOrder[3]);

	pGUI->UpdateInterface();
}
void Restaurant:: Load( )
{
	int normal[4],frozen[4],vip[4];
	string filename;
	ifstream inputFile;
	filename=pGUI->GetString()+".txt";
	inputFile.open(filename);
	if(inputFile.is_open())
	{
	int s1,s2,s3;
	inputFile>>s1>>s2>>s3;

	
	for(int i=0;i<4;i++)
	{
		inputFile>>normal[i]>>frozen[i]>>vip[i];
	}
	///////////////////////////////////////////////
	for(int j=0;j<4;j++)
	{
		for(int i=0;i<normal[j];i++)
		{
			Motorcycle* pM=new Motorcycle(i+1,s1+2*i,TYPE_NRM);
			NormalMotors[j].enqueue(pM,pM->MotorGetSpeed());
		}
	}

	for(int j=0;j<4;j++)
	{
		for(int i=0;i<frozen[j];i++)
		{
			Motorcycle* pM=new Motorcycle(i+1,s2+i,TYPE_FROZ);
			FrozMotors[j].enqueue(pM,pM->MotorGetSpeed());
		}
	}
	for(int j=0;j<4;j++)
	{
		for(int i=0;i<vip[j];i++)
		{
			Motorcycle* pM=new Motorcycle(i+1,s3+3*i,TYPE_VIP);
			FastMotors[j].enqueue(pM,pM->MotorGetSpeed());
		}
	}
	inputFile>>AutoProm;
	int numofevents;
	inputFile>>numofevents;
		Event* ptr;
		for(int i=0;i<numofevents;i++)
		{

			char m;
			inputFile>>m;
			if(m=='R')
			{
				ptr= new ArrivalEvent(inputFile);
				AddEvent(ptr);
			}
			else if(m=='X')
			{
				ptr= new CancelEvent(inputFile);
				AddEvent(ptr);
			}
			else if (m=='P')
			{
				ptr= new PromotionEvent(inputFile);
				AddEvent(ptr);
			}
		}
	}

}
void Restaurant::DeleteActiveOrders()
{
	Order*op;
	for(int i=0;i<4;i++)
	{
		if(!ActiveNORMALOrder[i].isEmpty())
		{
			ActiveNORMALOrder[i].remove(ActiveNORMALOrder[i].getSize());
		}
	}
	for(int i=0;i<4;i++)
	{
		if(!ActiveVIPOrder[i].isEmpty())
		{
			ActiveVIPOrder[i].dequeue(op);
		}
	}
	for(int i=0;i<4;i++)
	{
		if(!ActiveFROZENOrder[i].isEmpty())
		{
			ActiveFROZENOrder[i].dequeue(op);
		}
	}
}
void Restaurant::printOutput(string (&s)[4])
{  
	pGUI->PrintMessage("RegionA :  ACorders:ViP: "+to_string(ActiveVIPOrder[0].getSize())+"  FROZEN: "+to_string(ActiveFROZENOrder[0].getSize())+"   NORMAL: "+to_string(ActiveNORMALOrder[0].getSize())+"       SERVED:VIP: "+to_string(ServicedVIPOrders[0])+" FROZ: "+to_string(ServicedFROZENOrders[0])+" NORM: "+to_string(ServicedNORMALOrders[0])+"        Motorcycles:ViP: "+to_string(FastMotors[0].getSize())+" FROZEN: "+to_string(FrozMotors[0].getSize())+" NORMAL: "+to_string(NormalMotors[0].getSize()),1);
	pGUI->PrintMessage("                   "+s[0],5);
	pGUI->PrintMessage("RegionB :  ACorders:ViP: "+to_string(ActiveVIPOrder[1].getSize())+"  FROZEN: "+to_string(ActiveFROZENOrder[1].getSize())+"   NORMAL: "+to_string(ActiveNORMALOrder[1].getSize())+"       SERVED:VIP: "+to_string(ServicedVIPOrders[1])+" FROZ: "+to_string(ServicedFROZENOrders[1])+" NORM: "+to_string(ServicedNORMALOrders[1])+"        Motorcycles:ViP: "+to_string(FastMotors[1].getSize())+" FROZEN: "+to_string(FrozMotors[1].getSize())+" NORMAL: "+to_string(NormalMotors[1].getSize()),2);
	pGUI->PrintMessage("                   "+s[1],6);
	pGUI->PrintMessage("RegionC :  ACorders:ViP: "+to_string(ActiveVIPOrder[2].getSize())+"  FROZEN: "+to_string(ActiveFROZENOrder[2].getSize())+"   NORMAL: "+to_string(ActiveNORMALOrder[2].getSize())+"       SERVED:VIP: "+to_string(ServicedVIPOrders[2])+" FROZ: "+to_string(ServicedFROZENOrders[2])+" NORM: "+to_string(ServicedNORMALOrders[2])+"        Motorcycles:ViP: "+to_string(FastMotors[2].getSize())+" FROZEN: "+to_string(FrozMotors[2].getSize())+" NORMAL: "+to_string(NormalMotors[2].getSize()),3);
	pGUI->PrintMessage("                   "+s[2],7);
	pGUI->PrintMessage("RegionD :  ACorders:ViP: "+to_string(ActiveVIPOrder[3].getSize())+"  FROZEN: "+to_string(ActiveFROZENOrder[3].getSize())+"   NORMAL: "+to_string(ActiveNORMALOrder[3].getSize())+"       SERVED:VIP: "+to_string(ServicedVIPOrders[3])+" FROZ: "+to_string(ServicedFROZENOrders[3])+" NORM: "+to_string(ServicedNORMALOrders[3])+"        Motorcycles:ViP: "+to_string(FastMotors[3].getSize())+" FROZEN: "+to_string(FrozMotors[3].getSize())+" NORMAL: "+to_string(NormalMotors[3].getSize()),4);
	pGUI->PrintMessage("                   "+s[3],8);
}

void Restaurant::AssighnOrdersToMotors(int TimeStep,string(&s)[4])
{
	for(int i=0;i<4;i++)
	{
		if(!ActiveVIPOrder[i].isEmpty())
		{
			AssighnOrder_PQueue(TimeStep,ActiveVIPOrder[i],AssighnedVIPOrder[i],FastMotors[i],InserviseFastMotors[i],s[i]);
		}
	}
	for(int i=0;i<4;i++)
	{
		if(!ActiveVIPOrder[i].isEmpty())
		{
			AssighnOrder_PQueue(TimeStep,ActiveVIPOrder[i],AssighnedVIPOrder[i],NormalMotors[i],InserviseNormalMotors[i],s[i]);
		}
	}
	for(int i=0;i<4;i++)
	{
		if(!ActiveVIPOrder[i].isEmpty())
		{
			AssighnOrder_PQueue(TimeStep,ActiveVIPOrder[i],AssighnedVIPOrder[i],FrozMotors[i],InserviseFrozMotors[i],s[i]);
		}
	}

	for(int i=0;i<4;i++)
	{
		if(!ActiveFROZENOrder[i].isEmpty())
		{
			AssighnOrder_Queue(TimeStep,ActiveFROZENOrder[i],AssighnedFROZENOrder[i],FrozMotors[i],InserviseFrozMotors[i],s[i]);
		}
	}
	for(int i=0;i<4;i++)
	{
		if(!ActiveNORMALOrder[i].isEmpty())
		{
			AssighnOrder_List(TimeStep,ActiveNORMALOrder[i],AssighnedNORMALOrder[i],NormalMotors[i],InserviseNormalMotors[i],s[i]);
		}
	}
	for(int i=0;i<4;i++)
	{
		if(!ActiveNORMALOrder[i].isEmpty())
		{
			AssighnOrder_List(TimeStep,ActiveNORMALOrder[i],AssighnedNORMALOrder[i],FastMotors[i],InserviseFastMotors[i],s[i]);
		}
	}
}
void Restaurant::AssighnOrder_PQueue(int TimeStep,PQueueLinkedList<Order*,int>& WaitingOrders,PQueueLinkedList<Order*,int>& InServiceOrders,PQueueLinkedList<Motorcycle*,int>& AvailableMotors,PQueueLinkedList<Motorcycle*,int>& InServiceeMotors,string&s)
{

		Order*pOrd;
		Motorcycle* pMotor;
		while(!AvailableMotors.isEmpty()&&!WaitingOrders.isEmpty())
		{	WaitingOrders.dequeue(pOrd);
		AvailableMotors.dequeue(pMotor);
		pOrd->SetServTime(ceil(double(pOrd->GetDistance())/double((pMotor->MotorGetSpeed()))));
		pOrd->SetWaitingTime(TimeStep-pOrd->GetArrivalTime());
		pOrd->SetFinishTime(ceil((double(TimeStep)+double(pOrd->GetServTime()))));
		pMotor->MotorSetFinishTime(pOrd->GetServTime()+pOrd->GetFinishTime());
		pMotor->MotorSetDistance(pOrd->GetServTime()*2);
		InServiceOrders.enqueue(pOrd,-pOrd->GetFinishTime());
		InServiceeMotors.enqueue(pMotor,-pMotor->MotorGetFinishTime());
		if (pMotor->MotorGetType()==TYPE_VIP)
			s+="V "+to_string(pMotor->MotorGetId())+" ";
		else if(pMotor->MotorGetType()==TYPE_FROZ)
			s+="F "+to_string(pMotor->MotorGetId())+" ";
		else
			s+="N "+to_string(pMotor->MotorGetId())+" ";

		s+="(V "+to_string(pOrd->GetID())+")    ";
		
	}
}
void Restaurant::AssighnOrder_Queue(int TimeStep,Queue <Order*>& WaitingOrders,PQueueLinkedList<Order*,int>& InServiceOrders,PQueueLinkedList<Motorcycle*,int>& AvailableMotors,PQueueLinkedList<Motorcycle*,int>& InServiceeMotors,string&s)
{

		Order*pOrd;
		Motorcycle* pMotor;
		while(!AvailableMotors.isEmpty()&&!WaitingOrders.isEmpty())
		{
			WaitingOrders.dequeue(pOrd);
			AvailableMotors.dequeue(pMotor);
			pOrd->SetServTime(ceil(double(pOrd->GetDistance())/double((pMotor->MotorGetSpeed()))));
			pOrd->SetWaitingTime(TimeStep-pOrd->GetArrivalTime());
			pOrd->SetFinishTime((ceil(double(TimeStep)+double(pOrd->GetServTime()))));
			pMotor->MotorSetFinishTime(pOrd->GetServTime()+pOrd->GetFinishTime());
			pMotor->MotorSetDistance(pOrd->GetServTime()*2);
			InServiceOrders.enqueue(pOrd,-pOrd->GetFinishTime());
			InServiceeMotors.enqueue(pMotor,-pMotor->MotorGetFinishTime());

			if (pMotor->MotorGetType()==TYPE_VIP)
				s+="V "+to_string(pMotor->MotorGetId())+" ";
			else if(pMotor->MotorGetType()==TYPE_FROZ)
				s+="F "+to_string(pMotor->MotorGetId())+" ";
			else
				s+="N "+to_string(pMotor->MotorGetId())+" ";

			s+="(F "+to_string(pOrd->GetID())+")    ";

		}
}
void Restaurant::AssighnOrder_List(int TimeStep,LinkedList<Order*>& WaitingOrders,PQueueLinkedList<Order*,int>& InServiceOrders,PQueueLinkedList<Motorcycle*,int>& AvailableMotors,PQueueLinkedList<Motorcycle*,int>& InServiceeMotors,string&s)
{	
		Order*pOrd;
		Motorcycle* pMotor;
		while(!AvailableMotors.isEmpty()&&!WaitingOrders.isEmpty())
		{
			WaitingOrders.DeleteLast(pOrd);
			AvailableMotors.dequeue(pMotor);
			pOrd->SetServTime(ceil(double(pOrd->GetDistance())/double((pMotor->MotorGetSpeed()))));
			pOrd->SetWaitingTime(TimeStep-pOrd->GetArrivalTime());
			pOrd->SetFinishTime((ceil(double(TimeStep)+double(pOrd->GetServTime()))));
			pMotor->MotorSetFinishTime(pOrd->GetServTime()+pOrd->GetFinishTime());
			pMotor->MotorSetDistance(pOrd->GetDistance()*2);
			InServiceOrders.enqueue(pOrd,-(pOrd->GetFinishTime()));
			InServiceeMotors.enqueue(pMotor,-(pMotor->MotorGetFinishTime()));

			if (pMotor->MotorGetType()==TYPE_VIP)
				s+="V "+to_string(pMotor->MotorGetId())+" ";
			else if(pMotor->MotorGetType()==TYPE_FROZ)
				s+="F "+to_string(pMotor->MotorGetId())+" ";
			else
				s+="N "+to_string(pMotor->MotorGetId())+" ";

			s+="(N "+to_string(pOrd->GetID())+")    ";

		}
		while(!WaitingOrders.isEmpty()&&((TimeStep-(WaitingOrders.getEntry(WaitingOrders.getSize()))->GetArrivalTime())>=AutoProm))
		{
			WaitingOrders.DeleteLast(pOrd);
			pOrd->SetType(TYPE_VIP);
				switch(pOrd->GetRegion())
				{
				case A_REG:
					AddtoVipOrders(pOrd,0);
					break;
				case B_REG:
					AddtoVipOrders(pOrd,1);
					break;
				case C_REG:
					AddtoVipOrders(pOrd,2);
					break;
				case D_REG:
					AddtoVipOrders(pOrd,3);
					break;
			}
		}
}

void Restaurant::Finishing(int CurrentTimeStep)
{
	Order *pOrd;
	PQueueLinkedList<Order*,int> TempPQueue;
	for(int i=0;i<4;i++)
	{
		while( AssighnedFROZENOrder[i].peekFront(pOrd) )	
		{
			if(pOrd->GetFinishTime()>CurrentTimeStep )
				break;
			AssighnedFROZENOrder[i].dequeue(pOrd);
			TempPQueue.enqueue(pOrd,-pOrd->GetServTime());
			ServicedFROZENOrders[i]++;
		}

		while( AssighnedVIPOrder[i].peekFront(pOrd) )	
		{
			if(pOrd->GetFinishTime()>CurrentTimeStep )
				break;
			AssighnedVIPOrder[i].dequeue(pOrd);
			TempPQueue.enqueue(pOrd,-pOrd->GetServTime());
			ServicedVIPOrders[i]++;
		}

		while( AssighnedNORMALOrder[i].peekFront(pOrd) )	
		{
			if(pOrd->GetFinishTime()>CurrentTimeStep )
				break;
			AssighnedNORMALOrder[i].dequeue(pOrd);
			TempPQueue.enqueue(pOrd,-pOrd->GetServTime());
			ServicedNORMALOrders[i]++;
		}
	}
	while(!TempPQueue.isEmpty())
	{
		TempPQueue.dequeue(pOrd);
		ServicedOrders.enqueue(pOrd);
	}

	Motorcycle* pMotor;
	for(int i=0;i<4;i++)
	{
		while( InserviseFrozMotors[i].peekFront(pMotor) )	
		{
			if(pMotor->MotorGetFinishTime()>CurrentTimeStep )
				break;
			InserviseFrozMotors[i].dequeue(pMotor);
			pMotor->MotorSetFinishTime(0);
			pMotor->MotorSetHealth(pMotor->MotorGetHealth()-pMotor->MotorGetHealth()*pMotor->MotorGetDistance()/1000);
			pMotor->MotorSetDistance(0);
			//--------------------------------------------------
			if(pMotor->MotorGetHealth()<5)
			{
				pMotor->MotorSetFinishTime(CurrentTimeStep+10-pMotor->MotorGetHealth());
				DamagedFrozMotors[i].enqueue(pMotor,-pMotor->MotorGetFinishTime());
			}
			else
			{
				FrozMotors[i].enqueue(pMotor,pMotor->MotorGetSpeed());
			}
			//--------------------------------------------------
		}
		while( InserviseNormalMotors[i].peekFront(pMotor) )	
		{
			if(pMotor->MotorGetFinishTime()>CurrentTimeStep )
				break;
			InserviseNormalMotors[i].dequeue(pMotor);
			pMotor->MotorSetFinishTime(0);
			pMotor->MotorSetHealth(pMotor->MotorGetHealth()-pMotor->MotorGetHealth()*pMotor->MotorGetDistance()/1000);
			pMotor->MotorSetDistance(0);
			//--------------------------------------------------
			if(pMotor->MotorGetHealth()<5)
			{
				pMotor->MotorSetFinishTime(CurrentTimeStep+10-pMotor->MotorGetHealth());
				DamagedNormalMotors[i].enqueue(pMotor,-pMotor->MotorGetFinishTime());
			}
			else
			{
				NormalMotors[i].enqueue(pMotor,pMotor->MotorGetSpeed());
			}
			//--------------------------------------------------
		}

		while( InserviseFastMotors[i].peekFront(pMotor) )	
		{
			if(pMotor->MotorGetFinishTime()>CurrentTimeStep )
				break;
			InserviseFastMotors[i].dequeue(pMotor);
			pMotor->MotorSetFinishTime(0);
			pMotor->MotorSetHealth(pMotor->MotorGetHealth()-pMotor->MotorGetHealth()*pMotor->MotorGetDistance()/1000);
			pMotor->MotorSetDistance(0);
			//--------------------------------------------------
			if(pMotor->MotorGetHealth()<5)
			{
				pMotor->MotorSetFinishTime(CurrentTimeStep+10-pMotor->MotorGetHealth());
				DamagedFastMotors[i].enqueue(pMotor,-pMotor->MotorGetFinishTime());
			}
			else
			{
				FastMotors[i].enqueue(pMotor,pMotor->MotorGetSpeed());
			}
			//--------------------------------------------------
		}
	}
}
void Restaurant::Repair(int CurrentTimeStep)
{
	Motorcycle* pMotor;
	for(int i=0;i<4;i++)
	{
		while( DamagedFrozMotors[i].peekFront(pMotor) )	
		{
			if(pMotor->MotorGetFinishTime()>CurrentTimeStep )
				break;
			DamagedFrozMotors[i].dequeue(pMotor);
			pMotor->MotorSetFinishTime(0);
			pMotor->MotorSetHealth(10);
			pMotor->MotorSetDistance(0);

			FrozMotors[i].enqueue(pMotor,pMotor->MotorGetSpeed());
		}
		while( DamagedNormalMotors[i].peekFront(pMotor) )	
		{
			if(pMotor->MotorGetFinishTime()>CurrentTimeStep )
				break;
			DamagedNormalMotors[i].dequeue(pMotor);
			pMotor->MotorSetFinishTime(0);
			pMotor->MotorSetHealth(10);
			pMotor->MotorSetDistance(0);
			NormalMotors[i].enqueue(pMotor,pMotor->MotorGetSpeed());
		}

		while( DamagedFastMotors[i].peekFront(pMotor) )	
		{
			if(pMotor->MotorGetFinishTime()>CurrentTimeStep )
				break;
			DamagedFastMotors[i].dequeue(pMotor);
			pMotor->MotorSetFinishTime(0);
			pMotor->MotorSetHealth(10);
			pMotor->MotorSetDistance(0);
			FastMotors[i].enqueue(pMotor,pMotor->MotorGetSpeed());
		}
	}
}
bool Restaurant::AllOrdersAREserved()
{ 
	int checkV=0;
	int checkF=0;
	int checkN=0;
	for (int i = 0; i < 4; i++)
	{  if(ActiveVIPOrder[i].isEmpty()) 
	checkV++;
	if(ActiveNORMALOrder[i].isEmpty()) 
		checkN++;
	if(ActiveFROZENOrder[i].isEmpty()) 
		checkF++;
	}


	if (checkV==4 && checkF==4 && checkN==4 )
		return true;
	else
		return false;

}
bool Restaurant::AllMotorsCameBack()
{

	int checkV=0;
	int checkF=0;
	int checkN=0;
	for (int i = 0; i < 4; i++)
	{  if(InserviseFastMotors[i].isEmpty()) 
	checkV++;
	if(InserviseNormalMotors[i].isEmpty()) 
		checkN++;
	if(InserviseFrozMotors[i].isEmpty()) 
		checkF++;
	}


	if (checkV==4 && checkF==4 && checkN==4 )
		return true;
	else
		return false;


}
bool Restaurant::ALLMotorsAreRepaird()
{
	int checkV=0;
	int checkF=0;
	int checkN=0;
	for (int i = 0; i < 4; i++)
	{  if(DamagedFastMotors[i].isEmpty()) 
	checkV++;
	if(DamagedNormalMotors[i].isEmpty()) 
		checkN++;
	if(DamagedFrozMotors[i].isEmpty()) 
		checkF++;
	}


	if (checkV==4 && checkF==4 && checkN==4 )
		return true;
	else
		return false;
}
void Restaurant::Output()
{
	string filename;
	ofstream outfile;
	pGUI->PrintMessage("Enter outputfile name ^_^");
	filename=pGUI->GetString()+".txt";
	outfile.open(filename);
	if(outfile.is_open(),ios::trunc)
	{
		outfile<<"FT" <<"\t"<<"ID"<<"\t"<<"AT"<<"\t"<<"WT"<<"\t"<<"ST"<<endl;
	int TotalWaitingTime[4];
	int TotalServiceTime[4];
	for (int i = 0; i < 4; i++)
	{
		TotalWaitingTime[i]=0;
	}

	for (int i = 0; i < 4; i++)
	{
		TotalServiceTime[i]=0;
	}
	while(!ServicedOrders.isEmpty())
	{
		Order*ptr; 
		ServicedOrders.dequeue(ptr);
			outfile<<ptr->GetFinishTime()<<"\t"<<ptr->GetID()<<"\t"<<ptr->GetArrivalTime()<<"\t"<<ptr->GetWaitingTime()<<"\t"<<ptr->GetServTime()<<endl;
			if(ptr)
			{
				switch(ptr->GetRegion())
				{
				case A_REG:
					TotalWaitingTime[0]=TotalWaitingTime[0]+ptr->GetWaitingTime();
					TotalServiceTime[0]=TotalServiceTime[0]+ptr->GetServTime();
					break;
				case B_REG:
					TotalWaitingTime[1]=TotalWaitingTime[1]+ptr->GetWaitingTime();
					TotalServiceTime[1]=TotalServiceTime[1]+ptr->GetServTime();
					break;
				case C_REG:
					TotalWaitingTime[2]=TotalWaitingTime[2]+ptr->GetWaitingTime();
					TotalServiceTime[2]=TotalServiceTime[2]+ptr->GetServTime();
					break;
				case D_REG:
					TotalWaitingTime[3]=TotalWaitingTime[3]+ptr->GetWaitingTime();
					TotalServiceTime[3]=TotalServiceTime[3]+ptr->GetServTime();
					break;
				}
			}
	}
		outfile<<".................................................."<<endl;
		outfile<<".................................................."<<endl;
	for(int i=0;i<4;i++)
	{
			outfile<<"Region"<<" "<<Region(i)<<":"<<endl;
		
	outfile<<"  "<<"Orders:"<<ServicedNORMALOrders[i]+ServicedFROZENOrders[i]+ServicedVIPOrders[i]<<"     [ "<<"Norm:"<<ServicedNORMALOrders[i]<<", "<<"Froz:"<<ServicedFROZENOrders[i]<<", "<<"VIP:"<<ServicedVIPOrders[i]<<"]"<<endl;
	outfile<<"  "<<"Motocycles:"<<NormalMotors[i].getSize()+FrozMotors[i].getSize()+FastMotors[i].getSize()<<" [ "<<"Norm:"<<NormalMotors[i].getSize()<<", "<<"Froz:"<<FrozMotors[i].getSize()<<", "<<"Fast:"<<FastMotors[i].getSize()<<"]"<<endl;
	outfile<<"  "<<"Avg Wait= "<<TotalWaitingTime[i]/(ServicedNORMALOrders[i]+ServicedFROZENOrders[i]+ServicedVIPOrders[i])<<",  "<<"Avg Serv= "<<TotalServiceTime[i]/(ServicedNORMALOrders[i]+ServicedFROZENOrders[i]+ServicedVIPOrders[i])<<"  "<<endl;

	}

	outfile.close();
}
}
char Restaurant::Region(int m)
{
	char p;
	if(m==0)
	{
		p='A';
	}
	else	if(m==1)
	{
		p='B';
	}
	else if(m==2)
	{
		p='C';
	}
	else if(m==3)
	{
		p='D';
	}

	return p;
}