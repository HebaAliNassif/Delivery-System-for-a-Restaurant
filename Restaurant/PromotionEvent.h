#pragma once
#include"Events\Event.h"
class PromotionEvent :
	public Event
{
private:
	double ExMoney;
public:
	PromotionEvent(int Ts,int id,double exmon);
	PromotionEvent(ifstream &inputFile);
	void Load(ifstream &inputFile);
	~PromotionEvent();
	virtual void Execute(Restaurant *pRest);
};



