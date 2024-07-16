#ifndef MULTI_INCLUDED
#define MULTI_INCLUDED

#include "Frame.hpp"

class MultiGameFrame : public Frame {
    private:
        int correctBoxIndex;
    public:
    MultiGameFrame(std::string _path, std::vector<Label> _labels) : Frame(_path, _labels) {
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        correctBoxIndex = std::rand() % _labels.size();
    };
    int getCorrectBoxIndex() const {
        return correctBoxIndex;
    }
    void show() override;
    void handleHit(double reactionTime) override;
    bool checkForHit(cv::Point p) override;
};

#endif // MULTI_INCLUDED