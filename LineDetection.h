// Author: Burak Özdemir
#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "CommonProcesses.h"
#include "Detection.h"
#include <vector>
/// @brief LineDetection class inherits from Detection.
/// The LineDetection class is derived from the Detection class, inheriting its functionality and properties.
class LineDetection: public Detection
{
	/// @brief Overloads the istream >> operator for reading Detection objects.
	/// @param is The input stream from which to read the Detection object.
	/// @param detection The Detection object to read data into.
	/// @return The modified input stream.
	friend istream& operator>>(istream&, LineDetection&);

	/// @brief Overloads the ostream << operator for writing Detection objects.
	/// @param os The output stream to which to write the Detection object.
	/// @param detection The Detection object to be written.
	/// @return The modified output stream.
	friend ostream& operator<<(ostream&, LineDetection&);

public:

	/// @brief Constructor for LineDetection with image, min threshold, max threshold, and kernel size.
	/// @param id The identifier for the LineDetection object.
	/// @param img The image data for the LineDetection object.
	/// @param min_thresh The minimum threshold for line detection.
	/// @param max_thresh The maximum threshold for line detection.
	/// @param kernelSize The kernel size for line detection.
	LineDetection(string id, Mat img, int min_thresh = 30, int max_thresh = 150, int kernelSize = 5);

	/// @brief Constructor for LineDetection with image path, min threshold, max threshold, and kernel size.
	/// @param id The identifier for the LineDetection object.
	/// @param p The file path of the image for the LineDetection object.
	/// @param min_thresh The minimum threshold for line detection.
	/// @param max_thresh The maximum threshold for line detection.
	/// @param kernelSize The kernel size for line detection.
	LineDetection(string id, string p, int min_thresh = 30, int max_thresh = 150, int kernelSize = 5);

	/// @brief Finds lines in the image using Canny and HoughLines algorithms.
	void findLine();

	/// @brief Sets the line data for the image.
	/// @param lines A vector of vectors of points representing the line data to be set.
	void setLine(vector<vector<Point>>);

	/// @brief Gets the line data from the image.
	/// @return A vector of vectors of points containing the line data.
	vector<vector<Point>> getLine();

	/// @brief Visualizes features with a trackbar for LineDetection.
	void visualizeFeatures_withTreackbar();

	/// @brief Change trackbar values.
	/// @param value The new value of the trackbar.
	/// @param dataPtr A pointer to data needed for the trackbar change.
	static void changeTrackbar(int value, void* dataPtr);

	/// @brief Gets the maximum threshold value for LineDetection.
	/// @return The maximum threshold value.
	int getMaxThr();

	/// @brief Gets the reference to the minimum threshold value for LineDetection.
	/// @return The reference to the minimum threshold value.
	int& getMinThr();

	/// @brief This function is a destructor of the Line Detection class.
	~LineDetection();


private:
	/// @brief Detected lines in the image.
	vector<vector<Point>> lines;
	/// @brief Minimum threshold value for line detection.
	int minThreshold;
	/// @brief Maximum threshold value for line detection (constant).
	const int maxThreshold;
	/// @brief Kernel size for line detection (constant).
	const int kernel_size;
};

