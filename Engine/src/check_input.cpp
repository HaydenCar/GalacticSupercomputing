//
//  check_input.cpp
//  Engine
//
//  Created by Hayden Carr on 27/01/2025.
//

#include "check_input.hpp"

void check_input(GLFWwindow *window, Renderer &renderer){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
        renderer.zoom_in();
    }
    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
        renderer.zoom_out();
    }
}
