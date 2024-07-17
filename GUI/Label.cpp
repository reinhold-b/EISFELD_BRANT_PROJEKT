#include <string>
#include <opencv2/opencv.hpp>
#include "Label.hpp"

Label::Label() : m_frame(0), m_type(""), m_bbox(cv::Rect()) {}
Label::Label(int frame, const std::string &type, const cv::Rect &bbox)
    : m_frame(frame), m_type(type), m_bbox(bbox) {}