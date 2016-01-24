#include <gfx/movement.hpp>

#include "movement-impl.hpp"

using std::shared_ptr;

namespace gfx{

shared_ptr<movement> movement::create(){
    return shared_ptr<movement>(new movement_impl());
}

}
