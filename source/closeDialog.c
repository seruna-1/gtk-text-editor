void
gte_closeDialog_create
( void )
{
	closeDialog = gtk_alert_dialog_new( "You have changes that have not been saved." );

	gtk_alert_dialog_set_cancel_button( closeDialog, 0);

	gtk_alert_dialog_set_default_button( closeDialog, 1);

	gtk_alert_dialog_set_buttons( closeDialog, closeDialog_buttons );
}

void
gte_closeDialog_callback
( GObject* source_object, GAsyncResult* res, gpointer data )
{
	GtkAlertDialog *dialog = GTK_ALERT_DIALOG( source_object );

	int button_clicked = gtk_alert_dialog_choose_finish( dialog, res, NULL );

	if ( button_clicked == 0 )
	{
		gte_close( topWindow );
	}

	return;
}

static void
gte_close
( GtkWidget* window )
{
	gtk_window_destroy( GTK_WINDOW( window ) );

	g_object_unref( app );

	exit( 0 );

	return;
}

gboolean
gte_closing
( GtkWidget* window, gpointer data )
{
	if ( EDITED == TRUE )
	{
		gtk_alert_dialog_choose( closeDialog, GTK_WINDOW( window ), NULL, gte_closeDialog_callback, NULL );
	}

	else
	{
		gte_close( window );
	}

	return TRUE;
}

