#include <gtk/gtk.h>

extern const gchar *gte_window_title_anonymous;

void
gte_window_generate_title_options
( void );

gboolean
gte_window_main_reply_closing
( GtkWidget* window_main, gpointer data );

void
gte_window_main_create
( GtkApplication *app );
