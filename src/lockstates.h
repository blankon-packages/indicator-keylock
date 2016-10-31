#ifndef _LOCKSTATES_H
#define _LOCKSTATES_H
#include <glib.h>

enum {
	INDICATOR_KEYLOCK_CAPS  = 0,
	INDICATOR_KEYLOCK_NUM = 1,
	INDICATOR_KEYLOCK_SCROLL = 2
} LockKey;

gboolean *get_led_states();
gboolean init_xkb_extension(GCallback show_func);

#endif
