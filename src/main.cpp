// main.cpp 
// Author: Burak Özdemir
//
#include <iostream>
#include "CommonProcesses.h"
#include <opencv2/opencv.hpp>
#include "CornerDetection.h"
#include <vector>
#include "LineDetection.h"
using namespace cv;
using namespace std;

int main()
 {

    string path = "./bb8.jpg";
    CommonProcesses cp1("BB8", path);  
    cp1.showImage();
    cp1.RGB2Gray().showImage();
    cp1.reduceNoise().showImage();
    cp1.rescaleImage(500, 100).showImage();
    cp1.visualizeHistogram();

    string path2 = "./arti-modified.jpg";
    Mat image = imread(path2, IMREAD_COLOR);
    CommonProcesses cp2("plus",image);

    cp2.showImage();
    cp2.erosion().showImage();

    CommonProcesses cp3;
    cp3 = cp1 + cp2;
    cp3.showImage();
    cp3 = cp1 - cp2;
    cp3.showImage();

    cp3 = cp2 + 45;
    cp3.showImage();

    cp3 = cp2 - 20;
    cp3.showImage();

    cp3 = cp2 * 2;
    cp3.showImage();

    cp3 = cp2 / 3;
    cp3.showImage();

    LineDetection lD1("line_obj1", path);
    lD1.findLine();
    lD1.visualizeFeatures();
    lD1.putFeature();
    lD1.writeFeatures();
    lD1.visualizeFeatures_withTreackbar();
    
    CornerDetection cd1("corner_obj1", path);
    cd1.findCorners();
    cd1.visualizeFeatures();
    cd1.putFeature();
    cd1.writeFeatures();
    cd1.visualizeFeatures_withTreackbar();

    CommonProcesses cp_new;
    cin >> cp_new;
    cp_new.showImage();
    cout << cp_new;
}
