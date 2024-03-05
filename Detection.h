// Author: Burak Özdemir
#pragma once
#include <vector>
#include "CommonProcesses.h"
#include <fstream>
#include <algorithm>
#include <cmath>

/// @brief Detection class inherits from CommonProcesses.
/// The Detection class is derived from the CommonProcesses class, inheriting its functionality and properties.
class Detection: public CommonProcesses{

	/// @brief Overloads the istream >> operator for reading Detection objects.
	/// @param is The input stream from which to read the Detection object.
	/// @param detection The Detection object to read data into.
	/// @return The modified input stream.
	friend istream& operator>>(istream& , Detection&);

	/// @brief Overloads the ostream << operator for writing Detection objects.
	/// @param os The output stream to which to write the Detection object.
	/// @param detection The Detection object to be written.
	/// @return The modified output stream.
	friend ostream& operator<<(ostream&, Detection&);

public:

	/// @brief Default constructor for the Detection class.
	/// @param id The identifier for the Detection object.
	/// @param img The image data for the Detection object.
	Detection(string = "0", cv::Mat = Mat(0, 0, CV_64F));

	/// @brief Constructor for initializing Detection object with id and image path.
	/// @param id The identifier for the Detection object.
	/// @param path The file path of the image for the Detection object.
	Detection(string, string);

	/// @brief Writes edge and line information for the image to a text file.
	void writeFeatures();

	/// @brief Visualizes edge and line information on the image.
	void visualizeFeatures();

	/// @brief Gets the edge or line data from the image.
	/// @return A vector of vectors of points containing the edge or line data.
	vector<vector<Point>> getData();

	/// @brief Sets the edge or line data for the image.
	/// @param data A vector of vectors of points containing the edge or line data to be set.
	void setData(vector<vector<Point>>);

	/// @brief Gets the detection type for the image.
	/// @return A string representing the detection type.
	string getDetectType();


	/// @brief Sets the detection type for the image.
	/// @param detectType A string representing the detection type to be set.
	void setDetectType(string);

	/// @brief Calculates the distance between two points.
	/// @param point1 The first point.
	/// @param point2 The second point.
	/// @return The distance between the two points.
	double calculateLegth(Point,Point);

	/// @brief Writes feature information on the image.
	void putFeature();

	/// @brief Gets the visualization name of the image.
	/// @return The visualize name of the image.
	string getWindowName();

	/// @brief This function is a destructor of the Detection class.
	~Detection();

private:
	/// @brief Type of detection for the image.
	string detectType;

	/// @brief Data containing points or lines for detection.
	vector<vector<Point>> data;

	/// @brief Feature image for visualization.
	Mat featureImg;

	/// @brief Showing name of the image
	string windowName;

	/// @brief This data member holds the number of objects created.
	static int count_detect;
};

