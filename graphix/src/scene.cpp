#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <gfx/scene.h>
#include <memory>

#include "convert_meshes.h"
#include "scene_impl.h"

// test
#include <iostream>
// test

using std::unique_ptr;

namespace gfx{

unique_ptr<scene> scene::create(
    float hfov,
    int width,
    int height,
    float near,
    float far,
    camera *cam,
    glm::vec4 clear_color
){
    return unique_ptr<scene>(
        new scene_impl(hfov, width, height, near, far, cam, clear_color)
    );
}

unique_ptr<scene> scene::load(
    float hfov,
    int width,
    int height,
    float near,
    float far,
    camera *cam,
    glm::vec4 clear_color,
    const std::string &filename
){
    Assimp::Importer importer;
    const aiScene* assimpscene = importer.ReadFile(
        filename,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType
    );

    if (!assimpscene){
        throw std::runtime_error(importer.GetErrorString());
    }

    aiMesh **assimpmeshes = nullptr;
    if (assimpscene->mNumMeshes){
        assimpmeshes = assimpscene->mMeshes;
    }

    // temp
    if (assimpscene->HasAnimations()){
        std::cout << "scene has animations" << std::endl;
    }

    if (assimpscene->HasCameras()){
        std::cout << "scene has cameras" << std::endl;
    }

    if (assimpscene->HasLights()){
        std::cout << "scene has lights" << std::endl;
    }

    if (assimpscene->HasMaterials()){
        std::cout << "scene has materials" << std::endl;
    }

    if (assimpscene->HasMeshes()){
        std::cout << "scene has meshes" << std::endl;
    }

    if (assimpscene->HasTextures()){
        std::cout << "scene has textures" << std::endl;
    }
    // temp

    std::list<std::shared_ptr<mesh>> meshes = convert_meshes(
        assimpmeshes, assimpscene->mNumMeshes
    );

    unique_ptr<scene> result(
        new scene_impl(
            hfov, width, height, near, far, cam, clear_color, meshes
        )
    );

    return result;
}

}
