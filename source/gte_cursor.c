#include <gtk/gtk.h>

#include <stdlib.h>

#include "gte_text.h"

extern GtkTextBuffer *gte_text_buffer;

extern GtkWidget *gte_text_view;

extern gulong gte_text_view_signal_change_handler;

GtkWidget *gte_cursor_menu_button, *gte_cursor_popover, *gte_cursor_popover_box, *gte_cursor_popover_entry_line, *gte_cursor_popover_entry_column, *gte_cursor_popover_button_go;

void
gte_cursor_set_position
( int line, int column )
{
	g_signal_handler_block( gte_text_buffer, gte_text_view_signal_change_handler );

	GtkTextIter iter;

	gtk_text_buffer_get_iter_at_line_offset( gte_text_buffer, &iter, line, column );

	gtk_text_buffer_place_cursor( GTK_TEXT_BUFFER( gte_text_buffer ), &iter );

	g_signal_handler_unblock( gte_text_buffer, gte_text_view_signal_change_handler );

	gtk_widget_grab_focus( gte_text_view );

	gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW( gte_text_view ), &iter, 0.0, FALSE, 0.5, 0.5 );

	gtk_text_view_reset_cursor_blink( GTK_TEXT_VIEW( gte_text_view ) );

	return;
}

void
gte_cursor_popover_button_go_reply_click
( void )
{
	GtkEntryBuffer *entry_buffer_line = gtk_entry_get_buffer( GTK_ENTRY( gte_cursor_popover_entry_line ) );

	GtkEntryBuffer *entry_buffer_column = gtk_entry_get_buffer( GTK_ENTRY( gte_cursor_popover_entry_column ) );

	const char *buffer_line = gtk_entry_buffer_get_text( entry_buffer_line );

	const char *buffer_column = gtk_entry_buffer_get_text( entry_buffer_column );

	int line = atoi ( buffer_line );

	int column = atoi ( buffer_column );

	gte_cursor_set_position( line, column );

	return;
}

void
gte_cursor_popover_create
( void )
{
	gte_cursor_popover = gtk_popover_new();

	gtk_popover_set_has_arrow( GTK_POPOVER( gte_cursor_popover ), FALSE );

	gte_cursor_popover_box = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0 );

	gtk_popover_set_child( GTK_POPOVER( gte_cursor_popover ), gte_cursor_popover_box );

	GtkWidget *label_line = gtk_label_new( "Line:" );

	gtk_box_append( GTK_BOX( gte_cursor_popover_box ), label_line );

	gte_cursor_popover_entry_line = gtk_entry_new();

	gtk_box_append( GTK_BOX( gte_cursor_popover_box ), gte_cursor_popover_entry_line );

	GtkWidget *label_column = gtk_label_new( "Column:" );

	gtk_box_append( GTK_BOX( gte_cursor_popover_box ), label_column );

	gte_cursor_popover_entry_column = gtk_entry_new();

	gtk_box_append( GTK_BOX( gte_cursor_popover_box ), gte_cursor_popover_entry_column );

	gte_cursor_popover_button_go = gtk_button_new_with_label( "Go" );

	g_signal_connect_data( gte_cursor_popover_button_go, "clicked", G_CALLBACK( gte_cursor_popover_button_go_reply_click ), NULL, NULL, G_CONNECT_DEFAULT );

	gtk_box_append( GTK_BOX( gte_cursor_popover_box ), gte_cursor_popover_button_go );

	gtk_menu_button_set_popover( GTK_MENU_BUTTON( gte_cursor_menu_button ), gte_cursor_popover );

	return;
}

void
gte_cursor_menu_button_create
( void )
{
	gte_cursor_menu_button = gtk_menu_button_new();

	gtk_menu_button_set_always_show_arrow( GTK_MENU_BUTTON( gte_cursor_menu_button ), FALSE );

	gtk_menu_button_set_direction( GTK_MENU_BUTTON( gte_cursor_menu_button ), GTK_ARROW_NONE );

	gte_cursor_popover_create();

	gte_cursor_set_position( 1, 1 );

	return;
}
