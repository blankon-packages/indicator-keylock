#include <glib.h>
#include <gdk/gdkx.h>
#include <X11/XKBlib.h>
#include <string.h>
#include "lockstates.h"

static Display *rootwin = NULL;
static gint xkbev = 0;
static gint xkberr = 0;

gboolean *get_led_states() {
	guint state = 0;
	static gboolean on[3] = {FALSE, FALSE, FALSE};
	int i;
	XkbGetIndicatorState(rootwin, XkbUseCoreKbd, &state);
	
	for (i = 0 ; i < 3 ; i++) {
		if (state & (1 << i))
			on[i] = TRUE;
		else
			on[i] = FALSE;
	}
	return(on);
}

/* Mostly borrowed from lock-keys-applet */
GdkFilterReturn event_filter(GdkXEvent *gdkxevent, GdkEvent *event, GCallback show_func) {
	XkbEvent ev;
	memcpy(&ev.core, gdkxevent, sizeof(ev.core));

	if (ev.core.type == xkbev + XkbEventCode) {
		if (ev.any.xkb_type == XkbIndicatorStateNotify)
			show_func();
	}

	return GDK_FILTER_CONTINUE;
}

gboolean init_xkb_extension(GCallback show_func) {
	int code;
	int maj = XkbMajorVersion;
	int min = XkbMinorVersion;
	rootwin = gdk_x11_get_default_xdisplay();

	if (!XkbLibraryVersion(&maj, &min))
		return FALSE;

	if (!XkbQueryExtension(rootwin, &code, &xkbev, &xkberr, &maj, &min))
		return FALSE;

	if (!XkbSelectEvents(rootwin, XkbUseCoreKbd, XkbIndicatorStateNotifyMask, XkbIndicatorStateNotifyMask))
		return FALSE;

	gdk_window_add_filter(NULL, (GdkFilterFunc)event_filter, show_func);

	return TRUE;
}
