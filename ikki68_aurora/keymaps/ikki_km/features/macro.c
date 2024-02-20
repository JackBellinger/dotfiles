#include "macro.h"
void search(void) {
    SEND_STRING(SS_LCTL("c"));
    send_macro(MAC_BROWSER);
    SEND_STRING(SS_DELAY(200) SS_LCTL("t" "l" "v") SS_TAP(X_ENT));
}
void editor(void) {
    SEND_STRING(SS_LGUI("1"));
}
void terminal(void) {
    SEND_STRING(SS_LGUI("2"));
}
void browser(void) {
    SEND_STRING(SS_LGUI("3"));
}
void blog_url(void) {
    SEND_STRING("https://jackbellinger.github.io/blog");
}
void screenshot(void) {
    SEND_STRING(SS_LALT(SS_TAP(X_PSCR)) SS_LGUI("r") SS_DELAY(500) "mspaint" SS_TAP(X_ENTER) SS_DELAY(600) SS_LCTL("v"));
}

/* Generate function to check if keycode is a macro */
int KC_isMacro(uint16_t keycode) {
    switch (keycode) {
#define MACRO(a, b, c) case a:
        MACRO_TABLE
#undef MACRO
        return 1;
    };
    return 0;
}

/* Generate Macro keycode to function map*/
struct action macros = {{
#define MACRO(a, b, c) &c,
    MACRO_TABLE
#undef MACRO
}};

void send_macro(uint16_t keycode) {
    macros.map[keycode - SAFE_RANGE]();
}