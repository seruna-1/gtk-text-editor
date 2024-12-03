gboolean
gte_window_main_reply_closing
( GtkWidget* window_main, gpointer data )
{
	if ( gte_unsaved == TRUE )
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
( void )
{
	gte_window_main = gtk_application_window_new( gte_app );

	gtk_window_set_default_size( GTK_WINDOW( gte_window_main ), -1, -1 );

	gtk_window_maximize( GTK_WINDOW( gte_window_main ) );

	return;
}