#include "jack.h"
// Matrix diagram for Wuque Ikki68 Aurora
/**
```	
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐┌───┬───┐	 ┌───────┐
│00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │2D ││0E │0F │	 │0D	 │ 2u Backspace
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤├───┼───┤	 └─┬─────┤
│10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D   ││1E │1F │	   │	 │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤└───┴───┘	┌──┴┐1D  │ ISO Enter
│20	│21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C	  │			 │2C │	│
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤┌───┐		└───┴────┘
│30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3C	│3D ││3E │
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴┬──┴┼───┼───┐
│40  │41  │42  │46					  │4A  │4B  │4C  │ │4D │4E │4F │
└────┴────┴────┴────────────────────────┴────┴────┴────┘ └───┴───┴───┘
┌────────┐									   ┌──────────┐
│30	  │ 2.25u LShift			 2.75u RShift │3C		│
└────────┘									   └──────────┘
┌────┬────┬────┬────────┬────┬──────────┬────┬────┬────┐
│40  │41  │42  │44	  │46  │48		│4A  │4B  │4C  │ Split Space
└────┴────┴────┴────────┴────┴──────────┴────┴────┴────┘
```
*/
#include QMK_KEYBOARD_H
// KC_NO used in empty split key options
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[ALPHAS] = LAYOUT_all(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC, KC_VOLU, TD(PLAY), 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_VOLD, TD(TASKBAR),
		CW_TOGG, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, KC_UP,
		KC_LCTL, KC_LGUI, TD(ALT), KC_NO, KC_SPC, KC_NO, SC_RAPC, MO(FUNCS), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
	),						   //space		  space
	[FUNCS] = LAYOUT_all(
		QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, TURBO, KC_DEL, _______, KC_BTN1,
		_______, _______, _______, TDM_END, TDM_RECORD, TD(TIMER), _______, _______, _______, _______, TDM_PLAY, _______, RGB_TOG, TD(MACRO), _______, KC_BTN2,
		KC_CAPS, _______, TDM_SELECT, TDM_DELAY, _______, _______, _______, _______, _______, TDM_LOOP, _______, _______, _______,
		_______, KC_NO, _______, _______, _______, _______, _______, _______, _______, KC_WBAK, KC_WFWD, LCTL(KC_F), _______, KC_NO, KC_PGUP,
		KC_NO, _______, _______, KC_NO, LLOCK, KC_NO, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
	),
};

#define CAPS_WORD_INVERT_ON_SHIFT
/*
	return is whether the keycode should be processed any more, false = skip further processing
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
	if (!process_temporal_dynamic_macro(keycode, record)) { return false; }
	// if (!process_mouse_turbo_click(keycode, record, TURBO)) { return false; }
	if (!process_macro(keycode, record)) { return false; }
	return true;
};

#define RGBLIGHT_RAINBOW_SWIRL_RANGE 127
#define RGB_MODE_DEFAULT RGBLIGHT_MODE_RAINBOW_SWIRL + 3
#define RGB_MODE_ALERT RGBLIGHT_MODE_ALTERNATING
#define RGB_MODE_TESTING RGBLIGHT_MODE_STATIC_LIGHT
void keyboard_post_init_user(void) {
	debug_enable=true;
	debug_keyboard=true;
	tdm_init();
	//rgblight_enable_noeeprom(); // enables Rgb, without saving settings
	//rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
	#ifdef RGB_MODE_TESTING
		rgblight_mode(RGB_MODE_DEFAULT); // sets mode to rainbow swirlwithout saving
	#endif
}




// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_led_indicators.md#example-of-user-led-update-implementation
#ifdef AUDIO_ENABLE
	float caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
	float caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);
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

uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
uint8_t mod_config(uint8_t mod) {
    return mod;
}