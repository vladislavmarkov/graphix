#include <gfx/scene.h>
#include <memory>

#include "scene_impl.h"

using std::unique_ptr;

namespace gfx{

unique_ptr<scene> scene::create(
    float hfov, int width, int height, float near, float far, camera *cam
){
    return unique_ptr<scene>(new scene_impl(hfov, width, height, near, far, cam));
}

}
