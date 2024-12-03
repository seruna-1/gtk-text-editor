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
	gte_unsaved = TRUE;

	if ( gte_file != NULL )
	{
		gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_unsaved );
	}

	return;
}

void
gte_text_buffer_reply_cursor_position_change
( GObject *self, GParamSpec *pspec, gpointer user_data )
{
	GValue position = G_VALUE_INIT;

	g_object_get_property( self, "cursor-position", &position );

	GtkTextIter iter;

	gtk_text_buffer_get_iter_at_offset( gte_text_buffer, &iter, g_value_get_int( &position ) );

	int line = gtk_text_iter_get_line( &iter );

	int column = gtk_text_iter_get_line_offset( &iter );

	g_free( gte_cursor_label );

	gte_cursor_label = g_strdup_printf( "Line: %d, Column: %d", line + 1, column + 1 );

	gtk_menu_button_set_label( GTK_MENU_BUTTON( gte_cursor_menu_button ), gte_cursor_label );

	return;
}

void
gte_text_view_create
( void )
{
	gte_text_view_scrolled_window = gtk_scrolled_window_new();

	gte_text_view = gtk_text_view_new();

	gte_text_buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( gte_text_view ) );

	gtk_text_view_set_left_margin( GTK_TEXT_VIEW( gte_text_view ), 2 );

	gtk_text_view_set_right_margin( GTK_TEXT_VIEW( gte_text_view ), 2 );

	gtk_text_view_set_top_margin( GTK_TEXT_VIEW( gte_text_view ), 2 );

	gtk_text_view_set_bottom_margin( GTK_TEXT_VIEW( gte_text_view ), 2 );

	gte_text_view_signal_change_handler = g_signal_connect_data( gte_text_buffer, "changed", G_CALLBACK( gte_text_buffer_reply_changing ), NULL, NULL, G_CONNECT_DEFAULT );

	g_signal_connect( gte_text_buffer, "notify::cursor-position", G_CALLBACK( gte_text_buffer_reply_cursor_position_change ), NULL );

	gtk_scrolled_window_set_child( GTK_SCROLLED_WINDOW( gte_text_view_scrolled_window ), gte_text_view );

	gtk_window_set_child( GTK_WINDOW( gte_window_main ), gte_text_view_scrolled_window );

	return;
}

