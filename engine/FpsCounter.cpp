#include "FpsCounter.h"

FpsCounter::FpsCounter()
{
    prevTime = 0.0;
    crntTime = 0.0;
    counter = 0;
    timeDiff = 999999999999;
}

double FpsCounter::getFps()
{
    crntTime = glfwGetTime();
    timeDiff = crntTime - prevTime;
    counter++;
    double fps = counter / timeDiff;
    prevTime = crntTime;
    counter = 0;
    return fps;
}
