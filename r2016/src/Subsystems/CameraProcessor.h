/*
 * CameraProcessor.h
 *
 *  Created on: Jan 16, 2016
 *      Author: FIRSTMentor
 */

#ifndef SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_
#define SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_
#include <iostream>
#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

#include <Commands/Subsystem.h>

class CameraProcessor: public Subsystem {
private:
	const int k_resX = 640;
	const int k_resY = 480;
	const int k_FOV = 60;
	const int k_tWidthIn = 20;
	const int k_tHeightIn = 12;
	double m_area;
	int m_posx;
	int m_posy;
	int m_width;
	int m_height;
	double m_angle;
	std::shared_ptr<NetworkTable> m_table;
public:

	CameraProcessor();
	virtual ~CameraProcessor();
	bool isTargetAvailable();
	int getTargetX();
	int getTargetY();
	double getArea();
	int getWidth();
	int getHeight();
	double calculate();
};

#endif /* SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_ */
