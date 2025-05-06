//
//  window_init.hpp
//  Engine
//
//  Created by Hayden Carr on 27/01/2025.
//

#ifndef window_init_hpp
#define window_init_hpp
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

GLFWwindow* window_init(int width, int height, const char* title);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif /* window_init_hpp */
