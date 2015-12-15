#pragma once
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

namespace gfx{

class window;

int run(gfx::window &main_window);
/*!<
Starts the application. Lifetime is bounded by a lifetime of
<EM>main_window</EM>.
\param main_window self-explanatory.
\returns exit-code of the application.
 */

}

#endif // __APPLICATION_H__