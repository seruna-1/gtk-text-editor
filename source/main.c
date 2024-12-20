#include <gtk/gtk.h>

#include <stdio.h>

#include <stdlib.h>

#include "gte_dialog_closing.h"

#include "gte_dialog_file.h"

#include "gte_file.h"

#include "gte_generate_titles.h"

#include "gte_text.h"

#include "gte_cursor.h"

#include "gte_toolbar.h"

#include "gte_window_main.h"

#include "gte_app.h"

#include "gte_dialog_closing.c"

#include "gte_dialog_file.c"

#include "gte_file.c"

#include "gte_generate_titles.c"

#include "gte_text.c"

#include "gte_cursor.c"

#include "gte_toolbar.c"

#include "gte_window_main.c"

#include "gte_app.c"

int
main
( int argc, char **argv )
{
	gte_app = gtk_application_new( "com.gtk-text-editor", G_APPLICATION_HANDLES_OPEN | G_APPLICATION_NON_UNIQUE );

	g_signal_connect( gte_app, "open", G_CALLBACK( gte_app_reply_open ), NULL );

	g_signal_connect( gte_app, "activate", G_CALLBACK( gte_app_reply_activate ), NULL );

	int status = g_application_run( G_APPLICATION( gte_app ), argc, argv );

	g_object_unref( gte_app );

	return status;
}
