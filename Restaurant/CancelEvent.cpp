#include "CancelEvent.h"
#include "Rest\Restaurant.h"
#include"GUI\GUI.h"
CancelEvent::CancelEvent(int T,int ID):Event(T,ID)
{
}
CancelEvent::CancelEvent(ifstream &inputFile):Event(0,0)
{
	Load(inputFile);
}
void CancelEvent::Load(ifstream &inputFile)
{
	inputFile>>EventTime>>OrderID;
}

void CancelEvent::Execute(Restaurant* pRest)
{

	int position;
	Order*pOrd=pRest->GetNormalOederWithId(OrderID,position);
	if(pOrd)
	{
	switch(pOrd->GetRegion())
	{
	case A_REG:
		pRest->RemoveFromNORMALOrdersList(position,0);
		break;
	case B_REG:
		pRest->RemoveFromNORMALOrdersList(position,1);
		break;
	case C_REG:
		pRest->RemoveFromNORMALOrdersList(position,2);
		break;
	case D_REG:
		pRest->RemoveFromNORMALOrdersList(position,3);
		break;
	}
	}
}

CancelEvent::~CancelEvent()
{
}

