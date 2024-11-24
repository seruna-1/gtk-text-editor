pkgconf_output=$(pkgconf --libs --cflags gtk4)

clang ${pkgconf_output} main.c -o gte


