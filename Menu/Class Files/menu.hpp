#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED
#include <iostream>
using namespace std;

class Menu{
private:
    string m_playerName;
    int m_imageCount;
    string m_imageSequence;
public:
    Menu(string _playerName, int _imageCount, string _imageSequence):
    m_playerName(_playerName),
    m_imageCount(_imageCount),
    m_imageSequence(_imageSequence){};
    Menu(); //this method contains the GUI text

    string getPlayerName();
    int getImageCount();
    string getImageSequence();

    void setPlayerName(string newPlayerName);
    void setImageCount(int newImageCount);
    void setImageSequence(int newImageSequence);

    ~Menu(){};
};

#endif