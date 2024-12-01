void
gte_generate_titles
( void )
{
	g_free( gte_window_title_saved );

	g_free( gte_window_title_unsaved );

	gte_window_title_saved = g_file_get_path( gte_file );

	GString *title_unsaved = g_string_new( "* " );

	title_unsaved = g_string_append( title_unsaved, gte_window_title_saved );

	gte_window_title_unsaved = g_string_free_and_steal( title_unsaved ); 

	return;
}

