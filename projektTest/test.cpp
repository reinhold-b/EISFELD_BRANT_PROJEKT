#include "gtest/gtest.h"
#include "../GUI/Label.hpp"
#include "../Models/Frame.hpp"
#include "../Menu/Class Files/menu.hpp"
#include "../Models/FrameFactory.hpp"
#include <vector>
#include <sstream>
#ifdef __APPLE__
#define APPLE true
#else
#define APPLE false
#endif

class ProjektTest : public ::testing::Test
{
protected:
    Frame frame;
    ProjektTest()
        : frame("", std::vector<Label>()) // Use default values or adjust as needed
    {
        // Optionally, you can use the SetUp method to modify the frame
        SetUp();
    }

    void SetUp() override
    {
        cv::Rect testBox(100, 100, 100, 100);
        Label testLabel = {0, "Car", testBox};
        std::vector<Label> testLabels;
        testLabels.push_back(testLabel);
        frame = Frame("", testLabels);
    }
};
TEST_F(ProjektTest, normalPointHits)
{
    cv::Point p = cv::Point(150, 150);
    EXPECT_TRUE(frame.checkForHit(p));
}

TEST_F(ProjektTest, negativePointDoesNotHit)
{
    cv::Point p = cv::Point(-1, -1);
    EXPECT_TRUE(!frame.checkForHit(p));
}

TEST_F(ProjektTest, pointOnCornerDoesHit)
{
    cv::Point p = cv::Point(100, 100);
    EXPECT_TRUE(frame.checkForHit(p));
}

TEST_F(ProjektTest, pointOnOtherCornerDoesHit)
{
    cv::Point p = cv::Point(199, 199);
    EXPECT_TRUE(frame.checkForHit(p));
}

TEST_F(ProjektTest, ValidateGamemodeCorrectly)
{
    /*since the readValidGamemode method will be stuck in a loop if all the inputs in secondOriginalCin are wrong, the test won't finish
     * if all the inputs are incorrect. Otherwise, the test will always pass.
     */
    std::istringstream input("TestPlayer\n5\n0001\n2");
    std::streambuf *originalCin = std::cin.rdbuf(input.rdbuf()); // Redirect std::cin
    Menu menu;
    std::cin.rdbuf(originalCin);

    std::istringstream secondInput("3\n2");
    std::streambuf *secondOriginalCin = std::cin.rdbuf(secondInput.rdbuf()); // Redirect std::cin
    EXPECT_EQ(2, menu.readValidGamemode());

    std::cin.rdbuf(secondOriginalCin);
}

TEST_F(ProjektTest, ValidateImagesequenceCorrectly)
{
    /*since the readValidImageSequence method will be stuck in a loop if all the inputs in secondOriginalCin are wrong, the test won't finish
     * if all the inputs are incorrect. Otherwise, the test will always pass.
     */
    std::istringstream input("TestPlayer\n5\n0001\n2");
    std::streambuf *originalCin = std::cin.rdbuf(input.rdbuf()); // Redirect std::cin
    Menu menu;
    std::cin.rdbuf(originalCin);

    std::istringstream secondInput("0023\n023\ntest\n0010");
    std::streambuf *secondOriginalCin = std::cin.rdbuf(secondInput.rdbuf()); // Redirect std::cin
    EXPECT_EQ("0010", menu.readValidImageSequence());

    std::cin.rdbuf(secondOriginalCin);
}

TEST_F(ProjektTest, buildImageCorrectly)
{
    string testImageSequence = "0001";
    int testLoopindex = 1;
    string testLoopindexStr = std::to_string(testLoopindex);
    FrameFactory Ffact = FrameFactory(testImageSequence);
    const std::string testImgPath = APPLE ? "./data_tracking_image_2/training/image_02/" : "../data_tracking_image_2/training/image_02/";
    EXPECT_EQ(testImgPath + testImageSequence + "/00000" + testLoopindexStr + ".png", Ffact.buildImageName(testLoopindex));
}
