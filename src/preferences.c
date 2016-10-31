#include "globals.h"
#include "lockstates.h"
#include "preferences.h"

GtkWidget *	self_pref_dialog 		= NULL;
GtkWidget *	self_use_indicator_check 	= NULL;
GtkWidget *	self_caps_lock_radio 		= NULL;
GtkWidget *	self_num_lock_radio 		= NULL;
GtkWidget *	self_scroll_lock_radio 		= NULL;
GtkWidget *	self_show_inactive_check 	= NULL;

void self_use_indicator_check_update() {
	self_use_indicator = g_settings_get_boolean(self_gsettings, "use-indicator");
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self_use_indicator_check)) != self_use_indicator) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_use_indicator_check), self_use_indicator);
	}
}

void self_show_inactive_check_update() {
	self_show_inactive = g_settings_get_boolean(self_gsettings, "show-inactive");
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self_show_inactive_check)) != self_show_inactive) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_show_inactive_check), self_show_inactive);
	}
}

void self_key_shown_radios_update() {
	self_key_shown = g_settings_get_enum(self_gsettings, "key-shown");
	switch (self_key_shown) {
	default:
	case INDICATOR_KEYLOCK_CAPS:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_caps_lock_radio), TRUE);
		break;
	case INDICATOR_KEYLOCK_NUM:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_num_lock_radio), TRUE);
		break;
	case INDICATOR_KEYLOCK_SCROLL:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_scroll_lock_radio), TRUE);
		break;
	}
}

void on_use_indicator_check_toggled() {
	self_use_indicator = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self_use_indicator_check));
	g_settings_set_boolean(self_gsettings, "use-indicator", self_use_indicator);
}

void on_caps_lock_radio_toggled() {
	self_key_shown = g_settings_get_enum(self_gsettings, "key-shown");
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self_caps_lock_radio)) == TRUE && self_key_shown != INDICATOR_KEYLOCK_CAPS) {
		self_key_shown = INDICATOR_KEYLOCK_CAPS;
		g_settings_set_enum(self_gsettings, "key-shown", self_key_shown);
		app_indicator_set_icon(self_appindicator, "caps-lock-off");
		app_indicator_set_attention_icon(self_appindicator, "caps-lock-on");
	}
}

void on_num_lock_radio_toggled() {
	self_key_shown = g_settings_get_enum(self_gsettings, "key-shown");
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self_num_lock_radio)) == TRUE && self_key_shown != INDICATOR_KEYLOCK_NUM) {
		self_key_shown = INDICATOR_KEYLOCK_NUM;
		g_settings_set_enum(self_gsettings, "key-shown", self_key_shown);
		app_indicator_set_icon(self_appindicator, "num-lock-off");
		app_indicator_set_attention_icon(self_appindicator, "num-lock-on");
	}
}

void on_scroll_lock_radio_toggled() {
	self_key_shown = g_settings_get_enum(self_gsettings, "key-shown");
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self_scroll_lock_radio)) == TRUE && self_key_shown != INDICATOR_KEYLOCK_SCROLL) {
		self_key_shown = INDICATOR_KEYLOCK_SCROLL;
		g_settings_set_enum(self_gsettings, "key-shown", self_key_shown);
		app_indicator_set_icon(self_appindicator, "scroll-lock-off");
		app_indicator_set_attention_icon(self_appindicator, "scroll-lock-on");
	}
}

void on_show_inactive_check_toggled() {
	self_show_inactive = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self_show_inactive_check));
	g_settings_set_boolean(self_gsettings, "show-inactive", self_show_inactive);
}

gboolean on_pref_dialog_delete_event() {
	gtk_widget_hide(self_pref_dialog);
	return(TRUE);
}

void on_pref_dialog_response() {
	gtk_widget_hide(self_pref_dialog);
}

void init_pref_dialog() {
	GString *ui_file_path = NULL;
	GtkBuilder *builder = NULL;
	GError *error = NULL;

	gboolean self_use_indicator = g_settings_get_boolean(self_gsettings, "use-indicator");
	gboolean self_show_inactive = g_settings_get_boolean(self_gsettings, "show-inactive");
	gint self_key_shown = g_settings_get_enum(self_gsettings, "key-shown");

	ui_file_path = g_string_new(DATADIR);
	g_string_append(ui_file_path, "/indicator-keylock/ui/indicator-keylock-prefs.ui");
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, ui_file_path->str, &error);
	if(error != NULL) {
		g_error("%s", error->message);
	}
	self_pref_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "pref_dialog"));
	self_use_indicator_check = GTK_WIDGET(gtk_builder_get_object(builder, "use_indicator_check"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_use_indicator_check), self_use_indicator);

	self_caps_lock_radio = GTK_WIDGET(gtk_builder_get_object(builder, "caps_lock_radio"));
	self_num_lock_radio = GTK_WIDGET(gtk_builder_get_object(builder, "num_lock_radio"));
	self_scroll_lock_radio = GTK_WIDGET(gtk_builder_get_object(builder, "scroll_lock_radio"));
	switch (self_key_shown) {
	default:
	case INDICATOR_KEYLOCK_CAPS:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_caps_lock_radio), TRUE);
		break;
	case INDICATOR_KEYLOCK_NUM:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_num_lock_radio), TRUE);
		break;
	case INDICATOR_KEYLOCK_SCROLL:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_scroll_lock_radio), TRUE);
		break;
	}

	self_show_inactive_check = GTK_WIDGET(gtk_builder_get_object(builder, "show_inactive_check"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self_show_inactive_check), self_show_inactive);
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(self_pref_dialog);
}

void show_pref_dialog() {
	gtk_widget_show(self_pref_dialog);
}
