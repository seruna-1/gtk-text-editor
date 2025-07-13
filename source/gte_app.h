#include <gtk/gtk.h>

void
gte_app_close
( void );

void
gte_app_reply_open
( GApplication *app, GFile **files, int fileCount );

void
gte_app_reply_activate
( GtkApplication *app );
