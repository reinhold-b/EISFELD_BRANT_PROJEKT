#include "./Menu/Class Files/menu.hpp"
#include "./GUI/Extractor.hpp"
#include "./GUI/GUI.hpp"

#include <map>
#include <filesystem>

int main(){
    Menu gameMenu = Menu();
    int numImages = gameMenu.getImageCount();
    int gamemode = gameMenu.getGamemode(); 
    std::string seq = gameMenu.getImageSequence();

    Extractor e = Extractor(numImages, seq);
    std::vector<std::string> pathsToOpen = e.getImgPaths();
    std::vector<int> labelIndices = e.getLabelIndices();
    std::vector<Label> labels; 

    GUI window = GUI();
    for (int i = 0; i < numImages; i++) {
        labels = e.getImgLabel(labelIndices[i]);
        if (labels.empty()) {
            std::cout << "Keien BBs" << std::endl;
            continue;
        }
        window.renderImage(pathsToOpen[i], labels);
    }

    return 0;
}