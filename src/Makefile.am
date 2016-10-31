bin_PROGRAMS              = indicator-keylock

indicator_keylock_SOURCES = main.c \
                            lockstates.c lockstates.h \
                            preferences.c preferences.h
indicator_keylock_CFLAGS  = -g -Wall -DDATADIR=\"$(datadir)\" \
                            $(PACKAGE_CFLAGS)
indicator_keylock_LDFLAGS = -g -Wall -export-dynamic -Xlinker --no-as-needed \
                            $(PACKAGE_LIBS)
