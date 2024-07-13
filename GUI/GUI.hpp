#ifndef GUI_HPP
#define GUI_HPP

#include "Label.hpp"  // Include the header file for the Label class
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class GUI {
private:
    struct Point
    {
        int x;
        int y;
    };
    Point cursorInfo;

public:
    GUI();
    int renderImage(const std::string &path, const std::vector<Label> &labels);
    void setCursorPos(Point p);
};

#endif // GUI_HPP
