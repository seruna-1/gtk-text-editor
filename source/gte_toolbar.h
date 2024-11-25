PangoFontDescription *fontDescription;

GtkWidget *gte_toolbar, *gte_button_save, *gte_button_save_as, *gte_button_open;

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

