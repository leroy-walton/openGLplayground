#ifndef FPSCOUNTER_CLASS_H
#define FPSCOUNTER_CLASS_H

#include <GLFW/glfw3.h>
#include <iostream>

class FpsCounter
{
public:
    FpsCounter();
    double getFps();

private:
    double last_time;
    double current_time;
    unsigned int frame_counter;
    double fps;
};

#endif