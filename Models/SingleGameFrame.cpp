#include "SingleGameFrame.hpp"
#include "FrameFactory.hpp"
#include "../GUI/Label.hpp"
#include "../helper.hpp"

#include <vector>
#include <string>
#include <chrono>

void SingleGameFrame::show()
{
    std::vector<Label> labels = SingleGameFrame::getLabels();
    std::vector<std::string> paths;

    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int random_value;
    random_value = std::rand() % labels.size();

    cv::Mat image;
    image = cv::imread(SingleGameFrame::getImgPath());
    if (image.empty())
    {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
    }

    const int thickness = 2;

    drawBox(image, labels[random_value].m_bbox, thickness, cv::Scalar(0, 0, 255));

    // Drawing the Rectangle
    cv::imshow("Display Image", image);

    cv::setMouseCallback("Display Image", helper::onMouse, this);
    waitForInput(3000, [this]()
                 { return this->result == 0; }, [this]()
                 {
            std::cout << "timeout" << std::endl;
            this->result = 5000; });
}

void SingleGameFrame::handleHit(double reactionTime)
{
    SingleGameFrame::result = reactionTime;
}