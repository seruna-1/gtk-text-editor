char* OPEN_FILE_PATH = "";

GtkFileDialog* fileDialog;

enum fileDialogMode { open, save };

void
setActiveFile
( GtkWidget *window, GFile *file );

void
gte_fileDialog_callback
( GObject* source_object, GAsyncResult* res, gpointer data );
