#include "gte_file.h"

#include "gte_window_main.h"

extern GtkWidget *gte_window_main;

#include "gte_text.h"

extern GtkWidget *gte_text_view;

extern GtkTextBuffer *gte_text_buffer;

extern gulong gte_text_view_signal_change_handler;

#include "gte_cursor.h"

extern gchar *gte_window_title_saved, *gte_window_title_unsaved;

extern bool gte_unsaved;

#include "gte_dialog_file.h"

extern GtkFileDialog *gte_dialog_file;

GFile *gte_file_opened = NULL;

void
gte_file_open
( GFile *file_to_open )
{
	char *content = NULL;

	gsize len;

	if
	(
		( gte_file_opened != NULL )
		&& ( gte_file_opened != file_to_open )
	)
	{
		g_clear_object( &gte_file_opened );
	}

	if
	( file_to_open == NULL  )
	{
		gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_anonymous );
	}

	else
	{
		gte_file_opened = g_object_ref( file_to_open );

		int file_type = g_file_query_file_type( file_to_open, G_FILE_QUERY_INFO_NONE, NULL );

		gte_window_generate_title_options();

		gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_saved );

		if ( file_type & gte_file_invalid_types )
		{
			printf("Error on function [gte_set_file]. Could not open file. Invalid type.\n");
		}

		else if ( file_type != G_FILE_TYPE_UNKNOWN )
		{
			g_file_load_contents( file_to_open, NULL, &content, &len, NULL, NULL );

			if ( g_utf8_validate( content, len, NULL ) == FALSE )
			{
				char *encoding = gte_buffer_get_encoding( content, len );

				content = g_convert( content, len, "UTF-8", encoding, NULL, &len, NULL );
			}
		}
	}

	g_signal_handler_block( gte_text_buffer, gte_text_view_signal_change_handler );

	if ( content == NULL )
	{
		gtk_text_buffer_set_text( gte_text_buffer, "", 0 );
	}

	else
	{
		gtk_text_buffer_set_text( gte_text_buffer, content, len );

		g_free( content );
	}

	g_signal_handler_unblock( gte_text_buffer, gte_text_view_signal_change_handler );

	gte_unsaved = FALSE;

	gte_cursor_set_position( 0, 0);

	return;
}


void
gte_file_write
( void )
{
	if ( gte_file_opened == NULL )
	{
		gtk_file_dialog_set_title( gte_dialog_file, "unamed" );

		gtk_file_dialog_save( gte_dialog_file, GTK_WINDOW( gte_window_main ), NULL, gte_dialog_file_manage_saving, NULL );

		return;
	}

	gtk_text_view_set_editable( GTK_TEXT_VIEW( gte_text_view ), FALSE );

	GtkTextIter start, end;

	gtk_text_buffer_get_bounds( gte_text_buffer, &start, &end );

	char *text = gtk_text_buffer_get_text( gte_text_buffer, &start, &end, true );

	g_file_replace_contents( gte_file_opened, text, strlen( text ), NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL, NULL );

	g_free( text );

	gte_unsaved = FALSE;

	gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_saved );

	gtk_text_view_set_editable( GTK_TEXT_VIEW( gte_text_view ), TRUE );

	return;
}
