#ifndef MULTI_INCLUDED
#define MULTI_INCLUDED

#include "Frame.hpp"

class MultiGameFrame : public Frame {
    public:
    MultiGameFrame(std::string _path, std::vector<Label> _labels) : Frame(_path, _labels) {};
    void show() override;
};

#endif // MULTI_INCLUDED