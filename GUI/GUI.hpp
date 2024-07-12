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
    // Private members can be added here if needed

public:
    GUI();

    int renderImage(const std::string &path, const std::vector<Label> &labels); 
};

#endif // GUI_HPP
