/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     Auto.c                                                      */
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

while ( alliance == 0 ) // BEGING BLUE ALLIANCE CODE
{
	while ( autonomousN == 0 ) // BEGIN AUTONOMOUS 1 CODE
	{
		BlueAuto1 ( ) ;
	}
	while ( autonomousN == 1 ) // BEGIN AUTONOMOUS 2 CODE
	{
		BlueAuto2 ( ) ;
	}
	while ( autonomousN == 2 ) // BEGIN AUTONOMOUS 3 CODE
	{
		BlueAuto3 ( ) ;
	}
	while ( autonomousN == 3 ) // BEGIN AUTONOMOUS 4 CODE
	{
		BlueAuto4 ( ) ;
	}
	while ( autonomousN == 4 ) // BEGIN AUTONOMOUS 5 CODE
	{
		BlueAuto5 ( );
	}
	// END BLUE ALLIANCE CODE
}
while ( alliance == 1 ) //  BEGIN RED ALLIANCE CODE
{
	while ( autonomousN == 0 ) // BEGIN AUTONOMOUS 1 CODE
	{
		RedAuto1 ( ) ;
	}
	while ( autonomousN == 1 ) // BEGIN AUTONOMOUS 2 CODE
	{
		RedAuto2 ( ) ;
	}
	while ( autonomousN == 2 ) // BEGIN AUTONOMOUS 3 CODE
	{
		RedAuto3 ( ) ;
	}
	while ( autonomousN == 3 ) // BEGIN AUTONOMOUS 4 CODE
	{
		RedAuto4 ( ) ;
	}
	while ( autonomousN == 4 ) // BEGIN AUTONOMOUS 5 CODE
	{
		RedAuto5 ( ) ;
	}
	// END RED ALLIANCE CODE
}
while ( alliance == 2 ) // BEGIN SELF CHECK CODE
{
	SelfCheckCode ( ) ;
	// END SELF CHECK CODE
}
while ( alliance == 3 ) // BEGIN SELF CHECK CODE
{
	DebugCode ( ) ;
	// END DebugCode
}
