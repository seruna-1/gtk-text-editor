#include <gtk/gtk.h>

#define gte_file_invalid_types (G_FILE_TYPE_DIRECTORY | G_FILE_TYPE_MOUNTABLE | G_FILE_TYPE_SPECIAL)

void
gte_file_open
( GFile *file );

void
gte_file_write
( void );
