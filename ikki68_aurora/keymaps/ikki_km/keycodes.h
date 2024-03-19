#pragma once
#include QMK_KEYBOARD_H

typedef enum {
	TURBO = SAFE_RANGE,
	MAC_SEARCH,
	MAC_TERMINAL,
	MAC_EDITOR,
	MAC_BROWSER,
	MAC_SCREENSHOT,
	LLOCK //needs to be last for num keycodes calc
} custom_keycodes;
