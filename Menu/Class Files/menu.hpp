#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED
#include <iostream>
using namespace std;

class Menu{
private:
    string m_playerName;
    int m_imageCount;
    int m_gamemode;
    string m_imageSequence;
    string getValidName();
    int getValidImageCount();
    int getValidGamemode();
    string getValidImageSequence();
public:
    Menu(string _playerName, int _imageCount, string _imageSequence, int _gamemode):
    m_playerName(_playerName),
    m_imageCount(_imageCount),
    m_imageSequence(_imageSequence),
    m_gamemode(_gamemode) {};
    Menu(); //this method contains the GUI text

    string getPlayerName();
    int getImageCount();
    string getImageSequence();
    int getGamemode();

    void setPlayerName(string newPlayerName);
    void setImageCount(int newImageCount);
    void setImageSequence(int newImageSequence);

    ~Menu(){};
};

#endif  //MENU_HPP_INCLUDED