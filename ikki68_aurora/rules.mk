# Build Options
#   change yes to no to disable
#
LAYOUT = all

BOOTMAGIC_ENABLE 	= yes	# Bootmagic Lite
DEFERRED_EXEC_ENABLE = yes	# Execute callback at after x time
CONSOLE_ENABLE 		= no	# Console for debug
COMMAND_ENABLE 		= no	# Commands for debug and configuration
NKRO_ENABLE 		= yes	# N-Key Rollover
SWAP_HANDS_ENABLE	= no	# Swapping split keeb sides

# Keys
EXTRAKEY_ENABLE 	= yes	# Audio control and System control
MOUSEKEY_ENABLE 	= no	# Mouse keys
UNICODE_COMMON		= no
UNICODE_ENABLE		= no	# Unicode
UCIS_ENABLE			= no	# Unicode mnemonics
LEADER_ENABLE		= no	# Leader key
CAPS_WORD_ENABLE	= yes	# Caps lock until end of word

# IO features
BACKLIGHT_ENABLE	= no	# Backlight
RGBLIGHT_ENABLE		= yes	# RGB underglow
AUDIO_ENABLE		= no	# In-keyboard audio

# Features Toggles
# MACRO_ENABLE		= yes	# Macros
TAP_DANCE_ENABLE	= yes	# Tap Dance
TIMERS_ENABLE		= yes	# Timers
# LAYER_LOCK_ENABLE	= yes	# Layer Lock


#Add features directory to compilation
SRC += features/macro.c
SRC += features/layer_lock.c
SRC += features/tap_dance.c
SRC += features/timer.c
# SRC += features/rgb.c
# SRC += features/combos.c

EXTRAFLAGS        += -flto
