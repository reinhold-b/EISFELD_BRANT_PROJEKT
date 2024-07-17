#include "helper.hpp"
#include <random>

namespace Helper
{
    void onMouse(int event, int x, int y, int flags, void *userdata)
    {
        Frame *self = static_cast<Frame *>(userdata);
        // Wenn ein Ergebnis vorliegt (bereits geclickt), dann wird der Click nicht mehr registriert
        if (self->result != 0)
            return;
        if (event == cv::EVENT_LBUTTONDOWN)
        {
            if (self->checkForHit(cv::Point(x, y)))
            {
                double r = self->calcReactionTime();
                self->handleHit(r);
            }
            else
            {
                // 5 sek strafzeit
                self->handleHit(5000);
            }
        }
    }

    int randomNumber(int start, int end)
    {
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        int random_value;
        random_value = std::rand() % end;
        return random_value;
    }
}
