#pragma once
#ifndef __GFX_CONVERT_MESHES_H__
#define __GFX_CONVERT_MESHES_H__

#include <gfx/mesh.h>
#include <list>
#include <memory>

struct aiMesh;

namespace gfx{

std::list<std::shared_ptr<mesh>> convert_meshes(aiMesh **, size_t count);

}

#endif // __GFX_CONVERT_MESHES_H__
