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
	m_angle = 0;
}

CameraProcessor::~CameraProcessor() {
	// TODO Auto-generated destructor stub
}
void CameraProcessor::Periodic() {
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
	m_angle = 0;
	if(areas.size() > 0){
		for (unsigned int i = 0; i < areas.size(); i++) {
			if(areas[i] > area) {
				area = areas[i];
				posx = centerXs[i];
				posy = centerYs[i];
				width = widths[i];
				height = heights[i];
			}
		}
		posx = (posx - k_resX/2.0);
		posy = (posy - k_resY/2.0);
		double d = (k_tWidthIn*k_resX)/(2.0*width*tan(k_FOV*(3.1415965/180)/2.0));
		double w_i = posx*((double)k_tWidthIn/(double)width);
		angle = atan(w_i/d)*180/3.14159265;
		SmartDashboard::PutNumber("Target Angle", angle);
		SmartDashboard::PutNumber("D",d);
		SmartDashboard::PutNumber("W_I",w_i);
		SmartDashboard::PutNumber("Target Area", area);
		SmartDashboard::PutNumber("Target of X", posx);
		SmartDashboard::PutNumber("Target of Y", posy);
		SmartDashboard::PutNumber("Target Width", width);
		SmartDashboard::PutNumber("Target Height", height);
		m_angle = angle;
		m_targetVisible = true;
	}
	else {
		m_targetVisible = false;
	}
}
