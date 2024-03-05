// Authot: Burak Özdemir
#include "LineDetection.h"


/// @details This constructor initializes a LineDetection object with the specified identifier, image, minimum threshold,
/// maximum threshold, and kernel size. Also this constructor sets detect type ( setDetectType("Line") ).
LineDetection::LineDetection(string id, Mat img,int min_thresh,int max_thresh, int kSize)
	:Detection(id,img),minThreshold(min_thresh),maxThreshold(max_thresh),kernel_size(kSize)
{
	setDetectType("Line");
	cout << "LineDetection Class constructor of the " << getID() << " object." << endl;
}

/// @details This constructor initializes a LineDetection object with the specified identifier, image path, minimum threshold,
/// maximum threshold, and kernel size. Also this constructor sets detect type ( setDetectType("Line") ).
LineDetection::LineDetection(string id, string p, int min_thresh,int max_thresh, int kSize)
	:Detection(id, p),minThreshold(min_thresh), maxThreshold(max_thresh), kernel_size(kSize)
{
	setDetectType("Line");
	cout << "LineDetection Class constructor of the " << getID() << " object."<<endl;
}

/// @details This is a destructor of the LineDetection class.
LineDetection::~LineDetection(){
	cout << "LineDetection Class destructor of the " << getID() << " object."<<endl;
}


/// @details This member function sets the line data for the visual image using the provided vector of vectors of points.
void LineDetection::setLine(vector<vector<Point>> l) {
	lines = l;
}

/// @details This member function returns a vector of vectors of points representing the line data from the visual image.
vector<vector<Point>> LineDetection::getLine() {
	return lines;
}

/// @details This member function returns the reference to the minimum threshold value used for line detection in LineDetection.
/// It allows direct modification of the minimum threshold value.
int & LineDetection::getMinThr() {
	return minThreshold;
}

/// @details This member function returns the maximum threshold value used for line detection in LineDetection.
int LineDetection::getMaxThr() {
	return maxThreshold;
}

/// @details This member function utilizes the Canny edge detection and HoughLines algorithms to detect lines in the image. 
/// Lines are converted to vector<vector<Point>> type (made to be the same type as corners). And it sets lines data.
void LineDetection::findLine() {
	Mat img_gray;
	vector<vector<Point>> lines;

	img_gray = RGB2Gray(getImage());
	Mat line_img;
	blur(img_gray, line_img, Size(kernel_size, kernel_size));
	Canny(line_img, line_img, getMinThr(), getMaxThr());
	vector<Vec4i> linesP;
	HoughLinesP(line_img, linesP, 1, CV_PI / 180, 30, 30, 10); 
	for (Vec4i& vec : linesP) {
		std::vector<Point> pointRow;
		for (int i = 0; i < 4; i += 2) {
			Point point(vec[i], vec[i + 1]);
			pointRow.push_back(point);
		}
		lines.push_back(pointRow);
	}
	setLine(lines);
	setData(getLine());
}

/// @details This static function is called when the trackbar value changes.
/// It is used in conjunction with visualizeFeatures_withTreackbar. This function sets minThreshold and calls findLine() and visualizeFeatures() functions.
void LineDetection::changeTrackbar(int value, void* dataPtr) {
	LineDetection* ptrObject = static_cast<LineDetection*>(dataPtr);
	ptrObject->minThreshold = value;
	ptrObject->findLine();
	ptrObject->visualizeFeatures();
	setTrackbarPos("Threshold:", ptrObject->getWindowName(), value);
}

/// @details This member function visualizes the features (lines) on the visual image while allowing the adjustment of the
/// min threshold value through a trackbar.
void LineDetection::visualizeFeatures_withTreackbar() {
	namedWindow(getWindowName(), WINDOW_AUTOSIZE);
	createTrackbar("Threshold:", getWindowName(), &getMinThr(), minThreshold * 3, changeTrackbar, this);
	cout << minThreshold << endl;

	while (true) {
		int key = waitKey(30);
		if (key == 27) break;
	}
}

/// @details This friend function is used to get the ID, path and minThreshold value of the object from the user.
istream& operator>>(istream& input, LineDetection& lineObject) {
	input >> static_cast<Detection&>(lineObject) 
		>> lineObject.minThreshold;

	return input;
}
/// @details This friend function is used to insert the image ID, width, height, image features and Threshold Min-Max into the output stream.
ostream& operator<<(ostream& output, LineDetection& lineObject) {
	output << static_cast<Detection&>(lineObject)
		<< "Theshold Min:" << lineObject.getMinThr()<< "- Max:" << lineObject.getMaxThr();

	return output;
}
