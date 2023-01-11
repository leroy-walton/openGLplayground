#include "FpsCounter.h"

FpsCounter::FpsCounter()
{
    glfwSetTime(0);
    last_time = 0.0;
    current_time = 0.0;
    frame_counter = 0;
    fps = 0;
}

double FpsCounter::getFps()
{
    current_time = glfwGetTime();
    double elapsed_time = current_time - last_time;
    frame_counter++;
    if (elapsed_time > 0.5)
    {
        double new_fps = frame_counter / elapsed_time;
        last_time = current_time;
        frame_counter = 0;
        fps = new_fps;
    }
    return fps;
}
