#pragma once
#ifndef __GRAPHIX_WINDOW_IMPL_HPP__
#define __GRAPHIX_WINDOW_IMPL_HPP__

#include <memory>
#include <SDL2/SDL.h>

#include "application_impl.hpp"
#include "window.hpp"

namespace gfx_impl{

class window_impl: public gfx::window{
    application_impl &_app;

    std::unique_ptr<
        SDL_Window,
        void(*)(SDL_Window*)
    > _wndhandle;

    std::unique_ptr<
        SDL_Surface,
        void(*)(SDL_Surface*)
    > _wndsurface;

    std::string _caption;

public:
    window_impl(const window_impl&) = delete;
    window_impl & operator = (const window_impl&) = delete;

    window_impl(
        application_impl&,
        const std::string&,
        std::int32_t,
        std::int32_t,
        std::uint32_t,
        std::uint32_t
    );

    ~window_impl() final;
    std::uint32_t get_id() const;
    void handle_message(const SDL_WindowEvent&);
};

}

#endif // __GRAPHIX_WINDOW_IMPL_HPP__
