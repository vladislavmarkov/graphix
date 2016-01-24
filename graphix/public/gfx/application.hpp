/*! \file gfx/application.hpp */

#pragma once
#ifndef __GFX_APPLICATION_HPP__
#define __GFX_APPLICATION_HPP__

namespace gfx{

class window;

/*! \fn int run(gfx::window &main_window);
    \brief Starts the application. Lifetime is bounded by a lifetime of
    <EM>main_window</EM>.
    \param main_window self-explanatory.
    \returns exit-code of the application.
 */
int run(gfx::window &main_window);

}

#endif // __GFX_APPLICATION_HPP__
