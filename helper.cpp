#include "helper.hpp"

namespace helper {
    void onMouse(int event, int x, int y, int flags, void *userdata)
    {
        Frame *self = static_cast<Frame *>(userdata);
        // Wenn ein Ergebnis vorliegt (bereits geclickt), dann wird der Click nicht mehr registriert
        if (self->result != 0)
            return;
        if (event == cv::EVENT_LBUTTONDOWN)
        {
            std::cout << "Lbutton down at x: " << x << " and y: " << y << std::endl;
            if (self->checkForHit(cv::Point(x, y)))
            {
                std::cout << std::endl
                          << "Hit on: " << self << std::endl;
                double r = self->calcReactionTime();
                self->handleHit(r);
            }
            else
            {
                // 5 sek strafzeit
                self->handleHit(5000);
                std::cout << "Miss!" << std::endl;
            }
        }
    }
}
