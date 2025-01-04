#pragma once

#include <sys/ioctl.h>
#include <termios.h>

struct _terminal_t {
    struct winsize size;
	struct termios oldt, newt;

    void (*configure)();
    void (*restore)();
    
    void (*flush)();
};

typedef struct _terminal_t terminal_t;

void init_terminal(terminal_t *terminal);

void terminal_configure();
void terminal_restore();

void refresh_screen();
void clear_screen();

void set_cursor_position(int row, int col);

char *color(int bg, int fg);

void play_bell();

void make_block();

void make_unblock();

void configure_terminal();

