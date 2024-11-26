void
gte_file_open
( GFile *file )
{
	if ( file == NULL )
	{
		gte_file_open_anonymous();

		return;
	}

	g_free( gte_file_path );

	gte_file_path = g_file_get_path( file );

	if ( gte_file_path == NULL )
	{
		printf( "Error on function [gte_set_file]. [gte_file_path] is NULL, but should not be." );

		return;
	}

	int file_type = g_file_query_file_type( file, G_FILE_QUERY_INFO_NONE, NULL );

	if ( file_type & gte_file_invalid_types )
	{
		printf("Error on function [gte_set_file]. Could not open file. Invalid type.\n");

		return;
	}

	if ( file_type != G_FILE_TYPE_UNKNOWN )
	{
		gte_file_read( file );
	}

	else
	{
		gtk_text_buffer_set_text( gte_text_buffer, "", 0 );
	}

	//g_object_unref( gte_file_gfile );

	gte_file_gfile = file;

	gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_file_path );

	gte_unsaved = FALSE;

	return;
}

void
gte_file_open_anonymous
( void )
{
	gte_unsaved = FALSE;

	if ( gte_file_gfile != NULL )
	{
		//g_object_unref( gte_file_gfile );

		gte_file_gfile = NULL;
	}

	g_free( gte_file_path );

	gte_file_path = NULL;

	gtk_text_buffer_set_text( gte_text_buffer, "", 0 );

	gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_fallback );

	return;
}

bool
gte_file_read
( GFile *file )
{
	char* text;

	gsize len;

	g_file_load_contents( file, NULL, &text, &len, NULL, NULL );

	if ( g_utf8_validate( text, len, NULL ) == FALSE )
	{
		char* encoding = gte_buffer_get_encoding( text, len );

		text = g_convert( text, len, "UTF-8", encoding, NULL, &len, NULL );
	}

	gtk_text_buffer_set_text( gte_text_buffer, text, len );

	g_free( text );

	return true;
}


void
gte_file_write
( GFile *file )
{
	GtkTextIter start, end;

	if ( file == NULL )
	{
		printf( "Error on function [gte_file_write]. [gte_file_gfile] is NULL, so there is no destination to write to.\n" );

		return;
	}

	gtk_text_buffer_get_bounds( gte_text_buffer, &start, &end );

	char *text = gtk_text_buffer_get_text( gte_text_buffer, &start, &end, true );

	g_file_replace_contents( file, text, strlen( text ), NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL, NULL );

	g_free( text );

	gte_unsaved = FALSE;

	gte_file_open( file );

	return;
}

