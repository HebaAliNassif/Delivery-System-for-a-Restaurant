#pragma once
#ifndef __Cancelation_Event_H_
#define __Cancelation_Event_H_
#include <string>
#include <fstream>
using namespace std;
#include"Events\Event.h"
class CancelEvent: public Event
{
public:
	CancelEvent(int T,int ID);
	CancelEvent(ifstream &inputFile);
	virtual void Load(ifstream &inputFile);
	~CancelEvent();
	void Execute(Restaurant* pOrd);
};
#endif