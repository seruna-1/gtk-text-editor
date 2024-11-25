GtkFileDialog* fileDialog;

void
gte_set_file
( GtkWidget *window, GFile *file );

void
gte_fileDialog_callback
( GObject* source_object, GAsyncResult* res, gpointer data );
