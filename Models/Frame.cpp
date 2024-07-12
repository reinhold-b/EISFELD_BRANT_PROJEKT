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