# Build Options
#   change yes to no to disable
#
LAYOUT = all

BOOTMAGIC_ENABLE 	= yes		# Enable Bootmagic Lite
CONSOLE_ENABLE 		= no		# Console for debug
COMMAND_ENABLE 		= no		# Commands for debug and configuration
NKRO_ENABLE 		= yes		# Enable N-Key Rollover
SWAP_HANDS_ENABLE	= no		# Allow swapping hands of keyboard

# Keys
EXTRAKEY_ENABLE 	= yes		# Audio control and System control
MOUSEKEY_ENABLE 	= no		# Mouse keys
UNICODE_COMMON		= yes
UNICODE_ENABLE		= yes		# Unicode
# UCIS_ENABLE			= yes		# Unicode mnemonics
LEADER_ENABLE		= yes		# Leader key
CAPS_WORD_ENABLE	= yes		# Caps lock until end of word

# IO features
AUDIO_ENABLE 		= no		# Audio output
BACKLIGHT_ENABLE 	= no		# Enable keyboard backlight functionality
RGBLIGHT_ENABLE 	= yes		# Enable keyboard RGB underglow
CUSTOM_RBGLIGHT		= yes		# Enable layer indication rgb mode

#Add features directory to compilation
SRC += features/layer_lock.c
EXTRAFLAGS        += -flto
