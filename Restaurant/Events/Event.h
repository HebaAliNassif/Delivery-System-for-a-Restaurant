#ifndef __EVENT_H_
#define __EVENT_H_
#include <string>
#include <fstream>
using namespace std;
#include "..\Defs.h"

class Restaurant;	//Forward declation

//The base class for all possible events in the system (abstract class)
class Event
{
protected:
	int EventTime;	//Timestep when this event takes place
	int OrderID;	//each event is related to certain order
	//ifstream inputFile;
public:
	Event(int eTime, int ordID);
	int getEventTime();
	int getOrderID();
	virtual ~Event();

	void setET(int eTime);           ///////////*************
	void setOrdID(int id);
	virtual void Load(ifstream &inputFile)=0;
	virtual void Execute(Restaurant* pRest)=0;

};


#endif