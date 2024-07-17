#ifndef MENU_CPP
#define MENU_CPP
#include "menu.hpp"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool containsChar(std::string str)
{
    for (char &c : str)
    {
        int i = static_cast<int>(c);
        if (c < 48 || c > 57)
            return true;
    }
    return false;
}

Menu::Menu()
{
    cout << "********************* KITTI Reaction Game *********************" << endl
         << "************* by Reinhold Brant and Albert Eisfeld ************" << endl
         << endl
         << "Player Name: ";
    m_playerName = readValidName();
    cout << "How many images do you want to play? ";
    m_imageCount = readValidImageCount();
    cout << "Which imagesequence do you chose? ";
    m_imageSequence = readValidImageSequence();
    cout << "Which gamemode? (1: single, 2: multi) ";
    m_gamemode = readValidGamemode();

    cout << m_playerName << endl
         << m_imageCount << endl
         << m_imageSequence << endl; // For Testing
}

string Menu::getPlayerName() const
{
    return m_playerName;
}

int Menu::getImageCount() const
{
    return m_imageCount;
}

string Menu::getImageSequence() const
{
    return m_imageSequence;
}

int Menu::getGamemode() const
{
    return m_gamemode;
};

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

/// @brief reads userinputs for m_playername until they are correct
/// @return correct Playername
string Menu::readValidName()
{
    string newName;
    std::cin >> newName;

    while (std::cin.fail()) // checks for weird ASCIIs
    {
        std::cin.clear(); // Clear the error flags
        std::cout << "Invalid name! Make sure your Playername doesn't contain spaces ";
        std::cout << "or letters that are not part of the english alphabet. " << std::endl;
        std::cout << "New Playername: ";
        std::cin >> newName;
    }
    return newName;
}

/// @brief reads userinputs for m_imagecount until they are correct
/// @return correct m_imagecount (1-99)
int Menu::readValidImageCount()
{
    int num;
    bool isNumber = true;
    bool isInRange = true;
    string newImageCount;
    std::cin >> newImageCount;
    try
    {
        num = std::stoi(newImageCount); // string to int
    }
    catch (const std::invalid_argument &e)
    {
        isNumber = false;
    }
    catch (const std::out_of_range &e)
    {
        isNumber = false;
    }

    isNumber = !containsChar(newImageCount);

    while (num < 1 || num > 99 || cin.fail() || !isNumber)
    /*
    Upper limit can be adjusted since the imagesequences contain up to 1000 images
    */
    {
        std::cin.clear();
        std::cout << "Invalid number of images! Make sure your number is in between 1 and 99. No letters." << std::endl;
        std::cout << "New number of images: ";
        std::cin >> newImageCount;
        isNumber = !containsChar(newImageCount);
        try
        {
            num = std::stoi(newImageCount); // string to int
        }
        catch (const std::invalid_argument &e)
        {
            isNumber = false;
        }
        catch (const std::out_of_range &e)
        {
            isInRange = false;
        }
    }
    return num;
}


/// @brief reads userinputs for m_gamemode until they are correct
/// @return correct m_gamemode (1 || 2)
int Menu::readValidGamemode()
{
    int num;
    bool isNumber = true;
    string newGamemode;
    std::cin >> newGamemode;
    try
    {
        num = std::stoi(newGamemode); // string to int
    }
    catch (const std::invalid_argument &e)
    {
        isNumber = false;
    }
    isNumber = !containsChar(newGamemode);
    while (num < 1 || num > 2 || std::cin.fail() || !isNumber)
    {
        std::cin.clear();
        std::cout << "Invalid input! Please enter [1] or [2] for your desired gamemode! " << std::endl;
        std::cout << "New gamemode: ";
        std::cin >> newGamemode;
        isNumber = true;
        try
        {
            num = std::stoi(newGamemode); // string to int
        }
        catch (const std::invalid_argument &e)
        {
            isNumber = false;
        }
    }
    return num;
}

/// @brief reads userinputs for m_imagesequence until they are correctly formated
/// @return correct m_imagesequence e.g. "0014", "0001"
string Menu::readValidImageSequence()
{
    string newImageSeq;
    bool isNumber = true;
    bool isInRange = true;
    int num;
    std::cin >> newImageSeq;
    try
    {
        num = std::stoi(newImageSeq); // string to int
    }
    catch (const std::invalid_argument &e)
    {
        isNumber = false;
    }
    catch (const std::out_of_range &e)
    {
        isInRange = false;
    }
    while (newImageSeq.length() != 4 ||
           newImageSeq[0] != '0' ||
           newImageSeq[1] != '0' ||
           num < 0 ||
           num > 20 ||
           !isNumber ||
           !isInRange ||
           std::cin.fail()) // Imagesequence needs to match the filefolder name
    {
        std::cin.clear(); // Clear the error flags
        std::cout << "Invalid imagesequence! Make sure to type in a number inbetween 0 and 20 and ";
        std::cout << "use exactly 4 digits (e.g. '0000' or '0017')." << std::endl;
        std::cout << "New imagesequence: ";
        std::cin >> newImageSeq;
        isNumber = true;
        isInRange = true;
        try
        {
            num = std::stoi(newImageSeq); // string to int
        }
        catch (const std::invalid_argument &e)
        {
            isNumber = false;
        }
        catch (const std::out_of_range &e)
        {
            isInRange = false;
        }
    }
    return newImageSeq;
}

void Menu::finishScreen(std::vector<double> times)
{
    struct timeImgPair
    {
        // necassary for printing out the 3 best times with the imagenumber
        double time;
        int imgNr;
    };

    double avg = 0;

    for (double &d : times)
    {
        avg += d;
    }
    avg /= times.size();
    std::vector<timeImgPair> timesWithImg;
    int c = 1;
    for (double &d : times)
    {
        timesWithImg.push_back({d, c});
        c++;
    }

    std::sort(timesWithImg.begin(), timesWithImg.end(), [](timeImgPair left, timeImgPair right)
              { return left.time < right.time; });

    std::cout << std::endl
              << "Results of: " << m_playerName << std::endl;
    std::cout << "Your averagetime: " << avg / 1000 << " s " << std::endl
              << "Your " << std::min<size_t>(3, timesWithImg.size()) << " fastest reactions:" << std::endl;

    for (size_t i = 0; i < std::min<size_t>(3, timesWithImg.size()); ++i)
    {
        std::cout << timesWithImg[i].time << " s at image Nr." << timesWithImg[i].imgNr << std::endl;
    }
}

#endif // MENU_CPP