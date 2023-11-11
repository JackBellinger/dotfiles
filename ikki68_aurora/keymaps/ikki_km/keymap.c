/* Copyright 2021 wuquestudio
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "features/layer_lock.h"

#define CAPS_WORD_INVERT_ON_SHIFT

typedef struct {
    bool is_press_action;
    int state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    TRIPLE_TAP = 5,
    TRIPLE_HOLD = 6
};

enum custom_keycodes {
    MAC_SELWORD = SAFE_RANGE,
    LLOCK,
    MAC_UNICODE,
    MAC_SEARCH,
    MAC_TERMINAL,
    MAC_QMKURL,
    MAC_MY_OTHER_MACRO,
};

#ifdef UCIS_ENABLE
// 3 codepoints at most, otherwise increase UCIS_MAX_CODE_POINTS
const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop", 0x1F4A9),                // 💩
    UCIS_SYM("rofl", 0x1F923),                // 🤣
    UCIS_SYM("look", 0x0CA0, 0x005F, 0x0CA0)  // ಠ_ಠ
);
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
    switch (keycode) {
        case MAC_SELWORD:  // Selects the current word under the cursor.
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
                // Mac users, change LCTL to LALT:
                // SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
            }
            return false;

        case MAC_UNICODE:  // Selects the current word under the cursor.
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
                // Mac users, change LCTL to LALT:
                // SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
            }
            return false;
        case MAC_SEARCH:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING(SS_LCTL("c") SS_DELAY(100) SS_LCTL(SS_LALT("u")) SS_DELAY(100) SS_LCTL("l") SS_LCTL("v") "\a\n");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case MAC_TERMINAL:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING(SS_LGUI("1"));
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case MAC_QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://jackbellinger.github.io/blog");
            } else {
                // when keycode QMKURL is released
            }
            break;

        case MAC_MY_OTHER_MACRO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ac")); // selects all and copies
            }
            break;
    }
    return true;
};


// Matrix diagram for Wuque Ikki68 Aurora
/**
```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐┌───┬───┐     ┌───────┐
│00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │2D ││0E │0F │     │0D     │ 2u Backspace
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤├───┼───┤     └─┬─────┤
│10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D   ││1E │1F │       │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤└───┴───┘    ┌──┴┐1D  │ ISO Enter
│20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C      │             │2C │    │
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤┌───┐        └───┴────┘
│30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3C    │3D ││3E │
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴┬──┴┼───┼───┐
│40  │41  │42  │46                      │4A  │4B  │4C  │ │4D │4E │4F │
└────┴────┴────┴────────────────────────┴────┴────┴────┘ └───┴───┴───┘
┌────────┐                                       ┌──────────┐
│30      │ 2.25u LShift             2.75u RShift │3C        │
└────────┘                                       └──────────┘
┌────┬────┬────┬────────┬────┬──────────┬────┬────┬────┐
│40  │41  │42  │44      │46  │48        │4A  │4B  │4C  │ Split Space
└────┴────┴────┴────────┴────┴──────────┴────┴────┴────┘
```
*/

// KC_NO used in empty split key options
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC, KC_MPLY, KC_VOLU,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, MAC_TERMINAL, KC_VOLD,
        CW_TOGG, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, KC_UP,
        KC_LCTL, KC_LGUI, SC_LAPO, KC_NO, KC_SPC, KC_NO, SC_RAPC, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),                           //space          space
    [1] = LAYOUT_all(
        QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, QK_LEAD, KC_DEL, RGB_TOG, KC_MNXT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WSCH, RGB_MOD, KC_MPRV,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LLOCK,
        _______, KC_NO, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO, KC_PGUP,
        _______, _______, _______, KC_NO, _______, KC_NO, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
};

void keyboard_post_init_user(void) {
    // Call the post init code.
    //rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    //rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
    #ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // sets mode to rainbow swirlwithout saving
    #endif
}

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_led_indicators.md#example-of-user-led-update-implementation
#ifdef AUDIO_ENABLE
    float caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
    float caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);
    float leader_start_song[][2] = SONG(ONE_UP_SOUND);
    float leader_succeed_song[][2] = SONG(ALL_STAR);
    float leader_fail_song[][2] = SONG(RICK_ROLL);
#endif

bool led_update_user(led_t led_state) {
    #ifdef AUDIO_ENABLE
        static uint8_t caps_state = 0;
        if (caps_state != led_state.caps_lock) {
            led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
            caps_state = led_state.caps_lock;
        }
    #endif
    return true;
}



#ifdef LEADER_ENABLE
    #define LEADER_PER_KEY_TIMING
    #define LEADER_TIMEOUT 1000

    void leader_start_user(void) {
    #ifdef AUDIO_ENABLE
        PLAY_SONG(leader_start_song);
    #endif
    }

    void leader_end_user(void) {
        #ifdef AUDIO_ENABLE
        bool did_leader_succeed = true;
        #endif
        #ifdef UCIS_ENABLE
            if (leader_sequence_one_key(KC_U)) {
                ucis_start();
            }
        #endif
        if ( leader_sequence_one_key(KC_S)) {
            SEND_STRING("save");
        }
        else if (leader_sequence_one_key(KC_H)) {
            send_unicode_string("ᕕ( ᐛ )ᕗ");  // happy
        }
        else if (leader_sequence_one_key(KC_D)) {
            send_unicode_string("ಠ_ಠ");  // disapproval
        }
        else if (leader_sequence_one_key(KC_L)) {
            send_unicode_string("( ͡° ͜ʖ ͡°)");  // lenny
        }
        // else if (leader_sequence_one_key(KC_S)) {
        //     send_unicode_string("¯\\_(ツ)_/¯");  // shrug
        // }
        // tableflip (LEADER - TF)
        else if (leader_sequence_two_keys(KC_T, KC_F)) {
            //set_unicode_input_mode(UNICODE_MODE_LINUX);
            //send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
            // UC(0x0028); //UC(30CE) UC(0CA0) UC(75CA) UC(0CA0) UC(0029) UC(30CE) UC(5F61) UC(253B) UC(2501) UC(253B));
            // send_unicode_string("(╯°□°）╯︵ ┻━┻");
            send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
            // if(get_unicode_input_mode() == UC_WINC) {
            //     tap_code(KC_ENT);
            // }
        }
        // untableflip
        else if (leader_sequence_three_keys(KC_U, KC_T, KC_F)) {
            //set_unicode_input_mode(UNICODE_MODE_LINUX);
            //send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
            send_unicode_string("┬─┬ノ( º _ ºノ)");
        }
        // else if (leader_sequence_four_keys(KC_S, KC_R, KC_C, KC_H)) {
        //     register_code(MAC_SEARCH);
        // }
        else {
            #ifdef AUDIO_ENABLE
            did_leader_succeed = false;
            #endif
        }
        #ifdef AUDIO_ENABLE
            if (did_leader_succeed) {
                PLAY_SONG(leader_succeed_song);
            } else {
                PLAY_SONG(leader_fail_song);
            }
        #endif
    }
#endif