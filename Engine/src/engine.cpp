//
//  engine.cpp
//  Engine
//
//  Created by Hayden Carr on 27/01/2025.
//

#include "engine.hpp"
#include "window/window_init.hpp"
#include "glew/glew_init.hpp"
#include "check_input.hpp"

void Engine::run()
{
    init();

    main_loop();

    cleanup();
}

void Engine::init()
{
    window = window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Engine");
    glew_init();
    renderer.create_render_data();
}

void Engine::main_loop()
{
    //renderer.load_data("./Dependencies/output.dat"); // xcode sucks
    renderer.load_data("/Users/haydencarr/Documents/GalacticSupercomputing/Engine/Dependencies/output.dat");

    while (!glfwWindowShouldClose(window))
    {
        // input
        check_input(window);

        // render
        renderer.render_frame();

        // swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::cleanup()
{
    glfwTerminate();
}
