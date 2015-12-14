#pragma once
#ifndef __GFX_WINDOW_H__
#define __GFX_WINDOW_H__

#include <memory>
#include <string>

namespace gfx{

class window{
protected:
    window() = default;

public:
    window(const window&) = delete;
    window &operator = (const window&) = delete;

    virtual void set_caption(const std::string&) = 0;
    virtual void set_width(size_t) = 0;
    virtual void set_height(size_t) = 0;

    virtual std::string get_caption() const = 0;
    virtual size_t get_width() const = 0;
    virtual size_t get_height() const = 0;

    static std::unique_ptr<window> create(
        const std::string &caption,
        size_t width,
        size_t height
    );
};

}

#endif // __GFX_WINDOW_H__