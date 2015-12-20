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
    "#440\n"
    "in vec3 vertex_position;\n"
    "void main(){\n"
    "    gl_Position = vec4(vertex_position, 1.0);\n"
    "}";

static const string default_fragment_shader__ =
    "#440\n"
    "uniform vec4 color;\n"
    "out vec4 frag_color;\n"
    "void main(){\n"
    "    frag_color = color;\n"
    "}";

} // anonymous

unique_ptr<shader> shader::create(
    type t,
    const string &code
){
    return unique_ptr<shader>(new shader_impl(t, code));
}

unique_ptr<shader> shader::load_from_file(
    type t,
    const string &filename
){
    ifstream file(filename, ifstream::in);
    if (file){
        string code(
            (istreambuf_iterator<char>(file)),
            istreambuf_iterator<char>()
        );
        file.close();
        return unique_ptr<shader>(
            new shader_impl(t, code)
        );
    }

    stringstream errmsg;
    errmsg << "no such file (" << filename << ")";
    throw invalid_argument(errmsg.str());
}

unique_ptr<shader> shader::create_default(type t){
    switch (t){
    case vertex:
        return unique_ptr<shader>(
            new shader_impl(t, default_vertex_shader__)
        );
    case fragment:
        return unique_ptr<shader>(
            new shader_impl(t, default_fragment_shader__)
        );
    default:
        throw invalid_argument("unknown type of shader");
    }

    return unique_ptr<shader>(); // just an overrule
}

}
