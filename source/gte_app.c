#include "gte_app.h"

#include "gte_toolbar.h"

#include "gte_file.h"

#include "gte_window_main.h"

extern GtkWidget *gte_window_main;

#include "gte_text.h"

#include "gte_dialog_closing.h"

#include "gte_dialog_file.h"

GFile *gte_app_file_to_open = NULL;

GtkApplication *gte_app;

void
gte_app_reply_open
( GApplication *app, GFile **files, int fileCount)
{
	if ( fileCount > 1 )
	{
		fprintf( stderr, "Error: Pass only one file as argument!\n" );

		exit( EXIT_FAILURE );
	}

	gte_app_file_to_open = g_object_ref( files[0] );

	g_application_activate( app );

	return;
}

void
gte_app_reply_activate
( GtkApplication *app )
{
	gte_window_main_create( app );

	gte_text_view_create( gte_window_main );

	gte_toolbar_create( gte_window_main );

	gte_dialog_closing_create();

	gte_dialog_file_create();

	gte_file_open( gte_app_file_to_open );

	gtk_window_present( GTK_WINDOW( gte_window_main ) );

	g_signal_connect( gte_window_main, "close-request", G_CALLBACK( gte_window_main_reply_closing ), NULL );

	return;
}

void
gte_app_close
( void )
{
	gtk_window_destroy( GTK_WINDOW( gte_window_main ) );

	g_object_unref( gte_app );

	exit( 0 );

	return;
}

