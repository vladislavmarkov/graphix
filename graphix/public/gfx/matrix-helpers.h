#pragma once
#ifndef __GFX_MATRIX_HELPERS_H__
#define __GFX_MATRIX_HELPERS_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gfx{

inline glm::vec3 get_direction(const glm::mat4 &view){
    #ifdef GLM_LEFT_HANDED
        return -glm::vec3(view[0][2], view[1][2], view[2][2]);
    #else // GLM_LEFT_HANDED
        return glm::vec3(view[0][2], view[1][2], view[2][2]);
    #endif // GLM_LEFT_HANDED
}

inline glm::vec3 get_right(const glm::mat4 &view){
    #ifdef GLM_LEFT_HANDED
        return glm::vec3(view[0][0], view[1][0], view[2][0]);
    #else // GLM_LEFT_HANDED
        return -glm::vec3(view[0][0], view[1][0], view[2][0]);
    #endif // GLM_LEFT_HANDED
}

inline glm::vec3 get_position(const glm::mat4 &view){
    glm::mat4 mx_t_ = glm::transpose(view);

    // get plane normals
    glm::vec3 n1(mx_t_[0]);
    glm::vec3 n2(mx_t_[1]);
    glm::vec3 n3(mx_t_[2]);

    // get plane distances
    float d1(mx_t_[0].w);
    float d2(mx_t_[1].w);
    float d3(mx_t_[2].w);

    // get the intersection of these 3 planes
    glm::vec3 n2n3 = glm::cross(n2, n3);
    glm::vec3 n3n1 = glm::cross(n3, n1);
    glm::vec3 n1n2 = glm::cross(n1, n2);

    glm::vec3 top = (n2n3 * d1) + (n3n1 * d2) + (n1n2 * d3);
    float denom = glm::dot(n1, n2n3);

    return top / -denom;
}

inline glm::vec3 get_up(const glm::mat4 &view){
    return glm::vec3(view[0][1], view[1][1], view[2][1]);
}

}

#endif // __GFX_MATRIX_HELPERS_H__
