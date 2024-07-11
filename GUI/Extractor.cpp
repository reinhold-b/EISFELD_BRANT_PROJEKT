#ifndef EXTRACTOR_CPP
#define EXTRACTOR_CPP
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <string>
#include <filesystem>
#include <map>

#include "Label.cpp"






class Extractor
{
    private:
        int m_imgCount = 1;
        std::string m_imgSeq;
        std::string m_labelPath = "./training/label_02/";
        std::string m_imgPath = "./data_tracking_image_2/training/image_02/";

        std::vector<Label> m_labels;
        std::vector<int> m_labelIndices; 

        std::string buildImageName(int loopIndex) {
            std::string paddingZeros = "";
            std::string loopIndexStr = std::to_string(loopIndex);

            for (int i = 0; i < 6 - loopIndexStr.length(); i++) {
                paddingZeros += "0";
            }
            return m_imgPath + m_imgSeq + "/" + paddingZeros + loopIndexStr + ".png";  
        }

std::vector<Label> loadLabelsFromFile(std::string filename)
{
    std::vector<Label> labels;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open label file: " << filename << std::endl;
        return labels;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        int frame, track_id, truncated, occluded;
        float alpha, bbox_left, bbox_top, bbox_right, bbox_bottom;
        float height, width, length;
        float loc_x, loc_y, loc_z, rot_y;
        std::string type;

        ss >> frame >> track_id >> type >> truncated >> occluded >> alpha >> bbox_left >> bbox_top >> bbox_right >> bbox_bottom >> height >> width >> length >> loc_x >> loc_y >> loc_z >> rot_y;

        if (!ss.fail())
        {
            cv::Rect bbox(static_cast<int>(bbox_left), static_cast<int>(bbox_top),
                            static_cast<int>(bbox_right - bbox_left), static_cast<int>(bbox_bottom - bbox_top));
            labels.emplace_back(frame, type, bbox);
        }
        else
        {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }
    return labels;
}

        int open() {
    //reading labels (GT Boxes) from KITTI Dataset
    std::cout << "Error: Could not open or find the image!" << std::endl;
    std::string pathToLabelFile = m_labelPath + m_imgSeq + ".txt"; 
    m_labels = loadLabelsFromFile(pathToLabelFile);
    std::cout << "numberOfLabels: " << m_labels.size() << std::endl;

    return 0;
    }

    int walkDir(std::string path) {
        int file_count = 0;
        if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        // Iterate through the directory
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            // Check if the entry is a regular file
            if (std::filesystem::is_regular_file(entry)) {
                ++file_count;
            }
        }
    } else {
        std::cerr << "Path does not exist or is not a directory." << std::endl;
        return -1;
    }
    m_imgCount = file_count;
    return 0;
    }

    public:
    Extractor(){
        open();
    }
    Extractor(int imgCount, std::string imgSeq) : m_imgCount(imgCount), m_imgSeq(imgSeq) {
        open();
        walkDir(m_imgPath + m_imgSeq + "/");
    }

    //Get current timestamp
    // auto now = std::chrono::system_clock::now();
    // std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    // std::cout << "Current time: " << std::ctime(&now_time_t) << std::endl;

    std::vector<std::string> getImgPaths() {
        std::vector<std::string> paths; 
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        int random_value; 
        for (int i = 0; i < m_imgCount; i++) {
            random_value = std::rand() % m_imgCount;
            paths.push_back(buildImageName(random_value));
            m_labelIndices.push_back(random_value);
        }
        return paths;
    }

    std::vector<Label> getImgLabel(int i) {
        std::vector<Label> labelsTToReturn;
        for (auto &l : m_labels) 
        {
            if (l.m_frame == i && l.m_type != "DontCare") labelsTToReturn.push_back(l);
        }
        return labelsTToReturn;
    }

    std::vector<int> getLabelIndices() {
        return m_labelIndices;
    }
};

#endif //EXTRACTOR_CPP