#include <gtk/gtk.h>

void
gte_dialog_file_create
( void );

void
gte_dialog_file_manage_opening
( GObject* source_object, GAsyncResult* res, gpointer data );

void
gte_dialog_file_manage_saving
( GObject *source_object, GAsyncResult *res, gpointer data );

