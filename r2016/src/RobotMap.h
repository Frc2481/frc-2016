#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

//DriveTrain
#define RM_MOTOR 0
#define LM_MOTOR 1
#define LS_MOTOR 2
#define RS_MOTOR 3
#define DRIVETRAIN_SHIFTER 2

//Shooter
#define SHOOTER_MOTOR 5
#define SHOOTER_ANGLE_ADJUST 0

//Intake
#define INTAKE_MOTOR 4
#define INTAKE_EXTENDER 1
#define INTAKE_FWD_SPD 1
#define INTAKE_REV_SPD -1

//Lift
#define LIFT_MOTOR 7
#define LIFT_LIMIT_SWITCH 0

#define LIFT_UP_SPEED 0.5
#define LIFT_DOWN_SPEED -0.5

//Kicker
#define KICKER 6

//Camera
#define CAMERA_LIGHT 4
#define CAMERA_TOLERANCE .5

#endif
