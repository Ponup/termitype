#include "game_end.h"

#include <stdio.h>

#include "terminal.h"
#include "printer.h"

void start_game_end(const game_state_t *game_state)
{
    clear_screen();
    printer_t *p;
    printer_t *printer = p = new_printer();
    printer->pos(p, 10, 10)
        ->text(p, "Score: %d", game_state->score)
        ->pos(p, 10, 12)
        ->underline_on(p)
        ->text(p, "Press any key to exit")
        ->underline_off(p)
        ->pos(p, 0, 0)
        ->flush(p);
    delete_printer(printer);
    getchar();
}
