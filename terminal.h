#pragma once

void refresh_screen();

void clear_screen();

void set_cursor_position(int row, int col);

char *color(int bg, int fg);

void play_bell();

void make_block();

void make_unblock();

void configure_terminal();

void restore_terminal();
