#include "MultiGameFrame.hpp"
#include "FrameFactory.hpp"

// void onMouse(int event, int x, int y, int, void*){
//     if (event == cv::EVENT_LBUTTONDOWN){
        
//         std::cout << "Lbutton down at x: " << x << " and y: " << y << std::endl;
//     }
// }

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
    // cv::setMouseCallback("Display Image", FrameFactory::onMouse, nullptr);
    cv::waitKey(0);
}

void MultiGameFrame::handleHit(double reactionTime) 
{
    MultiGameFrame::result = reactionTime;
}