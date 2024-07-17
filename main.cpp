#include "./Menu/Class Files/menu.hpp"
#include "./Models/FrameFactory.hpp"
#include "./Models/Frame.hpp"

#include <map>
#include <filesystem>

#define DOUBLE_BR std::endl \
                      << std::endl


int main()
{
    Menu gameMenu = Menu();
    int numImages = gameMenu.getImageCount();
    GameMode gamemode;
    if (gameMenu.getGamemode() == 1)
    {
        gamemode = GameMode::singular;
    }
    else
    {
        gamemode = GameMode::allAtOnce;
    }

    std::string seq = gameMenu.getImageSequence();

    FrameFactory fac = FrameFactory(seq);

    std::vector<double> times;

    cv::imshow("Display Image", 0);

    Frame *frame;
    for (int i = 0; i < numImages; i++)
    {
        frame = fac.take(gamemode);
        (*frame).show();
        std::cout << "Reaction Time: " << (*frame).result << std::endl;
        times.push_back(frame->result);
    }

    double avg = 0;
    for (double &d : times)
    {
        avg += d;
    }
    avg /= times.size();

    std::cout << DOUBLE_BR << "Deine Ergebnisse " << gameMenu.getPlayerName() << DOUBLE_BR;

    std::cout << "Durchschnitt: " << avg / 1000 << " s " << std::endl;

    return 0;
}