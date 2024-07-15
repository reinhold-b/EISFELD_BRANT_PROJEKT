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

void Frame::onMouse(int event, int x, int y, int, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        Frame* self = static_cast<Frame*>(userdata);
        if (self->checkForHit(cv::Point(x, y)))
        {
            std::cout << "Hit!" << std::endl;
        }
        else
        {
            std::cout << "Miss!" << std::endl;
        }   
        std::cout << "Lbutton down at x: " << x << " and y: " << y << std::endl;
    }
}
