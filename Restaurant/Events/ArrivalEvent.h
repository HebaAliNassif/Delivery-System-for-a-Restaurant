#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	REGION OrdRegion;  //Region of this order	                
	double OrdMoney;	//Total order money
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg,int r_Distance,double r_totalMoney);
	//Add more constructors if needed

	ArrivalEvent(ifstream &inputFile);
	virtual void Execute(Restaurant *pRest);	//override execute function
	virtual void Load(ifstream &inputFile);
	void region(char reg);
	void orderType(char oType);
	void setMoney(double mon);
	void setDistance(int odis);
};

#endif