#include <gtk/gtk.h>

#include <stdio.h>

#include <stdlib.h>

#include "gte_app.h"

extern GtkApplication *gte_app;

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
