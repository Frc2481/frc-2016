/*
 * OI.h
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#ifndef SRC_OI_H_
#define SRC_OI_H_
#include "WPILib.h"
//#include "Joystick.h"
#include "XboxController.h"
//#include "CommandBase.h"
//#include "ControllerMap.h"
//#include "Joystick2.h"

class OI {
private:
	Joystick* driveStick;

	//Button* intakeOut;
	//Button* intakeIn;
public:
	OI();
	virtual ~OI();
	Joystick* GetDriveStick();
};

#endif /* SRC_OI_H_ */
