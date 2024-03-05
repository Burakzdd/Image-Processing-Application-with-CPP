// Author: Burak Özdemir
#include "Detection.h"

/// This constructor initializes a Detection object with default values. This default constructor initializes the CommonProcesses object with the specified ID and image.
/// And also intitialize windowName (= detectType + " " + ID)
Detection::Detection(string id, Mat img):CommonProcesses(id,img)
{
    windowName = detectType + " " + id;

    count_detect += 1;
    cout << "Detection Class constructor of the " << getID() << " object, Count =" << count_detect << endl;
}

/// @details This constructor initializes a Detection object with the specified identifier and image path. And also intitialize windowName (= detectType + " " + ID)
Detection::Detection(string id, string p):CommonProcesses(id,p)
{
    windowName = detectType + " " + id;

    count_detect += 1;
    cout << "Detection Class constructor of the " << getID() << " object, Count =" << count_detect << endl;
}

/// @details This is a destructor of the Detection class.
Detection::~Detection(){
    count_detect -= 1;
    cout << "Detection Class destructor of the " << getID() << " object, Count =" << count_detect << endl;
}

/// @details This member function returns a vector of vectors of points representing either edge or line data from the image.
vector<vector<Point>> Detection::getData(){
    return data;
}


/// @details This member function sets the edge or line data for the visual image using the provided vector of vectors of points.
void Detection::setData(vector<vector<Point>> d) {
    data = d;
}

string Detection::getWindowName(){
    return windowName;
}

/// @details This member function writes the specified features (edge or corner) of the image to a text file.
void Detection::writeFeatures() {

    ofstream file("./"+detectType + getID() + ".txt");
    file << "Featues of image" << getID()<<endl;

    for (int i = 0; i < data.size(); ++i) {
        cout << detectType << i + 1 << " Points:" << endl;
        file << detectType << i + 1 << " Points:" << endl;
        for_each(data[i].begin(), data[i].end(), [&](Point value){
            std::cout << value  << std::endl;
            file << value << std::endl;
            });
    }
}

/// @details This member function visualizes the points representing edge and line information on the image. 
/// The line function is used to show edges, and the circle function is used to show corners.
void Detection::visualizeFeatures(){
    featureImg = getImage().clone();

    if (detectType == "Line") {
        for (vector<Point> pointRow : data) {
            for (int i = 0; i + 1 < pointRow.size(); i += 2) {
                const Point& start = pointRow[i];
                const Point& end = pointRow[i + 1];
                line(featureImg, Point(start.x, start.y), Point(end.x, end.y), Scalar(255, 0, 0), 2, LINE_AA);
            }
        }
    }
    else {
        for (const auto& point : data) {
            circle(featureImg, point[0], 20, Scalar(255, 0, 0), 2);
        }
    }
    imshow(windowName, featureImg);
}

/// @details This member function returns the detection type data member for the object.
string Detection::getDetectType(){
    return detectType;
}


/// @details This member function sets the detection type for the visual image.
void Detection::setDetectType(string dtype) {
    detectType = dtype;
}


/// @details This member function calculates the Euclidean distance between two points.
double Detection::calculateLegth(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}


/// @details This member function writes information about points or lines onto the image.
/// The center point for edges and the length for lines (with the Calculate Length function) are printed on the image.
void Detection::putFeature() {
        if (featureImg.empty()) 
            featureImg = getImage().clone();

        if (detectType == "Line") {
            for (vector<Point> pointRow : data) {
                for (size_t i = 0; i + 1 < pointRow.size(); i += 2) {
                    Point& start = pointRow[i];
                    Point& end = pointRow[i + 1];
                    double length = calculateLegth(start,end);
                    putText(featureImg, to_string(int(round(length))) + "px", Point(start.x, start.y - 1), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);
                }
            }
        }
        else {
            for (vector<Point> point : data) {
                putText(featureImg, to_string(point[0].x)+","+ to_string(point[0].y), point[0], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);
            }
        }
        imshow(detectType + " " + getID(), featureImg);
        int k = waitKey(0);
}

/// @details This friend function is used to extract the object's ID and path from the user. 
istream& operator>>(istream& input, Detection& detectImage) {
    input >> static_cast<CommonProcesses&>(detectImage);
    return input;
}

/// @details This friend function is used to insert the image ID, width, height and image features into the output stream.
ostream& operator<<(ostream& output , Detection& detectImage) {
        output << static_cast<CommonProcesses&>(detectImage)
        << endl << "Detect Type is" << detectImage.getDetectType() << endl
        << "Features of image" << detectImage.getID();

        for (int i = 0; i < detectImage.data.size(); ++i) {
            output << detectImage.getDetectType() << i + 1 << " Points:" << endl;
            for_each(detectImage.data[i].begin(), detectImage.data[i].end(), [&](Point value) {
                output << value << endl;
                });
        }
    return output;
}

/// @detais Initialize the static data member.
int Detection::count_detect = 0;
