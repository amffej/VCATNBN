/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     Tasks.c                                                     */
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

////////////////////////////RPM CALCULATION TASK
task RPMCALC()
{
	int count = 0;
	int status = 0;
	clearTimer(T1);
	while(1)
	{
		if (SensorValue[TAC] == 0 && status == 0)
		{
			count++;
			status = 1;
		} else if (SensorValue[TAC] == 1)
		{
			status = 0;
		}
		if (count == 5)
		{
			CurrentSpeed = (1000*5*30)/time1[T1];
			clearTimer(T1);
			count = 0;
		}
		if (time1[T1] > 500)
		{
			CurrentSpeed = 0;
		}
	}
}
////////////////////////////RPM CONTROL TASK
task BANGBANG ()
{
	int MotorPower = 0;
	while(1)
	{
		//////SELECT SPEED
		if(ShootingMode == 1)//FULL COURT
		{
			TargetSpeed = 2800;
			BasePower = 38;
		}else if(ShootingMode == 2)//MID FIELD
		{
			TargetSpeed = 2400;
			BasePower = 30; //35
		}else if(ShootingMode == 3)//BAR SHOTS
		{
			TargetSpeed = 2100;//2150
			BasePower = 20;
		}else if(ShootingMode == 5)//SKILLS
		{
			TargetSpeed = 2300;
			BasePower = 30;
		}else if(ShootingMode == 4)//LAUNCHER OFF
		{
			TargetSpeed = 0;
			BasePower = 0;
		}
		///////CONTROL
		if (CurrentSpeed > TargetSpeed){
			MotorPower = BasePower;
		}
		else if (CurrentSpeed < TargetSpeed){
			MotorPower = 127;
		}
		motor[m1] = MotorPower;
		motor[m2] = MotorPower;
		EndTimeSlice(); //OR DELAY 20 MILLI
		////ERROR CALCULATION//
		rpmError = abs((TargetSpeed - CurrentSpeed)/10);
	}
}
////////////////////////////BALL COUNTER TASK
task BALLCOUNTER ()
{
	int CounterIn = 0;
	int CounterOut = 0;
	while(1)
	{
		//COUNT BALLS COMING IN
		if(SensorValue[IR1] == 0 && CounterIn == 0)
		{
			BallCounter++;
			CounterIn++;
		}
		if(SensorValue[IR1] == 1)
		{
			CounterIn = 0;
		}
		//COUNT BALLS COMING OUT
		if(SensorValue[IR4] == 0 && CounterOut == 0)
		{
			CounterOut++;
		}
		if(SensorValue[IR4] == 1 && CounterOut == 1)
		{
			if(BallCounter > 0)
			{
				BallCounter--;
			}
			CounterOut = 0;
		}
		EndTimeSlice(); //OR DELAY 20 MILLI
	}
}
