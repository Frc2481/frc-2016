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
}

CameraProcessor::~CameraProcessor() {
	// TODO Auto-generated destructor stub
}

void CameraProcessor::SetLight(bool state) {
	m_cameraLight->Set(state);
}

void CameraProcessor::Periodic() {
	calculate();
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
		double camDistToTargetHyp = (k_tWidthIn*k_resX)/(2.0 * width * tan(k_FOV*(M_PI/180)/2.0));		//hypotenuse distance from camera to Target in inches (Dc)
		double camDistToTargetX = posx*((double)k_tWidthIn/(double)width);	//Camera's distance to the Target on the X-axis (Parallel to target)(Wc)
		if(fabs(camDistToTargetHyp) > fabs(camDistToTargetX)){
			double camDistToTargetY = sqrt(pow(camDistToTargetHyp,2) - pow(camDistToTargetX,2));	//Camera's distance to the Target on the Y-axis (perpendicular to target)(Dr)
//			double robotDistToTargetX = camDistToTargetX + k_xOffset;		//Robot's distance to the Target on the X-axis (Wr)
			double robotDistToTargetX = camDistToTargetX - k_xOffset;		//Robot's distance to the Target on the X-axis (Wr)
			double robotDistToTargetY = camDistToTargetY - k_yOffset;		//Robot's distance to the Target on the Y-axis (Lr)
			angle = atan2(robotDistToTargetY,robotDistToTargetX) * 180/M_PI;		//angle from X-axis of Robot
//			angle = atan2(robotDistToTargetX,robotDistToTargetY) * 180/3.14159265;		//angle from X-axis of Robot
			angle = 90 - angle;

			SmartDashboard::PutNumber("Camera Area", area);
			SmartDashboard::PutNumber("Camera Width", width);
			SmartDashboard::PutNumber("Camera Height", height);
			SmartDashboard::PutNumber("Camera PosX", posx);
			SmartDashboard::PutNumber("Camera PosY", posy);
			SmartDashboard::PutNumber("Camera Dist to Target Hyp",camDistToTargetHyp);
			SmartDashboard::PutNumber("Camera Dist To Target X",camDistToTargetX);
			SmartDashboard::PutNumber("Camera Dist To Target Y",camDistToTargetY);
			SmartDashboard::PutNumber("Robot  Dist To Target X",robotDistToTargetX);
			SmartDashboard::PutNumber("Robot  Dist To Target Y",robotDistToTargetY);
			SmartDashboard::PutNumber("Target Angle (relative)", angle);

			m_angle = angle;
			m_targetVisible = true;
		}
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
