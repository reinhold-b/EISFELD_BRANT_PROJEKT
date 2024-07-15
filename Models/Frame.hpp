#ifndef FRAME_INCLUDED
#define FRAME_INCLUDED

#include <string>
#include <vector>
#include <chrono>

#include "../GUI/Label.hpp"

enum GameMode {singular, allAtOnce};

class Frame {
    private:
        std::string m_imgPath; 
        std::vector<Label> m_labels; 
        GameMode mode; 
        std::chrono::steady_clock::time_point start;

    public:
        double result;

        void setStart() {
            //Get current timestamp
            start = std::chrono::steady_clock::now();
        } 

        auto getStart() {
            return start;
        }

        Frame(std::string _path, std::vector<Label> _labels) :
            m_imgPath(_path),
            m_labels(_labels),
            mode(GameMode::singular) {
                std::cout << std::endl << "Created: " << this << std::endl;
                setStart();
                calcReactionTime();
           };

        Frame(std::string _path, std::vector<Label> _labels, GameMode mode) :
            m_imgPath(_path),
            m_labels(_labels),
            mode(mode) {
                std::cout << this << std::endl;
                setStart();
                calcReactionTime();
            };

        std::string getImgPath();
        std::vector<Label> getLabels();
        virtual void handleHit(double reactionTime);
        virtual bool checkForHit(cv::Point p);
        virtual void show();
        double calcReactionTime();
};

#endif //FRAME_INCLUDED