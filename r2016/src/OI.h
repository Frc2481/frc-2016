/*
 * OI.h
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#ifndef SRC_OI_H_
#define SRC_OI_H_
#include "WPILib.h"
#include "XboxController.h"
//#include "Joystick2.h"

class OI {
public:
	Joystick* driveStick;
	OI();
	virtual ~OI();
};

#endif /* SRC_OI_H_ */
