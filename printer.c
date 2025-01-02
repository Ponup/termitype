#include "printer.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "terminal.h"

struct _printer *bold_on(struct _printer *this)
{
    printf("\033[5m");
    return this;
}

struct _printer *bold_off(struct _printer *this)
{
    printf("\033[25m");
    return this;
}

struct _printer *underline_on(struct _printer *this)
{
    printf("\033[4m");
    return this;
}

struct _printer *underline_off(struct _printer *this)
{
    printf("\033[24m");
    return this;
}

printer_t *printer_pos(printer_t *this, int x, int y)
{
    set_cursor_position(x, y);
    return this;
}

printer_t *printer_text(printer_t *this, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char text[100];
    vsprintf(text, format, args);
    va_end(args);
    printf("%s", text);
    return this;
}

printer_t *printer_color(printer_t *this, color_t background, color_t foreground)
{
    printf("%s", color(background, foreground));
    return this;
}

void printer_flush(printer_t *this)
{
    refresh_screen();
    printf("\033[0m");
}

printer_t *new_printer()
{
    printer_t *printer = (printer_t *)malloc(sizeof(printer_t));
    printer->pos = printer_pos;
    printer->text = printer_text;
    printer->color = printer_color;
    printer->flush = printer_flush;
    printer->underline_off = underline_off;
    printer->underline_on = underline_on;
    printer->bold_off = bold_off;
    printer->bold_on = bold_on;
    return printer;
}

void delete_printer(printer_t *printer)
{
    // free(printer);
}
