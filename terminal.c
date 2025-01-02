#include "terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "colors.h"

static struct termios oldt, newt;
static int flags;

void refresh_screen()
{
    fflush(stdout);
}

void clear_screen()
{
    printf("\033[2J");
}

void set_cursor_position(int row, int col)
{
    printf("\033[%d;%dH", col, row);
}

char *color(int bg, int fg)
{
    char *text = malloc(100);
    sprintf(text, "\033[%d;%dm", fg, bg + 10);
    return text;
}

void play_bell()
{
    printf("%c", '\a');
}

void make_block()
{
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void make_unblock()
{
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void configure_terminal()
{
    flags = fcntl(STDIN_FILENO, F_GETFL, 0);

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restore_terminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    clear_screen();
}
