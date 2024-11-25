GtkAlertDialog *gte_dialog_closing;

const char *const gte_dialog_closing_button_labes[] = { "Close without saving", "Go back", NULL };

void
gte_dialog_closing_create
( void );

void
gte_dialog_closing_manage
( GObject* source_object, GAsyncResult* res, gpointer data );

