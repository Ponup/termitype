#include "game.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "terminal.h"
#include "printer.h"

#define TEXT "this is a test"

void sleep_microseconds(unsigned int microseconds) {
    struct timespec ts;
    ts.tv_sec = microseconds / 1000000;
    ts.tv_nsec = (microseconds % 1000000) * 1000;
    nanosleep(&ts, NULL);
}

void init_game_state(game_state_t *game_state)
{
    game_state->text_pos = 0;
    game_state->score = 0;
    game_state->start_time = time(nullptr);
}

void print_time(const game_state_t *game_state)
{
    time_t now = time(nullptr);
    long seconds = now - game_state->start_time;

    printer_t *printer = new_printer();
    printer->pos(printer, 1, 1)
        ->color(printer, COLOR_BLACK, COLOR_RED)
        ->text(printer, "Time:")
        ->color(printer, COLOR_BLACK, COLOR_GREEN);
    if (seconds > 5)
    {
        printer->bold_on(printer);
    }
    printer->text(printer, " %d", seconds);
    if (seconds > 5)
    {
        printer->bold_off(printer);
    }
    printer->flush(printer);
    delete_printer(printer);
}

void print_score(const game_state_t *game_state, const terminal_t* terminal, bool error)
{
    printer_t *printer = new_printer();
    printer->pos(printer, terminal->size.ws_col - 15, 1)
        ->text(printer, "Score: %d", game_state->score)
        ->flush(printer);
    delete_printer(printer);
}

void print_line(const game_state_t *game_state)
{
    printer_t *printer = new_printer();
    printer->pos(printer, 1, 20);
    printer->color(printer, COLOR_BLACK, COLOR_GREEN);
    for (int i = 0; i < game_state->text_pos; i++)
    {
        printer->text(printer, "%c", TEXT[i]);
    }
    for (int i = game_state->text_pos; i < sizeof(TEXT); i++)
    {
        printer->color(printer, COLOR_BLACK, COLOR_RED)
            ->text(printer, "%c", TEXT[i]);
    }
    printer->flush(printer);
    delete_printer(printer);
}

void play_game(game_state_t* game_state, const terminal_t *terminal)
{
    make_block();
    init_game_state(game_state);
    while (true)
    {
        bool error = true;
        clear_screen();
        print_time(game_state);
        print_score(game_state, terminal, error);
        print_line(game_state);
        int c = getchar();
        if (c != EOF)
        {
            if (TEXT[game_state->text_pos] == c)
            {
                game_state->text_pos++;
                game_state->score++;
            }
            else
            {
                play_bell();
                error = true;
                if (game_state->score > 0)
                    game_state->score--;
            }
            if (game_state->text_pos == strlen(TEXT))
            {
                break;
            }
        }
        refresh_screen();
        ioctl(STDOUT_FILENO, TIOCGWINSZ, terminal->size);
        sleep_microseconds(300);
    }
}
