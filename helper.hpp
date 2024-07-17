#ifndef HELPER_INCLUDED
#define HELPER_INCLUDED

#include <opencv2/opencv.hpp>
#include "./Models/Frame.hpp"

namespace Helper
{
    void onMouse(int event, int x, int y, int flags, void *userdata);
    int randomNumber(int start, int end);
}

#endif // HELPER_INCLUDED