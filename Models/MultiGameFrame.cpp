#include "MultiGameFrame.hpp"
#include "FrameFactory.hpp"

#include <chrono>


void MultiGameFrame::show() {
    std::vector<Label> labels = MultiGameFrame::getLabels();
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

    auto begin = std::chrono::high_resolution_clock::now();
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);

        cv::waitKey(10);
        if (elapsed.count() >= 3000) {
            break;
        }
    }

    setStart();
    rectangle(image, labels[getCorrectBoxIndex()].m_bbox, 
    cv::Scalar(0, 0, 255), 
    thickness + 2, cv::LINE_8);

    cv::imshow("Display Image", image);
        
    begin = std::chrono::high_resolution_clock::now();

    while (result == 0 ) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin); 
        if (elapsed.count() >= 3000) {
            std::cout << "timeout" << std::endl;
            result = 3000;
            break;
        }
        cv::waitKey(10);
    } 

}

bool MultiGameFrame::checkForHit(cv::Point p) {
    std::vector<Label> currLabels = getLabels();
    Label correctLabel = currLabels[correctBoxIndex];
    if (correctLabel.m_bbox.contains(p) && correctLabel.m_type != "DontCare") 
    {
        return true;
    }
    return false;
}

void MultiGameFrame::handleHit(double reactionTime) 
{
    auto begin = std::chrono::high_resolution_clock::now();
    MultiGameFrame::result = reactionTime;

    cv::waitKey(0);

    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);

    MultiGameFrame::result += elapsed.count();

    if (result > 5000) result = 5000;

    std::cout << MultiGameFrame::result << std::endl;

}