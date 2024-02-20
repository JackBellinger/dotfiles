/*
Copyright 2021 wuquestudio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#define TAPPING_TERM_PER_KEY
//#define PERMISSIVE_HOLD

#define NO_MUSIC_MODE

// #define UNICODE_SELECTED_MODES UC_WIN

// Firmware Size optimizations
#define LAYER_STATE_8BIT

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

// these rgb modes seem to only be compiled if they're used, undef doesn't reduce avr size
// RGBLIGHT_MODE_STATIC_LIGHT is always defined
// #undef RGBLIGHT_EFFECT_BREATHING
// #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
// #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #undef RGBLIGHT_EFFECT_SNAKE
// #undef RGBLIGHT_EFFECT_KNIGHT
// #undef RGBLIGHT_EFFECT_CHRISTMAS
// #undef RGBLIGHT_EFFECT_STATIC_GRADIENT
// #undef RGBLIGHT_EFFECT_RGB_TEST
// #undef RGBLIGHT_EFFECT_ALTERNATING
// #undef RGBLIGHT_EFFECT_TWINKLE