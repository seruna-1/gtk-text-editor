#include "gte_file.h"

#include "gte_window_main.h"

extern GtkWidget *gte_window_main;

#include "gte_text.h"

extern GtkWidget *gte_text_view;

extern GtkTextBuffer *gte_text_buffer;

extern gulong gte_text_view_signal_change_handler;

#include "gte_cursor.h"

extern bool gte_unsaved;

#include "gte_dialog_file.h"

extern GtkFileDialog *gte_dialog_file;

GFile *gte_file_opened = NULL;

void
gte_file_open
( GFile *file_to_open )
{
	char *content = NULL;

	gsize len = 0;

	if ( file_to_open != NULL  )
	{
		int file_type = g_file_query_file_type( file_to_open, G_FILE_QUERY_INFO_NONE, NULL );

		if ( file_type & gte_file_invalid_types )
		{
			printf( "Error on function [gte_file_open]. Could not open file. Invalid type: %d.\n", file_type );

			return;
		}
		else if ( file_type == G_FILE_TYPE_UNKNOWN )
		{
			printf( "Error on function [gte_file_open]. Could not open file. Type unknown." );

			return;
		}
		else
		{
			g_file_load_contents( file_to_open, NULL, &content, &len, NULL, NULL );

			if ( g_utf8_validate( content, len, NULL ) == FALSE )
			{
				char *encoding = gte_buffer_get_encoding( content, len );

				content = g_convert( content, len, "UTF-8", encoding, NULL, &len, NULL );
			}
		}
	}

	g_clear_object( &gte_file_opened );

	gte_file_opened = g_object_ref( file_to_open );

	g_signal_handler_block( gte_text_buffer, gte_text_view_signal_change_handler );

	gtk_text_buffer_set_text( gte_text_buffer, content, len );

	g_free( content );

	g_signal_handler_unblock( gte_text_buffer, gte_text_view_signal_change_handler );

	gte_unsaved = false;

	gte_window_create_title_options( gte_file_opened );

	gte_window_update_title( gte_file_opened, gte_unsaved );

	gte_cursor_set_position( 0, 0);

	return;
}

void
gte_file_write
( void )
{
	gtk_text_view_set_editable( GTK_TEXT_VIEW( gte_text_view ), FALSE );

	GtkTextIter start, end;

	gtk_text_buffer_get_bounds( gte_text_buffer, &start, &end );

	char *text = gtk_text_buffer_get_text( gte_text_buffer, &start, &end, true );

	g_file_replace_contents( gte_file_opened, text, strlen( text ), NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL, NULL );

	g_free( text );

	gte_unsaved = false;

	gte_window_update_title( gte_file_opened, gte_unsaved );

	gtk_text_view_set_editable( GTK_TEXT_VIEW( gte_text_view ), TRUE );

	return;
}
