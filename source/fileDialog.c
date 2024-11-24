void
setActiveFile
( GtkWidget *window, GFile *file )
{
	EDITED = FALSE;

	gtk_window_set_title( ( GtkWindow* ) window , g_file_get_basename( file ) );

	OPEN_FILE_PATH = g_file_get_path( file );

	g_object_unref(file);

	return;
}

void
gte_openFileDialog_callback
( GObject* source_object, GAsyncResult* res, gpointer data )
{
	GtkFileDialog* dialog = GTK_FILE_DIALOG( source_object );

	GFile* file = gtk_file_dialog_open_finish( dialog, res, NULL );

	fileToTextBuffer(file);

	setActiveFile( topWindow, file );

	return;
}

void
gte_saveFileDialog_callback
( GObject* source_object, GAsyncResult* res, gpointer data )
{
	GtkFileDialog* dialog = source_object;

	GFile* file = gtk_file_dialog_save_finish( dialog, res, NULL );

	textBufferToFile(file);

	setActiveFile( topWindow, file );

	return;
}

