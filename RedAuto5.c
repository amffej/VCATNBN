/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     RedAuto5.c                                                  */
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

void RedAuto5(void)
{
	//SKILLS AUTO //4 PILES
	stage = 1;
	int YouAreGoodToCount = 0;
	DistanceCalculator(1);
	while(DistanceCalculator(0) < 12) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		Move(2, 127);
	}
	while(SensorValue[IR1] == 1 ) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		IntakeOnAuto();
		Move(2, 20);
	}
	IntakePower(0);
	Break(100,10);
	while(MoveDist(-1, 20,0) == 1) // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
	}
	while(MoveDist(27, 40,0) == 1)//17 // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
	}
	IntakePower(0);
	while(MoveDist(-7, 30,0) == 1);
	delay(200);
	while(LineStatus() == 0)
	{
		Move(-1, 22);
	}
	ShootingMode = 3;
	SetRPM(2200);
	while(LineStatus() == 1) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(40);
		if(LineStatusOffset() == 1)
		{
			DistanceCalculator(1);
			YouAreGoodToCount = 1;
		}
		if(DistanceCalculator(0) > 18 && YouAreGoodToCount == 1) break;
	}
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
		if(time1[T3] > 6000)
		{
			break;
		}
		IntakeOnAuto();
	}
	while(LineStatus() == 1 && DistanceCalculator(0) < 37 )//*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(35);
		IntakeOnAuto();
	}
	MoveTime(600,127);
	StopDrive();
	delay(500);
	IntakePower(127);///SHOT BAR SHOTS
	delay(4000);
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
	while(DistanceCalculatorTurn(0) < 82) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		Move(1, 100);
	}
	Break2(100,-10);
	delay(300);
	DistanceCalculator(1);
	while(DistanceCalculator(0) < 24) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		Move(2, 127);
	}
	while(SensorValue[IR1] == 1 ) //*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		IntakeOnAuto();
		Move(2, 20);
	}
	IntakePower(0);
	Break(100,10);
	while(MoveDist(-1, 20,0) == 1) // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
	}
	while(MoveDist(17, 35,0) == 1) // DO WE NEED FAILSAFE HERE?
	{
		IntakeOnAuto();
	}
	IntakePower(0);
	///////////////////////////////////////////////////////////////////////////////////PICK UP 3RD
	SetRPM(2200);
	while(LineStatus() == 0 )
	{
		Move(-2, 127);
	}
	Break(200,-15);
	while(MoveDist(3, 40,0) == 1);
	while(LineStatus() == 0) // TURN UNTILL IT SEES LINE (WHAT IF WE NEVER SEE LINE)
	{
		Move(1,22);
	}
	DistanceCalculator(1);
	while(LineStatus() == 1 && DistanceCalculator(0) < 12)//*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(35);
	}
	Break(100,20);
	StopDrive();
	delay(500);
	IntakePower(127);///SHOT LAST BALLS BAR SHOTS
	delay(3000);
	ShootingMode = 3;
	stage = 1;
	DistanceCalculator(1);
	clearTimer(T3);
	while(LineStatus() == 1 && DistanceCalculator(0) < 37 )//*FAILSE WHAT IF WE GET OFF THE LINE ( WHAT IF ROBOT BLOCKS PATH AND WE ARE STILL ON THE LINE)
	{
		FollowLine(35);
		IntakeOnAuto();
		if(time1[T3] > 5000)break;
	}
	MoveTime(600,127);
	StopDrive();
	delay(500);
	IntakePower(127);///SHOT LAST BALLS BAR SHOTS
	delay(4000);
	KillALL();
	while(1);
}
