/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     RedAuto1Failsafe.c                                          */
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

void Red1Fail1(void)
{
	IntakePower(0);
	MoveTime(2000,-100)
	KillALL();
	while(1);
}

void Red1FailInfinite(void)
{
	KillALL();
	while(1);
}
