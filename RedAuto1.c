/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     RedAuto1.c                                                  */
/*    Author:     Jefferson Maldonado                                         */
/*    Created:    2 May 2016                                                  */
/*                                                                            */
/*    Copyright (c) VCAT Robotics 2016, All Rights Reserved                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Licensed under the Apache License, Version 2.0 (the "License");         */
/*    you may not use this file except in compliance with the License.        */
/*    You may obtain a copy of the License at                                 */
/*                                                                            */
/*    http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "RedAuto1Failsafe.c"
void RedAuto1(void)
{
	int Launch = 0;
	Transmission(1);
	BallCounter = 4;
	ShootingMode = 1;
	IntakeShoot(6000);//SHOOT 4 PRELOADS // * FAILSAFE POINT
	ShootingMode = 4;
	stage = 1;
	TurnDegree(-10,40,0); // DO WE NEED FAILSAFE HERE?
	delay(200);
	Move(2,127);
	delay(500);
	clearTimer(T3);
	while(SensorValue[IR1] == 1) //*FAILSAFE ?WHAT IF WE DONT SEE ANY BALLS
	{
		IntakeOnAuto();
		Move(2,20);
		if(time1[T3] > 8000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Red1Fail1();/////////////////////RED1FAIL1
		IntakePower(0);
	Break(100,10);
	while(MoveDist(-1, 20,0) == 1) // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
	}
	while(MoveDist(40, 50,0) == 1) //*FAILSAFE ?WHAT IF WE ARE BLOCKED (ROBOT FINISHED ABOUT MID COURT)
	{
		if(FailSafeEngaged == 1)Red1Fail1();/////////////////////RED1FAIL1
			IntakeOnAuto();
	}
	IntakePower(0);
	TurnDegree(-45,127,2000); //*FAILSAFE ?WHAT IF WE ARE BLOCKED
	if(FailSafeEngaged == 1)Red1FailInfinite();
	delay(200);
	SetRPM(2250);//LAUNCHER ON (NEXT SHOOTING RPM)
	clearTimer(T3);
	while(LineStatus() == 0) //*FAILSAFE AT WHAT POINT DO WE STOP MOVING? WHAT IF WE ARE OF COURSE?
	{
		Move(-2,30);
		if(time1[T3] > 3500)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Red1FailInfinite();
	Break(100,-20);
	delay(200);
	while(MoveDist(7, 30,0) == 1){} // DO WE NEED FAILSAFE HERE?
	clearTimer(T3);
	while(LineStatus() == 0) // TURN UNTILL IT SEES LINE (WHAT IF WE NEVER SEE LINE)
	{
		Move(1,22);
		if(time1[T3] > 3000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Red1FailInfinite();
	while(LineStatus() == 1 && LineStatusOffset() == 0) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(40);
		if(LineStatus() == 1 && LineStatusOffset() == 1) Launch = 1;//WE REACHED THE CROSS(MIDDLE OF FIELD SET FLAG
	}
	if(LineStatus() == 1 && LineStatusOffset() == 1) Launch = 1;
	Break(100,20);
	StopDrive();
	delay(300);
	if(Launch) //IF LAUNCH FLAG WAS SATISFIED EARLIER THEN WE CAN LAUNCH BALLS
	{
		IntakePower(127); // SHOOT MID COURT
		delay(3000);
	}
	stage = 1;
	ShootingMode = 3;
	DistanceCalculator(1);
	while(SensorValue[IR1] == 1 && LineStatus() == 1 && DistanceCalculator(0) < 55) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(35);
		IntakeOnAuto();
	}
	Break(100,20);
	StopDrive();
	while(stage == 1) // WHAT IF TWO BALLS ARE STUCK FOREVER? TIMER?
	{
		IntakeOnAuto();
	}
	while(LineStatus() == 1 && DistanceCalculator(0) < 55)//*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(35);
		IntakeOnAuto();
	}
	MoveTime(300,127);
	StopDrive();
	IntakePower(127);///SHOT LAST BALLS BAR SHOTS
	delay(4000);
	stage = 1;
	///////////
	KillALL();
	while(1);
}
