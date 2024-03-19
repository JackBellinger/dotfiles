#pragma once
#include QMK_KEYBOARD_H
#pragma once
#include "../custom_keycodes.h"

/* Define the macros (enum variant name, enum value, function to call) */
#define MACRO_TABLE \
	MACRO(MAC_SEARCH, search)\
	MACRO(MAC_TERMINAL, terminal)\
	MACRO(MAC_EDITOR, editor)\
	MACRO(MAC_BROWSER, browser)\
	MACRO(MAC_SCREENSHOT, screenshot)


/* Generate function prototypes */
#define MACRO(a, b) bool b(keyrecord_t* record);
	MACRO_TABLE
#undef MACRO

typedef enum {
	MAC_TRUE = MACRO_RANGE_START, //does nothing, helps range calculation
	#define MACRO(a, b) a,
		MACRO_TABLE
	#undef MACRO
	MAC_FALSE //stops processing the keypress, helps range calculation
} macro_keycodes;

//function takes the keypress event, runs the macro, & returns whether to keep processing the key press
typedef bool (*func_p)(keyrecord_t* record);

struct action {
  func_p map[MAC_FALSE - MAC_TRUE +1];
};
bool true_macro(keyrecord_t* record);
bool false_macro(keyrecord_t* record);

bool send_macro(uint16_t keycode, keyrecord_t* record);
bool process_macro(uint16_t keycode, keyrecord_t* record);