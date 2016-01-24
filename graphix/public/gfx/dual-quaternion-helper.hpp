#pragma once
#ifndef __GFX_DUAL_QUATERNION_HELPER_HPP__
#define __GFX_DUAL_QUATERNION_HELPER_HPP__

#include <glm/gtx/dual_quaternion.hpp>

namespace gfx{

inline glm::mat4 dual_quat_to_mat4(const glm::dualquat &dq){
   glm::fdualquat norm_dq = glm::normalize(dq);

   // get an identity matrix
   glm::mat4 mat;

   // extract rotational information
   float scalar = norm_dq.real.w;
   float x = norm_dq.real.x;
   float y = norm_dq.real.y;
   float z = norm_dq.real.z;

   mat[0][0] = (scalar * scalar) + (x * x) - (y * y) - (z * z);
   mat[0][1] = (2 * x * y) + (2 * scalar * z);
   mat[0][2] = (2 * x * z) - (2 * scalar * y);

   mat[1][0] = (2 * x * y) - (2 * scalar * z);
   mat[1][1] = (scalar * scalar) + (y * y) - (x * x) - (z * z);
   mat[1][2] = (2 * y * z) + (2 * scalar * x);

   mat[2][0] = (2 * x * z) + (2 * scalar * y);
   mat[2][1] = (2 * y * z) - (2 * scalar * x);
   mat[2][2] = (scalar * scalar) + (z * z) - (x * x) - (y * y);

   // extract translational information
   glm::fquat trans = (norm_dq.dual * 2.0f) * glm::conjugate(norm_dq.real);
   mat[3][0] = trans.x;
   mat[3][1] = trans.y;
   mat[3][2] = trans.z;

   return mat;
}

}

#endif // __GFX_DUAL_QUATERNION_HELPER_HPP__
