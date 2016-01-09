#include <gfx/movement.h>

#include "movement_impl.h"

using std::shared_ptr;

namespace gfx{

shared_ptr<movement> movement::create(){
    return shared_ptr<movement>(new movement_impl());
}

}
