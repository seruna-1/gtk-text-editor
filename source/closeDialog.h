GtkAlertDialog* closeDialog;

const char* closeDialog_buttons[] = { "Close without saving", "Go back", NULL };

void
gte_closeDialog_create
( void );

void
gte_closeDialog_choose
( void );

void
gte_closeDialog_callback
( GObject *source_object, GAsyncResult* res, gpointer data );

static void
gte_close
( GtkWidget *window );

gboolean
gte_closing
( GtkWidget* window, gpointer data );
