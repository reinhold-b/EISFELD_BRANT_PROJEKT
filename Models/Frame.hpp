#ifndef FRAME_INCLUDED
#define FRAME_INCLUDED

#include <string>
#include <vector>

#include "Label.hpp"

enum GameMode {singular, allAtOnce};

class Frame {
    private:
        std::string m_imgPath; 
        std::vector<Label> m_labels; 
        GameMode mode; 
    public:
        Frame(std::string _path, std::vector<Label> _labels) :
            m_imgPath(_path),
            m_labels(_labels),
            mode(GameMode::singular) {};

        Frame(std::string _path, std::vector<Label> _labels, GameMode mode) :
            m_imgPath(_path),
            m_labels(_labels),
            mode(mode) {};

        std::string getImgPath();
        std::vector<Label> getLabels();
        virtual void show();
};

#endif //FRAME_INCLUDED