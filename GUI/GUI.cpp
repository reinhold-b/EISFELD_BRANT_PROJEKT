#ifndef GUI_CPP
#define GUI_CPP
#include "Label.hpp" 
#include "GUI.hpp"

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc.hpp> 
  
#include <opencv2/highgui/highgui.hpp> 


        GUI::GUI() {};
        
        int GUI::renderImage(const std::string &path, const std::vector<Label> &labels) {
            cv::Mat image; 
            image = cv::imread(path);
            if (image.empty()) {
                std::cerr << "Error: Could not open or find the image!" << std::endl;
                return -1;
            }

            int thickness = 2; 

            for (auto &l : labels) {
                rectangle(image, l.m_bbox, 
                cv::Scalar(255, 0, 0), 
                thickness, cv::LINE_8);
 
            }
            // Drawing the Rectangle 
            cv::imshow("Display Image", image);
            cv::waitKey(0);
            return 0;
            }
#endif //GUI_CPP