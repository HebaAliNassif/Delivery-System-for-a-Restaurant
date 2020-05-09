#include "Motorcycle.h"
#include <iostream>
using namespace std;
Motorcycle::Motorcycle()
{
}
Motorcycle::Motorcycle(int r_Id,ORD_TYPE r_Type,int r_Speed,REGION r_REGION,STATUS r_Status)
{
	MotorSetId(r_Id);
	MotorSetRegion(r_REGION);
	MotorSetSpeed(r_Speed);
	MotorSetstatus(r_Status);
	MotorSetType(r_Type);
	MotorHealth=10;
}
Motorcycle::Motorcycle(int Motor_ID,int Speed,ORD_TYPE r_Type)
{
	MotorSetId(Motor_ID);
	MotorSetSpeed(Speed);
	MotorSetType(r_Type);
	MotorHealth=10;
}
int Motorcycle::MotorGetId()const
{
	return ID;
}
void Motorcycle::MotorSetId(int r_Id)
{
	ID=r_Id;
}
ORD_TYPE Motorcycle::MotorGetType() const
{
	return order_typr;
}
void Motorcycle::MotorSetType(ORD_TYPE r_Type)
{
	order_typr=r_Type;
}
int Motorcycle::MotorGetSpeed()const
{
	return speed;
}
void Motorcycle::MotorSetSpeed(int r_Speed)
{
	speed=r_Speed;
}

REGION Motorcycle::MotorGetRegion()const
{
	return region;
}
void Motorcycle::MotorSetRegion(REGION r_REGION)
{
	region=r_REGION;
}

STATUS Motorcycle::MotorGetstatus()const
{
	return status;
}
void Motorcycle::MotorSetstatus(STATUS r_Status)
{
	switch (r_Status)
	{
	case IDLE:
		status=IDLE;
		break;
	case SERV:
		status=SERV;
	case InRep:
		status=InRep;
		break;
	default:
		break;
	}
}
int Motorcycle::MotorGetFinishTime()const
{
	return FinishTime;
}
void Motorcycle::MotorSetFinishTime(int r_Time)
{
	FinishTime=r_Time;
}
int Motorcycle::MotorGetDistance() const
{
	return Distance;
}
void Motorcycle::MotorSetDistance(int r_D)
{
	Distance=r_D;
}
int Motorcycle::MotorGetHealth() const
{
	return MotorHealth;
}
void Motorcycle::MotorSetHealth(int r_H)
{
	MotorHealth=r_H;
}
	Motorcycle::~Motorcycle()
{
}
