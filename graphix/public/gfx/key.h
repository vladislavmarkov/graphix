/*! \file gfx/key.h */

#pragma once
#ifndef __GFX_KEY_H__
#define __GFX_KEY_H__

#include <GLFW/glfw3.h>

namespace gfx{

namespace key{

/** @defgroup enums enumerations
 *  @{
 */

/// List of key codes.
enum class code: int{
    unknown = GLFW_KEY_UNKNOWN, ///< Unknown key code.
    space = GLFW_KEY_SPACE, ///< Space key (key code: 32).
    apostrophe = GLFW_KEY_APOSTROPHE, ///< "'" (key code: 39).
    comma = GLFW_KEY_COMMA, ///< "," (key code: 44).
    minus = GLFW_KEY_MINUS, ///< "-" (key code: 45).
    period = GLFW_KEY_PERIOD, ///< "." (key code: 46).
    slash = GLFW_KEY_SLASH, ///< "/" (key code 47).
    number_0 = GLFW_KEY_0, ///< "0" (key code: 48).
    number_1 = GLFW_KEY_1, ///< "1" (key code: 49).
    number_2 = GLFW_KEY_2, ///< "2" (key code: 50).
    number_3 = GLFW_KEY_3, ///< "3" (key code: 51).
    number_4 = GLFW_KEY_4, ///< "4" (key code: 52).
    number_5 = GLFW_KEY_5, ///< "5" (key code: 53).
    number_6 = GLFW_KEY_6, ///< "6" (key code: 54).
    number_7 = GLFW_KEY_7, ///< "7" (key code: 55).
    number_8 = GLFW_KEY_8, ///< "8" (key code: 56).
    number_9 = GLFW_KEY_9, ///< "9" (key code: 57).
    semicolon = GLFW_KEY_SEMICOLON, ///< ";" (key code: 59).
    equal = GLFW_KEY_EQUAL, ///< "=" (key code: 61).
    charkey_a = GLFW_KEY_A, ///< "a" (key code: 65).
    charkey_b = GLFW_KEY_B, ///< "b" (key code: 66).
    charkey_c = GLFW_KEY_C, ///< "c" (key code: 67).
    charkey_d = GLFW_KEY_D, ///< "d" (key code: 68).
    charkey_e = GLFW_KEY_E, ///< "e" (key code: 69).
    charkey_f = GLFW_KEY_F, ///< "f" (key code: 70).
    charkey_g = GLFW_KEY_G, ///< "g" (key code: 71).
    charkey_h = GLFW_KEY_H, ///< "h" (key code: 72).
    charkey_i = GLFW_KEY_I, ///< "i" (key code: 73).
    charkey_j = GLFW_KEY_J, ///< "j" (key code: 74).
    charkey_k = GLFW_KEY_K, ///< "k" (key code: 75).
    charkey_l = GLFW_KEY_L, ///< "l" (key code: 76).
    charkey_m = GLFW_KEY_M, ///< "m" (key code: 77).
    charkey_n = GLFW_KEY_N, ///< "n" (key code: 78).
    charkey_o = GLFW_KEY_O, ///< "o" (key code: 79).
    charkey_p = GLFW_KEY_P, ///< "p" (key code: 80).
    charkey_q = GLFW_KEY_Q, ///< "q" (key code: 81).
    charkey_r = GLFW_KEY_R, ///< "r" (key code: 82).
    charkey_s = GLFW_KEY_S, ///< "s" (key code: 83).
    charkey_t = GLFW_KEY_T, ///< "t" (key code: 84).
    charkey_u = GLFW_KEY_U, ///< "u" (key code: 85).
    charkey_v = GLFW_KEY_V, ///< "v" (key code: 86).
    charkey_w = GLFW_KEY_W, ///< "w" (key code: 87).
    charkey_x = GLFW_KEY_X, ///< "x" (key code: 88).
    charkey_y = GLFW_KEY_Y, ///< "y" (key code: 89).
    charkey_z = GLFW_KEY_Z, ///< "z" (key code: 90).
    left_bracket = GLFW_KEY_LEFT_BRACKET, ///< "[" (key code: 91).
    backslash = GLFW_KEY_BACKSLASH, ///< "\" (key code: 92).
    right_bracket = GLFW_KEY_RIGHT_BRACKET, ///< "]" (key code: 93).
    grave_accent = GLFW_KEY_GRAVE_ACCENT, ///< "`" (key code: 96).
    world_1 = GLFW_KEY_WORLD_1, ///< non-US #1 (key code: 161).
    world_2 = GLFW_KEY_WORLD_2, ///< non-US #2 (key code: 161).
    escape = GLFW_KEY_ESCAPE, ///< esc (key code: 256).
    enter = GLFW_KEY_ENTER, ///< enter (key code: 257).
    tab = GLFW_KEY_TAB, ///< tab (key code: 258).
    backspace = GLFW_KEY_BACKSPACE, ///< backspace (key code: 259).
    insert = GLFW_KEY_INSERT, ///< insert (key code: 260).
    del = GLFW_KEY_DELETE, ///< delete (key code: 261).
    right = GLFW_KEY_RIGHT, ///< right arrow (key code: 262).
    left = GLFW_KEY_LEFT, ///< left arrow (key code: 263).
    down = GLFW_KEY_DOWN, ///< down arrow (key code: 264).
    up = GLFW_KEY_UP, ///< up arrow (key code: 265).
    page_up = GLFW_KEY_PAGE_UP, ///< pgup (key code: 266).
    page_down = GLFW_KEY_PAGE_DOWN, ///< pgdown (key code: 267).
    home = GLFW_KEY_HOME, ///< home (key code: 268).
    end = GLFW_KEY_END, ///< end (key code: 269).
    caps_lock = GLFW_KEY_CAPS_LOCK, ///< capslock (key code: 280).
    scroll_lock = GLFW_KEY_SCROLL_LOCK, ///< scrollock (key code: 281).
    num_lock = GLFW_KEY_NUM_LOCK, ///< numlock (key code: 282).
    print_screen = GLFW_KEY_PRINT_SCREEN, ///< prtscr (key code: 283).
    pause = GLFW_KEY_PAUSE, ///< pause (key code: 284).
    f1 = GLFW_KEY_F1, ///< F1 (key code: 290).
    f2 = GLFW_KEY_F2, ///< F2 (key code: 291).
    f3 = GLFW_KEY_F3, ///< F3 (key code: 292).
    f4 = GLFW_KEY_F4, ///< F4 (key code: 293).
    f5 = GLFW_KEY_F5, ///< F5 (key code: 294).
    f6 = GLFW_KEY_F6, ///< F6 (key code: 295).
    f7 = GLFW_KEY_F7, ///< F7 (key code: 296).
    f8 = GLFW_KEY_F8, ///< F8 (key code: 297).
    f9 = GLFW_KEY_F9, ///< F9 (key code: 298).
    f10 = GLFW_KEY_F10, ///< F10 (key code: 299).
    f11 = GLFW_KEY_F11, ///< F11 (key code: 300).
    f12 = GLFW_KEY_F12, ///< F12 (key code: 301).
    f13 = GLFW_KEY_F13, ///< F13 (key code: 302).
    f14 = GLFW_KEY_F14, ///< F14 (key code: 303).
    f15 = GLFW_KEY_F15, ///< F15 (key code: 304).
    f16 = GLFW_KEY_F16, ///< F16 (key code: 305).
    f17 = GLFW_KEY_F17, ///< F17 (key code: 306).
    f18 = GLFW_KEY_F18, ///< F18 (key code: 307).
    f19 = GLFW_KEY_F19, ///< F19 (key code: 308).
    f20 = GLFW_KEY_F20, ///< F20 (key code: 309).
    f21 = GLFW_KEY_F21, ///< F21 (key code: 310).
    f22 = GLFW_KEY_F22, ///< F22 (key code: 311).
    f23 = GLFW_KEY_F23, ///< F23 (key code: 312).
    f24 = GLFW_KEY_F24, ///< F24 (key code: 313).
    f25 = GLFW_KEY_F25, ///< F25 (key code: 314).
    kp_0 = GLFW_KEY_KP_0, ///< (key code: 320).
    kp_1 = GLFW_KEY_KP_1, ///< (key code: 321).
    kp_2 = GLFW_KEY_KP_2, ///< (key code: 322).
    kp_3 = GLFW_KEY_KP_3, ///< (key code: 323).
    kp_4 = GLFW_KEY_KP_4, ///< (key code: 324).
    kp_5 = GLFW_KEY_KP_5, ///< (key code: 325).
    kp_6 = GLFW_KEY_KP_6, ///< (key code: 326).
    kp_7 = GLFW_KEY_KP_7, ///< (key code: 327).
    kp_8 = GLFW_KEY_KP_8, ///< (key code: 328).
    kp_9 = GLFW_KEY_KP_9, ///< (key code: 329).
    kp_decimal = GLFW_KEY_KP_DECIMAL, ///< (key code: 330).
    kp_divide = GLFW_KEY_KP_DIVIDE, ///< (key code: 331).
    kp_multiply = GLFW_KEY_KP_MULTIPLY, ///< (key code: 332).
    kp_subtract = GLFW_KEY_KP_SUBTRACT, ///< (key code: 333).
    kp_add = GLFW_KEY_KP_ADD, ///< (key code: 334).
    kp_enter = GLFW_KEY_KP_ENTER, ///< (key code: 335).
    kp_equal = GLFW_KEY_KP_EQUAL, ///< (key code: 336).
    left_shift = GLFW_KEY_LEFT_SHIFT, ///< left shift (key code: 340).
    left_control = GLFW_KEY_LEFT_CONTROL, ///< left control (key code: 341).
    left_alt = GLFW_KEY_LEFT_ALT, ///< left alt (key code: 342).
    left_super = GLFW_KEY_LEFT_SUPER, ///< left super (key code: 343).
    right_shift = GLFW_KEY_RIGHT_SHIFT, ///< right shift (key code: 344).
    right_control = GLFW_KEY_RIGHT_CONTROL, ///< right control (key code: 345).
    right_alt = GLFW_KEY_RIGHT_ALT, ///< right alt (key code: 346).
    right_super = GLFW_KEY_RIGHT_SUPER, ///< right super (key code: 347).
    menu = GLFW_KEY_MENU ///< menu (key code: 348).
};

/// List of key states.
enum class state{
    press = GLFW_PRESS, ///< The key or mouse button was pressed.
    release = GLFW_RELEASE, ///< The key or mouse button was released.
    repeat = GLFW_REPEAT ///< The key was held down until it repeated.
};

/** @} */ // end of enumerations

}

}

#endif // __GFX_KEY_H__
