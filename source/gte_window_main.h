#include <gtk/gtk.h>

void
gte_window_create_title_options
( GFile *gte_file_opened );

void
gte_window_update_title
( GFile *gte_file_opened, bool gte_unsaved );

gboolean
gte_window_main_reply_closing
( GtkWidget* window_main, gpointer data );

void
gte_window_main_create
( GtkApplication *app );
