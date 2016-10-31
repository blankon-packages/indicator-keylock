SUBDIRS           = po pixmaps src

desktopdir        = $(datadir)/applications
desktop_in_files  = indicator-keylock.desktop.in
desktop_DATA      = $(desktop_in_files:.desktop.in=.desktop)

autostartdir      = $(sysconfdir)/xdg/autostart
autostart_DATA    = $(desktop_DATA)

@INTLTOOL_DESKTOP_RULE@

datauidir         = $(datadir)/indicator-keylock/ui
dataui_DATA       = indicator-keylock-prefs.ui

gschema_in_files  = apps.indicators.keylock.gschema.xml.in

@INTLTOOL_XML_NOMERGE_RULE@

gsettings_SCHEMAS = $(gschema_in_files:.xml.in=.xml)

@GSETTINGS_RULES@

EXTRA_DIST        = $(desktop_in_files) $(gschema_in_files)

CLEANFILES        = $(desktop_DATA) $(gsettings_SCHEMAS)
