#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "pico/stdlib.h"

/** Top-center horizontal bar. */
#define SEGMENT_A 7 // Pin 10 (GPIO 07)

/** Top-right vertical bar */
#define SEGMENT_B 6 // Pin 09 (GPIO 06)

/** Bottom-right vertical bar */
#define SEGMENT_C 20 // Pin 26 (GPIO 20)

/** Bottom-center horizontal bar */
#define SEGMENT_D 19 // Pin 25 (GPIO 19)

/** Bottom-left vertical bar */
#define SEGMENT_E 18 // Pin 24 (GPIO 18)

/** Top-left vertical bar */
#define SEGMENT_F 8 // Pin 11 (GPIO 08)

/** Center horizontal bar */
#define SEGMENT_G 9 // Pin 12 (GPIO 09)

/** Decimal-point */
#define SEGMENT_DP 21 // Pin 27 (GPIO 21)

static const unsigned int ALL_SEGMENTS[] = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, SEGMENT_DP};

#define ALL_SEGMENTS_COUNT 8

void ss_init();
void ss_off();
void ss_on();
void ss_put(char c);

#endif