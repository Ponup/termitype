#include "game_intro.h"

#include <stdio.h>

#include "printer.h"
#include "colors.h"
#include "terminal.h"

static const char LOGO[12][25] = {
    "        \\   /          ",
    "         \\_/           ",
    "    __   / \\   __      ",
    "  -'  `. \\_/ .'  `-    ",
    "        \\/ \\/          ",
    "   _.---(   )--._      ",
    "_.'   _.-\\_/-._  `._   ",
    "     /   /_\\   \\       ",
    "    /   /___\\   \\      ",
    "   /   |_____|   \\     ",
    "_.'    | ___ |    `._  ",
    "        \\___/          "};

void start_game_intro()
{
    clear_screen();
    printf("\e[?25l");
    printer_t *printer = new_printer();
    printer
        ->color(printer, COLOR_BLUE, COLOR_WHITE)
        ->pos(printer, 10, 9)
        ->text(printer, "|------------------------|")
        ->pos(printer, 10, 10)
        ->text(printer, "| Press any key to start |")
        ->pos(printer, 10, 11)
        ->text(printer, "|------------------------|")
        ->flush(printer);
    for (int i = 0; i < 12; i++)
    {
        printer->pos(printer, 10, 12 + i);
        printer->bold_on(printer);
        printer->color(printer, COLOR_BLACK, COLOR_YELLOW);
        printer->text(printer, LOGO[i]);
        printer->flush(printer);
    }
    printf("\e[?25h");
    delete_printer(printer);
    getchar();
}