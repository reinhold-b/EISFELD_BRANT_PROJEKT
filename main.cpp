#include "./Menu/Class Files/menu.cpp"
#include "./GUI/Extractor.cpp"
#include "./GUI/GUI.cpp"

int main(){
    Menu gameMenu = Menu();
    int numImages = gameMenu.getImageCount();
    std::string seq = gameMenu.getImageSequence();

    Extractor e = Extractor(numImages, seq);
    std::vector<std::string> pathsToOpen = e.getImgPaths();

    GUI window = GUI();
    
    for (int i = 0; i < numImages; i++) {
        window.renderImage(pathsToOpen[i]);
    }

    return 0;
}