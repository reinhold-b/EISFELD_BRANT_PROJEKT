#include <string>

#include "Frame.hpp"

std::string Frame::getImgPath() {
    return m_imgPath;
}

std::vector<Label> Frame::getLabels() {
    return m_labels;
}

void Frame::show() {
    return;
}

void Frame::handleHit(double reactionTime) {
    return;
}

bool Frame::checkForHit(cv::Point p)
{
    for (const auto& i : m_labels){
        if (i.m_bbox.contains(p) && i.m_type != "DontCare") 
        {
            std::cout << i.m_bbox.x << " || " << i.m_bbox.y << " - " << i.m_bbox.width << " || " << i.m_bbox.height << std::endl;
            return true;
        }
        
    }
    return false;
}



double Frame::calcReactionTime() {
    //Get current timestamp
    auto now = std::chrono::steady_clock::now();

    double elapsed_time_ms = std::chrono::steady_clock::duration(now - start).count();

    std::cout << elapsed_time_ms / 1000000 << "ms" << std::endl;
    return elapsed_time_ms / 1000000;
}
