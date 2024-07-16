#include "./Menu/Class Files/menu.hpp"
#include "./Models/FrameFactory.hpp"
#include "./Models/Frame.hpp"

#include <map>
#include <filesystem>


void onMouse(int event, int x, int y, int flags, void* userdata)
{
    Frame* self = static_cast<Frame*>(userdata);
    // Wenn ein Ergebnis vorliegt (bereits geclickt), dann wird der Click nicht mehr registriert
    if (self->result != 0) return;
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        std::cout << "Lbutton down at x: " << x << " and y: " << y << std::endl;
        if (self->checkForHit(cv::Point(x, y)))
        {
            std::cout << std::endl << "Hit on: " << self << std::endl;
            double r = self->calcReactionTime();
            self->handleHit(r);
        }
        else
        {
            // 5 sek strafzeit
            self->handleHit(5000);
            std::cout << "Miss!" << std::endl;
        }   
    }
}


int main(){
    Menu gameMenu = Menu();
    int numImages = gameMenu.getImageCount();
    GameMode gamemode;
    if (gameMenu.getGamemode() == 1) {
        gamemode = GameMode::singular;
    } else {
        gamemode = GameMode::allAtOnce;
    } 

    std::string seq = gameMenu.getImageSequence();

    FrameFactory fac = FrameFactory(seq);

    // Extractor e = Extractor(numImages, seq);
    // std::vector<std::string> pathsToOpen = e.getImgPaths();
    // std::vector<int> labelIndices = e.getLabelIndices();
    // std::vector<Label> labels; 

    // GUI window = GUI();

    std::vector<double> times;

    cv::imshow("Display Image", 0);

    Frame* frame; 
    for (int i = 0; i < numImages; i++) {
        frame = fac.take(gamemode);
        cv::setMouseCallback("Display Image", onMouse, frame);
        (*frame).show();
        std::cout << "Reaction Time: " << (*frame).result << std::endl;
        times.push_back(frame->result);
    }

    double avg = 0;
    for (double &d : times) {
        avg += d;
    }
    avg /= times.size();
    std::cout << "Durchschnitt: " << avg << std::endl;

    return 0;
}