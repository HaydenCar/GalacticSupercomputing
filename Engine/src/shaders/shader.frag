//
//  shader.frag
//  Engine
//
//  Created by Hayden Carr on 01/02/2025.
//

#version 330 core
out vec4 FragColor;
uniform vec3 color;  

void main() {
    FragColor = vec4(color, 1.0);
}
