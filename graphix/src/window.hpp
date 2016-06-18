#pragma once
#ifndef __GRAPHIX_WINDOW_HPP__
#define __GRAPHIX_WINDOW_HPP__

#include <memory>
#include <string>

#include "application.hpp"

namespace gfx {

class window {
public:
    window()              = default;
    window(const window&) = delete;
    window& operator=(const window&) = delete;
    virtual ~window()                = default;

    static std::shared_ptr<window> make_shared(
        application&,
        const std::string&,
        std::int32_t  pos_x  = -1,
        std::int32_t  pos_y  = -1,
        std::uint32_t width  = 0,
        std::uint32_t height = 0);

    static std::unique_ptr<window> make_unique(
        application&,
        const std::string&,
        std::int32_t  pos_x  = -1,
        std::int32_t  pos_y  = -1,
        std::uint32_t width  = 0,
        std::uint32_t height = 0);
};
}

#endif // __GRAPHIX_WINDOW_HPP__
