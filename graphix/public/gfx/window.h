#pragma once
#ifndef __GFX_WINDOW_H__
#define __GFX_WINDOW_H__

#include <memory>
#include <string>

namespace gfx{

/*!
\relates window
Represents a [window](@ref window) <B><EM>interface</EM></B>.
 */
class window{
protected:
    window() = default;

public:
    window(const window&) = delete;
    /*!<
    Deleted.
     */
    window &operator = (const window&) = delete;
    /*!<
    Deleted.
     */

    virtual ~window() = default;
    /*!<
    Default destructor.
     */

    virtual void set_caption(const std::string&) = 0;
    /*!<
    Sets window's caption.
     */

    virtual void set_width(size_t) = 0;
    /*!<
    Sets window's width.
     */

    virtual void set_height(size_t) = 0;
    /*!<
    Sets window's height.
     */

    virtual std::string get_caption() const = 0;
    /*!<
    Retrieves window's caption.
     */

    virtual size_t get_width() const = 0;
    /*!<
    Retrieves window's width.
     */

    virtual size_t get_height() const = 0;
    /*!<
    Retrieves window's height.
     */

    static std::unique_ptr<window> create(
        const std::string &caption,
        size_t width = 0,
        size_t height = 0
    );
    /*!<
    Creates a [window](@ref window) with specified parameters and returns a
    [std::unique_ptr](http://ru.cppreference.com/w/cpp/memory/unique_ptr) to a
    created [window](@ref window) object.
    \param caption caption of the [window](@ref window). Can not be empty.
    \param width can be ignored to use a default value.
    \param height can be ignored to use a default value.
     */
};

}

#endif // __GFX_WINDOW_H__
