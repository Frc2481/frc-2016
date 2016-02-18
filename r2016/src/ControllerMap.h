/*
 * ControllerMap.h
 *
 *  Created on: Feb 8, 2016
 *      Author: FIRSTMentor
 */

#ifndef SRC_CONTROLLERMAP_H_
#define SRC_CONTROLLERMAP_H_
#include <OI.h>
#include "WPILib.h"
#include <XboxController.h>
#include "Components/AnalogJoystickButton.h"

//Drive Stick
#define INTAKE_BUTTON AnalogJoystickButton(driveStick, XboxController::xbRightTrigger, .5)
#define CAMERA_ROTATE_BUTTON JoystickButton(driveStick, XboxController::xbAButton)
#define DRIVE_TRAIN_SHIFT_BUTTON JoystickButton(driveStick, XboxController::xbRightBumper)
#define INTAKE_REVERSE_BUTTON JoystickButton(driveStick, XboxController::xbBButton)

//Operator Stick
#define TURN_SHOOTER_ON_BUTTON JoystickButton(operatorStick, XboxController::xbRightBumper)
#define TURN_SHOOTER_OFF_BUTTON JoystickButton(operatorStick, XboxController::xbLeftBumper)
#define FIRE_BALL_BUTTON AnalogJoystickButton(operatorStick, XboxController::xbRightTrigger, .5)
#define TOGGLE_INTAKE_BUTTON JoystickButton(operatorStick, XboxController::xbStartButton)
#define TOGGLE_SHOOTER_ANGLE_BUTTON JoystickButton(operatorStick, XboxController::xbBButton)

//Debug Stick
#define NO_CAMERA_ROTATE_BUTTON JoystickButton(debugStick, XboxController::xbBButton)

#endif /* SRC_CONTROLLERMAP_H_ */
