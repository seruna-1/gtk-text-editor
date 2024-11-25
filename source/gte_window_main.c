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

