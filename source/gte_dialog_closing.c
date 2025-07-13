#include "gte_dialog_closing.h"

#include "gte_app.h"

GtkAlertDialog *gte_dialog_closing;

extern gchar *gte_window_title_unsaved;

const char* const gte_dialog_closing_button_labels[] = { "Close without saving", "Go back", NULL };

void
gte_dialog_closing_create
( void )
{
	gte_dialog_closing = gtk_alert_dialog_new( "You have changes that have not been saved." );

	gtk_alert_dialog_set_cancel_button( gte_dialog_closing, 1);

	gtk_alert_dialog_set_default_button( gte_dialog_closing, 1);

	gtk_alert_dialog_set_buttons( gte_dialog_closing, gte_dialog_closing_button_labels );

	return;
}

void
gte_dialog_closing_manage
( GObject* source_object, GAsyncResult* res, gpointer data )
{
	GtkAlertDialog* dialog = GTK_ALERT_DIALOG( source_object );

	int button_clicked = gtk_alert_dialog_choose_finish( dialog, res, NULL );

	if ( button_clicked == 0 )
	{
		gte_app_close();
	}

	return;
}

