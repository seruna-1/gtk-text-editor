#include <gtk/gtk.h>

extern const char* const gte_dialog_closing_button_labels[];

void
gte_dialog_closing_create
( void );

void
gte_dialog_closing_manage
( GObject* source_object, GAsyncResult* res, gpointer data );

