#include "FrameFactory.hpp"

#include <vector>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <string>
#include <random>
#include <filesystem>
#include <map>
#include <iostream>
#include <fstream>
#include "../GUI/Label.hpp"
#include "Frame.hpp"
#include "MultiGameFrame.hpp"
#include "SingleGameFrame.hpp"

/**
 * @brief Konstruiert aus der Nummer des Bildes,
 * das angezeigt werden soll, den Pfad zum Bild.
 *
 * @param loopIndex
 * @return std::string
 */
std::string FrameFactory::buildImageName(int loopIndex)
{
    std::string paddingZeros = "";
    std::string loopIndexStr = std::to_string(loopIndex);

    for (int i = 0; i < 6 - loopIndexStr.length(); i++)
    {
        paddingZeros += "0";
    }
    return m_imgPath + m_imgSeq + "/" + paddingZeros + loopIndexStr + ".png";
}

std::vector<Label> FrameFactory::loadLabelsFromFile(std::string filename)
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

/**
 * @brief Initialisiert die FrameFactory mit den gelesenen Labels.
 *
 * @return int
 */
int FrameFactory::open()
{
    // reading labels (GT Boxes) from KITTI Dataset
    std::string pathToLabelFile = m_labelPath + m_imgSeq + ".txt";
    m_labels = loadLabelsFromFile(pathToLabelFile);

    return 0;
}

/**
 * @brief Zählt die Anzahl der Dateien innerhalb des Ordners der Sequenz.
 *
 * @param path
 * @return int
 */
int FrameFactory::walkDir(std::string path)
{
    int file_count = 0;
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
    {
        // Iterate through the directory
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            // Check if the entry is a regular file
            if (std::filesystem::is_regular_file(entry))
            {
                ++file_count;
            }
        }
    }
    else
    {
        std::cerr << "Path does not exist or is not a directory." << std::endl;
        return -1;
    }
    m_imgCount = file_count;
    return 0;
}

FrameFactory::FrameFactory()
{
    open();
}
FrameFactory::FrameFactory(std::string imgSeq) : m_imgSeq(imgSeq)
{
    open();
    walkDir(m_imgPath + m_imgSeq + "/");
}

/**
 * @brief Lädt die Labels zu dem Bild, was gespielt wird.
 *
 * @param i
 * @return std::vector<Label>
 */
std::vector<Label> FrameFactory::getImgLabel(int i)
{
    std::vector<Label> labelsTToReturn;
    for (auto &l : m_labels)
    {
        if (l.m_frame == i && l.m_type != "DontCare")
            labelsTToReturn.push_back(l);
    }
    return labelsTToReturn;
}

/**
 * @brief "Fabriziert" ein neues Frame. Das Frame wird mit den nötigen Startwerten
 * wie Bildpfad, Labels intialisiert. Je nachdem, was für ein Spielmodus gespielt wird, wird
 * ein entsprechendes Frame returnt.
 *
 * @param mode
 * @return Frame*
 */
Frame *FrameFactory::take(GameMode mode)
{
    std::random_device rd;
    std::vector<std::string> paths;
    std::srand(rd()); // use current time as seed for random generator
    int random_value;

    random_value = std::rand() % m_imgCount;
    std::string imgPath = buildImageName(random_value);

    std::vector<Label> labelsToReturn = getImgLabel(random_value);

    if (labelsToReturn.empty())
    {
        return FrameFactory::take(mode);
    }

    if (mode == GameMode::singular)
    {
        Frame *res = new SingleGameFrame(imgPath, labelsToReturn);
        return res;
    }
    else
    {
        Frame *res = new MultiGameFrame(imgPath, labelsToReturn);
        return res;
    }
}