// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "MainApp.h"

int main()
{
    MainApp app{};

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}