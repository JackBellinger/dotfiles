# Build Options
#   change yes to no to disable
#
LAYOUT = all

BOOTMAGIC_ENABLE 		= yes	# Bootmagic Lite
DEFERRED_EXEC_ENABLE = yes	# Execute callback at after x time
CONSOLE_ENABLE 		= yes	# Console for debug
COMMAND_ENABLE 		= no	# Commands for debug and configuration
NKRO_ENABLE 			= yes	# N-Key Rollover
SWAP_HANDS_ENABLE		= no	# Swapping split keeb sides

# Keys
EXTRAKEY_ENABLE 		= yes	# Audio control and System control
MOUSEKEY_ENABLE 		= no	# Mouse keys
UNICODE_COMMON			= no
UNICODE_ENABLE			= no	# Unicode
UCIS_ENABLE				= no	# Unicode mnemonics
LEADER_ENABLE			= no	# Leader key
CAPS_WORD_ENABLE		= yes	# Caps lock until end of word

# IO features
BACKLIGHT_ENABLE		= no	# Backlight
RGBLIGHT_ENABLE		= yes	# RGB underglow
OLED_ENABLE				= no
AUDIO_ENABLE			= no	# In-keyboard audio
MUSIC_ENABLE			= no

# Features Toggles
TAP_DANCE_ENABLE		= yes	# Tap Dance
SPACE_CADET_ENABLE	= no
GRAVE_ESC_ENABLE		= no 
MAGIC_ENABLE			= no

#Custom Features
TIMERS_ENABLE			= yes	# Timers
#MACRO_ENABLE			= yes	# Macros are always enabled
# LAYER_LOCK_ENABLE	= yes	# Layer Lock is always enabled


#Add features directory to compilation
SRC += features/macro.c
SRC += features/layer_lock.c
SRC += features/tap_dance.c
SRC += features/timer.c
# SRC += features/turbo_click.c
SRC += features/temporal_dynamic_macro.c
# SRC += features/rgb.c
# SRC += features/combos.c

#AVR Size optimizations
ifneq ($(strip $(LTO_SUPPORTED)), no)
	LTO_ENABLE        = yes
endif
# AVR_USE_MINIMAL_PRINTF = yes

EXTRAFLAGS				+= -Os -ffunction-sections -fdata-sections -Wl,--gc-sections -finline-functions -flto
