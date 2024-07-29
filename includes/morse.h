#ifndef MORSE_H
#define MORSE_H

#include "pico/stdlib.h"

typedef struct morse_t
{
    uint8_t payload;
    bool defined;
} mchar;

mchar mchar_new();
bool mchar_is_defined(mchar *m_ch);
char mchar_decode(mchar m_ch);
void mchar_add_signal(mchar *m, bool is_dash);

#endif