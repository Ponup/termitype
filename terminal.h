#pragma once

#include <sys/ioctl.h>

struct _terminal_t {
    struct winsize size;

    void (*flush)();
};

typedef struct _terminal_t terminal_t;

terminal_t* new_terminal();

void refresh_screen();

void clear_screen();

void set_cursor_position(int row, int col);

char *color(int bg, int fg);

void play_bell();

void make_block();

void make_unblock();

void configure_terminal();

void restore_terminal();
