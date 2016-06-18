#pragma once
#ifndef __GRAPHIX_ERROR_HPP__
#define __GRAPHIX_ERROR_HPP__

#include <stdexcept>

namespace gfx {

class error : public std::exception {
    const std::string _errmsg;

  public:
    explicit error(const std::string& errmsg) : _errmsg(errmsg){};
    ~error() override = default;
};
}

#endif // __GRAPHIX_ERROR_HPP__
