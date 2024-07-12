#include "./Menu/Class Files/menu.hpp"
#include "./GUI/Extractor.hpp"
#include "./GUI/GUI.hpp"
#include "./Models/FrameFactory.hpp"
#include "./Models/Frame.hpp"

#include <map>
#include <filesystem>

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

    for (int i = 0; i < numImages; i++) {
        Frame* frame = fac.take(gamemode);
        (*frame).show();
    }

    return 0;
}