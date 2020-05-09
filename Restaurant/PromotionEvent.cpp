#include "PromotionEvent.h"
#include "Rest\Restaurant.h"
PromotionEvent::PromotionEvent(int Ts,int id,double exmon):Event(Ts,id)
{
	ExMoney=exmon;
}
PromotionEvent::PromotionEvent(ifstream &inputFile):Event(0,0)
{
	Load(inputFile);
}
void PromotionEvent::Load(ifstream &inputFile)
{
	inputFile>>EventTime>>OrderID>>ExMoney;

}
void PromotionEvent::Execute(Restaurant *pRest)
{
	int position;
	Order*pOrd = pRest->GetNormalOederWithId(OrderID, position);
	if (pOrd)
	{
		switch (pOrd->GetRegion())
		{
		case A_REG:
			pRest->RemoveFromNORMALOrdersList(position, 0);
			pOrd->SetType(TYPE_VIP);
			pOrd->SetMoney(pOrd->GetMoney()+ExMoney);
			pRest->AddtoVipOrders(pOrd, 0);
				
			break;
		case B_REG:
			pRest->RemoveFromNORMALOrdersList(position, 1);
			pOrd->SetType(TYPE_VIP);
			pOrd->SetMoney(pOrd->GetMoney()+ExMoney);
			pRest->AddtoVipOrders(pOrd, 1);
				
			break;
		case C_REG:	
			pRest->RemoveFromNORMALOrdersList(position, 2);
			pOrd->SetType(TYPE_VIP);
			pOrd->SetMoney(pOrd->GetMoney()+ExMoney);
			pRest->AddtoVipOrders(pOrd, 2);
			break;
		case D_REG:
			pRest->RemoveFromNORMALOrdersList(position, 3);
			pOrd->SetType(TYPE_VIP);
			pOrd->SetMoney(pOrd->GetMoney()+ExMoney);
			pRest->AddtoVipOrders(pOrd, 3);
			
			break;
		}
	}

}
PromotionEvent::~PromotionEvent()
{

}
