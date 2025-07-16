#include "gte_text.h"

#include <stdio.h>

#include <stdlib.h>

#include "gte_cursor.h"

extern GtkWidget *gte_cursor_menu_button;

extern GtkWidget *gte_window_main;

extern gchar *gte_window_title_saved, *gte_window_title_unsaved;

extern GFile *gte_file_opened;

const char* UTF_16_BE_BOM = "\xFE\xFF";

const char* UTF_16_LE_BOM = "\xFF\xFE";

const char* UTF_32_BE_BOM = "\x00\x00\xFE\xFF";

const char* UTF_32_LE_BOM = "\xFF\xFE\x00\x00";

bool gte_unsaved;

GtkTextBuffer *gte_text_buffer;

GtkWidget *gte_text_view, *gte_text_view_scrolled_window;

gulong gte_text_view_signal_change_handler;

GtkEventController *gte_text_view_key_event_controller;

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

	if ( gte_file_opened != NULL )
	{
		gtk_window_set_title( GTK_WINDOW( gte_window_main ), gte_window_title_unsaved );
	}

	return;
}

void
gte_text_buffer_reply_cursor_position_change
( GObject *self, GParamSpec *pspec, gpointer user_data )
{
	GString *gte_cursor_label = user_data;

	GValue position = G_VALUE_INIT;

	g_object_get_property( self, "cursor-position", &position );

	GtkTextIter iter;

	gtk_text_buffer_get_iter_at_offset( gte_text_buffer, &iter, g_value_get_int( &position ) );

	int line = gtk_text_iter_get_line( &iter );

	int column = gtk_text_iter_get_line_offset( &iter );

	g_string_printf( gte_cursor_label, "Line: %d, Column: %d", line + 1, column + 1 );

	gtk_menu_button_set_label( GTK_MENU_BUTTON( gte_cursor_menu_button ), gte_cursor_label->str );

	return;
}

gboolean
gte_text_view_reply_key
( GtkEventControllerKey* self, guint key_value, guint key_code, GdkModifierType state, gpointer user_data )
{
	if ( ( key_value == GDK_KEY_Left ) || ( key_value == GDK_KEY_Right ) || ( key_value == GDK_KEY_Up ) || ( key_value == GDK_KEY_Down ) )
	{
		GValue position = G_VALUE_INIT;

		g_object_get_property( G_OBJECT( gte_text_buffer ), "cursor-position", &position );

		GtkTextIter iter;

		gtk_text_buffer_get_iter_at_offset( gte_text_buffer, &iter, g_value_get_int( &position ) );

		gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW( gte_text_view ), &iter, 0.0, TRUE, 0.5, 0.5 );
	}

	return GDK_EVENT_PROPAGATE;
}

void
gte_text_view_set_margins
( void )
{
	gtk_text_view_set_left_margin( GTK_TEXT_VIEW( gte_text_view ), 2 );

	gtk_text_view_set_right_margin( GTK_TEXT_VIEW( gte_text_view ), 2 );

	gtk_text_view_set_top_margin( GTK_TEXT_VIEW( gte_text_view ), 2 );

	gtk_text_view_set_bottom_margin( GTK_TEXT_VIEW( gte_text_view ), 2 );

	return;
}

void
gte_text_view_create
( GtkWidget *gte_window_main )
{
	gte_text_view_scrolled_window = gtk_scrolled_window_new();

	gte_text_view = gtk_text_view_new();

	gte_text_view_set_margins();

	gte_text_buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( gte_text_view ) );

	gte_text_view_signal_change_handler = g_signal_connect_data(
		gte_text_buffer,
		"changed",
		G_CALLBACK( gte_text_buffer_reply_changing ),
		NULL,
		NULL,
		G_CONNECT_DEFAULT
	);

	GString *gte_cursor_label = g_string_sized_new(40);

	g_signal_connect(
		gte_text_buffer,
		"notify::cursor-position",
		G_CALLBACK( gte_text_buffer_reply_cursor_position_change ),
		gte_cursor_label
	);

	gte_text_view_key_event_controller = gtk_event_controller_key_new();

	g_signal_connect_data(
		gte_text_view_key_event_controller,
		"key-pressed",
		G_CALLBACK( gte_text_view_reply_key ),
		NULL,
		NULL,
		G_CONNECT_AFTER
	);

	gtk_widget_add_controller (GTK_WIDGET( gte_text_view ), gte_text_view_key_event_controller);

	gtk_scrolled_window_set_child( GTK_SCROLLED_WINDOW( gte_text_view_scrolled_window ), gte_text_view );

	gtk_window_set_child( GTK_WINDOW( gte_window_main ), gte_text_view_scrolled_window );

	return;
}

