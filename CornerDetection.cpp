// Author: Burak Özdemir
#include "CornerDetection.h"

/// @details This constructor initializes a CornerDetection object with the specified identifier and image, threshold.
/// Also this constructor sets detect type ( setDetectType("Corner") ).
/// Default values are provided for the parameters.
CornerDetection::CornerDetection(string id, Mat img,int thr):Detection(id,img), thresholdValue(thr)
{
    setDetectType("Corner");
    cout << "CornerDetection constructor of the " << getID() << " object." << endl;
}

/// @details This constructor initializes a CornerDetection object with the specified identifier, image path, threshold.
/// Also this constructor sets detect type ( setDetectType("Corner") ).
CornerDetection::CornerDetection(string id, string p,int thr):Detection(id,p), thresholdValue(thr)
{
    setDetectType("Corner");
    cout << "CornerDetection constructor of the " << getID() << " object." << endl;
}

/// @details This is a destructor of the CornerDetection class.
CornerDetection::~CornerDetection() {
    cout << "CornerDetection destructor of the " << getID() << " object." << endl;
}

/// @details This member function utilizes the cornerHarris algorithm to detect corners in the visual image.
/// Corners are converted to vector<vector<Point>> type. And it sets corners data.
void CornerDetection::findCorners()
{
    Mat img_gray;
    Mat dst = Mat::zeros(getImage().size(), CV_32FC1);

    vector<vector<Point>> cor;
    img_gray = RGB2Gray(getImage());
    cornerHarris(img_gray, dst, blockSize, aperatureSize, k);
    Mat dst_norm, dst_norm_scaled;
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());

    if (thresholdValue < 95) thresholdValue = 95;

    for (int i = 0; i < dst_norm.rows; i++)
    {
        for (int j = 0; j < dst_norm.cols; j++)
        {
            if ((int)dst_norm.at<float>(i, j) > thresholdValue)
            {
                cor.push_back({ Point(j, i) });
            }
        }
    }
    setCorners(cor);
    setData(getCorners());
}


/// @details This static function is called when the trackbar value changes.
/// It is used in conjunction with visualizeFeatures_withTreackbar.
void CornerDetection::changeTrackbar(int value, void* dataPtr) {
    CornerDetection* ptrObject = static_cast<CornerDetection*>(dataPtr);
    ptrObject->thresholdValue = value;
    ptrObject->findCorners();
    ptrObject->visualizeFeatures();
    setTrackbarPos("Threshold:", ptrObject->getWindowName(), value);
}

void CornerDetection::visualizeFeatures_withTreackbar() {
    namedWindow(getWindowName(), WINDOW_AUTOSIZE);
    createTrackbar("Threshold:", getWindowName(), &thresholdValue, 300, changeTrackbar, this);
    setTrackbarPos("Threshold:", getWindowName(), thresholdValue);
    while (true) {
        int key = waitKey(30);
        if (key == 27) break;
    }
}

/// @details This function returns the threshold value used in the feature visualization.
int CornerDetection::getThreshold(){
    return thresholdValue;
}

/// @details This member function sets the corner data for the visual image using the provided vector of vectors of points.
void CornerDetection::setCorners(vector<vector<Point>> cor)
{
    corners = cor;
}

/// @details This member function returns a vector of vectors of points representing the corner data from the visual image.
vector<vector<Point>> CornerDetection::getCorners(){
    return corners;
}

/// @details This friend function is used to extract the object's ID and path from the user.
istream& operator>>(istream& input, CornerDetection& lineObject) {
    input >> static_cast<Detection&>(lineObject)
        >> lineObject.thresholdValue;

    return input;
}
/// @details This friend function is used to insert the image ID, width, height, image features and Threshold into the output stream.
ostream& operator<<(ostream& output, CornerDetection& lineObject) {
    output << static_cast<Detection&>(lineObject)
        <<endl<< "Theshold: " << lineObject.thresholdValue;

    return output;
}