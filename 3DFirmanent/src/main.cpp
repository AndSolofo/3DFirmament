#pragma once
#include "Application.h"


int main(void)
{
    try {
        Application app;
        app.Run();
        return 0;
    }
    catch (std::exception& exc) {
        std::cerr <<"ERROR::RUNNING APP: " << exc.what() << "\n";
        return -1;
    }
}
