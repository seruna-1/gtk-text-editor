void
gte_dialog_file_manage_opening
( GObject* source_object, GAsyncResult* res, gpointer data )
{
	GtkFileDialog *dialog = GTK_FILE_DIALOG( source_object );

	GFile *file = gtk_file_dialog_open_finish( dialog, res, NULL );

	gte_file_open( file );

	return;
}

void
gte_dialog_file_manage_saving
( GObject *source_object, GAsyncResult *res, gpointer data )
{
	GtkFileDialog *dialog = GTK_FILE_DIALOG( source_object );

	GFile *file = gtk_file_dialog_save_finish( dialog, res, NULL );

	gte_file_open( file );

	gte_file_write();

	return;
}

