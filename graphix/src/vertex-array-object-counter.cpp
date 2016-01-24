#include "vertex-array-object-counter.hpp"

namespace gfx{

unsigned int get_vertex_count(){
    static unsigned int count = 0;
    return count++;
}

}
