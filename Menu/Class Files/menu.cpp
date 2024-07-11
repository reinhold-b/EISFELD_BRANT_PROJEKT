#ifndef MENU_CPP
#define MENU_CPP
#include "menu.hpp"
#include <iostream>

using namespace std;

Menu::Menu(){
    cout << "********************* KITTI Reaction Game *********************" << endl <<
            "************* by Reinhold Brant and Albert Eisfeld ************" << endl << endl <<
            "Player Name: ";
    cin >> m_playerName;
    cout << "How many images do you want to play? ";
    cin >> m_imageCount;
    cout << "Which imagesequence do you chose? ";
    cin >> m_imageSequence;

    cout << m_playerName << endl << m_imageCount << endl << m_imageSequence; //For Testing


}

string Menu::getPlayerName(){
    return m_playerName;
};
int Menu::getImageCount(){
    return m_imageCount;
};
string Menu::getImageSequence(){
    return m_imageSequence;
};

void Menu::setPlayerName(string newPlayerName){
    m_playerName = newPlayerName;
}
void Menu::setImageCount(int newImageCount){
    m_imageCount = newImageCount;
}
void Menu::setImageSequence(int newImageSequence){
    m_imageSequence = newImageSequence;
}

#endif //MENU_CPP