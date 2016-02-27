/*
  * OI.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#include "Commands/AcquireBallCommandGroup.h"
#include "Commands/ToggleShooterPositionCommand.h"
#include "Commands/TurnIntakeOnRevCommand.h"
#include <OI.h>
#include <ControllerMap.h>
#include "Commands/FireBallCommandGroup.h"
#include "Commands/WaitForBallTestCommandGroup.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/ShiftDriveTrainCommand.h"
#include "Commands/ToggleIntakeCommand.h"
#include "Commands/TraversePortcullisCommandGroup.h"

OI::OI() {
	driveStick = new Joystick2481(0);
	operatorStick = new Joystick2481(1);
	debugStick = new Joystick(2);

	intakeButton = new INTAKE_BUTTON;
	intakeButton->WhenPressed(new IntakeBallCommandGroup());
	intakeButton->WhenReleased(new BringIntakeUpCommandGroup());

	turnOnShooter = new TURN_SHOOTER_ON_BUTTON;
	turnOnShooter->WhenPressed(new TurnOnShooterCommand());

	turnOffShooter = new TURN_SHOOTER_OFF_BUTTON;
	turnOffShooter->WhenPressed(new TurnOffShooterCommand());

	manualIntakeButton = new TOGGLE_INTAKE_BUTTON;
	manualIntakeButton->WhenPressed(new ToggleIntakeCommand());

	intakeRevButton = new INTAKE_REVERSE_BUTTON;
	intakeRevButton->WhileHeld(new TurnIntakeOnRevCommand());

	rotateToAngleCam = new CAMERA_ROTATE_BUTTON;
	rotateToAngleCam->WhenPressed(new RotateToAngleFromCameraCommand());

	driveTrainShift = new DRIVE_TRAIN_SHIFT_BUTTON;
	driveTrainShift->WhenPressed(new ShiftDriveTrainCommand(true));
	driveTrainShift->WhenReleased(new ShiftDriveTrainCommand(false));


	rotateToAngleNoCam = new NO_CAMERA_ROTATE_BUTTON;
	rotateToAngleNoCam->WhileHeld(new RotateToAngleCommand(90));

	fireBall = new FIRE_BALL_BUTTON;
	fireBall->WhenPressed(new FireBallCommandGroup());

	changeShooterAngle = new TOGGLE_SHOOTER_ANGLE_BUTTON;
	changeShooterAngle->WhenPressed(new ToggleShooterPositionCommand());

	waitForBallTest = new TEST_INTAKE_WAIT_BUTTON;
	waitForBallTest->WhenPressed(new WaitForBallTestCommandGroup());

	portcullisTraverse = new PORTCULLIS_BUTTON;
	portcullisTraverse->WhenPressed(new TraversePortcullisCommandGroup());
}

OI::~OI() {
	// TODO Auto-generated destructor stub
}

Joystick2481* OI::GetDriveStick() {
	return driveStick;
}

Joystick2481* OI::GetOperatorStick() {
	return operatorStick;
}

Joystick* OI::GetDebugStick() {
	return debugStick;
}
