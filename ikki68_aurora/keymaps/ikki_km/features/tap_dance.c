#include "tap_dance.h"
#include "macro.h"
#include "timer.h"

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else if (state->count == 4) {
        if (state->interrupted || !state->pressed) return TD_QUAD_TAP;
        else return TD_QUAD_HOLD;
    } else return TD_UNKNOWN;
}

// === PLAY ===
static td_tap_t play_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void play_finished(tap_dance_state_t *state, void *user_data) {
    play_tap_state.state = cur_dance(state);
    switch (play_tap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING(SS_TAP(X_MEDIA_PLAY_PAUSE)); break;
        case TD_DOUBLE_TAP: SEND_STRING(SS_TAP(X_MEDIA_NEXT_TRACK)); break;
        case TD_TRIPLE_TAP: SEND_STRING(SS_TAP(X_MEDIA_PREV_TRACK)); break;
        case TD_QUAD_TAP: SEND_STRING(SS_TAP(X_AUDIO_MUTE)); break;
        default: break;
    }
}

void play_reset(tap_dance_state_t *state, void *user_data) {
    switch (play_tap_state.state) {
        // case TD_SINGLE_TAP: unregister_code(KC_X); break;
        // case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        // case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    play_tap_state.state = TD_NONE;
}

// === TASKBAR ===
static td_tap_t taskbar_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void taskbar_finished(tap_dance_state_t *state, void *user_data) {
    taskbar_tap_state.state = cur_dance(state);
    switch (taskbar_tap_state.state) {
        case TD_SINGLE_TAP: send_macro(MAC_TERMINAL); break;
        case TD_DOUBLE_TAP: send_macro(MAC_EDITOR); break;
        case TD_TRIPLE_TAP: SEND_STRING(SS_LGUI("3")); break;
        case TD_QUAD_TAP: SEND_STRING(SS_LGUI("4")); break;
        default: break;
    }
}

void taskbar_reset(tap_dance_state_t *state, void *user_data) {
    switch (taskbar_tap_state.state) {
        // case TD_SINGLE_TAP: unregister_code(KC_X); break;
        // case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        // case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;//SEND_STRING(SS_TAP(X_ENT));
    }
    taskbar_tap_state.state = TD_NONE;
}

// === TIMER ===
static td_tap_t timer_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void timer_each(tap_dance_state_t *state, void *user_data) {
    timer_tap_state.state = cur_dance(state);
    switch (timer_tap_state.state) {
        // case TD_SINGLE_TAP: send_timer(1); break;
        // case TD_DOUBLE_TAP: send_timer(2); break;
        // case TD_TRIPLE_TAP: send_timer(3); break;
        // case TD_QUAD_TAP: send_timer(4); break;
        default: break;
    }
}

void timer_finished(tap_dance_state_t *state, void *user_data) {
    timer_tap_state.state = cur_dance(state);
    switch (timer_tap_state.state) {
        case TD_SINGLE_TAP: send_timer(1); break;
        case TD_DOUBLE_TAP: send_timer(2); break;
        case TD_TRIPLE_TAP: send_timer(3); break;
        case TD_QUAD_TAP: send_timer(4); break;
        default: break;
    }
}

void timer_reset(tap_dance_state_t *state, void *user_data) {
    switch (taskbar_tap_state.state) {
        // case TD_SINGLE_TAP: unregister_code(KC_X); break;
        // case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        // case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;//SEND_STRING(SS_TAP(X_ENT));
    }
    timer_tap_state.state = TD_NONE;
}

// === MACRO-TAPS ===
static td_tap_t macro_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void macro_finished(tap_dance_state_t *state, void *user_data) {
    macro_tap_state.state = cur_dance(state);
    switch (macro_tap_state.state) {
        case TD_SINGLE_TAP: send_macro(MAC_SEARCH); break;
        case TD_DOUBLE_TAP: send_macro(MAC_SCREENSHOT); break;
        // case TD_TRIPLE_TAP: send_macro(MAC_SEARCH); break;
        // case TD_QUAD_TAP: send_macro(MAC_SEARCH); break;
        default: break;
    }
}

void macro_reset(tap_dance_state_t *state, void *user_data) {
    switch (macro_tap_state.state) {
        default: break;
    }
    macro_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [PLAY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, play_finished, taskbar_reset),
    [TASKBAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, taskbar_finished, taskbar_reset),
    [TIMER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, timer_finished, timer_reset),
    [MACRO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, macro_finished, macro_reset)
};
