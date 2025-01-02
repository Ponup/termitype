#pragma once

#include "colors.h"

struct _printer
{
    struct _printer *(*pos)(struct _printer *, int, int);
    struct _printer *(*text)(struct _printer *, const char *, ...);
    struct _printer *(*color)(struct _printer *, color_t, color_t);

    struct _printer *(*underline_on)(struct _printer *);
    struct _printer *(*underline_off)(struct _printer *);

    struct _printer *(*bold_on)(struct _printer *);
    struct _printer *(*bold_off)(struct _printer *);

    void (*flush)(struct _printer *);
};

typedef struct _printer printer_t;

printer_t *printer_pos(printer_t *, int, int);

printer_t *printer_text(printer_t *, const char *, ...);

printer_t *printer_color(printer_t *, color_t, color_t);

void printer_flush(printer_t *);

printer_t *new_printer();

void delete_printer(printer_t *);
