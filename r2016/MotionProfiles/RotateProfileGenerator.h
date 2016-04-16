#ifndef RotateProfileGenerator_H
#define RotateProfileGenerator_H

#include "WPILib.h"

class RotateProfileGenerator
{
private:
	const double kMaxVelocity = 8;
	const double kMaxAccel = 4;
	const double kJerk = 0;
	const double kPeriod = .005;
	const double kWheelBaseCircum = 80.1;
	/*(2)(PI)(4) = 25.12 in
	 * (30.55)(128) = 3909.9 Ticks/Rotation
	 * 3909.9/25.12 = 155.64 Ticks/Inch */
	const double kTicksPerInch = 155.64;
	const double kTicksPerRotation = 3909.9;
	double m_accel;
	double m_position; //Rotations
	double m_velocity; //Rev/Min
	double m_time; //MSec
	double m_velocityAtMaxAccel;
	double m_posAtMaxVelocity;
	double m_totalDistance;
	int m_iCounter;
	double m_distanceToStop;
	bool m_rotateRight;
	double** RightGeneratedMotionProfile; //[2481][3];
	double** LeftGeneratedMotionProfile; //[2481][3];
	bool m_done;
	double m_angle;
public:
	RotateProfileGenerator();
	~RotateProfileGenerator();
	int GetProfileLength();
	double** GetRightProfile();
	double** GetLeftProfile();
	void GenerateMotionProfile(double angle);
	void FillArray();
	void InitDefaultCommand();
};

#endif
