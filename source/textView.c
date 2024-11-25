const char* UTF_16_BE_BOM = "\xFE\xFF";

const char* UTF_16_LE_BOM = "\xFF\xFE";

const char* UTF_32_BE_BOM = "\x00\x00\xFE\xFF";

const char* UTF_32_LE_BOM = "\xFF\xFE\x00\x00";

char*
gte_buffer_get_encoding
( const char* data, size_t size )
{
	if ( size >= 4 )
	{
		if ( memcmp( data, UTF_32_LE_BOM, 4 ) == 0 )
		{
			return "UTF-32-LE";
		}

		else if ( memcmp( data, UTF_32_BE_BOM, 4 ) == 0 )
		{
			return "UTF-32-BE";
		}
	}

	else if (size >= 2)
	{
		if ( memcmp( data, UTF_16_LE_BOM, 2 ) == 0 )
		{
			return "UTF-16-LE";
		}

		else if ( memcmp( data, UTF_16_BE_BOM, 2 ) == 0 )
		{
			return "UTF-16-BE";
		}
	}

	return "ISO-8859-1";
}

void
gte_text_buffer_reply_changing
( GtkWidget* textBuffer, gpointer data  )
{
	if ( gte_unsaved == TRUE )
	{
		return;
	}

	gte_unsaved = TRUE;

	g_free( gte_window_title_unsaved );

	GString* title_unsaved = g_string_new( "* " );

	title_unsaved = g_string_append( title_unsaved, gte_file_path );

	gte_window_title_unsaved = g_string_free_and_steal( title_unsaved ); 

	gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_unsaved );

	return;
}

void
gte_textview_create
( void )
{
	gte_textview_scrolled_window = gtk_scrolled_window_new();

	gte_textview = gtk_text_view_new();

	gte_text_buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( gte_textview ) );

	gtk_text_view_set_left_margin( GTK_TEXT_VIEW( gte_textview ), 2 );

	gtk_text_view_set_right_margin( GTK_TEXT_VIEW( gte_textview ), 2 );

	gtk_text_view_set_top_margin( GTK_TEXT_VIEW( gte_textview ), 2 );

	gtk_text_view_set_bottom_margin( GTK_TEXT_VIEW( gte_textview ), 2 );

	g_signal_connect( gte_text_buffer, "changed", G_CALLBACK( gte_text_buffer_reply_changing ), NULL );

	gtk_scrolled_window_set_child( GTK_SCROLLED_WINDOW( gte_textview_scrolled_window ), gte_textview );

	gtk_window_set_child( GTK_WINDOW( gte_window_main ), gte_textview_scrolled_window );

	return;
}

