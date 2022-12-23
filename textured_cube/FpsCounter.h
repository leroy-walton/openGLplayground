#ifndef FPSCOUNTER_CLASS_H
#define FPSCOUNTER_CLASS_H

#include<GLFW/glfw3.h>
#include<iostream>

class FpsCounter
{
    public:
        FpsCounter();
        double getFps();
    private:
        double prevTime;
        double crntTime;
        double timeDiff;
        double prevCounter;
        unsigned int counter;
};

#endif