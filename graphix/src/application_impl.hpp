#pragma once
#ifndef __GRAPHIX_APPLICATION_IMPL_HPP__
#define __GRAPHIX_APPLICATION_IMPL_HPP__

#include "application.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>
#include <zmq.hpp>

union SDL_Event;

namespace gfx_impl {

class window_impl;

class application_impl final : public gfx::application {
    std::unordered_map<std::uint32_t, window_impl*> _wnd_ptrs;

    const Uint32 _attach_window_msg_type;
    const Uint32 _detach_window_msg_type;

    void register_messages();

    void manage_pending_windows();

    void handle_attach_detach_event(const SDL_Event*);

    bool handle_event(const SDL_Event*); // return true when done

public:
    application_impl();
    ~application_impl() final;

    application_impl(const application_impl&) = delete;

    application_impl& operator=(const application_impl&) = delete;

    int run() final;

    void attach_window(window_impl*);

    void detach_window(window_impl*);
};
}

#endif // __GRAPHIX_APPLICATION_IMPL_HPP__
