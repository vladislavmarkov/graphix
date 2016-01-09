#include "vertex_array_object_counter.h"

namespace gfx{

unsigned int get_vertex_count(){
    static unsigned int count = 0;
    return count++;
}

}
