# Build Options
#   change yes to no to disable
#
LAYOUT = all

BOOTMAGIC_ENABLE 	= yes	# Enable Bootmagic Lite
CONSOLE_ENABLE 		= no	# Console for debug
COMMAND_ENABLE 		= no	# Commands for debug and configuration
NKRO_ENABLE 		= yes	# Enable N-Key Rollover
SWAP_HANDS_ENABLE	= no	# Allow swapping hands of keyboard

# Keys
EXTRAKEY_ENABLE 	= yes	# Audio control and System control
MOUSEKEY_ENABLE 	= no	# Mouse keys
UNICODE_COMMON		= no
UNICODE_ENABLE		= no	# Unicode
UCIS_ENABLE			= no	# Unicode mnemonics
LEADER_ENABLE		= no	# Leader key
CAPS_WORD_ENABLE	= yes	# Caps lock until end of word

# IO features# Audio output
BACKLIGHT_ENABLE	= no	# Enable keyboard backlight functionality
RGBLIGHT_ENABLE		= yes	# Enable keyboard RGB underglow
CUSTOM_RBGLIGHT		= yes	# Enable layer indication rgb mode

# Features Toggles
# MACRO_ENABLE		= yes	# Macros
TAP_DANCE_ENABLE	= yes	# Tap Dance
# LAYER_LOCK_ENABLE	= yes	# Layer Lock


#Add features directory to compilation
SRC += features/macro.c
SRC += features/layer_lock.c
SRC += features/tap_dance.c
# SRC += features/rgb.c
# SRC += features/combos.c

EXTRAFLAGS        += -flto
