#pragma once
#ifndef __GFX_MOVEMENT_HPP__
#define __GFX_MOVEMENT_HPP__

#include <functional>
#include <memory>

namespace gfx{

class movement{
public:
    virtual ~movement() = default;

    virtual void make_move() = 0;
    virtual void set_move_callback(std::function<void()>) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    static std::shared_ptr<movement> create();
};

}

#endif // __GFX_MOVEMENT_HPP__
