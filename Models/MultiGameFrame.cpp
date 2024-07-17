#include "MultiGameFrame.hpp"
#include "FrameFactory.hpp"

#include <chrono>


/**
 * @brief 
 * 
 */
void MultiGameFrame::show() {
    std::vector<Label> labels = MultiGameFrame::getLabels();
    cv::Mat image; 
    image = cv::imread(MultiGameFrame::getImgPath());

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
    }

    const int thickness = 2; 

    for (auto &l : Frame::getLabels()) {
        drawBox(image, l.m_bbox, thickness, cv::Scalar(255, 0, 0));
    }
 
   // Drawing the Rectangle 
    cv::imshow("Display Image", image);

    waitForInput(3000, [](){return true;}, [](){});

    setStart();
    drawBox(image, labels[getCorrectBoxIndex()].m_bbox, thickness + 2, cv::Scalar(0, 0, 255));

    cv::imshow("Display Image", image);
        
    waitForInput(3000, [this](){return this->result == 0;}, [this]() {
        std::cout << "timeout" << std::endl;
        this->result = 5000;
    });

}

/**
 * @brief  
 * 
 * @param p 
 * @return true 
 * @return false 
 */
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