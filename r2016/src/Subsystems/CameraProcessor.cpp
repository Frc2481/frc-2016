/*
 * CameraProcessor.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: FIRSTMentor
 */

#include <Subsystems/CameraProcessor.h>
#include <CMath>
#include <SubsystemBase.h>

CameraProcessor::CameraProcessor() : SubsystemBase("CameraProcessor") {
	m_area = 0;
	m_posx = 0;
	m_posy = 0;
	m_width = 0;
	m_height = 0;
	m_angle = 0;
}

CameraProcessor::~CameraProcessor() {
	// TODO Auto-generated destructor stub
}
void CameraProcessor::Periodic() {
	SmartDashboard::PutNumber("Target Area", m_area);
	SmartDashboard::PutNumber("Target of X", m_posx);
	SmartDashboard::PutNumber("Target of Y", m_posy);
	SmartDashboard::PutNumber("Target Width", m_width);
	SmartDashboard::PutNumber("Target Height", m_height);
	SmartDashboard::PutNumber("Target Angel", m_angle);
}

bool CameraProcessor::isTargetAvailable(){
	return true;
}

int CameraProcessor::getTargetX(){
	return m_posx;
}

int CameraProcessor::getTargetY(){
	return m_posy;
}

double CameraProcessor::getArea(){
	return m_area;
}

int CameraProcessor::getWidth(){
	return m_width;
}

int CameraProcessor::getHeight(){
	return m_height;
}

void CameraProcessor::calculate(){
	m_table = NetworkTable::GetTable("GRIP/aGoalContours");
	std::vector<double> areas = m_table->GetNumberArray("area", llvm::ArrayRef<double>());
	std::vector<double> centerYs = m_table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	std::vector<double> centerXs = m_table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> widths = m_table->GetNumberArray("width", llvm::ArrayRef<double>());
	std::vector<double> heights = m_table->GetNumberArray("height", llvm::ArrayRef<double>());
	double angle = 0;
	if(areas.size() > 0){
		for (unsigned int i = 0; i < areas.size(); i++) {
			if(areas[i] > m_area) {
				m_area = areas[i];
				m_posx = centerXs[i];
				m_posy = centerYs[i];
				m_width = widths[i];
				m_height = heights[i];
			}
		}
		m_posx = (m_posx - k_resX/2.0);
		m_posy = (m_posy - k_resY/2.0);
		double d = (k_tWidthIn*k_resX)/(2.0*m_width*tan(k_FOV*(3.1415965/180)/2.0));
		double w_i = m_posx*(k_tWidthIn/m_width);
		angle = atan(w_i/d)*180/3.14159265;
		SmartDashboard::PutNumber("Target Angle", angle);
		m_angle = angle;
	}
	//if we cant see the goal that means we are not facing the goal
	m_angle = 180;
}
