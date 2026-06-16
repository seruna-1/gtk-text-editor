$(CC) = gcc
FLAGS = -Wall -Wextra -Wpedantic -Wconversion

SRCDIR = source

SRCS := main.c gte_app.c gte_cursor.c gte_file.c gte_window_main.c gte_dialog_file.c gte_toolbar.c gte_dialog_closing.c gte_text.c
OUTPUT = -o gte

SRC_FILES := $(addprefix $(SRCDIR)/, $(SRCS))

PKG := $(shell pkg-config --cflags --libs gtk4)

all:
	clang $(SRC_FILES) $(OUTPUT) $(PKG) 

warn:
	$(CC) $(SRC_FILES) $(OUTPUT) $(PKG) $(FLAGS)
