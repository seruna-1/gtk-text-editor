GtkWidget *gte_textview_scrolled_window, *gte_textview;

char*
gte_buffer_get_encoding
( const char* data, size_t size );

void
gte_text_buffer_reply_changing
( GtkWidget* textBuffer, gpointer data  );

void
gte_textview_create
( void );
