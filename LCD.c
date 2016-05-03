/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     LCD.c                                                       */
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

clearLCDLine(0);
clearLCDLine(1);
string mainBattery, backupBattery, batteryTwo;
displayLCDString(0, 0, "P:");
sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
displayNextLCDString(mainBattery);
displayLCDString(1, 0, "E:");
sprintf(batteryTwo, "%1.2f%c", SensorValue[Pexpander]/280.0, 'V');    //Build the value to be displayed
displayNextLCDString(batteryTwo);
displayNextLCDString("  B:");
sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');
displayNextLCDString(backupBattery);
if (alliance == 0) displayLCDString(0, 10, "BLUE:");
if (alliance == 1) displayLCDString(0, 11, "RED:");
if (alliance == 2) displayLCDString(0, 8, "SELF CHK");
if (alliance == 3) displayLCDString(0, 11, "DEBUG");
if (alliance == 0 || autonomousN == 1) displayLCDNumber(0, 15, autonomousN+1, 1);
if (autonomousN == 5 && alliance != 2 && alliance != 3 ) displayLCDString(0, 8, "INIT ESC");
