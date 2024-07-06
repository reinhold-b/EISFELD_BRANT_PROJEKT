#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <string>


class Label
{
public:
    Label() : m_frame(0), m_type(""), m_bbox(cv::Rect()) {}
    Label(int frame, const std::string &type, const cv::Rect &bbox)
        : m_frame(frame), m_type(type), m_bbox(bbox) {}

    int m_frame;            //Frame number, where the bounding box corresponds to
    std::string m_type;     //Class of the bounding box (e.g. Pedestrian, Car, Cyclist) --> DontCare should be ignored
    cv::Rect m_bbox;
};

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


class Extractor
{
    private:
        int m_imgCount = 1;
        std::string m_imgSeq;
        std::string m_labelPath = "./training/label_02/";
        std::string m_imgPath = "./data_tracking_image_2/training/image_02/";

        std::vector<Label> m_labels;

        std::string buildImageName(int loopIndex) {
            std::string paddingZeros = "";
            std::string loopIndexStr = std::to_string(loopIndex);

            for (int i = 0; i < 6 - loopIndexStr.length(); i++) {
                paddingZeros += "0";
            }
            return m_imgPath + m_imgSeq + "/" + paddingZeros + loopIndexStr + ".png";  
        }

        int open() {
    //reading labels (GT Boxes) from KITTI Dataset
    std::cout << "Error: Could not open or find the image!" << std::endl;
    std::string pathToLabelFile = m_labelPath + m_imgSeq + ".txt"; 
    m_labels = loadLabelsFromFile(pathToLabelFile);
    std::cout << "numberOfLabels: " << m_labels.size() << std::endl;
    for (const auto& label : m_labels) { //print class of all elements from frame number 5
        if (label.m_frame == 5) {
            std::cout << "Type: " << label.m_type << std::endl;
        }
    }
    return 0;
    }

    public:
    Extractor(){
        open();
    }
    Extractor(int imgCount, std::string imgSeq) : m_imgCount(imgCount), m_imgSeq(imgSeq) {
        open();
    }

    //Get current timestamp
    // auto now = std::chrono::system_clock::now();
    // std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    // std::cout << "Current time: " << std::ctime(&now_time_t) << std::endl;

    std::vector<std::string> getImgPaths() {
        std::vector<std::string> paths; 
        for (int i = 0; i < m_imgCount; i++) {
            paths.push_back(buildImageName(i));
        }
        return paths;
    }
};
