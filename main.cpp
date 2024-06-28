#include "./Menu/Class Files/menu.cpp"
#include "./GUI/Extractor.cpp"

int main(){
    Menu gameMenu = Menu();
    int numImages = gameMenu.getImageCount();
    std::string seq = gameMenu.getImageSequence();
    Extractor e = Extractor(numImages, seq);
    e.open();
    return 0;
}