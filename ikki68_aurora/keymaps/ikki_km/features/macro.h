#pragma once
#include "jack.h"

/* Define the macros (enum variant name, enum value, function to call) */
#define MACRO_TABLE \
	MACRO(MAC_SEARCH,		SAFE_RANGE + 0, search)\
	MACRO(MAC_TERMINAL,		SAFE_RANGE + 1, terminal)\
	MACRO(MAC_EDITOR,		SAFE_RANGE + 2, editor) \
	MACRO(MAC_BROWSER,		SAFE_RANGE + 3, browser) \
	MACRO(MAC_SCREENSHOT,	SAFE_RANGE + 4, screenshot)

/* Define any additional keycodes that don't have a void func with no params
	LLOCK has to be last in this table to init the array mapping keys to funcs*/
#define KEYCODES_TABLE \
	KEYCODE(TURBO,			SAFE_RANGE + 5) \
	KEYCODE(LLOCK,			SAFE_RANGE + 6)

/* Generate function prototypes */
#define MACRO(a, b, c) void c(void);
    MACRO_TABLE
#undef MACRO

typedef enum {
	#define MACRO(a, b, c) a = b,
    MACRO_TABLE
	#undef MACRO
	#define KEYCODE(a, b) a = b,
    KEYCODES_TABLE
	#undef KEYCODE
} custom_keycodes;

typedef void (*func_p)(void);
struct action {
  func_p map[LLOCK - SAFE_RANGE];
};
struct action macros;

int KC_isMacro(uint16_t keycode);

void send_macro(uint16_t keycode);
