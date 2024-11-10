#include "tap_dance.h"
// #include "../custom_keycodes.h" //set_oneshot_layer(FUNCS...
#if MACRO_ENABLE
#include "macro.h" //send_macro
#endif

#if TIMER_ENABLE
#include "timer.h" //send_timer
#endif

#if TDM_ENABLE
#include "temporal_dynamic_macro.h" //tdm_state_transition
#endif

td_state_t cur_dance(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (!state->pressed) return TD_SINGLE_TAP;
		if (state->interrupted) return TD_TAP_INTERRUPT;
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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	#define TAPDANCE(a, b) \
		case TD(a): return b;
	TD_TABLE
	#undef TAPDANCE
		default:
			return TAPPING_TERM;
	}
}
#define TAPDANCE(a, b) \
    static td_tap_t a ## _tap_state = { .is_press_action = true, .state = TD_NONE };
TD_TABLE
#undef TAPDANCE


// === PLAY ===
#if EXTRAKEY_ENABLE
void PLAY_finished(tap_dance_state_t *state, void *user_data) {
	PLAY_tap_state.state = cur_dance(state);
	switch (PLAY_tap_state.state) {
		case TD_SINGLE_TAP: SEND_STRING(SS_TAP(X_MEDIA_PLAY_PAUSE)); break;
		case TD_DOUBLE_TAP: SEND_STRING(SS_TAP(X_MEDIA_NEXT_TRACK)); break;
		case TD_TRIPLE_TAP: SEND_STRING(SS_TAP(X_MEDIA_PREV_TRACK)); break;
		case TD_QUAD_TAP: SEND_STRING(SS_TAP(X_AUDIO_MUTE)); break;
		default: break;
	}
}

void PLAY_reset(tap_dance_state_t *state, void *user_data) {
	switch (PLAY_tap_state.state) {
		// case TD_SINGLE_TAP: unregister_code(KC_X); break;
		// case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
		// case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
		// case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
		// case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
		default: break;
	}
	PLAY_tap_state.state = TD_NONE;
}
#endif
// === TASKBAR ===
#if MACRO_ENABLE
void TASKBAR_finished(tap_dance_state_t *state, void *user_data) {
	TASKBAR_tap_state.state = cur_dance(state);
	switch (TASKBAR_tap_state.state) {
		case TD_SINGLE_TAP: send_macro(MAC_EDITOR, NULL); break;
		case TD_DOUBLE_TAP: send_macro(MAC_TERMINAL, NULL); break;
		case TD_TRIPLE_TAP: SEND_STRING(SS_LGUI("3")); break;
		case TD_QUAD_TAP: SEND_STRING(SS_LGUI("4")); break;
		default: break;
	}
}

void TASKBAR_reset(tap_dance_state_t *state, void *user_data) {
	switch (TASKBAR_tap_state.state) {
		// case TD_SINGLE_TAP: unregister_code(KC_X); break;
		// case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
		// case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
		// case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
		// case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
		default: break;//SEND_STRING(SS_TAP(X_ENT));
	}
	TASKBAR_tap_state.state = TD_NONE;
}
// === MACRO-TAPS ===
void MACRO_finished(tap_dance_state_t *state, void *user_data) {
	MACRO_tap_state.state = cur_dance(state);
	switch (MACRO_tap_state.state) {
		case TD_SINGLE_TAP: send_macro(MAC_SEARCH, NULL); break;
		case TD_DOUBLE_TAP: send_macro(MAC_SCREENSHOT, NULL); break;
		// case TD_TRIPLE_TAP: send_macro(MAC_SEARCH, NULL); break;
		// case TD_QUAD_TAP: send_macro(MAC_SEARCH, NULL); break;
		default: break;
	}
}

void MACRO_reset(tap_dance_state_t *state, void *user_data) {
	switch (MACRO_tap_state.state) {
		default: break;
	}
	MACRO_tap_state.state = TD_NONE;
}
#endif
// === TIMER ===
#if TIMER_ENABLE
void TIMER_each(tap_dance_state_t *state, void *user_data) {
	TIMER_tap_state.state = cur_dance(state);
	switch (TIMER_tap_state.state) {
		// case TD_SINGLE_TAP: send_timer(1); break;
		// case TD_DOUBLE_TAP: send_timer(2); break;
		// case TD_TRIPLE_TAP: send_timer(3); break;
		// case TD_QUAD_TAP: send_timer(4); break;
		default: break;
	}
}

void TIMER_finished(tap_dance_state_t *state, void *user_data) {
	TIMER_tap_state.state = cur_dance(state);
	switch (TIMER_tap_state.state) {
		case TD_SINGLE_TAP: send_timer(1); break;
		case TD_DOUBLE_TAP: send_timer(2); break;
		case TD_TRIPLE_TAP: send_timer(3); break;
		case TD_QUAD_TAP: send_timer(4); break;
		default: break;
	}
}

void TIMER_reset(tap_dance_state_t *state, void *user_data) {
	switch (TIMER_tap_state.state) {
		// case TD_SINGLE_TAP: unregister_code(KC_X); break;
		// case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
		// case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
		// case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
		// case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
		default: break;//SEND_STRING(SS_TAP(X_ENT));
	}
	TIMER_tap_state.state = TD_NONE;
}
#endif
// === Temporal Dynamic Macros ===
#if TDM_ENABLE
// 	TDM_RECORD, needs it's own key (has built in tap handling)
// 	TDM_DELAY, yes
// 	TDM_END, yes
// 	TDM_PLAY, built in tapping
// 	TDM_LOOP, built in tapping
void TDM_D_finished(tap_dance_state_t *state, void *user_data) {
	TDM_D_tap_state.state = cur_dance(state);
	switch (TDM_D_tap_state.state) {
		case TD_SINGLE_TAP: process_temporal_dynamic_macro(TDM_DELAY, NULL); break;
		case TD_DOUBLE_TAP: process_temporal_dynamic_macro(TDM_END, NULL); break;
		default: break;
	}
}

void TDM_D_reset(tap_dance_state_t *state, void *user_data) {
	switch (TDM_D_tap_state.state) {
		// case TD_SINGLE_TAP: unregister_code(KC_X); break;
		// case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
		// case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
		// case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
		// case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
		default: break;
	}
	TDM_D_tap_state.state = TD_NONE;
}
#endif
// === CTRL-TAPS ===

void CTRL_finished(tap_dance_state_t *state, void *user_data) {
	CTRL_tap_state.state = cur_dance(state);
	switch (CTRL_tap_state.state) {
		case TD_SINGLE_TAP: //SEND_STRING("1");
			set_oneshot_layer(1, ONESHOT_START); break;
		case TD_TAP_INTERRUPT: //SEND_STRING("1i");
		case TD_SINGLE_HOLD : //SEND_STRING("1h"); 
			register_code(KC_LCTL); break;
		case TD_DOUBLE_TAP: //SEND_STRING("2"); 
			set_oneshot_layer(1, ONESHOT_START); set_oneshot_layer(1, ONESHOT_PRESSED); break;
		case TD_DOUBLE_HOLD: //SEND_STRING("2h"); 
			register_code(KC_LCTL); layer_on(1); break;
		// case TD_TRIPLE_TAP: send_macro(MAC_SEARCH, NULL); break;
		// case TD_QUAD_TAP: send_macro(MAC_SEARCH, NULL); break;
		default: break;
	}
}

void CTRL_reset(tap_dance_state_t *state, void *user_data) {
	switch (CTRL_tap_state.state) {
		case TD_SINGLE_TAP: //SEND_STRING("1 d");
			clear_oneshot_layer_state(ONESHOT_PRESSED); break;
		case TD_TAP_INTERRUPT: //SEND_STRING("1i d");
		case TD_SINGLE_HOLD : //SEND_STRING("1h d"); 
			unregister_code(KC_LCTL); break;
		case TD_DOUBLE_TAP: //SEND_STRING("2 d"); 
			clear_oneshot_layer_state(ONESHOT_PRESSED); break;
		case TD_DOUBLE_HOLD: //SEND_STRING("2h d");
			layer_off(1); unregister_code(KC_LCTL); break;
	}
	CTRL_tap_state.state = TD_NONE;
}

// === ALT-TAPS ===

void ALT_finished(tap_dance_state_t *state, void *user_data) {
	ALT_tap_state.state = cur_dance(state);
	switch (ALT_tap_state.state) {
		case TD_SINGLE_TAP: set_oneshot_layer(1, ONESHOT_START);  break;
		case TD_TAP_INTERRUPT:
		case TD_SINGLE_HOLD : register_code(KC_LALT); break;
		case TD_DOUBLE_TAP: set_oneshot_layer(1, ONESHOT_START); set_oneshot_layer(FUNCS, ONESHOT_PRESSED); break;
		case TD_DOUBLE_HOLD: register_code(KC_LALT); layer_on(1); break;
		// case TD_TRIPLE_TAP: send_macro(MAC_SEARCH, NULL); break;
		// case TD_QUAD_TAP: send_macro(MAC_SEARCH, NULL); break;
		default: break;
	}
}

void ALT_reset(tap_dance_state_t *state, void *user_data) {
	switch (ALT_tap_state.state) {
		case TD_SINGLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
		case TD_TAP_INTERRUPT:
		case TD_SINGLE_HOLD : unregister_code(KC_LALT); break;
		case TD_DOUBLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
		case TD_DOUBLE_HOLD: layer_off(1); unregister_code(KC_LALT); break;
	}
	ALT_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
#if EXTRAKEY_ENABLE
	[PLAY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, PLAY_finished, PLAY_reset),
#endif
#if MACRO_ENABLE
	[TASKBAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TASKBAR_finished, TASKBAR_reset),
	[MACRO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, MACRO_finished, MACRO_reset),
#endif
#if TIMER_ENABLE
	[TIMER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TIMER_finished, TIMER_reset),
#endif
#if TDM_ENABLE
	[TDM_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TDM_D_finished, TDM_D_reset),
#endif
	[CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, CTRL_finished, CTRL_reset),
	[ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ALT_finished, ALT_reset)
};

