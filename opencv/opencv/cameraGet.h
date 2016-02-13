#pragma once

#include <iostream>
class cameraGet
{
public:
	cameraGet();
	~cameraGet();
	double angle;
	double area;
	double posx;
	double posy;
	double width;
	double height;
	double m_angle;
	double k_resX;
	double k_resY;
	double k_FOV;
	double k_tWidthIn;
	int process();
};

