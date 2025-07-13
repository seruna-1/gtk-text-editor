pkgconf_output=$(pkgconf --libs --cflags gtk4)

clang ${pkgconf_output} main.c gte_app.c gte_cursor.c gte_file.c gte_window_main.c gte_dialog_file.c gte_toolbar.c gte_dialog_closing.c gte_text.c -o gte


