#include <assimp/mesh.h>
#include <gfx/mesh.h>
#include <glm/glm.hpp>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "mesh_impl.h"

// temp
#include <iostream>
// temp

using glm::vec3;
using std::begin; using std::end;
using std::invalid_argument;
using std::list;
using std::shared_ptr;
using std::string;
using std::vector;

namespace gfx{

namespace { // anoynmous

shared_ptr<mesh> convert_mesh(const aiMesh *assimpmesh){
    if (!assimpmesh){
        throw invalid_argument("mesh is null");
    }

    vector<vec3> vertices;
    vertices.reserve(assimpmesh->mNumVertices);
    for (size_t i = 0; i < assimpmesh->mNumVertices; ++i){
        vertices.emplace_back(
            vec3(
                assimpmesh->mVertices[i].x,
                assimpmesh->mVertices[i].y,
                assimpmesh->mVertices[i].z
            )
        );
    }

    vector<unsigned int> faces;
    for (size_t i = 0; i < assimpmesh->mNumFaces; ++i){
        faces.insert(
            end(faces),
            assimpmesh->mFaces[i].mIndices,
            assimpmesh->mFaces[i].mIndices +
                assimpmesh->mFaces[i].mNumIndices
        );
    }

    mesh_impl *m = new mesh_impl(
        string(assimpmesh->mName.C_Str()), vertices, faces
    );

    return shared_ptr<mesh>(m);
}

} // anoynmous

list<shared_ptr<mesh>> convert_meshes(aiMesh **assimpmeshes, size_t count){
    if (!assimpmeshes || !count){
        throw invalid_argument("no meshes to convert");
    }

    list<shared_ptr<mesh>> result;

    for (size_t i = 0; i < count; ++i){
        result.emplace_back(convert_mesh(assimpmeshes[i]));
    }

    return result;
}

}
