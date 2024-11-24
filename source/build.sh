pkgconf_output=$(pkgconf --libs --cflags gtk4)

clang ${pkgconf_output} gtk-text-editor.c -o gtk-text-editor


