#include "application_impl.hpp"

#include "application.hpp"
#include "error.hpp"
#include "message.hpp"
#include "window_impl.hpp"
#include <SDL2/SDL.h>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <zmq.hpp>

namespace gfx {

std::shared_ptr<application>
application::make_shared()
{
    return std::shared_ptr<application>{
        std::make_shared<gfx_impl::application_impl>()};
}

std::unique_ptr<application>
application::make_unique()
{
    return std::unique_ptr<application>{
        std::make_unique<gfx_impl::application_impl>()};
}
}

namespace gfx_impl {

void
application_impl::manage_pending_windows()
{
    SDL_PumpEvents();
    SDL_Event event;
    while (SDL_PeepEvents(
        &event,
        1,
        SDL_GETEVENT,
        _attach_window_msg_type,
        _detach_window_msg_type)) {
        handle_attach_detach_event(&event);
    }
}

namespace {

void
do_attach_window(
    std::unordered_map<std::uint32_t, window_impl*>& wnd_ptrs,
    std::uint32_t id,
    window_impl*  ptr)
{
    auto wnd_rec = wnd_ptrs.find(id);
    if (wnd_rec != wnd_ptrs.end()) {
        throw gfx::error(
            std::string("can't attach window with id ") + std::to_string(id) +
            " twice");
    }

    wnd_ptrs.insert(std::make_pair(id, ptr));
}

void
do_detach_window(
    std::unordered_map<std::uint32_t, window_impl*>& wnd_ptrs, std::uint32_t id)
{
    auto wnd_rec = wnd_ptrs.find(id);
    if (wnd_rec == wnd_ptrs.end()) {
        throw gfx::error(
            std::string("there is no window with id ") + std::to_string(id));
    }
    wnd_ptrs.erase(wnd_rec);
}
}

void
application_impl::handle_attach_detach_event(const SDL_Event* event)
{
    assert(event);

    if (event->type == _attach_window_msg_type) {
        do_attach_window(
            _wnd_ptrs,
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(event->user.data1)),
            reinterpret_cast<window_impl*>(event->user.data2));
    } else if (event->type == _detach_window_msg_type) {
        do_detach_window(
            _wnd_ptrs,
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(event->user.data1)));
    } else {
        throw gfx::error(
            "event expected to be of type attach / detach, but it's not");
    }
}

void
application_impl::register_messages()
{
    const_cast<Uint32&>(_attach_window_msg_type) = SDL_RegisterEvents(1);
    const_cast<Uint32&>(_detach_window_msg_type) = SDL_RegisterEvents(1);
}

bool
application_impl::handle_event(const SDL_Event* event)
{
    assert(event);

    switch (event->type) {
    case SDL_WINDOWEVENT:
        _wnd_ptrs.at(static_cast<std::uint32_t>(event->window.windowID))
            ->handle_message(event->window);
        break;

    case SDL_QUIT: return true;

    default:
        if (event->type == _attach_window_msg_type) {
            do_attach_window(
                _wnd_ptrs,
                static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(event->user.data1)),
                reinterpret_cast<window_impl*>(event->user.data2));
        } else if (event->type == _detach_window_msg_type) {
            do_detach_window(
                _wnd_ptrs,
                static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(event->user.data1)));
        }
        break;
    }

    return false;
}

application_impl::application_impl()
    : _attach_window_msg_type(0), _detach_window_msg_type(0)
{
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        throw gfx::error("failed to initialize SDL");
    }
    register_messages();
}

application_impl::~application_impl() { SDL_Quit(); }
int
application_impl::run()
{
    manage_pending_windows();

    SDL_Event e{};
    bool      done{false};

    while (!done) {
        if (SDL_WaitEvent(&e) != 0) {
            done = handle_event(&e);
        }
        std::this_thread::yield();
    }

    return EXIT_SUCCESS;
}

void
application_impl::attach_window(window_impl* wnd)
{
    assert(wnd);
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type       = _attach_window_msg_type;
    event.user.code  = 1;
    event.user.data1 = reinterpret_cast<void*>(wnd->get_id());
    event.user.data2 = reinterpret_cast<void*>(wnd);
    SDL_PushEvent(&event);
}

void
application_impl::detach_window(window_impl* wnd)
{
    assert(wnd);
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type       = _detach_window_msg_type;
    event.user.code  = 1;
    event.user.data1 = reinterpret_cast<void*>(wnd->get_id());
    event.user.data2 = nullptr;
    SDL_PushEvent(&event);
}
}
