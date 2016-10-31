#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdio.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <unique/unique.h>
#include <libappindicator/app-indicator.h>
#include <libnotify/notify.h>

extern GRand *			self_random;

extern UniqueApp *		self_unique_app;

extern gboolean			self_has_notify;
extern NotifyNotification *	self_notification;

extern GSettings *		self_gsettings;

extern AppIndicator *		self_appindicator;
extern GtkWidget *		self_menu;
extern GtkWidget *		self_menu_caps;
extern GtkWidget *		self_menu_caps_image;
extern GtkWidget *		self_menu_num;
extern GtkWidget *		self_menu_num_image;
extern GtkWidget *		self_menu_scroll;
extern GtkWidget *		self_menu_scroll_image;
extern GtkWidget *		self_menu_separator;
extern GtkWidget *		self_menu_preferences;
extern GtkWidget *		self_menu_quit;

extern gboolean			old_on[3];

extern gboolean			self_use_indicator;
extern gboolean			self_single_icon;
extern gint			self_key_shown;
extern gboolean			self_show_inactive;
extern gboolean			self_show_quit;
extern gboolean			self_notifications;

#endif /* _GLOBALS_H */
