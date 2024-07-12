#ifndef LABEL_INCLUDED
#define LABEL_INCLUDED

#include <string>
#include <opencv2/opencv.hpp>

class Label
{
public:
    Label();
    Label(int frame, const std::string &type, const cv::Rect &bbox);

    int m_frame;            // Frame number where the bounding box corresponds to
    std::string m_type;     // Class of the bounding box (e.g., Pedestrian, Car, Cyclist) --> DontCare should be ignored
    cv::Rect m_bbox;        // Bounding box
};

#endif // LABEL_INCLUDED
