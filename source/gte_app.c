void
gte_app_reply_open
( GApplication *app, GFile **files, int fileCount )
{
	if ( fileCount > 1 )
	{
		fprintf( stderr, "ERROR: Pass only one file as argument!\n" );

		exit( EXIT_FAILURE );
	}

	gte_file = g_object_ref( files[0] );

	g_application_activate( app );

	return;
}

void
gte_app_reply_activate
( GtkApplication *app )
{
	gte_window_main_create();

	gte_text_view_create();

	gte_toolbar_create();

	gte_dialog_closing_create();

	gte_dialog_file = gtk_file_dialog_new();

	gte_file_open( gte_file );

	gtk_window_present( GTK_WINDOW( gte_window_main ) );

	g_signal_connect( gte_window_main, "close-request", G_CALLBACK( gte_window_main_reply_closing ), NULL );

	return;
}

void
gte_app_close
( void )
{
	gtk_window_destroy( GTK_WINDOW( gte_window_main ) );

	g_object_unref( gte_app );

	exit( 0 );

	return;
}

