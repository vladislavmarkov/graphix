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
    space = GLFW_KEY_SPACE, ///< Space key.
    apostrophe = GLFW_KEY_APOSTROPHE, ///< Symbol "'".
    comma = GLFW_KEY_COMMA, ///< Symbol ",".
    minus = GLFW_KEY_MINUS, ///< Symbol "-".
    period = GLFW_KEY_PERIOD, ///< Symbol ".".
    slash = GLFW_KEY_SLASH, ///< Symbol "/".
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
    semicolon = GLFW_KEY_SEMICOLON,
    equal = GLFW_KEY_EQUAL,
    charkey_a = GLFW_KEY_A,
    charkey_b = GLFW_KEY_B,
    charkey_c = GLFW_KEY_C,
    charkey_d = GLFW_KEY_D,
    charkey_e = GLFW_KEY_E,
    charkey_f = GLFW_KEY_F,
    charkey_g = GLFW_KEY_G,
    charkey_h = GLFW_KEY_H,
    charkey_i = GLFW_KEY_I,
    charkey_j = GLFW_KEY_J,
    charkey_k = GLFW_KEY_K,
    charkey_l = GLFW_KEY_L,
    charkey_m = GLFW_KEY_M,
    charkey_n = GLFW_KEY_N,
    charkey_o = GLFW_KEY_O,
    charkey_p = GLFW_KEY_P,
    charkey_q = GLFW_KEY_Q,
    charkey_r = GLFW_KEY_R,
    charkey_s = GLFW_KEY_S,
    charkey_t = GLFW_KEY_T,
    charkey_u = GLFW_KEY_U,
    charkey_v = GLFW_KEY_V,
    charkey_w = GLFW_KEY_W,
    charkey_x = GLFW_KEY_X,
    charkey_y = GLFW_KEY_Y,
    charkey_z = GLFW_KEY_Z,
    left_bracket = GLFW_KEY_LEFT_BRACKET,
    backslash = GLFW_KEY_BACKSLASH,
    right_bracket = GLFW_KEY_RIGHT_BRACKET,
    grave_accent = GLFW_KEY_GRAVE_ACCENT,
    world_1 = GLFW_KEY_WORLD_1,
    world_2 = GLFW_KEY_WORLD_2,
    escape = GLFW_KEY_ESCAPE,
    enter = GLFW_KEY_ENTER,
    tab = GLFW_KEY_TAB,
    backspace = GLFW_KEY_BACKSPACE,
    insert = GLFW_KEY_INSERT,
    del = GLFW_KEY_DELETE,
    right = GLFW_KEY_RIGHT,
    left = GLFW_KEY_LEFT,
    down = GLFW_KEY_DOWN,
    up = GLFW_KEY_UP,
    page_up = GLFW_KEY_PAGE_UP,
    page_down = GLFW_KEY_PAGE_DOWN,
    home = GLFW_KEY_HOME,
    end = GLFW_KEY_END,
    caps_lock = GLFW_KEY_CAPS_LOCK,
    scroll_lock = GLFW_KEY_SCROLL_LOCK,
    num_lock = GLFW_KEY_NUM_LOCK,
    print_screen = GLFW_KEY_PRINT_SCREEN,
    pause = GLFW_KEY_PAUSE,
    f1 = GLFW_KEY_F1,
    f2 = GLFW_KEY_F2,
    f3 = GLFW_KEY_F3,
    f4 = GLFW_KEY_F4,
    f5 = GLFW_KEY_F5,
    f6 = GLFW_KEY_F6,
    f7 = GLFW_KEY_F7,
    f8 = GLFW_KEY_F8,
    f9 = GLFW_KEY_F9,
    f10 = GLFW_KEY_F10,
    f11 = GLFW_KEY_F11,
    f12 = GLFW_KEY_F12,
    f13 = GLFW_KEY_F13,
    f14 = GLFW_KEY_F14,
    f15 = GLFW_KEY_F15,
    f16 = GLFW_KEY_F16,
    f17 = GLFW_KEY_F17,
    f18 = GLFW_KEY_F18,
    f19 = GLFW_KEY_F19,
    f20 = GLFW_KEY_F20,
    f21 = GLFW_KEY_F21,
    f22 = GLFW_KEY_F22,
    f23 = GLFW_KEY_F23,
    f24 = GLFW_KEY_F24,
    f25 = GLFW_KEY_F25,
    kp_0 = GLFW_KEY_KP_0,
    kp_1 = GLFW_KEY_KP_1,
    kp_2 = GLFW_KEY_KP_2,
    kp_3 = GLFW_KEY_KP_3,
    kp_4 = GLFW_KEY_KP_4,
    kp_5 = GLFW_KEY_KP_5,
    kp_6 = GLFW_KEY_KP_6,
    kp_7 = GLFW_KEY_KP_7,
    kp_8 = GLFW_KEY_KP_8,
    kp_9 = GLFW_KEY_KP_9,
    kp_decimal = GLFW_KEY_KP_DECIMAL,
    kp_divide = GLFW_KEY_KP_DIVIDE,
    kp_multiply = GLFW_KEY_KP_MULTIPLY,
    kp_subtract = GLFW_KEY_KP_SUBTRACT,
    kp_add = GLFW_KEY_KP_ADD,
    kp_enter = GLFW_KEY_KP_ENTER,
    kp_equal = GLFW_KEY_KP_EQUAL,
    left_shift = GLFW_KEY_LEFT_SHIFT,
    left_control = GLFW_KEY_LEFT_CONTROL,
    left_alt = GLFW_KEY_LEFT_ALT,
    left_super = GLFW_KEY_LEFT_SUPER,
    right_shift = GLFW_KEY_RIGHT_SHIFT,
    right_control = GLFW_KEY_RIGHT_CONTROL,
    right_alt = GLFW_KEY_RIGHT_ALT,
    right_super = GLFW_KEY_RIGHT_SUPER,
    menu = GLFW_KEY_MENU
};

/// List of key states
enum class state{
    press = GLFW_PRESS, ///< The key or mouse button was pressed.
    release = GLFW_RELEASE, ///< The key or mouse button was released.
    repeat = GLFW_REPEAT ///< The key was held down until it repeated.
};

/** @} */ // end of enumerations

}

}

#endif // __GFX_KEY_H__