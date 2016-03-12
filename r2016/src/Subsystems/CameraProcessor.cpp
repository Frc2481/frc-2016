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
	m_angle = 0;
	m_cameraLight = new Solenoid(CAMERA_LIGHT);
	m_onTarget = false;
	m_prevOwlCounter = 0;
	SmartDashboard::PutBoolean("Camera Tuning", false);
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
	double owlCounter = m_table->GetNumber("OwlCounter");
	if (owlCounter != m_prevOwlCounter){
		m_prevOwlCounter = owlCounter;
		m_owlMissingCounter = 0;
	}
	else {
		m_owlMissingCounter++;
		if (m_owlMissingCounter >= 50){
			SmartDashboard::PutNumber("Vision", false);
		}
		else{
			SmartDashboard::PutNumber("Vision", true);

		}
	}
}

bool CameraProcessor::isTargetAvailable(){
	return m_targetVisible;
}

double CameraProcessor::getAngle(){
	return m_angle;
}

void CameraProcessor::calculate(){
	m_table = NetworkTable::GetTable("GRIP/aGoalContours");
	std::vector<double> areas = m_table->GetNumberArray("area", llvm::ArrayRef<double>());
	std::vector<double> centerYs = m_table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	std::vector<double> centerXs = m_table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> widths = m_table->GetNumberArray("width", llvm::ArrayRef<double>());
	std::vector<double> heights = m_table->GetNumberArray("height", llvm::ArrayRef<double>());
	double angle = 0;
	double area = 0;
	double posx = 0;
	double posy = 0;
	double width = 0;
	double height = 0;
	m_targetVisible = false;
	m_angle = 0;
	//All of the size checks are needed to prevent a crash if GRIP is in the middle of removing a target while
	//we are grabbing the table.
	if(areas.size() > 0 &&
			areas.size() == centerXs.size() &&
			areas.size() == centerYs.size() &&
			areas.size() == widths.size() &&
			areas.size() == heights.size()){
		for (unsigned int i = 0; i < areas.size(); i++) {
			if(widths[i] > width) {
				area = areas[i];
				posx = centerXs[i];
				posy = centerYs[i];
				width = widths[i];
				height = heights[i];
			}
		}
		//refer to Drawing Github Wiki "Camera Processor"
		posx = (posx - k_resX/2.0);		//X position of target from center of Camera in pixels
		posy = (posy - k_resY/2.0);		//Y position of target from center of Camera in pixels

		double camDistToTargetY = (k_tWidthIn*k_resX)/(2.0 * width * tan(k_FOV*(M_PI/180)/2.0));		//hypotenuse distance from camera to Target in inches (Dc)
		double camDistToTargetX = posx*((double)k_tWidthIn/(double)width);	//Camera's distance to the Target on the X-axis (Parallel to target)(Wc)
		double camDistToTargetHyp = sqrt(pow(camDistToTargetY,2) + pow(camDistToTargetX,2));	//Camera's distance to the Target on the Y-axis (perpendicular to target)(Dr)
		SmartDashboard::PutBoolean("Shooter Hot Zones", camDistToTargetHyp > m_shotRange);
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
		angle = atan2(robotDistToTargetY_actual,robotDistToTargetX_actual) * (180/M_PI);		//angle from X-axis of Robot
		angle = 90 - angle;

		bool tuning = SmartDashboard::GetBoolean("Camera Tuning", false);
		if (tuning) {
			SmartDashboard::PutNumber("Camera Area", area);
			SmartDashboard::PutNumber("Camera Width", width);
			SmartDashboard::PutNumber("Camera Height", height);
			SmartDashboard::PutNumber("Camera PosX", posx);
			SmartDashboard::PutNumber("Camera PosY", posy);
			SmartDashboard::PutNumber("Camera Angle Actual", angle_actual);
			SmartDashboard::PutNumber("Camera Dist to Target Hyp",camDistToTargetHyp_actual);
			SmartDashboard::PutNumber("Camera Dist To Target X",camDistToTargetX_actual);
			SmartDashboard::PutNumber("Camera Dist To Target Y",camDistToTargetY_actual);
			SmartDashboard::PutNumber("Robot  Dist To Target X",robotDistToTargetX_actual);
			SmartDashboard::PutNumber("Robot  Dist To Target Y",robotDistToTargetY_actual);
		}
		SmartDashboard::PutNumber("Target Angle (relative)", angle);

		m_angle = angle;
		m_targetVisible = true;
	}
	if(-CAMERA_TOLERANCE < m_angle && m_angle < CAMERA_TOLERANCE){
			SmartDashboard::PutBoolean("Gyro on Target", m_targetVisible);
			m_onTarget = m_targetVisible;
		}
		else{
			SmartDashboard::PutBoolean("Gyro on Target", false);
			m_onTarget = false;
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
