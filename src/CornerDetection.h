// Author: Burak Özdemir
#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "CommonProcesses.h"
#include "Detection.h"
#include <vector>
using namespace cv;
using namespace std;

/// @brief CornerDetection class inherits from Detection.
/// The CornerDetection class is derived from the Detection class, inheriting its functionality and properties.
class CornerDetection: public Detection
{
	/// @brief Overloads the istream >> operator for reading Detection objects.
	/// @param is The input stream from which to read the Detection object.
	/// @param detection The Detection object to read data into.
	/// @return The modified input stream.
	friend istream& operator>>(istream&, CornerDetection&);

	/// @brief Overloads the ostream << operator for writing Detection objects.
	/// @param os The output stream to which to write the Detection object.
	/// @param detection The Detection object to be written.
	/// @return The modified output stream.
	friend ostream& operator<<(ostream&, CornerDetection&);

public:
	/// @brief Constructor for CornerDetection with default values for identifier and image.
	/// @param id The identifier for the CornerDetection object.
	/// @param img The image data for the CornerDetection object.
	CornerDetection(string = "0", Mat = Mat(0, 0, CV_64F),int thr = 200);

	/// @brief Constructor for CornerDetection with identifier and image path.
	/// @param id The identifier for the CornerDetection object.
	/// @param path The file path of the image for the CornerDetection object.
	CornerDetection(string, string, int thr = 200);

	/// @brief Finds corners in the image using the cornerHarris algorithm.
	void findCorners();

	/// @brief Sets the corner data for the image.
	/// @param corners A vector of vectors of points representing the corner data to be set.
	void setCorners(vector<vector<Point>>);

	/// @brief Gets the corner data from the image.
	/// @return A vector of vectors of points containing the corner data.
	vector<vector<Point>> getCorners();

	/// @brief Visualize features using a trackbar.
	void visualizeFeatures_withTreackbar();

	/// @brief Static function to change trackbar values.
	/// @param value The new value of the trackbar.
	/// @param dataPtr A pointer to data needed for the trackbar change.
	static void changeTrackbar(int value, void* dataPtr);

	/// @brief Get the threshold value.
	/// @return The threshold value.
	int getThreshold();

	/// @brief This function is a destructor of the CornerDetection class.
	~CornerDetection();

private:
	/// @brief Detected corners in the image.
	vector<vector<Point>> corners;
	/// @brief Threshold value for corner detection.
	int thresholdValue;
	
	///@brief Harris Corner Detection parameters.
	///
	/// These parameters are used in the Harris Corner Detection algorithm.
	///
	///Size of the block for gradient computation.
	const int blockSize = 2;       
	///Aperture parameter for the Sobel operator.
	const int aperatureSize = 3;  
	///Harris Corner Response parameter.
	const double k = 0.04;         
};
