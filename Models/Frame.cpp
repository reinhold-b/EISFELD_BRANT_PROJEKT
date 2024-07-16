#include <string>

#include "Frame.hpp"

auto Frame::getStart() const {
    return start;
}

std::string Frame::getImgPath() const {
    return m_imgPath;
}

std::vector<Label> Frame::getLabels() const {
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
    std::vector<Label> currLabels = m_labels;
    for (const auto& i : currLabels){
        std::cout << i.m_type << "  --  " << i.m_frame << "  --  "  << std::endl;
        std::cout << i.m_bbox.x << " || " << i.m_bbox.y << " - " << i.m_bbox.width << " || " << i.m_bbox.height << std::endl;
        if (i.m_bbox.contains(p) && i.m_type != "DontCare") 
        {
            
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

    // 3 sek zurueckgeben wenn timeout
    return elapsed_time_ms != 0 ? elapsed_time_ms / 1000000 : 3000;
}
