#ifndef MENU_CPP
#define MENU_CPP
#include "menu.hpp"
#include <iostream>

using namespace std;

Menu::Menu()
{
    cout << "********************* KITTI Reaction Game *********************" << endl <<
            "************* by Reinhold Brant and Albert Eisfeld ************" << endl << endl <<
            "Player Name: ";
    m_playerName = getValidName();
    cout << "How many images do you want to play? ";
    m_imageCount = getValidImageCount();
    cout << "Which imagesequence do you chose? ";
    m_imageSequence = getValidImageSequence();
    cout << "Which gamemode? (1: single, 2: multi) ";
    m_gamemode = getValidGamemode();

    cout << m_playerName << endl << m_imageCount << endl << m_imageSequence << endl; //For Testing
}

string Menu::getPlayerName()
{
    return m_playerName;
};
int Menu::getImageCount()
{
    return m_imageCount;
};
string Menu::getImageSequence()
{
    return m_imageSequence;
};

int Menu::getGamemode() 
{
    return m_gamemode;
}

void Menu::setPlayerName(string newPlayerName)
{
    m_playerName = newPlayerName;
}
void Menu::setImageCount(int newImageCount)
{
    m_imageCount = newImageCount;
}
void Menu::setImageSequence(int newImageSequence)
{
    m_imageSequence = newImageSequence;
}

string Menu::getValidName()
{
    string newName;
    std::cin >> newName;
    
        while(std::cin.fail()) //checks for weird ASCIIs
        {
            std::cin.clear(); // Clear the error flags
            std::cout << "Invalid name! Make sure your Playername doesn't contain spaces ";
            std::cout << "or letters that are not part of the english alphabet. " << std::endl;
            std::cout << "New Playername: ";
            std::cin >> newName;
        }
    return newName;
}

int Menu::getValidImageCount()
{
    int num;
    bool isNumber = true;
    bool isInRange = true;
    string newImageCount;
    std::cin >> newImageCount;
    try {
        num = std::stoi(newImageCount); //string to int
    } catch (const std::invalid_argument& e) {
        isNumber = false;
    } catch (const std::out_of_range& e) {
        isInRange = false;
    }
    while(num < 1 || num > 99 || std::cin.fail())
    /*
    Upper limit can be adjusted since the imagesequences contain up to 1000 images
    */
    {
        std::cin.clear();
        std::cout << "Invalid number of images! Make sure your number is in between 1 and 99" << std::endl;
        std::cout << "New number of images: ";
        std::cin >> newImageCount;
        try {
        num = std::stoi(newImageCount); //string to int
    } catch (const std::invalid_argument& e) {
        isNumber = false;
    } catch (const std::out_of_range& e) {
        isInRange = false;
    }
    }
    return num;
}

int Menu::getValidGamemode()
{
    int num;
    bool isNumber = true;
    string newGamemode;
    std::cin >> newGamemode;
    try {
        num = std::stoi(newGamemode); //string to int
    } catch (const std::invalid_argument& e) {
        isNumber = false;
    }
    while(num < 1 || num > 2 || std::cin.fail())
    {
        std::cin.clear();
        std::cout << "Invalid input! Please enter [1] or [2] for your desired gamemode! " << std::endl;
        std::cout << "New gamemode: ";
        std::cin >> newGamemode;
        isNumber = true;
        try {
        num = std::stoi(newGamemode); //string to int
    } catch (const std::invalid_argument& e) {
        isNumber = false;
    }
    }
    return num;
}

string Menu::getValidImageSequence()
{
    string newImageSeq;
    bool isNumber = true;
    bool isInRange = true;
    int num;
    std::cin >> newImageSeq;
    try {
        num = std::stoi(newImageSeq); //string to int
    } catch (const std::invalid_argument& e) {
        isNumber = false;
    } catch (const std::out_of_range& e) {
        isInRange = false;
    }
        while(newImageSeq.length() != 4 ||
        newImageSeq[0] != '0' ||
        newImageSeq[1] != '0' ||
        num < 0 ||
        num > 20||
        !isNumber ||
        !isInRange ||
        std::cin.fail()) //Imagesequence needs to match the filefolder name
        {
            std::cin.clear(); // Clear the error flags
            std::cout << "Invalid imagesequence! Make sure to type in a number inbetween 0 and 20 and ";
            std::cout << "use exactly 4 digits (e.g. '0000' or '0017')." << std::endl;
            std::cout << "New imagesequence: ";
            std::cin >> newImageSeq;
            isNumber = true;
            isInRange = true;
            try {
                num = std::stoi(newImageSeq); //string to int
            } catch (const std::invalid_argument& e) {
                isNumber = false;
            } catch (const std::out_of_range& e) {
                isInRange = false;
            }
        }
    return newImageSeq;
}


#endif //MENU_CPP