//
//  main.cpp
//
//  Created by Hayden Carr on 27/01/2025.
//

#include "src/engine.hpp"
#include <iostream>

int main()
{
    Engine engine;
    try {
        engine.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
