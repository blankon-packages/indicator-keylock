#include "globals.h"
#include "lockstates.h"
#include "preferences.h"

#define INDICATOR_KEYLOCK_OPEN_PREFS 1

GRand *			self_random 		= NULL;

UniqueApp *		self_unique_app 	= NULL;
gboolean		self_has_notify 	= FALSE;
NotifyNotification *	self_notification 	= NULL;

AppIndicator *		self_appindicator 	= NULL;
GtkWidget *		self_menu 		= NULL;
GtkWidget *		self_menu_caps 		= NULL;
GtkWidget *		self_menu_caps_image 	= NULL;
GtkWidget *		self_menu_num 		= NULL;
GtkWidget *		self_menu_num_image 	= NULL;
GtkWidget *		self_menu_scroll 	= NULL;
GtkWidget *		self_menu_scroll_image 	= NULL;
GtkWidget *		self_menu_separator 	= NULL;
GtkWidget *		self_menu_preferences 	= NULL;
GtkWidget *		self_menu_quit 		= NULL;

gboolean		old_on[3] 		= { FALSE, FALSE, FALSE };

GSettings *		self_gsettings		= NULL;

gboolean		self_use_indicator 	= TRUE;
gboolean		self_single_icon 	= TRUE;
gint			self_key_shown 		= INDICATOR_KEYLOCK_CAPS;
gboolean		self_show_inactive 	= FALSE;
gboolean		self_show_quit 		= FALSE;
gboolean		self_notifications 	= TRUE;

void set_attention(gboolean attention) {
	if (self_use_indicator == FALSE) {
		app_indicator_set_status(self_appindicator, APP_INDICATOR_STATUS_PASSIVE);
	} else {
		if (attention == TRUE) {
			app_indicator_set_status(self_appindicator, APP_INDICATOR_STATUS_ATTENTION);
		} else {
			if (self_show_inactive == TRUE) {
				app_indicator_set_status(self_appindicator, APP_INDICATOR_STATUS_ACTIVE);
			} else {
				app_indicator_set_status(self_appindicator, APP_INDICATOR_STATUS_PASSIVE);
			}
		}
	}
}

void show_quit_changed() {
	if (self_show_quit == TRUE) {
		gtk_widget_show_all(self_menu_quit);
	} else {
		gtk_widget_hide(self_menu_quit);
	}
}

void single_icon_changed() {
	if (self_single_icon == TRUE) {
		gtk_widget_show_all(self_menu_caps);
		gtk_widget_show_all(self_menu_num);
		gtk_widget_show_all(self_menu_scroll);
		gtk_widget_show_all(self_menu_separator);
	} else {
		gtk_widget_hide(self_menu_caps);
		gtk_widget_hide(self_menu_num);
		gtk_widget_hide(self_menu_scroll);
		gtk_widget_hide(self_menu_separator);
	}
}

/* TODO: The notification code is fugly, make it leaner */
void on_xkb_event() {
	gboolean *on = get_led_states();
	GError *error = NULL;
	set_attention(on[self_key_shown]);
	if (on[INDICATOR_KEYLOCK_CAPS] == FALSE) {
		if (self_has_notify == TRUE && self_notifications && old_on[INDICATOR_KEYLOCK_CAPS] == TRUE) {
			if (notify_notification_update(self_notification, "Caps Lock off", NULL, "caps-lock-off") == TRUE) {
				if (notify_notification_show(self_notification, &error) == FALSE) {
					g_warning("Couldn't show notification: %s", error->message);
				}
			} else {
				g_warning("Failed to update notification.");
			}
		}
		gtk_image_set_from_icon_name(GTK_IMAGE(self_menu_caps_image), "caps-lock-off", GTK_ICON_SIZE_MENU);
	} else {
		if (self_has_notify == TRUE && self_notifications && old_on[INDICATOR_KEYLOCK_CAPS] == FALSE) {
			if (notify_notification_update(self_notification, "Caps Lock on", NULL, "caps-lock-on") == TRUE) {
				if (notify_notification_show(self_notification, &error) == FALSE) {
					g_warning("Couldn't show notification: %s", error->message);
				}
			} else {
				g_warning("Failed to update notification.");
			}
		}
		gtk_image_set_from_icon_name(GTK_IMAGE(self_menu_caps_image), "caps-lock-on", GTK_ICON_SIZE_MENU);
	}
	if (on[INDICATOR_KEYLOCK_NUM] == FALSE) {
		if (self_has_notify == TRUE && self_notifications && old_on[INDICATOR_KEYLOCK_NUM] == TRUE) {
			if (notify_notification_update(self_notification, "Num Lock off", NULL, "num-lock-off") == TRUE) {
				if (notify_notification_show(self_notification, &error) == FALSE) {
					g_warning("Couldn't show notification: %s", error->message);
				}
			} else {
				g_warning("Failed to update notification.");
			}
		}
		gtk_image_set_from_icon_name(GTK_IMAGE(self_menu_num_image), "num-lock-off", GTK_ICON_SIZE_MENU);
	} else {
		if (self_has_notify == TRUE && self_notifications && old_on[INDICATOR_KEYLOCK_NUM] == FALSE) {
			if (notify_notification_update(self_notification, "Num Lock on", NULL, "num-lock-on") == TRUE) {
				if (notify_notification_show(self_notification, &error) == FALSE) {
					g_warning("Couldn't show notification: %s", error->message);
				}
			} else {
				g_warning("Failed to update notification.");
			}
		}
		gtk_image_set_from_icon_name(GTK_IMAGE(self_menu_num_image), "num-lock-on", GTK_ICON_SIZE_MENU);
	}
	if (on[INDICATOR_KEYLOCK_SCROLL] == FALSE) {
		if (self_has_notify == TRUE && self_notifications && old_on[INDICATOR_KEYLOCK_SCROLL] == TRUE) {
			if (notify_notification_update(self_notification, "Scroll Lock off", NULL, "scroll-lock-off") == TRUE) {
				if (notify_notification_show(self_notification, &error) == FALSE) {
					g_warning("Couldn't show notification: %s", error->message);
				}
			} else {
				g_warning("Failed to update notification.");
			}
		}
		gtk_image_set_from_icon_name(GTK_IMAGE(self_menu_scroll_image), "scroll-lock-off", GTK_ICON_SIZE_MENU);
	} else {
		if (self_has_notify == TRUE && self_notifications && old_on[INDICATOR_KEYLOCK_SCROLL] == FALSE) {
			if (notify_notification_update(self_notification, "Scroll Lock on", NULL, "scroll-lock-on") == TRUE) {
				if (notify_notification_show(self_notification, &error) == FALSE) {
					g_warning("Couldn't show notification: %s", error->message);
				}
			} else {
				g_warning("Failed to update notification.");
			}
		}
		gtk_image_set_from_icon_name(GTK_IMAGE(self_menu_scroll_image), "scroll-lock-on", GTK_ICON_SIZE_MENU);
	}
	old_on[INDICATOR_KEYLOCK_CAPS] = on[INDICATOR_KEYLOCK_CAPS];
	old_on[INDICATOR_KEYLOCK_NUM] = on[INDICATOR_KEYLOCK_NUM];
	old_on[INDICATOR_KEYLOCK_SCROLL] = on[INDICATOR_KEYLOCK_SCROLL];
}

void on_self_menu_caps_activate(GtkMenuItem *menuitem, gpointer user_data) {
	app_indicator_set_icon(self_appindicator, "caps-lock-off");
	app_indicator_set_attention_icon(self_appindicator, "caps-lock-on");
}

void on_self_menu_num_activate(GtkMenuItem *menuitem, gpointer user_data) {
	app_indicator_set_icon(self_appindicator, "num-lock-off");
	app_indicator_set_attention_icon(self_appindicator, "num-lock-on");
}

void on_self_menu_scroll_activate(GtkMenuItem *menuitem, gpointer user_data) {
	app_indicator_set_icon(self_appindicator, "scroll-lock-off");
	app_indicator_set_attention_icon(self_appindicator, "scroll-lock-on");
}

void on_self_menu_preferences_activate(GtkMenuItem *menuitem, gpointer user_data) {
	show_pref_dialog();
}

void on_self_menu_quit_activate(GtkMenuItem *menuitem, gpointer user_data) {
	gtk_main_quit();
}

UniqueResponse on_self_unique_app_message_received(UniqueApp *app, gint command, UniqueMessageData *message_data, guint time_, gpointer user_data) {
	if(command == INDICATOR_KEYLOCK_OPEN_PREFS) {
		show_pref_dialog();
	}
	return(UNIQUE_RESPONSE_OK);
}

int main(int argc, char *argv[]) {
	gtk_init_with_args(&argc, &argv, _("Indicator/Status Icon for keyboard lock keys"), NULL, NULL, NULL);
	self_random = g_rand_new();
	self_unique_app = unique_app_new_with_commands("org.desktop.indicator-keylock", NULL, "open-prefs", INDICATOR_KEYLOCK_OPEN_PREFS, NULL);
	g_signal_connect(self_unique_app, "message-received", G_CALLBACK(on_self_unique_app_message_received), NULL);

	if (!init_xkb_extension(G_CALLBACK(on_xkb_event))) {
		GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, _("Could not initialize X Keyboard Extension."));
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return(0);
	}

	self_gsettings = g_settings_new("apps.indicators.keylock");

	self_use_indicator 	= g_settings_get_boolean(self_gsettings, "use-indicator");
	self_single_icon 	= g_settings_get_boolean(self_gsettings, "icon-mode");
	self_key_shown 		= g_settings_get_enum(self_gsettings, "key-shown");
	self_show_inactive 	= g_settings_get_boolean(self_gsettings, "show-inactive");
	self_show_quit 		= g_settings_get_boolean(self_gsettings, "show-quit");
	self_notifications 	= g_settings_get_boolean(self_gsettings, "notifications");

	init_pref_dialog();

	if (unique_app_is_running(self_unique_app) == TRUE) {
		UniqueResponse response = unique_app_send_message(self_unique_app, INDICATOR_KEYLOCK_OPEN_PREFS, NULL);
		return(response);
	}

	self_menu_caps = gtk_image_menu_item_new_with_label(_("Caps Lock"));
	self_menu_caps_image = gtk_image_new_from_icon_name("caps-lock-off", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(self_menu_caps), self_menu_caps_image);
	gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(self_menu_caps), TRUE);
	g_signal_connect(self_menu_caps, "activate", G_CALLBACK(on_self_menu_caps_activate), NULL);
	gtk_widget_show_all(self_menu_caps);

	self_menu_num = gtk_image_menu_item_new_with_label(_("Num Lock"));
	self_menu_num_image = gtk_image_new_from_icon_name("num-lock-off", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(self_menu_num), self_menu_num_image);
	gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(self_menu_num), TRUE);
	g_signal_connect(self_menu_num, "activate", G_CALLBACK(on_self_menu_num_activate), NULL);
	gtk_widget_show_all(self_menu_num);

	self_menu_scroll = gtk_image_menu_item_new_with_label(_("Scroll Lock"));
	self_menu_scroll_image = gtk_image_new_from_icon_name("scroll-lock-off", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(self_menu_scroll), self_menu_scroll_image);
	gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(self_menu_scroll), TRUE);
	g_signal_connect(self_menu_scroll, "activate", G_CALLBACK(on_self_menu_scroll_activate), NULL);
	gtk_widget_show_all(self_menu_scroll);

	self_menu_separator = gtk_separator_menu_item_new();
	gtk_widget_show_all(self_menu_separator);

	self_menu_preferences = gtk_image_menu_item_new_from_stock(GTK_STOCK_PREFERENCES, NULL);
	g_signal_connect(self_menu_preferences, "activate", G_CALLBACK(on_self_menu_preferences_activate), NULL);
	gtk_widget_show_all(self_menu_preferences);

	self_menu_quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
	g_signal_connect(self_menu_quit, "activate", G_CALLBACK(on_self_menu_quit_activate), NULL);

	single_icon_changed();
	show_quit_changed();

	self_menu = gtk_menu_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(self_menu), self_menu_caps);
	gtk_menu_shell_append(GTK_MENU_SHELL(self_menu), self_menu_num);
	gtk_menu_shell_append(GTK_MENU_SHELL(self_menu), self_menu_scroll);
	gtk_menu_shell_append(GTK_MENU_SHELL(self_menu), self_menu_separator);
	gtk_menu_shell_append(GTK_MENU_SHELL(self_menu), self_menu_preferences);
	gtk_menu_shell_append(GTK_MENU_SHELL(self_menu), self_menu_quit);

	switch (self_key_shown) {
	default:
	case INDICATOR_KEYLOCK_CAPS:
		self_appindicator = app_indicator_new("indicator-keylock", "caps-lock-off", APP_INDICATOR_CATEGORY_HARDWARE);
		app_indicator_set_attention_icon(self_appindicator, "caps-lock-on");
		break;
	case INDICATOR_KEYLOCK_NUM:
		self_appindicator = app_indicator_new("indicator-keylock", "num-lock-off", APP_INDICATOR_CATEGORY_HARDWARE);
		app_indicator_set_attention_icon(self_appindicator, "num-lock-on");
		break;
	case INDICATOR_KEYLOCK_SCROLL:
		self_appindicator = app_indicator_new("indicator-keylock", "scroll-lock-off", APP_INDICATOR_CATEGORY_HARDWARE);
		app_indicator_set_attention_icon(self_appindicator, "scroll-lock-on");
		break;
	}
	app_indicator_set_menu(self_appindicator, GTK_MENU(self_menu));

	self_has_notify = notify_init("indicator-keylock");
	if (self_has_notify == TRUE) {
		self_notification = notify_notification_new("Indicator for Lock Keys active", NULL, NULL);
		if (self_notification == NULL) {
			g_warning("Failed to create notifications.");
		} else {
			notify_notification_set_hint_string(self_notification,
			                                    "x-canonical-private-synchronous",
			                                    "indicator-keylock");
			notify_notification_set_hint_int32(self_notification, "transient", 1);
			notify_notification_set_category(self_notification, "keyboard");
			notify_notification_set_urgency(self_notification, NOTIFY_URGENCY_NORMAL);
			notify_notification_set_timeout(self_notification, 5000);
		}
	} else {
		g_warning("Couldn't initialize libnotify.");
	}

	old_on[INDICATOR_KEYLOCK_CAPS] = FALSE;
	old_on[INDICATOR_KEYLOCK_NUM] = FALSE;
	old_on[INDICATOR_KEYLOCK_SCROLL] = FALSE;

	on_xkb_event();
	gtk_main();
	return(0);
}
