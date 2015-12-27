#include <fstream>
#include <gfx/shader.h>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "shader_impl.h"

using std::ifstream;
using std::invalid_argument;
using std::istreambuf_iterator;
using std::string;
using std::stringstream;
using std::unique_ptr;

namespace gfx{

namespace { // anonymous

static const string default_vertex_shader__ =
    "#version 440\n"
    "in vec3 vertex_position;\n"
    "uniform mat4 mvp;\n"
    "void main(){\n"
    "    gl_Position = mvp * vec4(vertex_position, 1.0);\n"
    "}";

static const string default_fragment_shader__ =
    "#version 440\n"
    "out vec4 frag_color;\n"
    "void main(){\n"
    "    frag_color = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}";

} // anonymous

template<>
unique_ptr<shader<shader_type::vertex>>
shader<shader_type::vertex>::create(const string &code){
    return unique_ptr<shader>(new shader_impl<shader_type::vertex>(code));
}

template<>
unique_ptr<shader<shader_type::fragment>>
shader<shader_type::fragment>::create(const string &code){
    return unique_ptr<shader>(new shader_impl<shader_type::fragment>(code));
}

template<>
unique_ptr<shader<shader_type::vertex>>
shader<shader_type::vertex>::load_from_file(const string &filename){
    ifstream file(filename, ifstream::in);
    if (file){
        string code(
            (istreambuf_iterator<char>(file)),
            istreambuf_iterator<char>()
        );
        file.close();
        return unique_ptr<shader<shader_type::vertex>>(
            new shader_impl<shader_type::vertex>(code)
        );
    }

    stringstream errmsg;
    errmsg << "no such file (" << filename << ")";
    throw invalid_argument(errmsg.str());
}

template<>
unique_ptr<shader<shader_type::fragment>>
shader<shader_type::fragment>::load_from_file(const string &filename){
    ifstream file(filename, ifstream::in);
    if (file){
        string code(
            (istreambuf_iterator<char>(file)),
            istreambuf_iterator<char>()
        );
        file.close();
        return unique_ptr<shader<shader_type::fragment>>(
            new shader_impl<shader_type::fragment>(code)
        );
    }

    stringstream errmsg;
    errmsg << "no such file (" << filename << ")";
    throw invalid_argument(errmsg.str());
}

template<>
unique_ptr<shader<shader_type::vertex>>
shader<shader_type::vertex>::create_default(){
    return unique_ptr<shader<shader_type::vertex>>(
        new shader_impl<shader_type::vertex>(default_vertex_shader__)
    );
}

template<>
unique_ptr<shader<shader_type::fragment>>
shader<shader_type::fragment>::create_default(){
    return unique_ptr<shader<shader_type::fragment>>(
        new shader_impl<shader_type::fragment>(default_fragment_shader__)
    );
}

}
