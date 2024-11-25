void
gte_save_callback
( gpointer *action, GtkWidget *window, bool saveAs )
{
	char *name = "Untitled Document";

	if (file_path[0] )
	{
		GFile *file = g_file_new_for_path( file_path );

		name = g_file_get_basename(file);

		if ( saveAs == FALSE )
		{
			textBufferToFile(file);

			EDITED = false;

			gtk_window_set_title(GTK_WINDOW(window), name);

			g_object_unref(file);

			return;
		}
	}

	gtk_file_dialog_set_title( fileDialog, name );

	gtk_file_dialog_save( fileDialog, GTK_WINDOW( topWindow ), NULL, gte_saveFileDialog_callback, NULL );

	return;
}

GtkWidget*
attachSaveMenu
( GtkWidget *window, GtkWidget *saveButton )
{
	GtkWidget *menuButton = gtk_menu_button_new();

	GMenu *saveMenu = g_menu_new();

	g_menu_append(saveMenu, "Save As", "win.saveAs");

	GSimpleAction *action = g_simple_action_new("saveAs", NULL);

	//g_signal_connect(action, "activate", G_CALLBACK(gte_save_callback), TRUE);

	g_action_map_add_action(G_ACTION_MAP(window), (GAction *)action);

	GtkWidget *menuPopover = gtk_popover_menu_new_from_model((GMenuModel *)saveMenu);
	gtk_menu_button_set_popover(GTK_MENU_BUTTON(menuButton), menuPopover);

	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_prepend(GTK_BOX(box), saveButton);
	gtk_box_append(GTK_BOX(box), menuButton);

	gtk_widget_add_css_class(box, "linked");

	return box;
}

GtkWidget*
gte_saveButton_create
( GtkWidget *window )
{
	GtkWidget *saveButton = gtk_button_new_with_mnemonic("_Save");

	g_signal_connect( saveButton, "clicked", G_CALLBACK(gte_save_callback), window );

	return saveButton;
}
