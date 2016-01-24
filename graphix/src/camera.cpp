#include <gfx/camera.hpp>
#include <glm/glm.hpp>
#include <memory>

#include "camera-impl.hpp"

using std::shared_ptr;

namespace gfx{

shared_ptr<camera> camera::create(glm::mat4 mx){
    return shared_ptr<camera>(new camera_impl(std::move(mx)));
}

}
