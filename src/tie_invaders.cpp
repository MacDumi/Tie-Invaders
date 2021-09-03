#include "engine/engine.h"
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    Engine* engine;
    if (argc == 2)
    {
        std::string arg(argv[1]);
        if (arg == "-h" || arg == "--help")
        {
            std::cout << "TIE INVADERS" << std::endl;
            std::cout << "Usage: ./tie_invaders [OPTION]" << std::endl;
            std::cout << std::endl;
            std::cout << "-h, --help\tPrint this help message and exit";
            std::cout << std::endl;
            std::cout << "-w, --windowed\tRun in windowed mode (1920x1080)";
            std::cout << std::endl;
            return 0;
        }
        else if (arg == "-w" || arg == "--windowed")
        {
            engine = new Engine(1920, 1080);
        }
    }
    else
    {
        engine = new Engine();
    }


    engine->run();

    return 0;
}


