void
gte_set_file
( GtkWidget *window, GFile *file )
{
	EDITED = FALSE;

	char* new_file_path = g_file_get_path( file );

	free( file_path );

	file_path = new_file_path;

	gtk_window_set_title( GTK_WINDOW( window ) , file_path );

	g_object_unref( file );

	return;
}

void
gte_openFileDialog_callback
( GObject* source_object, GAsyncResult* res, gpointer data )
{
	GtkFileDialog* dialog = GTK_FILE_DIALOG( source_object );

	GFile* file = gtk_file_dialog_open_finish( dialog, res, NULL );

	fileToTextBuffer(file);

	gte_set_file( GTK_WINDOW( topWindow ), file );

	return;
}

void
gte_saveFileDialog_callback
( GObject* source_object, GAsyncResult* res, gpointer data )
{
	GtkFileDialog* dialog = GTK_FILE_DIALOG( source_object );

	GFile* file = gtk_file_dialog_save_finish( dialog, res, NULL );

	textBufferToFile( file );

	gte_set_file( GTK_WINDOW( topWindow ), file );

	return;
}

