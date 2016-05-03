//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                       VEX Competition Control Include File
//
// This file provides control over a VEX Competition Match. It should be included in the user's
// program with the following line located near the start of the user's program
//        #include "VEX_Competition_Includes.h"
// The above statement will cause this program to be included in the user's program. There's no
// need to modify this program.
//
// The program displays status information on the new VEX LCD about the competition state. You don't
// need the LCD, the program will work fine whether or not the LCD is actually provisioned.
//
// The status information is still useful without the LCD. The ROBOTC IDE debugger has a "remote screen"
// that contains a copy of the status information on the LCD. YOu can use this to get a view of the
// status of your program. The remote screen is shown with the menu command
//   "Robot -> Debugger Windows -> VEX Remote Screen"
//
// The LCD is 2 lines x 16 characters. There are three display formats to look for:
//
//        State          Description
//
//    ----------------
//   |Disabled        |  The robot is idle. This occurs before both the autonomous and user
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been idle.
//    ----------------
//
//    ----------------
//   |Autonomous      |  The robot is running autonomous code.
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been running.
//    ----------------
//
//    ----------------
//   |User Control    |  The robot is running user control code.
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been running.
//    ----------------
//////////////////////////////////////////////////////////////////////////////////////////////////////


void allMotorsOff();
void allTasksStop();
void pre_auton();
task autonomous();
task usercontrol();

int nTimeXX = 0;
bool bStopTasksBetweenModes = true;

static void displayStatusAndTime();

task main()
{
	// Master CPU will not let competition start until powered on for at least 2-seconds
	displayLCDCenteredString(0, "TEAM FIRE");
	displayLCDCenteredString(1, "STARTING UP");
	wait1Msec(2000);


	pre_auton();

	//wait1Msec(500);


	while (true)
	{

		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDPos(0, 0);

		while (bIfiRobotDisabled)
		{
			nTimeXX = 0;
			while (true)
			{
				////////////////////////////////////BEGIN LCD DATA
				string mainBattery, backupBattery, batteryTwo;
				displayLCDString(0, 0, "P:");
				sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
				displayNextLCDString(mainBattery);
				displayLCDString(1, 0, "E:");
				sprintf(batteryTwo, "%1.2f%c", SensorValue[Pexpander]/280.0, 'V');    //Build the value to be displayed
				displayNextLCDString(batteryTwo);
				if (alliance == 0) displayLCDString(0, 10, "BLUE:");
				if (alliance == 1) displayLCDString(0, 11, "RED:");
				if (alliance == 2) displayLCDString(0, 8, "SELF CHK");
				if (alliance == 3) displayLCDString(0, 11, "DEBUG");
				if (alliance == 0 || autonomousN == 1) displayLCDNumber(0, 15, autonomousN+1, 1);
				if (autonomousN == 5 && alliance != 2 && alliance != 3 ) displayLCDString(0, 8, "INIT ESC");
				////////////////////////////////////END LCD DATA
				displayStatusAndTime();
				if (!bIfiRobotDisabled)
					break;
				wait1Msec(25);

				displayStatusAndTime();
				if (!bIfiRobotDisabled)
					break;
				wait1Msec(25);

				displayStatusAndTime();
				if (!bIfiRobotDisabled)
					break;
				wait1Msec(25);

				displayStatusAndTime();
				if (!bIfiRobotDisabled)
					break;
				wait1Msec(25);
				++nTimeXX;
			}
		}

		nTimeXX = 0;
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDPos(0, 0);
		if (bIfiAutonomousMode)
		{
			displayNextLCDString("Autonomous");
			startTask(autonomous);

			// Waiting for autonomous phase to end
			while (bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (!bVEXNETActive)
				{
					if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
						allMotorsOff();
				}
				wait1Msec(25);               // Waiting for autonomous phase to end
			}
			allMotorsOff();
			if(bStopTasksBetweenModes)
			{
				allTasksStop();
			}
		}

		else
		{
			displayNextLCDString("User Control");
			startTask(usercontrol);

			// Here we repeat loop waiting for user control to end and (optionally) start
			// of a new competition run
			while (!bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
					allMotorsOff();
				wait1Msec(25);
			}
			allMotorsOff();
			if(bStopTasksBetweenModes)
			{
				allTasksStop();
			}
		}
	}
}


void allMotorsOff()
{
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
#if defined(VEX2)
	motor[port9] = 0;
	motor[port10] = 0;
#endif
}

void allTasksStop()
{
	stopTask(1);
	stopTask(2);
	stopTask(3);
	stopTask(4);
#if defined(VEX2)
	stopTask(5);
	stopTask(6);
	stopTask(7);
	stopTask(8);
	stopTask(9);
	stopTask(10);
	stopTask(11);
	stopTask(12);
	stopTask(13);
	stopTask(14);
	stopTask(15);
	stopTask(16);
	stopTask(17);
	stopTask(18);
	stopTask(19);
#endif
}

static void displayStatusAndTime()
{
	//displayLCDPos(1, 9);
	displayLCDString(1, 8, "DIS");
	//if (bIfiRobotDisabled)
	//  displayNextLCDString("Disable ");
	//else
	//{
	//  if (bIfiAutonomousMode)
	//    displayNextLCDString("Auton  ");
	//  else
	//    displayNextLCDString("Driver ");
	//}
	displayNextLCDNumber(nTimeXX / 600, 2);
	displayNextLCDChar(':');
	displayNextLCDNumber((nTimeXX / 10) % 60, -2);
}
