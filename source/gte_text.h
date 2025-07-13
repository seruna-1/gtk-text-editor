#include <gtk/gtk.h>

char*
gte_buffer_get_encoding
( const char* data, size_t size );

void
gte_text_buffer_reply_changing
( GtkWidget* textBuffer, gpointer data  );

void
gte_text_view_create
( GtkWidget *gte_window_main );
