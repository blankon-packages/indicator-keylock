#ifndef _PREFERENCES_H
#define _PREFERENCES_H
#include <glib.h>
#include <gio/gio.h>
#include <gtk/gtk.h>

extern GtkWidget *		self_pref_dialog;
extern GtkWidget *		self_use_indicator_check;
extern GtkWidget *		self_caps_lock_radio;
extern GtkWidget *		self_num_lock_radio;
extern GtkWidget *		self_scroll_lock_radio;
extern GtkWidget *		self_show_inactive_check;
extern GtkWidget *		self_show_quit_check;
extern GtkWidget *		self_notifications_check;

void init_pref_dialog();
void show_pref_dialog();

void self_use_indicator_check_update();
void self_key_shown_radios_update();
void self_show_inactive_check_update();

#endif /* _PREFERENCES_H */
