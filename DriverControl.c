/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     DriverControl.c                                             */
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

startTask( RPMCALC );
startTask( BANGBANG );
startTask( BALLCOUNTER );

while (true)
{
	/////////////////////////////////////////LCD DISPLAY
#include "LCD.c"
	////////////////////////////////////////////////FLYWHEEL CONTROL
	if(vexRT[Btn8R]==1)ShootingMode = 1;
	else if(vexRT[Btn8L]==1)ShootingMode = 2;
	else if(vexRT[Btn8D]==1)ShootingMode = 3;
	else if(vexRT[Btn8U]==1)ShootingMode = 4;
	else if(vexRT[Btn7U]==1)ShootingMode = 5;
	////////////////////////////////////////////////INTAKE CONTROL
	if(vexRT[Btn6U]==1 && vexRT[Ch2] < 50) //SMART INTAKE
	{
		IntakeOnAuto();
	}else if(vexRT[Btn5U]==1)
	{
		motor[Intake] = -127;
		motor[feeder] = -127;
	}else if(vexRT[Btn6U]== 1 && vexRT[Ch2] > 50) //LAUNCHING BALLS (JOYSTICK BYPASSES SMART INTAKE)
	{
		if(ShootingMode == 1)//IF SHOOTING FROM FULL COURT
		{
			if(rpmError < 8 && SensorValue[IR4] == 0 || SensorValue[IR4] == 1)//ONLY SHOOT IF RPM RPM IS WITHIN TOLERANCE
			{
				motor[Intake] = 127;
				motor[feeder] = 127;
			}else
			{
				motor[Intake] = 0;
				motor[feeder] = 0;
			}
		}else
		{
			motor[Intake] = 127;
			motor[feeder] = 127;
		}
		stage = 1;
	}else
	{
		motor[Intake] = 0;
		motor[feeder] = 0;
	}
	////////////////////////////////////////////////DRIVE TRAIN

	if (vexRT[Btn7L] ==1) //SMALL ADJUSTMENTS
	{
		motor[Left1] = -30;
		motor[Left2] = -30;
		motor[Left3] = -30;
		motor[Right1] = 30;
		motor[Right2] = 30;
		motor[Right3] = 30;
	}else if (vexRT[Btn7R] ==1)//SMALL ADJUSTMENTS
	{
		motor[Left1] = 30;
		motor[Left2] = 30;
		motor[Left3] = 30;
		motor[Right1] = -30;
		motor[Right2] = -30;
		motor[Right3] = -30;
	}else
	{
		if(vexRT[Ch3] > 15 || vexRT[Ch4] > 15 || vexRT[Ch3] < -15 || vexRT[Ch4] < -15) //JOYSTICK DEADBAND
		{
			motor[Left1] = (vexRT[Ch3] + vexRT[Ch4]);
			motor[Left2] = (vexRT[Ch3] + vexRT[Ch4]);
			motor[Left3] = (vexRT[Ch3] + vexRT[Ch4]);
			motor[Right1] = (vexRT[Ch3] - vexRT[Ch4]);
			motor[Right2] = (vexRT[Ch3] - vexRT[Ch4]);
			motor[Right3] = (vexRT[Ch3] - vexRT[Ch4]);
		}
		else
		{
			motor[Left1] = 0;
			motor[Left2] = 0;
			motor[Left3] = 0;
			motor[Right1] = 0;
			motor[Right2] = 0;
			motor[Right3] = 0;
		}

	}
	////////////////////////////////////////////////TRANSMISSION
	if(vexRT[Btn6D]==1)SensorValue[solenoid] = 1;
	else if(vexRT[Btn5D]==1)SensorValue[solenoid] = 0;
	////////////////////////////////////////////////////////////
	wait1Msec(10);
}
