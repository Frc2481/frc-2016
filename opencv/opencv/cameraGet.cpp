#include "cameraGet.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

cameraGet::cameraGet()
{
	angle = 0;
	area = 0;
	posx = 0;
	posy = 0;
	width = 0;
	height = 0;
	m_angle = 0;
}


cameraGet::~cameraGet()
{
}

int cameraGet::process(){

	Mat image;
	image = imread("opencvlogo.png", IMREAD_COLOR); // Read the file

	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Scalar minValues(37, 41, 41);
	Scalar maxValues(100, 154, 255);
	Mat hslImage;
	cv::cvtColor(image, hslImage, COLOR_BGR2HLS);

	Mat binImage;
	cv::inRange(hslImage, minValues, maxValues, binImage);

	vector<vector<Point> > contours;
	vector<Vec4i > hierarchy;
	findContours(binImage, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_TC89_KCOS);

	Mat temp = Mat::zeros(binImage.size(), CV_8UC3);
	RNG rng(12345);
	for (int i = 0; i < contours.size(); i++) {
		Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(temp, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	const double minArea = 400;
	double maxArea = 0;
	Mat target;
	for (int i = 0; i < contours.size(); i++) {
		Mat contour(contours[i]);
		double area = contourArea(contour);
		if (area < minArea) continue;
		if (area > maxArea) {
			maxArea = area;
			target = contour;
		}
	}
	if (maxArea) {
		Rect bounds = boundingRect(target);
		double width = bounds.width;
		double height = bounds.height;
		double centerX = bounds.x + bounds.width / 2.0;
		double centerY = bounds.y + bounds.height / 2.0;
		posx = (posx - k_resX / 2.0);
		posy = (posy - k_resY / 2.0);
		double d = (k_tWidthIn*k_resX) / (2.0*width*tan(k_FOV*(3.14159265) / 180) / 2.0);
		double w_i = posx*((double)k_tWidthIn / (double)width);
		angle = atan(w_i / d) * 180 / 3.14159265;
		cout << "Width: " << width;
		cout << " Height: " << height;
		cout << " centerX: " << centerX;
		cout << " centerY: " << centerY;
		//cout << endl;
	}



	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", temp); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;

}