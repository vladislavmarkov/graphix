#pragma once
#ifndef __GRAPHIX_APPLICATION_HPP__
#define __GRAPHIX_APPLICATION_HPP__

#include <memory>

namespace gfx{

class application{
public:
    application() = default;
    application(const application&) = delete;
    application & operator = (const application&) = delete;
    virtual ~application() = default;
    virtual int run() = 0;

    static std::shared_ptr<application> make_shared();
    static std::unique_ptr<application> make_unique();
};

}

#endif // __GRAPHIX_APPLICATION_HPP__
