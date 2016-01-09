#pragma once
#ifndef __GFX_MOVEMENT_IMPL_H__
#define __GFX_MOVEMENT_IMPL_H__

#include <gfx/movement.h>

namespace gfx{

class movement_impl: public movement{
    std::function<void()> move_{[](){}};
    bool active_{false};

public:
    void make_move() override;
    void set_move_callback(std::function<void()>) override;
    void start() override;
    void stop() override;
};

}

#endif // __GFX_MOVEMENT_IMPL_H__
