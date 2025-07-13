#include <gtk/gtk.h>

#include "gte_window_main.h"

extern GFile *gte_file_opened;

#include "gte_app.h"

#include "gte_dialog_closing.h"

extern GtkAlertDialog *gte_dialog_closing;

extern bool gte_unsaved;

GtkWidget *gte_window_main;

gchar *gte_window_title_saved, *gte_window_title_unsaved;

gchar *gte_window_title_anonymous = "* untitled";

void
gte_window_create_title_options
( GFile *gte_file_opened )
{
	g_free( gte_window_title_saved );

	g_free( gte_window_title_unsaved );

	gte_window_title_saved = g_file_get_path( gte_file_opened );

	GString *title_unsaved = g_string_new( "* " );

	title_unsaved = g_string_append( title_unsaved, gte_window_title_saved );

	gte_window_title_unsaved = g_string_free_and_steal( title_unsaved );

	return;
}

void
gte_window_update_title
( GFile *gte_file_opened, bool gte_unsaved )
{
	gchar *title;

	if ( gte_file_opened == NULL )
	{
		title = gte_window_title_anonymous;
	}
	else if ( gte_unsaved == true )
	{
		title = gte_window_title_unsaved;
	}
	else
	{
		title = gte_window_title_saved;
	}

	gtk_window_set_title( GTK_WINDOW( gte_window_main ), title );

	return;
}

gboolean
gte_window_main_reply_closing
( GtkWidget* window_main, gpointer data )
{
	if ( gte_unsaved == true )
	{
		gtk_alert_dialog_choose( gte_dialog_closing, GTK_WINDOW( window_main ), NULL, gte_dialog_closing_manage, NULL );
	}

	else
	{
		gte_app_close();
	}

	return TRUE;
}

void
gte_window_main_create
( GtkApplication *app )
{
	gte_window_main = gtk_application_window_new( app );

	gtk_window_set_default_size( GTK_WINDOW( gte_window_main ), -1, -1 );

	gtk_window_maximize( GTK_WINDOW( gte_window_main ) );

	return;
}
