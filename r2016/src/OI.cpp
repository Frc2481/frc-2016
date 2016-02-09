/*
  * OI.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#include <OI.h>
#include <ControllerMap.h>
#include "Commands/RetractIntakeCommand.h"
#include "Commands/ExtendIntakeCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/FireBallCommand.h"

OI::OI() {
	driveStick = new Joystick(0);
	operatorStick = new Joystick(1);
	debugStick = new Joystick(2);

	intakeIn = new INTAKE_RETRACT_BUTTON;
	intakeIn->WhenReleased(new RetractIntakeCommand());

	intakeOut = new INTAKE_EXTEND_BUTTON;
	intakeOut->WhenPressed(new ExtendIntakeCommand());

	turnOnShooter = new TURN_SHOOTER_ON_BUTTON;
	turnOnShooter->WhenPressed(new TurnOnShooterCommand());

	turnOffShooter = new TURN_SHOOTER_OFF_BUTTON;
	turnOffShooter->WhenPressed(new TurnOffShooterCommand());

	rotateToAngleCam = new CAMERA_ROTATE_BUTTON;
	rotateToAngleCam->WhileHeld(new RotateToAngleFromCameraCommand());

	rotateToAngleNoCam = new NO_CAMERA_ROTATE_BUTTON;
	rotateToAngleNoCam->WhileHeld(new RotateToAngleCommand(90));

	fireBall = new FIRE_BALL_BUTTON;
	fireBall->WhenPressed(new FireBallCommand());
}

OI::~OI() {
	// TODO Auto-generated destructor stub
}

Joystick* OI::GetDriveStick() {
	return driveStick;
}

Joystick* OI::GetOperatorStick() {
	return operatorStick;
}

Joystick* OI::GetDebugStick() {
	return debugStick;
}
