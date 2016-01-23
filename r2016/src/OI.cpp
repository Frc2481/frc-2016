/*
  * OI.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#include <OI.h>

OI::OI() {
	driveStick = new Joystick(0);
}

OI::~OI() {
	// TODO Auto-generated destructor stub
}

Joystick* OI::GetDriveStick() {
	return driveStick;
}
