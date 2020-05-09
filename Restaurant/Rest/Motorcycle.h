#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_

#include"..\Defs.h"
#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE order_typr; //for each order type there is a corresponding motorcycle type
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	int Distance;
	int FinishTime;
	int MotorHealth;

public:
	Motorcycle();
	Motorcycle(int r_Id,ORD_TYPE  r_Type,int r_Speed,REGION r_REGION,STATUS r_Status);
	Motorcycle(int r_Id,ORD_TYPE  r_Type,int r_Speed,REGION r_REGION);
	Motorcycle(int Motor_ID,int Speed,ORD_TYPE r_Type);

	int MotorGetId() const;
	void MotorSetId(int r_Id);

	ORD_TYPE MotorGetType() const;
	void MotorSetType(ORD_TYPE r_Type);

	int MotorGetSpeed() const;
	void MotorSetSpeed(int r_Speed);

	REGION MotorGetRegion() const;
	void MotorSetRegion(REGION r_REGION);

	STATUS MotorGetstatus() const;
	void MotorSetstatus(STATUS r_Status);

	int MotorGetFinishTime() const;
	void MotorSetFinishTime(int r_Time);

	int MotorGetDistance() const;
	void MotorSetDistance(int r_D);

	int MotorGetHealth() const;
	void MotorSetHealth(int r_H);

	virtual ~Motorcycle();
};

#endif