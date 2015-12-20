/*! \file gfx/application.h */

#pragma once
#ifndef __GFX_APPLICATION_H__
#define __GFX_APPLICATION_H__

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

#endif // __GFX_APPLICATION_H__
