void
gte_file_open
( GFile *file )
{
	int file_type;

	char *content = NULL;

	gsize len;

	if ( ( gte_file != NULL ) && ( gte_file != file ) )
	{
		g_clear_object( &gte_file );
	}

	if ( file == NULL  )
	{
		gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_anonymous );
	}

	else
	{
		gte_file = g_object_ref( file );

		file_type = g_file_query_file_type( file, G_FILE_QUERY_INFO_NONE, NULL );

		gte_generate_titles();

		gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_saved );

		if ( file_type & gte_file_invalid_types )
		{
			printf("Error on function [gte_set_file]. Could not open file. Invalid type.\n");
		}

		else if ( file_type != G_FILE_TYPE_UNKNOWN )
		{
			g_file_load_contents( file, NULL, &content, &len, NULL, NULL );

			if ( g_utf8_validate( content, len, NULL ) == FALSE )
			{
				char *encoding = gte_buffer_get_encoding( content, len );

				content = g_convert( content, len, "UTF-8", encoding, NULL, &len, NULL );
			}
		}
	}

	g_signal_handler_block( gte_text_buffer, gte_textview_signal_change_handler );

	if ( content == NULL )
	{
		gtk_text_buffer_set_text( gte_text_buffer, "", 0 );
	}

	else
	{
		gtk_text_buffer_set_text( gte_text_buffer, content, len );

		g_free( content );
	}

	g_signal_handler_unblock( gte_text_buffer, gte_textview_signal_change_handler );

	gte_unsaved = FALSE;

	return;
}


void
gte_file_write
( void )
{
	if ( gte_file == NULL )
	{
		gtk_file_dialog_set_title( gte_dialog_file, "unamed" );

		gtk_file_dialog_save( gte_dialog_file, GTK_WINDOW( gte_window_main ), NULL, gte_dialog_file_manage_saving, NULL );

		return;
	}

	gtk_text_view_set_editable( GTK_TEXT_VIEW( gte_textview ), FALSE );

	GtkTextIter start, end;

	gtk_text_buffer_get_bounds( gte_text_buffer, &start, &end );

	char *text = gtk_text_buffer_get_text( gte_text_buffer, &start, &end, true );

	g_file_replace_contents( gte_file, text, strlen( text ), NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL, NULL );

	g_free( text );

	gte_unsaved = FALSE;

	gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_saved );

	gtk_text_view_set_editable( GTK_TEXT_VIEW( gte_textview ), TRUE );

	return;
}
