#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

class GUI {
    private:  

    public:
        GUI() {};
        
        int renderImage(std::string path) {
        cv::Mat image; 
        image = cv::imread(path);
        if (image.empty()) {
            std::cerr << "Error: Could not open or find the image!" << std::endl;
            return -1;
        }
        cv::imshow("Display Image", image);
        cv::waitKey(0);
        return 0;
        }
};