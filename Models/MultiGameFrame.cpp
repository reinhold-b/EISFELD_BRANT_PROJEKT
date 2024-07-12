#include "MultiGameFrame.hpp"

void MultiGameFrame::show() {
            cv::Mat image; 
            image = cv::imread(MultiGameFrame::getImgPath());
            if (image.empty()) {
                std::cerr << "Error: Could not open or find the image!" << std::endl;
            }

            int thickness = 2; 

            for (auto &l : MultiGameFrame::getLabels()) {
                rectangle(image, l.m_bbox, 
                cv::Scalar(255, 0, 0), 
                thickness, cv::LINE_8);
 
            }
            // Drawing the Rectangle 
            cv::imshow("Display Image", image);
            cv::waitKey(0);
}