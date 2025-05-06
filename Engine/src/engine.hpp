//
//  engine.hpp
//  Engine
//
//  Created by Hayden Carr on 27/01/2025.
//

#ifndef engine_hpp
#define engine_hpp
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "renderer/renderer.hpp"

class Engine{
public:
    void run();
    
    GLFWwindow* window;
    Renderer renderer;

private:
    void init();
    void main_loop();
    void cleanup();
    
    const unsigned int SCREEN_WIDTH = 800;
    const unsigned int SCREEN_HEIGHT = 600;
};

#endif /* engine_hpp */
