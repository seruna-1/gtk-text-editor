#include "gte_toolbar.h"

#include "gte_cursor.h"

extern GtkWidget *gte_cursor_menu_button;

#include "gte_dialog_file.h"

extern GtkWidget *gte_window_main;

#include "gte_file.h"

extern GFile *gte_file_opened;

extern GtkFileDialog *gte_dialog_file;

PangoFontDescription *fontDescription;

GtkWidget *gte_toolbar, *gte_button_save, *gte_button_save_as, *gte_button_open;

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
	if ( gte_file_opened != NULL )
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
	if ( gte_file_opened != NULL )
	{
		char* name = g_file_get_basename( gte_file_opened );

		gtk_file_dialog_set_title( gte_dialog_file, name );
	}

	gtk_file_dialog_set_title( gte_dialog_file, "unamed" );

	gtk_file_dialog_save( gte_dialog_file, GTK_WINDOW( gte_window_main ), NULL, gte_dialog_file_manage_saving, NULL );

	return;
}

void
gte_toolbar_create
( GtkWidget *gte_window_main )
{
	gte_toolbar = gtk_header_bar_new();

	gte_button_save = gtk_button_new_with_label( "Save" );

	g_signal_connect( gte_button_save, "clicked", G_CALLBACK( gte_button_save_reply_click ), NULL );

	gte_button_save_as = gtk_button_new_with_label( "Save As" );

	g_signal_connect( gte_button_save_as, "clicked", G_CALLBACK( gte_button_save_as_reply_click ), NULL );

	gte_button_open = gtk_button_new_with_label( "Open" );

	g_signal_connect( gte_button_open, "clicked", G_CALLBACK( gte_button_open_reply_click ), NULL );

	gte_cursor_menu_button_create();

	gtk_header_bar_pack_start( GTK_HEADER_BAR( gte_toolbar ), gte_button_save );

	gtk_header_bar_pack_start( GTK_HEADER_BAR( gte_toolbar ), gte_button_save_as );

	gtk_header_bar_pack_start( GTK_HEADER_BAR( gte_toolbar ), gte_button_open );

	gtk_header_bar_pack_end( GTK_HEADER_BAR( gte_toolbar ), gte_cursor_menu_button );

	gtk_window_set_titlebar( GTK_WINDOW( gte_window_main ), gte_toolbar );

	return;
}
