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
    string readValidName();
    int readValidImageCount();
    int readValidGamemode();
    string readValidImageSequence();
    friend class ProjektTest_ValidateGamemodeCorrectly_Test;
    friend class ProjektTest_ValidateImagesequenceCorrectly_Test;
public:
    Menu(string _playerName, int _imageCount, string _imageSequence, int _gamemode):
    m_playerName(_playerName),
    m_imageCount(_imageCount),
    m_imageSequence(_imageSequence),
    m_gamemode(_gamemode) {};
    Menu(); //this method contains the GUI text

    string getPlayerName() const;
    int getImageCount() const;
    string getImageSequence() const;
    int getGamemode() const;

    void setPlayerName(string newPlayerName);
    void setImageCount(int newImageCount);
    void setImageSequence(int newImageSequence);

    ~Menu(){};
};

#endif  //MENU_HPP_INCLUDED