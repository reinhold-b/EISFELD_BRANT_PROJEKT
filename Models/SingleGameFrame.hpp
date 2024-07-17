#ifndef SINGLE_INCLUDED
#define SINGLE_INCLUDED

#include "Frame.hpp"

class SingleGameFrame : public Frame
{
public:
    SingleGameFrame(std::string _path, std::vector<Label> _labels) : Frame(_path, _labels){};
    void show() override;
    void handleHit(double reactionTime) override;
};

#endif // SINGLE_INCLUDED