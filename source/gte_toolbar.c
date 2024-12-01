void
gte_button_cursor_position_set
( int line, int column )
{
	if ( gte_button_cursor_position_label != NULL )
	{
		g_free( gte_button_cursor_position_label );

		gte_button_cursor_position_label = NULL;
	}

	gte_button_cursor_position_label = g_strdup_printf( "Line: %d, Column: %d", line, column );

	gtk_button_set_label( GTK_BUTTON( gte_button_cursor_position ), gte_button_cursor_position_label );

	return;
}

void
gte_button_open_reply_click
( GtkWidget* gte_button_open )
{
	gtk_file_dialog_open( gte_dialog_file, GTK_WINDOW( gte_window_main ), NULL, gte_dialog_file_manage_opening, NULL );

	return;
}

void
gte_button_save_reply_click
( GtkWidget *gte_button_save, gpointer data )
{
	if ( gte_file != NULL )
	{
		gte_file_write();
	}

	else
	{
		gtk_file_dialog_save( gte_dialog_file, GTK_WINDOW( gte_window_main ), NULL, gte_dialog_file_manage_saving, NULL );
	}

	return;
}

void
gte_button_save_as_reply_click
( GtkWidget* gte_button_save, gpointer data )
{
	if ( gte_file != NULL )
	{
		char* name = g_file_get_basename( gte_file );

		gtk_file_dialog_set_title( gte_dialog_file, name );
	}

	gtk_file_dialog_set_title( gte_dialog_file, "unamed" );

	gtk_file_dialog_save( gte_dialog_file, GTK_WINDOW( gte_window_main ), NULL, gte_dialog_file_manage_saving, NULL );

	return;
}

void
gte_toolbar_create
( void )
{
	gte_toolbar = gtk_header_bar_new();

	gte_button_save = gtk_button_new_with_label( "Save" );

	g_signal_connect( gte_button_save, "clicked", G_CALLBACK( gte_button_save_reply_click ), NULL );

	gte_button_save_as = gtk_button_new_with_label( "Save As" );

	g_signal_connect( gte_button_save_as, "clicked", G_CALLBACK( gte_button_save_as_reply_click ), NULL );

	gte_button_open = gtk_button_new_with_label( "Open" );

	g_signal_connect( gte_button_open, "clicked", G_CALLBACK( gte_button_open_reply_click ), NULL );

	gte_button_cursor_position = gtk_button_new();

	gte_button_cursor_position_set( 1, 1 );

	//GtkFontDialog* fontDialog = gtk_font_dialog_new();

	//GtkWidget* fontDialogButton = gtk_font_dialog_button_new( fontDialog );

	//gtk_font_dialog_button_set_use_font( GTK_FONT_DIALOG_BUTTON( fontDialogButton ), TRUE );

	//fontDescription = gtk_font_dialog_button_get_font_desc(fontDialogButton);

	gtk_header_bar_pack_start( GTK_HEADER_BAR( gte_toolbar ), gte_button_save );

	gtk_header_bar_pack_start( GTK_HEADER_BAR( gte_toolbar ), gte_button_save_as );

	gtk_header_bar_pack_start( GTK_HEADER_BAR( gte_toolbar ), gte_button_open );

	gtk_header_bar_pack_end( GTK_HEADER_BAR( gte_toolbar ), gte_button_cursor_position );

	//gtk_header_bar_pack_start( GTK_HEADER_BAR( headerBar ), fontDialogButton );

	gtk_window_set_titlebar( GTK_WINDOW( gte_window_main ), gte_toolbar );

	return;
}
