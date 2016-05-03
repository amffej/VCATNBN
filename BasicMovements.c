/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     BasicMovements.c                                            */
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


///////////////////////////////////////STOP DRIVE TRAIN
void StopDrive(void)
{
	motor[Left1] = 0;
	motor[Left2] = 0;
	motor[Left3] = 0;
	motor[Right1] = 0;
	motor[Right2] = 0;
	motor[Right3] = 0;
}
///////////////////////////////////////APPLY BREAKS
void Break(int time, int speed)
{
	motor[Left1] = -speed;
	motor[Left2] = -speed;
	motor[Left3] = -speed;
	motor[Right1] = -speed;
	motor[Right2] = -speed;
	motor[Right3] = -speed;
	wait1Msec(time);
	StopDrive();
}
void Break2(int time, int speed)
{
	motor[Left1] = speed;
	motor[Left2] = speed;
	motor[Left3] = speed;
	motor[Right1] = -speed;
	motor[Right2] = -speed;
	motor[Right3] = -speed;
	wait1Msec(time);
	StopDrive();
}
///////////////////////////////////////ENGAGE - DISENGAGE TRANSMISSION
void Transmission(int Mode)
{
	if(Mode == 1)SensorValue[solenoid] = 1; //TORQUE MODE
	else if(Mode == 2)SensorValue[solenoid] = 0; //SPEED MODE
}
///////////////////////////////////////MOVE ROBOT BASED ON SPEED EXAMPLE // direction: -1 = left   1 = right 2 = Forward -2 = Backwards// while(condition){ Move(2,127) };//THIS MOVES FORWARD UNTIL CONDITION IS MET
void Move(int direction, int speed)
{
	int left = 0, right = 0;
	if (direction == 1){left = 1; right = -1;}
	else if (direction == -1){left = -1; right =  1; }
	else if (direction == 2) {left =  1; right =  1; }
	else if (direction == -2){left = -1; right = -1; }
	else if (direction == 3){left = 1; right = 0; }
	else if (direction == -3){left = 0; right = 1; }
	else if (direction == 4){left = -1; right = 0; }
	else if (direction == -4){left = 0; right = -1; }
	motor[Left1] = speed*left;
	motor[Left2] = speed*left;
	motor[Left3] = speed*left;
	motor[Right1] = speed*right;
	motor[Right2] = speed*right;
	motor[Right3] = speed*right;
}
///////////////////////////////////////TURN BASED ON GYRO DEGREES EXAMPLE // TurnDegree(-90, 127);//THIS TURNS LEFT 90 DEGREES AT 127 POWER
void TurnDegree(int degrees, int speed, int Timeout)
{
	int left = 0, right = 0;
	SensorValue[Gyro] = 0;
	if (degrees < 0){left = -1; right = 1;}
	else if (degrees > 0){left = 1; right = -1; }
	float ticks = abs(degrees*6.7);
	clearTimer(T3);

	while(abs(SensorValue[Gyro]) < ticks)
	{
		////////////////////////////////////FAILASFE TIMEOUT
		if(time1[T3] > TimeOut && TimeOut > 0){ FailSafeEngaged = 1; break;}
		////////////////////////////////////////////////////
		motor[Left1] = speed*left;
		motor[Left2] = speed*left;
		motor[Left3] = speed*left;
		motor[Right1] = speed*right;
		motor[Right2] = speed*right;
		motor[Right3] = speed*right;
	}
	motor[Left1] = (speed*left*-1)/9;
	motor[Left2] = (speed*left*-1)/9;
	motor[Left3] = (speed*left*-1)/9;
	motor[Right1] = (speed*right*-1)/9;
	motor[Right2] = (speed*right*-1)/9;
	motor[Right3] = (speed*right*-1)/9;
	wait1Msec(250);
	StopDrive();
}
///////////////////////////////////////MOVE FORWARD/BACKWARDS BASED ON TIME EXAMPLE// MoveTime(1000, -127);//THIS MOVES BACKWARDS FOR 1 SECOND
void MoveTime(int time, int speed)
{
	motor[Left1] = speed;
	motor[Left2] = speed;
	motor[Left3] = speed;
	motor[Right1] = speed;
	motor[Right2] = speed;
	motor[Right3] = speed;
	wait1Msec(time);
	motor[Left1] = (speed*-1)/15;
	motor[Left2] = (speed*-1)/15;
	motor[Left3] = (speed*-1)/15;
	motor[Right1] = (speed*-1)/15;
	motor[Right2] = (speed*-1)/15;
	motor[Right3] = (speed*-1)/15;
	wait1Msec(250);
	StopDrive();
}
///////////////////////////////////////MOVE FORWARD/BACKWARDS BASED ON ENCODER READING// while(MoveFwdDist(-10, 127) == 1){DO SOMETHING LIKE INTAKE ON}//THIS MOVES BACKWARDS FOR 10 INCHES AT POWER 127
int MoveDist(int inches, int speed, int TimeOut)
{
	int status, direction = 0;
	if (MoveCounter == 0 )
	{
		SensorValue[ENCR] = 0;
		MoveCounter = 1;
		clearTimer(T3);
	}
	////////////////////////////////////FAILASFE TIMEOUT
	if(time1[T3] > TimeOut && TimeOut > 0) FailSafeEngaged = 1;
	////////////////////////////////////////////////////
	if (inches < 0){direction = -1;}
	else if (inches > 0){direction = 1;}
	int ticks = abs(inches*19); ///NEEDS TO BE ADJUSTED BASED ON ENCONDER RATIO
	if(abs(SensorValue[ENCR]) < ticks) //ENCODER TO USE FOR DISTANCE
	{
		motor[Left1] = speed*direction;
		motor[Left2] = speed*direction;
		motor[Left3] = speed*direction;
		motor[Right1] = speed*direction;
		motor[Right2] = speed*direction;
		motor[Right3] = speed*direction;
		status = 1;
	}
	else
	{
		motor[Left1] = (speed*direction*-1)/20;
		motor[Left2] = (speed*direction*-1)/20;
		motor[Left3] = (speed*direction*-1)/20;
		motor[Right1] = (speed*direction*-1)/19;
		motor[Right2] = (speed*direction*-1)/19;
		motor[Right3] = (speed*direction*-1)/19;
		delay(330);
		StopDrive();
		status = 0;
		MoveCounter = 0;
	}
	return status;
}
//////////////////////////////////////////////////// RETURNS TRUE IF FRONT LINE TRACKER SEES THE LINE
int LineStatus(void)
{
	if (SensorValue[LineLeft] < 1500 || SensorValue[LineMiddle] < 1500 || SensorValue[LineRight] < 1500)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int LineStatusOffset(void)
{
	if (SensorValue[LineOffest] < 1500 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//////////////////////////////////////////////////// FOLLOW THE WHITE LINE EXAMPLE// while(LineStatus() == 1){FollowLine(100)}
void FollowLine(int Initial)
{
	///0.003*FOR SPEED MODE
	int left = 0, right = 0;
	float LineMath = 0.008*(SensorValue[LineLeft]-SensorValue[LineRight]); //0.009
	int Speed = abs(LineMath);
	if (LineMath < 0){left = -1; right =  1; 	}//TURN LEFT
	else if (LineMath > 0){left = 1; right = -1;	}//TURN RIGHT
	else{left =  1; right =  1;  }//MOVE STRAIGHT
	motor[Left1] = Initial+(Speed*left);
	motor[Left2] = Initial+(Speed*left);
	motor[Left3] = Initial+(Speed*left);
	motor[Right1] = Initial+(Speed*right);
	motor[Right2] = Initial+(Speed*right);
	motor[Right3] = Initial+(Speed*right);
}
/////////////////////////////////////////CALCULATE DISTANCE TRAVELED
int DistanceCalculator(int reset)
{
	if(reset)
	{
		SensorValue[ENCR] = 0;
	}
	int Distance = abs(SensorValue[ENCR]/28.64);
	return Distance;
}
int DistanceCalculatorTurn(int reset)
{
	if(reset)
	{
		SensorValue[ENCR] = 0;
	}
	int Distance = abs(SensorValue[ENCR]);
	return Distance;
}
//////////////////////////////////////////////////// INTAKE SIMPLE POWER CONTROL
void IntakePower(int Power)
{
	motor[Intake] = Power;
	motor[feeder] = Power;
}
//////////////////////////////////////////////////// INTAKE IN AUTO MODE
void IntakeOnAuto(void)
{
	if (stage == 1)/////////////////////STAGE 1
	{
		motor[Intake]= 127;
		if ( FeederStatus == 0 )motor[feeder]= 0;
		else if (FeederStatus == 1 )motor[feeder]= 127;
		if(SensorValue[IR1] == 0)	FeederStatus = 1;
		if(SensorValue[IR2] == 0)
		{
			FeederStatus = 0;
			stage = 2;
		}
	}else if (stage == 2)/////////////////////STAGE 2
	{
		motor[Intake] = 127;
		if ( FeederStatus == 0 )
			motor[feeder]= 0;
		else if (FeederStatus == 1)
		{
			motor[feeder]= 127;
		}
		if(SensorValue[IR4] == 0)
		{
			FeederStatus = 0;
			stage = 4;
		}
		if(SensorValue[IR1] == 0)FeederStatus = 1;
		if(SensorValue[IR3] == 0)
		{
			FeederStatus = 0;
			stage = 3;
		}
		if(SensorValue[IR4] == 0)
		{
			FeederStatus = 0;
			stage = 4;
		}
	}else if (stage == 3)/////////////////////STAGE 3
	{
		motor[Intake] = 127;
		if ( FeederStatus == 0 )
			motor[feeder]= 0;
		else if (FeederStatus == 1)
		{
			motor[feeder]= 127;
		}
		if(SensorValue[IR1] == 0)FeederStatus = 1;
		if(SensorValue[IR4] == 0)
		{
			FeederStatus = 0;
			stage = 4;
		}
	}else if (stage == 4)/////////////////////STAGE 4
	{
		motor[Intake] = 127;
		motor[feeder] = 0;
	}
}

///////////////////////////////////////INTAKE SHOOT BASED ON RPM AND TOLERANCES
void IntakeShoot(int TimeOut, int Tolerance = 8)
{
	if (BallCounter == 1) Tolerance = 12;
	clearTimer(T3);
	while(BallCounter > 0)
	{
		while(SensorValue[IR4] == 1)//MOVE BALL UP TO SENSOR
		{
			//BREAK STATEMENTS
			if(time1[T3] > TimeOut && TimeOut > 0){ FailSafeEngaged = 1; break;}
			if(BallCounter == 0) break;
			//BREAK STATEMENTS
			motor[Intake]= 127;
			motor[feeder]= 127;
		}

		if(rpmError < Tolerance)
		{
			motor[Intake]= 127;
			motor[feeder]= 127;
		}else
		{
			motor[Intake]= 0;
			motor[feeder]= 0;
		}
		if(time1[T3] > TimeOut && TimeOut > 0){ FailSafeEngaged = 1; break;}//BREAK STATEMENTS
	}
}
///////////////////////////////////////TURN LAUNCHER ON TO SET RPM
void SetRPM(int RPM)
{
	ShootingMode = 6; //FAKE SHOOTING MODE
	TargetSpeed = RPM; //TARGET RPM
	BasePower = -0.00002*RPM*RPM+0.1075*RPM-107.23; //CALCULATE BASE POWER BASED ON RPM
}
///////////////////////////////////////TURN EVERYTHING OFF
void KillALL(void)
{
	StopDrive();
	IntakePower(0);
	ShootingMode = 4;
}
