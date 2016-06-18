#include <msgpack.hpp>
#include <zmq.hpp>

#include "application.hpp"
#include "window.hpp"

int
main()
{
    auto app    = gfx::application::make_unique();
    auto window = gfx::window::make_unique(*app, "graphix");
    return app->run();
}