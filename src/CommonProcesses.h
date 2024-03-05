// Author: Burak Özdemir
#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iomanip>
#include "matplotlibcpp.h"

using namespace std;
using namespace cv;

/// @brief CommonProcesses class for various image processing operations.
/// This class is designed to handle operations such as storing raw RGB data, displaying it on a viewer,
/// reading RGB data from a file, writing RGB data to a file, showing RGB data on the viewer,
/// rescaling, filtering noise, and converting from RGB to grayscale esc.
class CommonProcesses{

	/// @brief Overloaded input stream extraction operator for CommonProcesses.
	/// @param input The input stream (e.g., `cin`) from which the data is extracted.
	/// @param obj The CommonProcesses object to store the extracted data.
	/// @return A reference to the input stream after extraction.
	friend istream& operator>>(istream&, CommonProcesses&);

	/// @brief Overloaded output stream insertion operator for CommonProcesses.
	/// @param output The output stream (e.g., `cout`) to which the data is inserted.
	/// @param obj The CommonProcesses object from which data is extracted for insertion.
	/// @return A reference to the output stream after insertion.
	friend ostream& operator<<(ostream&, CommonProcesses&);

	public:
		/// @brief Default Constructor for the CommonProcesses class.
		/// @param id The ID to set for the CommonProcesses object (default is "0").
		/// @param image The image data to set for the CommonProcesses object (default is an empty matrix).
		CommonProcesses(string = "0", Mat = Mat(0, 0, CV_64F)); // içine id ve görüntüyü alýr.

		/// @brief Constructor for the CommonProcesses class that reads an image from a file.
		/// @param id The ID to set for the CommonProcesses object.
		/// @param path The file path from which to read the image.
		CommonProcesses(string,string); 

		/// @brief Sets the image data member of the CommonProcesses object.
		/// @param image The image to set as the new image data member.
		void setImage(Mat);

		/// @brief Gets the image data member of the CommonProcesses object.
		/// @return The image data member.
		Mat getImage();

		/// @brief Sets the ID of the CommonProcesses object.
		/// @param id The ID to set for the CommonProcesses object.
		void setID(string);

		/// @brief Gets the ID data member of the CommonProcesses object.
		/// @return The ID data member.
		string getID();

		/// @brief Sets the file path for the CommonProcesses object.
		/// @param path The file path to set for the CommonProcesses object.
		void setPath(string);

		/// @brief Gets the file path of the CommonProcesses object.
		/// @return The file path.
		string getPath();

		/// @brief Reads an image and sets it as the data member of CommonProcesses.
		/// @return The read image data.
		Mat readImage(); 

		/// @brief Reads an image from the specified file path.
		/// @param path The file path from which to read the image.
		/// @return The read image data. 
		static Mat readImage(string);

		/// @brief Saves the image to the current file path.
		void saveImage();

		/// @brief Saves the image to the specified file path.
		/// @param path The file path where the image will be saved.
		void saveImage(string);

		/// @brief Displays the image on the screen.
		void showImage();

		/// @brief Rescales the image to the specified height and width.
		/// @param img The input image to be rescaled.
		/// @param height The target height of the rescaled image.
		/// @param width The target width of the rescaled image.
		/// @return The rescaled image.
		static Mat rescaleImage(Mat,int, int);

		/// @brief Rescales the image to the specified height and width.
		/// @param h The target height of the rescaled image.
		/// @param w The target width of the rescaled image.
		/// @return A new CommonProcesses object with the rescaled image. 
		CommonProcesses rescaleImage(int,int);

		/// @brief Reduces noise in the image.
		/// @param img The input image from which to reduce noise.
		/// @return The image with reduced noise.
		static Mat reduceNoise(Mat);

		/// @brief Reduces noise in the image.
		/// @return A new CommonProcesses object with the image having reduced noise.
		CommonProcesses reduceNoise(); 


		/// @brief Converts the image to grayscale.
		/// @param img The input image to be converted.
		/// @return The grayscale version of the input image.
		static Mat RGB2Gray(Mat);

		/// @brief Converts the image to grayscale.
		/// @return A new CommonProcesses object with the image converted to grayscale.
		CommonProcesses RGB2Gray();

		/// @brief Normalizes the image.
		/// @return A new CommonProcesses object with the normalized image.
		CommonProcesses normalizeImage();

		/// @brief Applies erosion to the image.
		/// @return A new CommonProcesses object with the image after erosion.
		CommonProcesses erosion();

		/// @brief Applies dilation to the image.
		/// @return A new CommonProcesses object with the image after dilation.
		CommonProcesses dilation();

		/// @brief Applies opening operation to the image.
		/// @return A new CommonProcesses object with the image after opening operation.
		CommonProcesses openImage();

		/// @brief Applies closing operation to the image.
		/// @return A new CommonProcesses object with the image after closing operation.
		CommonProcesses closeImage();

		/// @brief Calculates the histogram of the image.
		/// @return A matrix representing the histogram of the image.
		Mat calculateHistogram();

		/// @brief Visualizes the histogram of the image.
		void visualizeHistogram();


		/// @brief Addition operator for CommonProcesses objects.
		/// @param other The CommonProcesses object whose image will be added.
		/// @return A new CommonProcesses object with the summed image.
		CommonProcesses operator+(CommonProcesses&);

		/// @brief Subtraction operator for CommonProcesses objects.
		/// @param other The CommonProcesses object whose image will be subtracted.
		/// @return A new CommonProcesses object with the subtracted image.
		CommonProcesses operator-(CommonProcesses&);

		/// @brief Addition (Rotation) operator for rotating CommonProcesses objects.
		/// @param degree The degree by which to rotate the image.
		/// @return A new CommonProcesses object with the rotated image.
		CommonProcesses operator+(int);

		/// @brief Subtraction (Rotation with counter clockwise) operator for rotating CommonProcesses objects.
		/// @param degrees The degree by which to rotate the image in the opposite direction.
		/// @return A new CommonProcesses object with the oppositely rotated image.
		CommonProcesses operator-(int);

		/// @brief Multiplication (Scaling) operator for scaling CommonProcesses objects.
		/// @param factor The factor by which to scale the image.
		/// @return A new CommonProcesses object with the scaled image.
		CommonProcesses operator*(int);

		/// @brief Division operator for rescaling CommonProcesses objects.
		/// @param factor The factor by which to rescale the image.
		/// @return A new CommonProcesses object with the rescaled image.
		CommonProcesses operator/(int);

		/// @brief This function is a destructor of the CommonProcesses class.
		~CommonProcesses();

	private:
		/// @brief Identifier for the CommonProcesses object.
		string ID;

		/// @brief Image data for the CommonProcesses object.
		Mat image;

		/// @brief Width of the image for the CommonProcesses object.
		int weight;

		/// @brief Height of the image for the CommonProcesses object.
		int height;

		/// @brief File path for the image for the CommonProcesses object.
		string path;

		/// @brief Gets the width of the image.
		/// @return The width of the image.
		int getWidth();

		/// @brief Gets the height of the image.
		/// @return The height of the image.
		int getHeight();

		/// @brief Gets the size of the image.
		/// @return The size of the image.
		Size getSize();

		/// @brief This data member holds the number of objects created.
		static int count;
};

