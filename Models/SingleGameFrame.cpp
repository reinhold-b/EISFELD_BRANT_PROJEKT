#include "SingleGameFrame.hpp"
#include "FrameFactory.hpp"
#include "../GUI/Label.hpp"

#include <vector>
#include <string>
#include <chrono>



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
    cv::Scalar(0, 0, 255), 
    thickness, cv::LINE_8);

    // Drawing the Rectangle 
    cv::imshow("Display Image", image);

    auto begin = std::chrono::high_resolution_clock::now();

    while (result == 0 ) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin); 
        if (elapsed.count() >= 3000) {
            std::cout << "timeout" << std::endl;
            break;
        }
        cv::waitKey(10);
    } 
}

void SingleGameFrame::handleHit(double reactionTime) 
{
    SingleGameFrame::result = reactionTime;
}