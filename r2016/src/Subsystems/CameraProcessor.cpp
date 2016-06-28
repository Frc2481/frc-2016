/*
 * CameraProcessor.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: FIRSTMentor
 */

#include <Subsystems/CameraProcessor.h>
#include <CMath>
#include <math.h>
#include <SubsystemBase.h>
#include "../RobotMap.h"

CameraProcessor::CameraProcessor() : SubsystemBase("CameraProcessor") {
	m_cameraLight = new Solenoid(CAMERA_LIGHT);
	m_onTarget = false;
	m_targetVisible = false;
	m_owlMissingCounter = 0;
	m_prevOwlCounter = 0;
	m_robotCounter = 0;
	m_activeTarget = RIGHT_TARGET;
	m_steadyCount = 0;
	SmartDashboard::PutBoolean("Camera Tuning", false);

	//Zero out all the targets.
	Target t{};
	for (int i = 0; i < TARGET_TYPE_SIZE; ++i) {
		m_targets[i] = t;
		m_prevTargets[i] = t;
	}
}

CameraProcessor::~CameraProcessor() {
	// TODO Auto-generated destructor stub
}

void CameraProcessor::SetLight(bool state) {
	m_cameraLight->Set(state);
}

void CameraProcessor::Periodic() {
	calculate();
	m_table = NetworkTable::GetTable("GRIP/aGoalContours");
	double owlCounter = m_table->GetNumber("OwlCounter", 0);
	if (owlCounter != m_prevOwlCounter){
		m_prevOwlCounter = owlCounter;
		m_owlMissingCounter = 0;
		SmartDashboard::PutBoolean("Vision", true);
	}
	else {
		m_owlMissingCounter++;
		if (m_owlMissingCounter >= 50){
			SmartDashboard::PutBoolean("Vision", false);
		}
		else{
			SmartDashboard::PutBoolean("Vision", true);
		}
	}
	m_table->PutNumber("RobotCounter", m_robotCounter++);
	SmartDashboard::PutNumber("Camera Offset Angle", m_OffsetAngle);
	SmartDashboard::PutBoolean("Target in Range", m_targets[m_activeTarget].distance > m_shotRange);
	SmartDashboard::PutNumber("Target Angle (relative)", m_targets[m_activeTarget].angle);
	SmartDashboard::PutBoolean("Camera Stable", isCameraSteady());
}

bool CameraProcessor::isTargetAvailable(){
	return m_targetVisible;
}

double CameraProcessor::getAngle(){
	return m_targets[m_activeTarget].angle;
}

void CameraProcessor::calculate(){
	m_table = NetworkTable::GetTable("GRIP/aGoalContours");
	std::vector<double> areas = m_table->GetNumberArray("area", llvm::ArrayRef<double>());
	std::vector<double> centerYs = m_table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	std::vector<double> centerXs = m_table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> widths = m_table->GetNumberArray("width", llvm::ArrayRef<double>());
	std::vector<double> heights = m_table->GetNumberArray("height", llvm::ArrayRef<double>());

	m_targetVisible = false;

	//Zero out all the targets.
	Target t{};
	for (int i = 0; i < TARGET_TYPE_SIZE; ++i) {
		m_targets[i] = t;
	}

	//All of the size checks are needed to prevent a crash if GRIP is in the middle of removing a target while
	//we are grabbing the table.
	if(areas.size() > 0 &&
			areas.size() == centerXs.size() &&
			areas.size() == centerYs.size() &&
			areas.size() == widths.size() &&
			areas.size() == heights.size()){

		for (unsigned int i = 0; i < areas.size(); i++) {

			Target target;
			target.x = centerXs[i];
			target.y = centerYs[i];
			target.width = widths[i];
			target.height = heights[i];
			target.area = areas[i];

			//Keep track of the left most target.
			if (centerXs[i] < m_targets[LEFT_TARGET].x || i == 0) {
				m_targets[LEFT_TARGET] = target;
			}

			//Keep track of the right most target.
			if (centerXs[i] > m_targets[RIGHT_TARGET].x || i == 0) {
				m_targets[RIGHT_TARGET] = target;
			}

			//Keep track of the largest target.
			if (widths[i] > m_targets[AUTO_TARGET].width) {
				m_targets[AUTO_TARGET] = target;
			}
		}

		//If one of the targets is vastly larger than the other then ignore the small one regardless.
//		if (areas.size() == 2) {
//			double ratio = m_targets[LEFT_TARGET].area / m_targets[RIGHT_TARGET].area;
//			if (ratio < 1 - k_sizeTolerance) {
//				printf("RIGHT %f %f %f\n", ratio, m_targets[LEFT_TARGET].area, m_targets[RIGHT_TARGET].area);
//				m_targets[LEFT_TARGET] = m_targets[RIGHT_TARGET];
//			}
//			else if (ratio > 1 + k_sizeTolerance) {
//				printf("LEFT %f %f %f\n", ratio, m_targets[LEFT_TARGET].area, m_targets[RIGHT_TARGET].area);
//				m_targets[RIGHT_TARGET] = m_targets[LEFT_TARGET];
//			}
//		}

		//If there are more than 2 targets ignore all but the largest.
		if (areas.size() > 2) {
			m_targets[LEFT_TARGET] = m_targets[RIGHT_TARGET] = m_targets[AUTO_TARGET];
		}

		//Calculate angle and distance of left target.
		calculateDistanceAndAngleOfTarget(m_targets[LEFT_TARGET]);

		//Calculate angle and distance of right target.
		calculateDistanceAndAngleOfTarget(m_targets[RIGHT_TARGET]);

		//Calculate angle and distance of auto target.
		calculateDistanceAndAngleOfTarget(m_targets[AUTO_TARGET]);

		bool tuning = SmartDashboard::GetBoolean("Camera Tuning", false);
		if (tuning) {
			SmartDashboard::PutNumber("Camera Area", m_targets[m_activeTarget].area);
			SmartDashboard::PutNumber("Camera Width", m_targets[m_activeTarget].width);
			SmartDashboard::PutNumber("Camera Height", m_targets[m_activeTarget].height);
			SmartDashboard::PutNumber("Camera PosX", m_targets[m_activeTarget].x);
			SmartDashboard::PutNumber("Camera PosY", m_targets[m_activeTarget].y);
		}

		m_targetVisible = true;
	}

	calculateSteadyCount();

	if(-CAMERA_TOLERANCE < getAngle() && getAngle() < CAMERA_TOLERANCE){
			SmartDashboard::PutBoolean("Camera on Target", m_targetVisible);
			m_onTarget = m_targetVisible;
		}
		else{
			SmartDashboard::PutBoolean("Camera on Target", false);
			m_onTarget = false;
		}
}

void CameraProcessor::calculateDistanceAndAngleOfTarget(Target& target) {
	target.x = (target.x - k_resX/2.0);		//X position of target from center of Camera in pixels

	double camDistToTargetY = (k_tWidthIn*k_resX)/(2.0 * target.width * tan(k_FOV*(M_PI/180)/2.0));		//hypotenuse distance from camera to Target in inches (Dc)
	double camDistToTargetX = target.x*((double)k_tWidthIn/(double)target.width);	//Camera's distance to the Target on the X-axis (Parallel to target)(Wc)

	//Camera Angle
	double camAngle = 20.0;
	double testDistance = target.y/tan(camAngle * (M_PI/180));

	double camDistToTargetHyp = sqrt(pow(camDistToTargetY,2) + pow(camDistToTargetX,2));	//Camera's distance to the Target on the Y-axis (perpendicular to target)(Dr)
	double camera_angle = atan2(camDistToTargetY,camDistToTargetX) * (180/M_PI);
	camera_angle = 90 - camera_angle;


	double angle_actual = m_OffsetAngle + camera_angle;
	double camDistToTargetY_actual = (camDistToTargetHyp * cos(angle_actual * M_PI/180));
	double camDistToTargetX_actual = (camDistToTargetHyp * sin(angle_actual * M_PI/180));
	double camDistToTargetHyp_actual = sqrt(pow(camDistToTargetY_actual,2) + pow(camDistToTargetX_actual,2));

//		double robotDistToTargetX = camDistToTargetX + k_xOffset;		//Robot's distance to the Target on the X-axis (Wr)

//		angle = atan2(robotDistToTargetX,robotDistToTargetY) * 180/3.14159265;		//angle from X-axis of Robot
	double robotDistToTargetX_actual = camDistToTargetX_actual + k_xOffset;
	double robotDistToTargetY_actual = camDistToTargetY_actual + k_yOffset;
	//double robotDistToTargetX = camDistToTargetX - k_xOffset;		//Robot's distance to the Target on the X-axis (Wr)
	//double robotDistToTargetY = camDistToTargetY - k_yOffset;		//Robot's distance to the Target on the Y-axis (Lr)
	target.angle = atan2(robotDistToTargetY_actual,robotDistToTargetX_actual) * (180/M_PI);		//angle from X-axis of Robot
	target.angle = 90 - target.angle;
	target.distance = camDistToTargetHyp;

	bool tuning = SmartDashboard::GetBoolean("Camera Tuning", false);

	if (tuning) {
		SmartDashboard::PutNumber("Test Camera Distance", testDistance);
		SmartDashboard::PutNumber("Camera Angle Actual", angle_actual);
		SmartDashboard::PutNumber("Camera Dist to Target Hyp",camDistToTargetHyp_actual);
		SmartDashboard::PutNumber("Camera Dist To Target X",camDistToTargetX_actual);
		SmartDashboard::PutNumber("Camera Dist To Target Y",camDistToTargetY_actual);
		SmartDashboard::PutNumber("Robot  Dist To Target X",robotDistToTargetX_actual);
		SmartDashboard::PutNumber("Robot  Dist To Target Y",robotDistToTargetY_actual);
	}
}

bool CameraProcessor::isOnTarget() {
	return m_onTarget;
}

void CameraProcessor::incOffsetAngle() {
	m_OffsetAngle += .5;
}

void CameraProcessor::decOffSetAngle() {
	m_OffsetAngle -= .5;
}

void CameraProcessor::lockOnTarget(target_type_t target) {
	//FIXME: Only allow left and right for now.
	if (target < TARGET_TYPE_SIZE - 1) {
		m_activeTarget = target;
	}
}

void CameraProcessor::calculateSteadyCount() {
	if (m_targetVisible &&
			(m_prevTargets[LEFT_TARGET] == m_targets[LEFT_TARGET] ||
			m_prevTargets[RIGHT_TARGET] == m_targets[RIGHT_TARGET])) {
		m_steadyCount++;
	}
	else {
		m_steadyCount = 0;
//		printf("PREV: %f ", m_prevTargets[LEFT_TARGET].x);
//		printf(" %f ", m_prevTargets[LEFT_TARGET].area);
//		printf(" %f ", m_prevTargets[RIGHT_TARGET].x);
//		printf(" %f ", m_prevTargets[RIGHT_TARGET].area);
//		printf(" %f ", m_prevTargets[AUTO_TARGET].x);
//		printf(" %f\n", m_prevTargets[AUTO_TARGET].area);
//		printf("CUR: %f ", m_targets[LEFT_TARGET].x);
//		printf(" %f ", m_targets[LEFT_TARGET].area);
//		printf(" %f ", m_targets[RIGHT_TARGET].x);
//		printf(" %f ", m_targets[RIGHT_TARGET].area);
//		printf(" %f ", m_targets[AUTO_TARGET].x);
//		printf(" %f\n", m_targets[AUTO_TARGET].area);
	}

	for (int i = 0; i < TARGET_TYPE_SIZE; ++i) {
		m_prevTargets[i] = m_targets[i];
	}
}

bool CameraProcessor::isCameraSteady() {
	return m_steadyCount > 20;
}
