static void
gte_openFileButton_callback
( GtkWidget* openButton )
{
	gtk_file_dialog_open( fileDialog, topWindow, NULL, gte_openFileDialog_callback, NULL );

	return;
}

void
gte_titleBar_create
( void )
{
	GtkWidget *headerBar = gtk_header_bar_new();

	GtkWidget *saveButton = gte_saveButton_create( topWindow );

	GtkWidget *saveButtonAndMenu = attachSaveMenu( topWindow, saveButton );

	GtkWidget *openButton = gtk_button_new_with_mnemonic( "_Open" );

	g_signal_connect( openButton, "clicked", G_CALLBACK( gte_openFileButton_callback ), NULL );

	GtkFontDialog *fontDialog = gtk_font_dialog_new();

	GtkWidget *fontDialogButton = gtk_font_dialog_button_new( fontDialog );

	gtk_font_dialog_button_set_use_font( fontDialogButton, TRUE );

	//fontDescription = gtk_font_dialog_button_get_font_desc(fontDialogButton);

	gtk_header_bar_pack_start(GTK_HEADER_BAR(headerBar), saveButtonAndMenu);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(headerBar), openButton);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(headerBar), fontDialogButton);

	gtk_window_set_titlebar( topWindow, headerBar);

	return;
}
