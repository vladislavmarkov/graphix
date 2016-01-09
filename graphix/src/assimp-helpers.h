#pragma once
#ifndef __GFX_ASSIMP_HELPERS_H__
#define __GFX_ASSIMP_HELPERS_H__

#include <list>
#include <memory>

struct aiScene;

namespace gfx{

struct node;

std::vector<std::shared_ptr<drawable>> extract_meshes(const aiScene*);
std::shared_ptr<node> extract_root_node(const aiScene *);

}

#endif // __GFX_ASSIMP_HELPERS_H__
