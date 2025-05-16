//
// renderer.cpp
//  Engine
//
//  Created by Hayden Carr on 31/01/2025.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"
#include "../shaders/shader.hpp"
#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../../Dependencies/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../bodies.hpp"
#include <vector>

unsigned int texture;

// Vertex array object and Vertex buffer object
unsigned int VBO, VAO;

// Vector that hold all bodies
std::vector<Body> bodies;

// Cubes
float vertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    // Front face
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    // Left face
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    // Right face
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    // Top face
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

// Constructor
Renderer::Renderer()
{
    VBO = 0;
    VAO = 0;
    cameraDistance = 100.0f;
}

// Destructor
Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

// Loads the data from output.dat
void Renderer::load_data(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Can't open " << filename << std::endl;
        return;
    }

    unsigned int timestep;
    int body_id;
    double x, y, z;
    float normalise = 1e-10f;

    bodies.clear();
    currentTimestep = 0;
    lastFrameTime = 0.0f;

    // Figured this out from here read this!!!: https://stackoverflow.com/questions/43956124/c-while-loop-to-read-from-input-file
    while (file >> timestep >> body_id >> x >> y >> z)
    {
        bodies.push_back({body_id, glm::vec3(x * normalise, y * normalise, z * normalise)});
    }
    std::cout << "Loaded " << bodies.size() << " bodies" << std::endl;
}

void Renderer::zoom_out()
{
    cameraDistance = cameraDistance - zoom_distance;
}

void Renderer::zoom_in()
{
    cameraDistance = cameraDistance + zoom_distance;
}

void Renderer::set_follow(int id)
{
    current_follow = id;
}

// Creates the render data
void Renderer::create_render_data()
{
    // Necessary for 3D
    glEnable(GL_DEPTH_TEST);

    // Gen and bind buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load in a texture not in use atm
    /*
    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Engine/Res/wall.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    */
}

// Used to render a frame
void Renderer::render_frame()
{
    static Shader ourShader("src/shaders/shader.vert", "src/shaders/shader.frag");
    static float r = 0.0f, g = 0.0f, b = 0.0f;

    // Clear buffers
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate shader
    ourShader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    // Camera setup
    float cameraX = 0.0f;
    float cameraZ = cameraDistance;

    // Look at the center of your data
    glm::mat4 view = glm::lookAt(
        glm::vec3(cameraX, cameraDistance * 0.5f, cameraZ),
        follow_vec, // bodies[i].position??
        glm::vec3(0.0f, 1.0f, 0.0f));

    // Wider perspective view
    glm::mat4 projection = glm::perspective(
        glm::radians(60.0f),
        800.0f / 600.0f,
        1.0f,
        1000.0f);

    // Send matrices to shader
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);

    // Next frame when timestep is met
    float currentTime = glfwGetTime();
    if (currentTime - lastFrameTime > frameTimeStep)
    {
        currentTimestep += bodiesPerFrame;
        lastFrameTime = currentTime;

        // Loop back to start of data if file end
        if (currentTimestep >= bodies.size())
        {
            currentTimestep = 0;
        }
    }

    // Renders the
    int endIndex;
    if (currentTimestep + bodiesPerFrame < bodies.size())
    {
        endIndex = currentTimestep + bodiesPerFrame;
    }
    else
    {
        endIndex = bodies.size();
    }
    for (int i = currentTimestep; i < endIndex; i++)
    {
        Body &body = bodies[i];
        glm::mat4 model = glm::mat4(1.0f);

        float scale;
        glm::vec3 color;
        if (body.id > 9) // Default
        {
            scale = 1.0f;
            color = glm::vec3(1.0f, 1.0f, 1.0f); // White
        }
        else if (body.id == 0) // Sun
        {
            scale = 5.0f;
            color = glm::vec3(1.0f, 0.9f, 0.1f);
        }
        else if (body.id == 1) // Earth
        {
            scale = 1.5f;
            color = glm::vec3(0.2f, 0.5f, 1.0f);
        }
        else if (body.id == 2) // Mercury
        {
            scale = 1.2f;
            color = glm::vec3(0.6f, 0.6f, 0.6f);
        }
        else if (body.id == 3) // Venus
        {
            scale = 1.48f;
            color = glm::vec3(1.0f, 0.6f, 0.2f);
        }
        else if (body.id == 4) // Mars
        {
            scale = 1.3f;
            color = glm::vec3(0.8f, 0.3f, 0.1f);
        }
        else if (body.id == 5) // Jupiter
        {
            scale = 3.0f;
            color = glm::vec3(0.9f, 0.7f, 0.5f);
        }
        else if (body.id == 6) // Saturn
        {
            scale = 2.5f;
            color = glm::vec3(0.9f, 0.8f, 0.4f);
        }
        else if (body.id == 7) // Uranus
        {
            scale = 2.0f;
            color = glm::vec3(0.4f, 0.8f, 0.9f);
        }
        else if (body.id == 8) // Neptune
        {
            scale = 1.9f;
            color = glm::vec3(0.1f, 0.3f, 0.8f);
        }
        else if (body.id == 9) // Pluto
        {
            scale = 1.1f;
            color = glm::vec3(0.7f, 0.5f, 0.4f);
        }
        else {
            scale = 1.0f;
            color = glm::vec3(1.0f, 1.0f, 1.0f); // White
        }
        
        if(body.id == current_follow){
            follow_vec = body.position;
        }

        model = glm::translate(model, body.position);
        model = glm::scale(model, glm::vec3(scale));

        ourShader.setVec3("color", color);
        ourShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
