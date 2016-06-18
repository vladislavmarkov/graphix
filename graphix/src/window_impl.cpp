#include <SDL2/SDL.h>

// temp
#include <iostream>
// temp

#include "error.hpp"
#include "window.hpp"
#include "window_impl.hpp"

namespace gfx{

std::shared_ptr<window> window::make_shared(
    application &app,
    const std::string &caption,
    int32_t pos_x, int32_t pos_y,
    uint32_t width, uint32_t height
){
    return std::shared_ptr<window>{
        std::make_shared<gfx_impl::window_impl>(
            static_cast<gfx_impl::application_impl&>(app),
            caption, pos_x, pos_y, width, height
        )
    };
}

std::unique_ptr<window> window::make_unique(
    application &app,
    const std::string &caption,
    int32_t pos_x, int32_t pos_y,
    uint32_t width, uint32_t height
){
    return std::unique_ptr<window>{
        std::make_unique<gfx_impl::window_impl>(
            static_cast<gfx_impl::application_impl&>(app),
            caption, pos_x, pos_y, width, height
        )
    };
}

}

namespace gfx_impl{

window_impl::window_impl(
    application_impl &app,
    const std::string &caption,
    int32_t pos_x, int32_t pos_y,
    uint32_t width, uint32_t height
):
    _app(app),
    _wndhandle(
        SDL_CreateWindow(
            caption.c_str(),
            pos_x == -1 ? SDL_WINDOWPOS_UNDEFINED : pos_x,
            pos_y == -1 ? SDL_WINDOWPOS_UNDEFINED : pos_y,
            width ? width : 640,
            height ? height : 480,
            SDL_WINDOW_SHOWN
        ),
        SDL_DestroyWindow
    ),
    _wndsurface(SDL_GetWindowSurface(_wndhandle.get()), SDL_FreeSurface),
    _caption(caption)
{
    if (!_wndhandle || !_wndsurface)
        throw gfx::error("failed to initialize window");

    _app.attach_window(this);

    // fill the surface white
    SDL_FillRect(
        _wndsurface.get(),
        nullptr,
        SDL_MapRGB(_wndsurface->format, 0xff, 0xff, 0xff)
    );

    // update the surface
    SDL_UpdateWindowSurface(_wndhandle.get());
}

window_impl::~window_impl(){
    _app.detach_window(this);
}

uint32_t window_impl::get_id() const{
    return SDL_GetWindowID(_wndhandle.get());
}

void window_impl::handle_message(const SDL_WindowEvent&){
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
}

}
