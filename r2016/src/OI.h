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
#include "Components/Joystick2481.h"

class OI {
private:
	Joystick2481* driveStick;
	Joystick* operatorStick;
	Joystick* debugStick;

	//Driver Buttons
	AnalogJoystickButton* intakeButton;
	Button* intakeRevButton;
	Button* rotateToAngleCam;
	Button* driveTrainShift;

	//Operator Buttons
	AnalogJoystickButton* fireBall;
	Button* turnOnShooter;
	Button* turnOffShooter;
	Button* manualIntakeButton;
	Button* changeShooterAngle;

	//Debug Buttons
	Button* rotateToAngleNoCam;
	Button* waitForBallTest;

public:
	OI();
	virtual ~OI();
	Joystick2481* GetDriveStick();
	Joystick* GetOperatorStick();
	Joystick* GetDebugStick();
};

#endif /* SRC_OI_H_ */
