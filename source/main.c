#include <gtk/gtk.h>

#include <stdio.h>

#include <stdlib.h>

GtkApplication* app;

GtkWidget* topWindow;

GFile *file;

char* file_path = NULL;

int fileType;

int invalidTypes = G_FILE_TYPE_DIRECTORY | G_FILE_TYPE_MOUNTABLE | G_FILE_TYPE_SPECIAL;

#include "closeDialog.h"

#include "fileDialog.h"

#include "textView.h"

#include "titleBar.h"

#include "save.h"

#include "closeDialog.c"

#include "fileDialog.c"

#include "textView.c"

#include "titleBar.c"

#include "save.c"

void
gte_open
( GApplication *app, GFile **files, int fileCount )
{
	if ( fileCount > 1 )
	{
		fprintf( stderr, "ERROR: Pass only one file as argument!\n" );

		exit( EXIT_FAILURE );
	}

	file = g_file_dup( files[0] );

	g_application_activate( app );

	return;
}

static void
gte_activate
( GtkApplication *app )
{
	topWindow = gtk_application_window_new( app );

	gtk_window_set_title( topWindow, "Untitled Document" );

	gtk_window_set_default_size( (GtkWindow*) topWindow, 0, 0 );

	GtkCssProvider *cssProvider = gtk_css_provider_new();

	GdkDisplay *display = gdk_display_get_default();

	gtk_css_provider_load_from_string( cssProvider, "*{font-size:16pt;} textview{font-family:monospace;}" );

	gtk_style_context_add_provider_for_display( display, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER );

	buildTextView( topWindow );

	gte_titleBar_create();

	gte_closeDialog_create();

	fileDialog = gtk_file_dialog_new();

	if ( file != NULL )
	{
		fileType = g_file_query_file_type( file, G_FILE_QUERY_INFO_NONE, NULL );

		if ( !(fileType & invalidTypes) )
		{
			fileToTextBuffer( file );

			gte_set_file( GTK_WINDOW( topWindow ), file );
		}
	}

	gtk_window_present( ( GtkWindow* ) topWindow );

	g_signal_connect( topWindow, "close-request", G_CALLBACK( gte_closing ), NULL );

	return;
}

int
main
( int argc, char **argv )
{
	app = gtk_application_new( "com.gtk-text-editor", G_APPLICATION_HANDLES_OPEN | G_APPLICATION_NON_UNIQUE );

	g_signal_connect( app, "open", G_CALLBACK( gte_open ), NULL );

	g_signal_connect( app, "activate", G_CALLBACK( gte_activate ), NULL );

	int status = g_application_run( app, argc, argv );

	g_object_unref( app );

	return status;
}
