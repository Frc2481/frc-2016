/*
 * CameraProcessor.h
 *
 *  Created on: Jan 16, 2016
 *      Author: FIRSTMentor
 */

#ifndef SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_
#define SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_
#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include <SubsystemBase.h>

class CameraProcessor: public SubsystemBase {
private:
	const int k_resX = 640;
	const int k_resY = 480;
	const int k_FOV = 47;
	const int k_tWidthIn = 20;
	const int k_tHeightIn = 12;
	bool m_targetVisible;
	double m_angle;
	std::shared_ptr<NetworkTable> m_table;
public:

	CameraProcessor();
	virtual ~CameraProcessor();
	bool isTargetAvailable();
	double getAngle();
	void calculate();
	void Periodic();
};

#endif /* SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_ */
