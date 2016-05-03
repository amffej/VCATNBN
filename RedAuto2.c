/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     RedAuto2.c                                                  */
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

void RedAuto2(void)
{
	/// 4 PRELOADS 3 PILE
	/// STARTING TYLE IS FURTHERST TYLE
	int YouAreGoodToCount = 0;
	Transmission(1);
	BallCounter = 4;
	ShootingMode = 1;
	IntakeShoot(6000);//SHOOT 4 PRELOADS // * FAILSAFE POINT
	ShootingMode = 4;
	DistanceCalculatorTurn(1);
	while(DistanceCalculatorTurn(0) < 15) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		Move(-1, 50);
	}
	Break2(100,-10);
	//while(1);
	//TurnDegree(10,40,0); // DO WE NEED FAILSAFE HERE?
	delay(200);
	stage = 1;
	SetRPM(2200);
	DistanceCalculator(1);
	while(DistanceCalculator(0) < 12) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		Move(2, 127);
	}
	clearTimer(T3);
	while(SensorValue[IR1] == 1 ) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		IntakeOnAuto();
		Move(2, 20);
		if(time1[T3] > 6000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Blue1Fail1();/////////////////////RED1FAIL1
		IntakePower(0);
	Break(100,10);
	while(MoveDist(-1, 20,0) == 1) // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
	}
	while(MoveDist(27, 40,3000) == 1)//17 // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
		if(FailSafeEngaged == 1)Blue1FailInfinite();/////////////////////RED1FAIL1
	}
	IntakePower(0);
	while(LineStatus() == 0)
	{
		Move(-2, 100);
	}
	Break(100,-10);
	while(MoveDist(3, 30,0) == 1);
	delay(200);
	SetRPM(2200);
	while(LineStatus() == 0) //TURN UNTIL YOU SEE THE LINE
	{
		Move(1, 20);
	}
	DistanceCalculator(1);
	while(LineStatus() == 1) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(40);
		if(LineStatusOffset() == 1)
		{
			DistanceCalculator(1);
			YouAreGoodToCount = 1;
		}
		if(DistanceCalculator(0) > 18 && YouAreGoodToCount == 1)
		{
			DistanceCalculator(1);
			break;

		}
	}
	if(DistanceCalculator(0) < 50 && YouAreGoodToCount == 0)Blue1FailInfinite();//**FAIL GOOD
		Break(100,20);
	delay(500);
	IntakePower(127);///SHOT FIRST PILE
	delay(3000);
	ShootingMode = 3;
	StopDrive();
	stage = 1;
	DistanceCalculator(1);
	while(SensorValue[IR1] == 1 && LineStatus() == 1) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(35);
		IntakeOnAuto();
	}
	Break(100,20);
	StopDrive();
	clearTimer(T3)
	while(stage == 1) // WHAT IF TWO BALLS ARE STUCK FOREVER? TIMER?
	{
		if(time1[T3] > 10000)
		{
			break;
		}
		IntakeOnAuto();
	}
	clearTimer(T3)
	while(LineStatus() == 1 && DistanceCalculator(0) < 37 )//*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(35);
		IntakeOnAuto();
		if(time1[T3] > 10000)
		{
			break;
		}
	}
	MoveTime(500,127);
	StopDrive();
	delay(500);
	IntakePower(127);///SHOT BAR SHOTS
	delay(3500);
	IntakePower(0);
	SetRPM(2200);
	stage = 1;
	//////////////////////////////////////////////////////SHOT 8 COMPLETE
	DistanceCalculator(1);
	while(DistanceCalculator(0) < 50) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		Move(-2, 127);
	}
	Break(200,-15);
	delay(200);
	DistanceCalculatorTurn(1);
	clearTimer(T3);
	while(DistanceCalculatorTurn(0) < 62) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		Move(-1, 100);
		if(time1[T3] > 5000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Blue1FailInfinite();
	Break2(100,10);
	delay(300);
	DistanceCalculator(1);
	clearTimer(T3);
	while(DistanceCalculator(0) < 24) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		Move(2, 127);
		if(time1[T3] > 5000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Blue1FailInfinite();
	clearTimer(T3);
	while(SensorValue[IR1] == 1 )//PILE BY THE WALL
	{
		IntakeOnAuto();
		Move(2, 20);
		if(time1[T3] > 5000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Blue1FailInfinite();
	IntakePower(0);
	Break(100,10);
	while(MoveDist(-1, 20,0) == 1) // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
	}
	while(MoveDist(19, 35,2000) == 1) // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
	}
	IntakePower(0);
	///////////////////////////////////////////////////////////////////////////////////PICK UP 3RD
	SetRPM(2200);
	clearTimer(T3);
	while(LineStatus() == 0 )
	{
		Move(-2, 127);
		if(time1[T3] > 5000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Blue1FailInfinite(); //**FAIL GOOD
		Break(200,-15);
	while(MoveDist(3, 40,0) == 1);
	clearTimer(T3)
	while(LineStatus() == 0) // TURN UNTILL IT SEES LINE (WHAT IF WE NEVER SEE LINE)
	{
		Move(1,22);
		if(time1[T3] > 5000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Blue1FailInfinite(); //**FAIL GOOD
		DistanceCalculator(1);
	clearTimer(T3);
	while(LineStatus() == 1 && DistanceCalculator(0) < 12)//*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(35);
		if(time1[T3] > 5000)
		{
			FailSafeEngaged = 1;
			break;
		}
	}
	if(FailSafeEngaged == 1)Blue1FailInfinite(); //**FAIL GOOD
		Break(100,20);
	StopDrive();
	delay(500);
	IntakePower(127);///SHOT LAST BALLS BAR SHOTS
	delay(3000);
	TurnDegree(-45,100,2000);
	while(MoveDist(24, 40,0) == 1);
	ShootingMode = 4;
	KillALL();
	while(1);
}
