#pragma once
#ifndef __GFX_WINDOW_H__
#define __GFX_WINDOW_H__

#include <functional>
#include <gfx/key.h>
#include <memory>
#include <string>

namespace gfx{

class scene;

/*! \class window
    \relates window
    \brief Represents a [window](@ref window) <B><EM>interface</EM></B>.
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
    Sets [window](@ref window)'s caption.
     */

    virtual void set_width(int) = 0;
    /*!<
    Sets [window](@ref window)'s width.
     */

    virtual void set_height(int) = 0;
    /*!<
    Sets [window](@ref window)'s height.
     */

    virtual std::string get_caption() const = 0;
    /*!<
    Retrieves [window](@ref window)'s caption.
     */

    virtual int get_width() const = 0;
    /*!<
    Retrieves [window](@ref window)'s width.
     */

    virtual int get_height() const = 0;
    /*!<
    Retrieves [window](@ref window)'s height.
     */

    virtual void close() = 0;
    /*!<
    Closes the [window](@ref window) and terminates an application if closed
    [window](@ref window) was the main [window](@ref window).
     */

    virtual void set_key_reaction(
        const std::function<void(window&, key::code, key::state)> &key_func
    ) = 0;
    /*!<
    Sets a key reaction callback function.
    \param key_func self-explanatory.
     */

    virtual void set_resize_reaction(
        const std::function<void(window&, int, int)> &resize_func
    ) = 0;
    /*!<
    Sets a resize reaction callback function.
    \param resize_func self-explanatory.
     */

    virtual void set_refresh_reaction(
        const std::function<void(window&)> &draw_func
    ) = 0;
    /*!<
    Sets a refresh reaction callback function.
    \param draw_func self-explanatory.
     */

    virtual void add(std::shared_ptr<scene> scene_obj) = 0;
    /*!<
    Adds a scene to a window.
    \param scene_obj scene to be added.
     */

    virtual void hide_mouse_cursor() const = 0;
    /*!<
    Hides mouse cursor.
     */

    virtual void show_mouse_cursor() const = 0;
    /*!<
    Shows mouse cursor.
     */

    static std::unique_ptr<window> create(
        const std::string &caption,
        int width = 0,
        int height = 0
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
