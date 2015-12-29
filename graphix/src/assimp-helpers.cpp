#include <algorithm>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <gfx/mesh.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include "mesh_impl.h"
#include "node.h"

using glm::vec3;
using std::begin; using std::end;
using std::for_each;
using std::invalid_argument;
using std::list;
using std::shared_ptr;
using std::string;
using std::vector;

// temp
#include <iostream>
// temp

namespace gfx{

namespace { // anoynmous

primitive_type convert_primitive_type(unsigned int aitype){
    switch (aitype){
    case aiPrimitiveType_POINT:
        return primitive_type::point;
    case aiPrimitiveType_LINE:
        return primitive_type::line;
    case aiPrimitiveType_TRIANGLE:
        return primitive_type::triangle;
    case aiPrimitiveType_POLYGON:
        return primitive_type::polygon;
    }

    throw invalid_argument("primitive type is uknown");
}

shared_ptr<mesh> convert_mesh(const aiMesh *assimpm){
    if (!assimpm){
        throw invalid_argument("mesh is null");
    }

    vector<vec3> vertices;
    vertices.reserve(assimpm->mNumVertices);
    for (size_t i = 0; i < assimpm->mNumVertices; ++i){
        vertices.emplace_back(
            vec3(
                assimpm->mVertices[i].x,
                assimpm->mVertices[i].y,
                assimpm->mVertices[i].z
            )
        );
    }

    vector<unsigned int> faces;
    for (size_t i = 0; i < assimpm->mNumFaces; ++i){
        faces.insert(
            end(faces),
            assimpm->mFaces[i].mIndices,
            assimpm->mFaces[i].mIndices +
                assimpm->mFaces[i].mNumIndices
        );
    }

    mesh_impl *m = new mesh_impl(
        string(assimpm->mName.C_Str()), vertices, faces
    );

    m->set_primitive_type(convert_primitive_type(assimpm->mPrimitiveTypes));

    return shared_ptr<mesh>(m);
}

shared_ptr<node> convert_node(const aiNode *assimpn){
    if (!assimpn){
        return shared_ptr<node>();
    }

    shared_ptr<node> result(new node(nullptr, assimpn->mName.C_Str()));

    // std::cout << "converted node: \"" << assimpn->mName.C_Str() << std::endl;

    result->transformation_ = std::move(glm::mat4(
        glm::vec4(
            assimpn->mTransformation.a1,
            assimpn->mTransformation.b1,
            assimpn->mTransformation.c1,
            assimpn->mTransformation.d1
        ),
        glm::vec4(
            assimpn->mTransformation.a2,
            assimpn->mTransformation.b2,
            assimpn->mTransformation.c2,
            assimpn->mTransformation.d2
        ),
        glm::vec4(
            assimpn->mTransformation.a3,
            assimpn->mTransformation.b3,
            assimpn->mTransformation.c3,
            assimpn->mTransformation.d3
        ),
        glm::vec4(
            assimpn->mTransformation.a4,
            assimpn->mTransformation.b4,
            assimpn->mTransformation.c4,
            assimpn->mTransformation.d4
        )
    ));

    #if 0
    // temp
    glm::mat4 &t = result->transformation_;
    std::cout
        << "transformation: " << std::endl
        << t[0][0] << ", " << t[0][1] << ", " << t[0][2] << ", " << t[0][3] << std::endl
        << t[1][0] << ", " << t[1][1] << ", " << t[1][2] << ", " << t[1][3] << std::endl
        << t[2][0] << ", " << t[2][1] << ", " << t[2][2] << ", " << t[2][3] << std::endl
        << t[3][0] << ", " << t[3][1] << ", " << t[3][2] << ", " << t[3][3] << std::endl;
    // temp
    #endif

    for (size_t i = 0; i < assimpn->mNumMeshes; ++i){
        result->mesh_indices_.push_back(assimpn->mMeshes[i]);
    }

    return result;
}

} // anoynmous

vector<shared_ptr<mesh>> extract_meshes(const aiScene *assimpscene){
    if (!assimpscene->mMeshes || !assimpscene->mNumMeshes){
        throw invalid_argument("no meshes to convert");
    }

    vector<shared_ptr<mesh>> result;

    for (size_t i = 0; i < assimpscene->mNumMeshes; ++i){
        result.emplace_back(convert_mesh(assimpscene->mMeshes[i]));
    }

    return result;
}

shared_ptr<node> extract_root_node(const aiScene *assimpscene){
    if (!assimpscene){
        throw invalid_argument("scene is a null pointer");
    }

    if (!assimpscene->HasMeshes()){
        return shared_ptr<node>();
    }

    if (!assimpscene->mRootNode){
        throw invalid_argument("invalid scene object");
    }

    aiNode *airoot = assimpscene->mRootNode;
    shared_ptr<node> root = convert_node(airoot);

    std::stack<aiNode*> ainodes;
    ainodes.push(airoot);
    std::stack<node*> nodes;
    nodes.push(root.get());

    while (!nodes.empty()){
        aiNode *aicurrent = ainodes.top();
        ainodes.pop();
        node *current = nodes.top();
        nodes.pop();
        for (size_t i = 0; i < aicurrent->mNumChildren; ++i){
            ainodes.push(aicurrent->mChildren[i]);
            shared_ptr<node> tmp(convert_node(aicurrent->mChildren[i]));
            nodes.push(tmp.get());
            current->children_.emplace_back(tmp);
            for_each(begin(current->children_), end(current->children_),
                [&current](shared_ptr<node> &n){
                    n->parent_ = current;
                }
            );
        }
    }

    return root;
}

}
