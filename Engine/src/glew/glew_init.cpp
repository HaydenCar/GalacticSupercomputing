//
//  glew_init.cpp
//  Engine
//
//  Created by Hayden Carr on 27/01/2025.
//

#include "glew_init.hpp"
#include <GL/glew.h>
#include <iostream>

void glew_init(){
    // glew initialisation
    glewExperimental = GL_TRUE; // Enable modern OpenGL features
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
}
