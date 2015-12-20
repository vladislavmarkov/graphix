#pragma once
#ifndef __GFX_SHADER_H__
#define __GFX_SHADER_H__

#include <memory>

namespace gfx{

class shader{
public:
    enum type: unsigned char{
        vertex,
        fragment
    };

    static std::unique_ptr<shader> create(
        type t,
        const std::string &code
    );

    static std::unique_ptr<shader> load_from_file(
        type t,
        const std::string &filename
    );

    static std::unique_ptr<shader> create_default(type t);
};

}

#endif // __GFX_SHADER_H__
