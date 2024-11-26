PangoFontDescription *fontDescription;

GtkWidget *gte_toolbar, *gte_button_save, *gte_button_save_as, *gte_button_open, *gte_button_cursor_position;

gchar *gte_button_cursor_position_label;

void
gte_button_cursor_position_set
( int line, int column );

void
gte_button_open_reply_click
( GtkWidget* gte_button_open );

void
gte_button_save_reply_click
( GtkWidget* gte_button_save, gpointer data );

void
gte_button_save_as_reply_click
( GtkWidget* gte_button_save, gpointer data );

void
gte_toolbar_create
( void );

