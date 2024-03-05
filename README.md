# RGB Image-Processing-Application-with-CPP

This project is a C++ application for performing various operations on RGB images. The application utilizes the OpenCV library to perform image processing tasks.

## Architecture
The architecture of this project follows an object-oriented design where the `CommonProcesses` class serves as the base class, and the `Detection` class is derived from it. Both `LineDetection` 
and `CornerDetection` classes further inherit from the `Detection` class. This architecture allows for a modular and extensible design, where common image processing functionalities are defined 
in the `CommonProcesses` class, while specific detection tasks like edge and corner detection are implemented in the derived classes.

## Features

- **Image Loading and Display:** Load and visualize images using the `CommonProcesses` class.
- **Conversion to Grayscale:** Convert images to grayscale using the `RGB2Gray` method.
- **Noise Reduction:** Reduce noise in images using the `reduceNoise` method.
- **Image Rescaling:** Rescale images to desired dimensions using the `rescaleImage` method.
- **Histogram Visualization:** Visualize the histogram of images using the `visualizeHistogram` method.
- **Edge Detection:** Detect edges in images using the `LineDetection` class.
- **Corner Detection:** Detect corners in images using the `CornerDetection` class.
- **Mathematical Operations:** Perform basic mathematical operations (+, -, *, /) on images using the `CommonProcesses` class.

## Usage

1. **Image Processing:**
   
   ```cpp
   #include "CommonProcesses.h"
   #include <opencv2/opencv.hpp>
   using namespace cv;
   using namespace std;

   int main() {
       string path = "./sample.jpg";
       CommonProcesses cp("Sample", path);
       
       // Load and display the image
       cp.showImage();
       
       // Convert to grayscale and display
       cp.RGB2Gray().showImage();
       
       // Reduce noise and display
       cp.reduceNoise().showImage();
       
       // Rescale the image and display
       cp.rescaleImage(500, 100).showImage();
       
       // Compute histogram and visualize
       cp.visualizeHistogram();
       
       return 0;
   }
   ```

2. **Edge Detection:**
   
   ```cpp
   #include "LineDetection.h"
   #include <opencv2/opencv.hpp>
   using namespace cv;
   using namespace std;

   int main() {
       string path = "./sample.jpg";
       LineDetection ld("LineDetector", path);
       
       // Detect edges and visualize
       ld.findLine();
       ld.visualizeFeatures();
       
       // Add edges to the image
       ld.putFeature();
       
       // Write edges to a file
       ld.writeFeatures();
       
       // Visualize edges and adjust threshold value
       ld.visualizeFeatures_withTreackbar();
       
       return 0;
   }
   ```

3. **Corner Detection:**
   
   ```cpp
   #include "CornerDetection.h"
   #include <opencv2/opencv.hpp>
   using namespace cv;
   using namespace std;

   int main() {
       string path = "./sample.jpg";
       CornerDetection cd("CornerDetector", path);
       
       // Detect corners and visualize
       cd.findCorners();
       cd.visualizeFeatures();
       
       // Add corners to the image
       cd.putFeature();
       
       // Write corners to a file
       cd.writeFeatures();
       
       // Visualize corners and adjust threshold value
       cd.visualizeFeatures_withTreackbar();
       
       return 0;
   }
   ```
# Detailed Description

## Line Detection

Line detection is performed using the Hough Line Transform. The `LineDetection` class extends the `Detection` class and utilizes OpenCV's `HoughLinesP` function to detect lines in the image. After detecting the lines, the class provides methods to visualize the detected lines, adjust the threshold value for line detection, and write the detected lines to a file.

## Corner Detection

Corner detection is performed using the Harris Corner Detection algorithm. The `CornerDetection` class extends the `Detection` class and utilizes OpenCV's `cornerHarris` function to detect corners in the image. After detecting the corners, the class provides methods to visualize the detected corners, adjust the threshold value for corner detection, and write the detected corners to a file.

## Requirements

- C++ compiler
- OpenCV library
- Python3 for matplotlib.h code The code for matplotlib.h has not been written by me, but it is a pre-existing library code.
## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
