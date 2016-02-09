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
#include "Components/AnalogJoystickButton.h"

class OI {
private:
	Joystick* driveStick;
	Joystick* operatorStick;
	Joystick* debugStick;

	//Driver Buttons
	AnalogJoystickButton* intakeOut;
	AnalogJoystickButton* intakeIn;
	Button* rotateToAngleCam;

	//Operator Buttons
	AnalogJoystickButton* fireBall;
	Button* turnOnShooter;
	Button* turnOffShooter;

	//Debug Buttons
	Button* rotateToAngleNoCam;

public:
	OI();
	virtual ~OI();
	Joystick* GetDriveStick();
	Joystick* GetOperatorStick();
	Joystick* GetDebugStick();
};

#endif /* SRC_OI_H_ */
