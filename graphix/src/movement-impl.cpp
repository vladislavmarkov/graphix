#include <functional>

#include "movement-impl.hpp"

using std::function;

namespace gfx{

void movement_impl::make_move(){ if (active_) move_(); }

void movement_impl::set_move_callback(function<void()> mv){
    move_ = std::move(mv);
}

void movement_impl::start(){ active_ = true; }

void movement_impl::stop(){ active_ = false; }

}
