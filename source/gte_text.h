GtkTextBuffer *gte_text_buffer;

bool gte_unsaved;

GtkWidget *gte_text_view, *gte_text_view_scrolled_window;

gulong gte_text_view_signal_change_handler;

char*
gte_buffer_get_encoding
( const char* data, size_t size );

void
gte_text_buffer_reply_changing
( GtkWidget* textBuffer, gpointer data  );

void
gte_text_view_create
( void );
