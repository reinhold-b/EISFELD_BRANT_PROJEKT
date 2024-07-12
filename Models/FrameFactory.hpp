#ifndef FACTORY_INCLUDED
#define FACTORY_INCLUDED

#include "Frame.hpp"

#include <vector>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <string>
#include <filesystem>
#include <map>
#include <iostream>
#include <fstream>
#include "../GUI/Label.hpp"  // Assuming you have a Label.hpp file#
#ifdef __APPLE__
#define APPLE true 
#endif


class FrameFactory {
    int m_imgCount = 1;
    std::string m_imgSeq;
    std::string m_labelPath = APPLE ? "./training/label_02/" : "";
    std::string m_imgPath = "./data_tracking_image_2/training/image_02/";

    std::vector<Label> m_labels;
    std::vector<int> m_labelIndices; 

    std::string buildImageName(int loopIndex);
    std::vector<Label> loadLabelsFromFile(std::string filename);
    int open();
    int walkDir(std::string path);

public:
    FrameFactory();
    FrameFactory(std::string imgSeq);
    std::vector<std::string> getImgPaths();
    std::vector<Label> getImgLabel(int i);
    std::vector<int> getLabelIndices();
    Frame* take(GameMode mode);
};

#endif //FACTORY_INCLUDED