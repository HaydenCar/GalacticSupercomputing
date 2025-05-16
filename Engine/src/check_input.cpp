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
    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS){
        renderer.set_follow(0);
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        renderer.set_follow(1);
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        renderer.set_follow(2);
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        renderer.set_follow(3);
    }
    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS){
        renderer.set_follow(4);
    }
    if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS){
        renderer.set_follow(5);
    }
    if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS){
        renderer.set_follow(6);
    }
    if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS){
        renderer.set_follow(7);
    }
    if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS){
        renderer.set_follow(8);
    }
    if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS){
        renderer.set_follow(9);
    }
}
