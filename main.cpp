#include "./Menu/Class Files/menu.cpp"
#include "./GUI/Extractor.cpp"
#include "./GUI/GUI.cpp"

int main(){
    Menu gameMenu = Menu();
    int numImages = gameMenu.getImageCount();
    std::string seq = gameMenu.getImageSequence();

    Extractor e = Extractor(numImages, seq);
    std::vector<std::string> pathsToOpen = e.getImgPaths();
    std::vector<Label> labels; 

    GUI window = GUI();
    
    for (int i = 0; i < numImages; i++) {
        labels = e.getImgLabel(i);
        if (labels.empty()) {
            std::cout << "Keien BBs" << std::endl;
            continue;
        }
        window.renderImage(pathsToOpen[i], labels);
    }

    return 0;
}