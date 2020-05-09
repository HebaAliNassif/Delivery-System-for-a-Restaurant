#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg,int r_Distance,double r_totalMoney):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdDistance=r_Distance;	  	                
    OrdMoney=r_totalMoney;
}
void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	Order* Ord = new Order(OrderID,OrdType,OrdRegion,OrdDistance,OrdMoney,EventTime);

	switch(OrdRegion)
	{
	case A_REG:
		{
			switch (OrdType)	
			{
			case TYPE_NRM:
				pRest->AddtoNormalOrders(Ord,0);
				break;
			case TYPE_FROZ:
				pRest->AddtoFROZENOrders(Ord,0);
				break;
			case TYPE_VIP:
				pRest->AddtoVipOrders(Ord,0);
				break;
			}
			break;
		}

	case B_REG:
		{
			switch (OrdType)	
		{
		case TYPE_NRM:
			pRest->AddtoNormalOrders(Ord,1);
			break;
		case TYPE_FROZ:
			pRest->AddtoFROZENOrders(Ord,1);
			break;
		case TYPE_VIP:
			pRest->AddtoVipOrders(Ord,1);
			break;
		}
		break;
		}

	case C_REG:
		{  switch (OrdType)	
		{
		case TYPE_NRM:
			pRest->AddtoNormalOrders(Ord,2);
			break;
		case TYPE_FROZ:
			pRest->AddtoFROZENOrders(Ord,2);
			break;
		case TYPE_VIP:
			pRest->AddtoVipOrders(Ord,2);
			break;
		}
		break;}

	case D_REG:
		{  switch (OrdType)	
		{
		case TYPE_NRM:
			pRest->AddtoNormalOrders(Ord,3);
			break;
		case TYPE_FROZ:
			pRest->AddtoFROZENOrders(Ord,3);
			break;
		case TYPE_VIP:
			pRest->AddtoVipOrders(Ord,3);
			break;
		}
		break;
		}



	};


}
ArrivalEvent::ArrivalEvent(ifstream &inputFile):Event(0,0)
{
	Load(inputFile);
}
void ArrivalEvent::Load(ifstream &inputFile)
{
	char Type;
	char reg;

	inputFile >> EventTime>> Type >>OrderID>>OrdDistance>>OrdMoney>>reg;
	region(reg);
	orderType(Type);
}
void ArrivalEvent::setMoney(double mon)
	{
		if(mon>0)
			OrdMoney=mon;
		else 
			OrdMoney=1;
	}
void ArrivalEvent::setDistance(int odis)
{
	if(odis>0)
		OrdDistance=odis;
	else OrdDistance=1;
}
void ArrivalEvent::region(char reg)
{
	REGION r;
	switch(reg)
	{
	case('A'):
		OrdRegion=A_REG;
		break;
	case('B'):
		OrdRegion=B_REG;
		break;
	case('C'):
		OrdRegion=C_REG;
		break;
	case('D'):
		OrdRegion=D_REG;
		break;
	}
}
void ArrivalEvent::orderType(char o)
{
	switch(o)
	{
	case('N'):
		OrdType=TYPE_NRM;
		break;
	case('F'):
		OrdType=TYPE_FROZ;
		break;
	case('V'):
		OrdType=TYPE_VIP;
		break;
	}
}