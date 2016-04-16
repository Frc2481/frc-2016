#include "RotateProfileGenerator.h"
#include "RobotMap.h"
#include <cmath>

RotateProfileGenerator::RotateProfileGenerator()
{
	m_done = false;
	m_position = 0;
	m_velocity = 0;
	m_accel = 0;
	m_iCounter = 0;
	m_rotateRight = true;
	LeftGeneratedMotionProfile = new double*[2481];
	RightGeneratedMotionProfile = new double*[2481];
	for(int q=0;q<2481;q++)
	{
		LeftGeneratedMotionProfile[q] = new double[3];
		RightGeneratedMotionProfile[q] = new double[3];
	}
}

RotateProfileGenerator::~RotateProfileGenerator()
{
	for(int q=0;q<2481;q++)
	{
		delete LeftGeneratedMotionProfile[q];
		delete RightGeneratedMotionProfile[q];
	}
	delete LeftGeneratedMotionProfile;
	delete RightGeneratedMotionProfile;
}

void RotateProfileGenerator::GenerateMotionProfile(double angle) {
	m_position = 0;
	m_velocity = 0;
	m_accel = 1;
	m_iCounter = 0;
	m_angle = angle;

	if (m_angle >= 0){
		m_rotateRight = true;
	}
	else {
		m_rotateRight = false;
	}

	m_totalDistance = m_angle / 360.0;
	m_totalDistance *= kWheelBaseCircum;		//Calculating distance in encoder ticks per inch
	m_totalDistance = fabs(m_totalDistance) * kTicksPerInch;
	m_totalDistance /= kTicksPerRotation;

//	FillArray();
//	while (m_velocity <= kMaxVelocity){
//		if (m_position >= (m_totalDistance / 2)){
//			break;
//		}
//		m_accel = std::min(m_accel + kJerk, kMaxAccel);
//		m_velocity = std::min(m_velocity + m_accel, kMaxVelocity);
//		m_position += m_velocity;
//		m_iCounter++;
//		FillArray();
//	}
//
//	m_distanceToStop = m_position;
//
//	while ((m_distanceToStop + m_position) <= m_totalDistance){
//		m_position += m_velocity;
//		m_iCounter++;
//		FillArray();
//	}
//
//	m_accel = 0.0;
//
//	while (m_velocity >= 0){
//		m_accel = std::min(m_accel + kJerk, kMaxAccel);
//		m_velocity = std::max(m_velocity - m_accel, 0.0);
//		m_position += m_velocity;
//		m_iCounter++;
//		FillArray();
//	}
	bool done = false;
	int state = 0;

/*
	while(!done){
		switch(state){
				case 0:{
					m_accel = std::min(m_accel + (kJerk * kPeriod), kMaxAccel);
					if (m_accel >= kMaxAccel) {
						m_velocityAtMaxAccel = m_velocity;
						state = 1;
					}
					break;}
				case 1:{
					if(m_velocity + m_velocityAtMaxAccel >= kMaxVelocity){
						state = 2;
					}
					break;}
				case 2:{
					m_accel = std::max(m_accel - (kJerk * kPeriod), 0.0);
					if(m_accel <= 0){
						m_posAtMaxVelocity = m_position;
						state = 3;
					}
					break;}
				case 3:{
					if(m_position + m_posAtMaxVelocity >= m_totalDistance){
						state = 4;
					}
					break;}
				case 4:{
					m_accel = std::max(m_accel - (kJerk * kPeriod), -kMaxAccel);
					if(m_accel <= -kMaxAccel){
						state = 5;
					}
					break;}
				case 5:{
					if(m_velocity - m_velocityAtMaxAccel >= 0){
						state = 6;
					}
					break;}
				case 6:{
					m_accel = std::min(m_accel + (kJerk * kPeriod), 0.0);
					if(m_accel >= 0){
						state = 0;
						done = true;
					}
					break;}
		}
		*/

	//for (int i = 0; i < 10; i++)
	while (!done)
	{
		switch(state)
		{
			//Begin Increasing Velocity
			case 0:
			{
				m_velocity = std::min(m_velocity + (m_accel * kPeriod), kMaxVelocity);

				if(m_velocity >= kMaxVelocity)
				{
					m_posAtMaxVelocity = m_position + m_velocity;
					state = 1;
				}
				if (m_position >= m_totalDistance / 2){
					state = 2;
				}
				break;
			}
			//Coasting
			case 1:
			{
				//Do nothing special
				if(m_posAtMaxVelocity + m_position >= m_totalDistance)
				{
					state = 2;
				}
				break;
			}
			//Begin Decreasing Velocity
			case 2:
			{
				m_velocity = std::max(m_velocity - (m_accel * kPeriod), 0.0);
				if(m_velocity <= 0.0)
				{
					state = 0;
					done = true;
				}
				break;
			}
		}
		//m_velocity += m_accel;
		m_position += (m_velocity * kPeriod);
		FillArray();
		m_iCounter++;
	}
}

void RotateProfileGenerator::FillArray() {
	printf("%f %f %f \n", m_position, m_velocity, kPeriod * 1000);
	if (m_rotateRight){
		RightGeneratedMotionProfile[m_iCounter][0] = -m_position;
		RightGeneratedMotionProfile[m_iCounter][1] = -m_velocity * 60;
		RightGeneratedMotionProfile[m_iCounter][2] = kPeriod * 1000;

		LeftGeneratedMotionProfile[m_iCounter][0] = m_position;
		LeftGeneratedMotionProfile[m_iCounter][1] = m_velocity * 60;
		LeftGeneratedMotionProfile[m_iCounter][2] = kPeriod * 1000;
	}
	else {
		RightGeneratedMotionProfile[m_iCounter][0] = m_position;
		RightGeneratedMotionProfile[m_iCounter][1] = m_velocity * 60;
		RightGeneratedMotionProfile[m_iCounter][2] = kPeriod * 1000;

		LeftGeneratedMotionProfile[m_iCounter][0] = -m_position;
		LeftGeneratedMotionProfile[m_iCounter][1] = -m_velocity * 60;
		LeftGeneratedMotionProfile[m_iCounter][2] = kPeriod * 1000;
	}
}

int RotateProfileGenerator::GetProfileLength() {
	return m_iCounter;
}

double** RotateProfileGenerator::GetRightProfile() {
	return RightGeneratedMotionProfile;
}

double** RotateProfileGenerator::GetLeftProfile() {
	return LeftGeneratedMotionProfile;
}

void RotateProfileGenerator::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
