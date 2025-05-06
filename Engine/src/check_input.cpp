//
//  check_input.cpp
//  Engine
//
//  Created by Hayden Carr on 27/01/2025.
//

#include "check_input.hpp"

void check_input(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
