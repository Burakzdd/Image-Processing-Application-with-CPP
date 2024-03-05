// Author: Burak Özdemir
#include "CommonProcesses.h"

/// @details This default constructor initializes the CommonProcesses object with the specified ID and image. It sets these parameters inside.
CommonProcesses::CommonProcesses(string id,Mat img) {
	setImage(img);
	setID(id);
	count += 1;
	cout << "CommonProcesses constructor of the " << getID() << " object, Count =" << count <<endl;

}
/// @details This constructor takes an ID and a file path, reads the image from the specified path, and initializes (sets) parameters.
CommonProcesses::CommonProcesses(string id,string p):path(p){

	Mat img = readImage();
	setImage(img);
	setID(id);
	count += 1;
	cout << "CommonProcesses constructor of the " << getID() << " object, Count =" << count << endl;

}
/// @details This is a destructor of the CommonProcesses class.
CommonProcesses::~CommonProcesses() {
	count -= 1;
	cout << "CommonProcesses destructor of the " << getID() << " object, Count ="<<count << endl;
}

/// @details This function sets the ID of the CommonProcesses object with the specified ID.
void CommonProcesses::setID(string id) {
	ID = id;
}


/// @details This function returns the ID data member of the CommonProcesses object.
string CommonProcesses::getID(){
	return ID;
}

/// @details This function sets the image data member of the CommonProcesses object with the specified image.
void CommonProcesses::setImage(Mat img) {
	image = img;
}

/// @details This function returns the image data member of the CommonProcesses object.
Mat CommonProcesses::getImage(){
	return image;
}
/// @details This function sets the file path for the CommonProcesses object with the specified path.
void CommonProcesses::setPath(string p)
{
	path = p;
}

/// @details This function returns the image path of the CommonProcesses object.
string CommonProcesses::getPath(){
	return path;
}


/// @details This member function returns the size (width and height) of the CommonProcesses object's image.
Size CommonProcesses::getSize()
{
	return (getImage().size());
}

/// @deails This member function returns the height of the CommonProcesses object's image.
int CommonProcesses::getHeight()
{
	return getSize().height;
}


/// @details This member function returns the width of the CommonProcesses object's image.
int CommonProcesses::getWidth()
{
	return getSize().width;
}



/// @details This function reads and returns an image with getPath().
Mat CommonProcesses::readImage(){
	Mat img = imread(getPath(), IMREAD_COLOR);
	return img;
}
/// @details This static function can be used independently of an object. It reads and returns an image from the specified file path.
Mat CommonProcesses::readImage(string p) {
	Mat img = imread(p, IMREAD_COLOR);
	return img;
}
/// @details This function saves the image to the directory where the code is located.
void CommonProcesses::saveImage(){
	imwrite(path+getID() + ".jpg", image);
}


/// @details This function saves the image to the specified file path.
void CommonProcesses::saveImage(string p) {
	imwrite(p, image);
}

/// @details This function displays the image on the screen.
void CommonProcesses::showImage() {
	imshow("Output image "+ID, image);
	int k = waitKey(0);
}

/// @details This static function rescales the input image to the specified height and width and it returns the resize image.
Mat CommonProcesses::rescaleImage(Mat img,int h, int w) {
	Mat resize_img;
	resize(img, resize_img, Size(w, h), INTER_LINEAR);
	return resize_img;
}

/// @details This member function rescales the CommonProcesses object's image to the specified height and width and it returns new object.
CommonProcesses CommonProcesses::rescaleImage(int h,int w) {
	Mat resize_img;
	resize(getImage(), resize_img, Size(w, h), INTER_LINEAR);
	return CommonProcesses(getID() + "_resize", resize_img);
}


/// @details This static function reduces noise in the input image and it returns current image.
Mat CommonProcesses::reduceNoise(Mat img) {
	Mat reduce_noise_img;
	fastNlMeansDenoisingColored(img, reduce_noise_img, 30, 7, 3, 10);
	return reduce_noise_img;
}


/// @details This member function reduces noise in the CommonProcesses object's image and it returns new object .
CommonProcesses CommonProcesses::reduceNoise() {
	Mat reduce_noise_img;
	fastNlMeansDenoisingColored(getImage(), reduce_noise_img, 30, 7, 3, 10);

	return CommonProcesses(getID() + "_reduceNoise", reduce_noise_img);
}


/// @details This static function converts the input image to grayscaleand returns gray scale image.
Mat CommonProcesses::RGB2Gray(Mat img) {
	Mat grayImg;
	cvtColor(img, grayImg, COLOR_BGR2GRAY);
	return grayImg;
}


/// @details This member function converts the CommonProcesses object's image to grayscale and it returns new object.
CommonProcesses CommonProcesses::RGB2Gray() {
	Mat grayImg;
	cvtColor(getImage(), grayImg, COLOR_BGR2GRAY);

	return CommonProcesses(getID() + "_2Gray", grayImg);
}

/// @details This member function normalizes the CommonProcesses object's image.
CommonProcesses CommonProcesses::normalizeImage() {
	Mat normalized_image;
	normalize(this->getImage(), normalized_image, 0, 1, NORM_MINMAX, CV_32F);
	return CommonProcesses(this->getID()+"_normalize", normalized_image);
}

/// @details This member function applies erosion to the CommonProcesses object's image  and it returns new object.
CommonProcesses CommonProcesses::erosion() {
	Mat eroded_image;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(50, 50));
	erode(image, eroded_image, kernel);

	return CommonProcesses(this->getID() + "_erode", eroded_image);
}

/// @details This member function applies dilation to the CommonProcesses object's image.
CommonProcesses CommonProcesses::dilation() {
	Mat dilated_image;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(50, 50));
	dilate(image, dilated_image, kernel);

	return CommonProcesses(this->getID() + "_dilate", dilated_image);
}

/// @details This member function applies opening operation (combination of erosion and dilation member functions) to the CommonProcesses object's image.
CommonProcesses CommonProcesses::openImage() {

	CommonProcesses e = this->erosion();
	CommonProcesses d = e.dilation();

	return CommonProcesses(this->getID() + "_opened", d.getImage());

}

/// @details This member function applies closing operation (combination of dilation and erosion member functions) to the CommonProcesses object's image.
CommonProcesses CommonProcesses::closeImage() {

	CommonProcesses d = this->dilation();
	CommonProcesses e = d.erosion();

	return CommonProcesses(this->getID() + "_opened", e.getImage());
}

/// @details This member function calculates the histogram of the CommonProcesses object's image and returns histogram matrix.
Mat CommonProcesses::calculateHistogram() {
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	Mat hist;
	Mat img = RGB2Gray(getImage());
	calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);
	for (int i = 0; i < histSize; i++) {
		cout << "Value " << i << ": " << hist.at<float>(i) << " px" << endl;
	}
	return hist;
}

/// @details This member function visualizes histogram with matplotlib libary.
/// This function uses calculateHistogram function. 
void CommonProcesses::visualizeHistogram() {
	namespace plt = matplotlibcpp;

	Mat hist = calculateHistogram();
	
	vector<double> hist_data;
	for (int i = 0; i < 256; i++) {
		hist_data.push_back(hist.at<float>(i));
	}
	plt::plot(hist_data);
	plt::title("Histogram");
	plt::xlabel("Pixel Value");
	plt::show();
}

/// @details This friend function is used to extract the object's ID and path from the user. Also include readImage and setImage functions.
istream& operator>>(istream &input, CommonProcesses &image_object)
{
	cout << "Enter the image ID (3value) and path";
	input >>setw(3) >> image_object.ID
		>> image_object.path;
	Mat img =	image_object.readImage();
	image_object.setImage(img);
	return input;
}

/// @details This friend function is used to insert the image ID, width, and height into the output stream.
ostream& operator<<(ostream &output, CommonProcesses &image_object)
{
	output << "Image " << image_object.getID()
		<< " of size (w,h) = (" << image_object.getWidth()
		<< "," << image_object.getHeight() << ")";
	return output;
}

/// This operator adds the images of two CommonProcesses objects.
/// First, it checks the dimensions of the two images and if their sizes are not equal, it makes them equal by applying the resize operation.
/// It then adds the two images. Returns the new object.
CommonProcesses CommonProcesses::operator+(CommonProcesses& obj) {
	cv::Mat resizedImage;

	if (this->getImage().size() != obj.getImage().size()) {
		resize(this->getImage(), resizedImage, obj.getImage().size());
	}
	cv::Mat sum;
	cv::add(resizedImage, obj.getImage(), sum);

	string id_ = "sumof_image" + this->getID() + "_and_" + obj.getID();
	return CommonProcesses(id_, sum);;
}

/// @details This operator subtracts the image of the specified CommonProcesses object from the image of the current object.
/// First, it checks the dimensions of the two images and if their sizes are not equal, it makes them equal by applying the resize operation.
/// It then subtracts the two images from each other. Returns the new object.
CommonProcesses CommonProcesses::operator-(CommonProcesses &obj) {
	cv::Mat resizedImage;

	if (this->getImage().size() != obj.getImage().size()) {
		resize(this->getImage(), resizedImage, obj.getImage().size());
	}
	Mat difference;
	absdiff(resizedImage, obj.getImage(), difference);

	return CommonProcesses("differenceof_" + this->getID() + "_and_" + obj.getID(), difference);
}

// @details This operator rotates the image of the CommonProcesses object by the specified degree.
CommonProcesses CommonProcesses::operator+(int degree) {
	int width = getWidth();
	int height = getHeight();

	Point2f center(float(width / 2), float(height / 2));
	Mat rotated_image;
	warpAffine(getImage(), rotated_image, getRotationMatrix2D(center, degree, 1.0), getImage().size());

	return CommonProcesses(getID() + to_string(degree) + "_degreeRotate", rotated_image);
}

/// @details This operator rotates the image of the CommonProcesses object in the opposite direction (counter clock wise) of the specified degree.
CommonProcesses CommonProcesses::operator-(int degree){
	int width = getWidth();
	int height = getHeight();

	Point2f center(float(width / 2), float(height / 2));
	Mat rotated_image;
	warpAffine(getImage(), rotated_image, getRotationMatrix2D(center,(360 - degree), 1.0), getImage().size());

	return CommonProcesses(getID() +"_minus" + to_string(degree) + "degreeRotate", rotated_image);
}

/// @details This operator rescales the image of the CommonProcesses object by the specified factor.
/// This function uses rescaleImage member function. Ex: new_obj = obj*2 (The size of the image doubles.)
CommonProcesses CommonProcesses::operator*(int scale) {

	return rescaleImage(getHeight() * scale, getWidth() * scale);
}

/// @details This operator rescales the image of the CommonProcesses object by dividing its size by the specified factor.
CommonProcesses CommonProcesses::operator/(int scale) {
	return rescaleImage(getHeight()  / scale, getWidth()  / scale);
}

/// @detais Initialize the static data member.
int CommonProcesses::count = 0;
