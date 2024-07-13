#include "SingleGameFrame.hpp"
#include "../GUI/Label.hpp"

#include <vector>
#include <string>

void SingleGameFrame::show() {
            std::vector<Label> labels = SingleGameFrame::getLabels();
            std::vector<std::string> paths; 

            std::srand(std::time(nullptr)); // use current time as seed for random generator
            int random_value; 
            random_value = std::rand() % labels.size();
 
                cv::Mat image; 
            image = cv::imread(SingleGameFrame::getImgPath());
            if (image.empty()) {
                std::cerr << "Error: Could not open or find the image!" << std::endl;
            }

            int thickness = 2; 

            rectangle(image, labels[random_value].m_bbox, 
            cv::Scalar(255, 0, 0), 
            thickness, cv::LINE_8);

            // Drawing the Rectangle 
            cv::imshow("Display Image", image);
            cv::waitKey(0);
}