#pragma once
#include "quantum.h"

/* Define the tap dances (td name, td tapping term (length between taps)) */
#define TD_TABLE \
	TAPDANCE(PLAY,		250) \
	TAPDANCE(TASKBAR,	250) \
	TAPDANCE(TIMER,	250) \
	TAPDANCE(MACRO,	250) \
	TAPDANCE(CTRL,		200) \
	TAPDANCE(ALT,		100)
	
enum {
	#define TAPDANCE(a, b) a,
	TD_TABLE
	#undef TAPDANCE
};

// Tap Dance
typedef struct {
	bool is_press_action;
	int  state;
} td_tap_t;

typedef enum {
	TD_NONE,
	TD_UNKNOWN,
	TD_SINGLE_TAP,
	TD_TAP_INTERRUPT,
	TD_SINGLE_HOLD,
	TD_DOUBLE_TAP,
	TD_DOUBLE_HOLD,
	TD_DOUBLE_SINGLE_TAP, // Sent when 2 taps are followed by another key
	TD_TRIPLE_TAP,
	TD_TRIPLE_HOLD,
	TD_QUAD_TAP,
	TD_QUAD_HOLD,
} td_state_t;

td_state_t cur_dance(tap_dance_state_t *state);

#define TAPDANCE(a, b) \
	void a ## _each(tap_dance_state_t *state, void *user_data); \
	void a ## _each_release(tap_dance_state_t *state, void *user_data); \
	void a ## _finished(tap_dance_state_t *state, void *user_data); \
	void a ## _reset(tap_dance_state_t *state, void *user_data);
TD_TABLE
#undef TAPDANCE

// declare tapdance functions here
// void play_each(tap_dance_state_t *state, void *user_data)
// void play_finished(tap_dance_state_t *state, void *user_data);
// void play_reset(tap_dance_state_t *state, void *user_data);

// void taskbar_finished(tap_dance_state_t *state, void *user_data);
// void taskbar_reset(tap_dance_state_t *state, void *user_data);

// void timer_each(tap_dance_state_t *state, void *user_data);
// void timer_finished(tap_dance_state_t *state, void *user_data);
// void timer_reset(tap_dance_state_t *state, void *user_data);

// void macro_finished(tap_dance_state_t *state, void *user_data);
// void macro_reset(tap_dance_state_t *state, void *user_data);

// void control_finished(tap_dance_state_t *state, void *user_data);
// void control_reset(tap_dance_state_t *state, void *user_data);


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *	in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *	letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
