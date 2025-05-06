//
//  bodies.hpp
//  Engine
//
//  Created by Hayden Carr on 27/03/2025.
//

#ifndef bodies_hpp
#define bodies_hpp

#include <glm/glm.hpp>

struct Body {
    int id; // 0 star, 1 planet, 2 moon using this for color and size distribution aswell 
    glm::vec3 position;
};

#endif /* bodies_hpp */
