#include "MultiGameFrame.hpp"
#include "FrameFactory.hpp"

#include <chrono>


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

    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);

        cv::waitKey(10);
        if (elapsed.count() >= 3000) {
            break;
        }
    }
    cv::waitKey(0);
}

void MultiGameFrame::handleHit(double reactionTime) 
{
    MultiGameFrame::result = reactionTime;
}