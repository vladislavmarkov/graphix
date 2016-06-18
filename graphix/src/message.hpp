#pragma once
#ifndef __GRAPHIX_MESSAGE_HPP__
#define __GRAPHIX_MESSAGE_HPP__

#include <msgpack.hpp>
#include <string>
#include <zmq.hpp>

namespace gfx_impl{

class window_impl;

struct message{
    enum msgtype: std::uint8_t{
        undefined = 0,
        attach_window,
        detach_window
    };

    std::uint8_t type;
    std::uint32_t wnd_id;
    std::uint64_t wnd_ptr;

    message(
        std::uint8_t t = 0,
        std::uint32_t id = 0,
        gfx_impl::window_impl *ptr = nullptr
    ):
        type(t), wnd_id(id), wnd_ptr(reinterpret_cast<std::uint64_t>(ptr))
    {}

    message(const message&) = delete;
    message &operator = (const message&) = delete;

    message(message&&) = default;
    message &operator = (message&&) = default;

    MSGPACK_DEFINE(type, wnd_id, wnd_ptr)
};

zmq::message_t wrap(const message&);
message unwrap(const zmq::message_t&);

}

#endif // __GRAPHIX_MESSAGE_HPP__