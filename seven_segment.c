#include "includes/seven_segment.h"

/** THE CODE IS EXTENDED FROM THE LAB TASK IN WEEK 6 - DISPLAYING DIGITS AND LETTERS A TO F IN 7 SEGEMENT DISPLAY*/

/**
 * We have eight pins, so we can represent the pins that
 * should be turned on as 8-bit values.
 *
 * We can then use bitwise operations and bitmasks to interpret these bitfields.
 *
 * By placing characters in an array, it allows the appropriate character to be refernced
 * as an index corresponding to ASCII values of the characters (i.e. B is 1 more than A)
 * the ASCII values are converted to fit the appropraite length of array, before calling the display
 *
 * (These bitfields are defined in the ordering of the ALL_SEGMENTS array
 * in the header file, i.e., from A in the most-significant bit to G, then
 * DP in the least-significant bit.)
 *
 */
// Array includes numbers, along with compulosory alphabet.
uint8_t values[] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
    0b11101110, // A
    0b00111110, // B
    0b10011100, // C
    0b01111010, // D
    0b10011110, // E
    0b10001110, // F
    0b11110110, // G
    0b01101110, // H
    0b00001100, // I
    0b01111000, // J
    0b01101110, // K
    0b00011100, // L
    0b10101000, // M
    0b00101010, // N
    0b11111100, // O
    0b11001110, // P
    0b11100110, // Q
    0b00001010, // R
    0b10110110, // S
    0b00011110, // T
    0b01111100, // U
    0b00111000, // V
    0b01010100, // W
    0b01101110, // X
    0b01110110, // Y
    0b11011010, // Z
    0b00000010, // dash
    0b00000000, // space
};

// ------------------------------------------------------------------
/**
 * Called once at the start of the program to initialize all of the GPIO
 * pins responsible for the seven-segment display.
 */
void ss_init()
{
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++)
    {
        gpio_init(ALL_SEGMENTS[i]);
        gpio_set_dir(ALL_SEGMENTS[i], GPIO_OUT);
    }

    ss_off();
}

/** Turn off the entire seven-segment display. */
void ss_off()
{
    // This display is common-anode, which means we need to turn a GPIO
    // pin ON for it to appear OFF on the display.
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++)
    {
        gpio_put(ALL_SEGMENTS[i], true);
    }
}

/** Turn on the entire seven-segment display. */
void ss_on()
{
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++)
    {
        gpio_put(ALL_SEGMENTS[i], false);
    }
}

/*
 * Function to convert ASCII value of character to correct index position.
 */
void ss_put(char c)
{
    // takes in input and then maps to correct starting index position

    int index;
    if (c >= 'A' && c <= 'Z')
        index = c - 'A' + 10;
    else if (c >= '0' && c <= '9')
        index = c - '0';
    else if (c == '-')
        index = 36;
    else if (c == ' ')
        index = 37;

    // this loop goes through the segments one by one and checks if that segment
    //  should be on or off then it turns it on or off
    for (unsigned int i = 0; i < 8; i++)
    {
        // Create a mask to check the current bit.
        //
        // Our first segment (A) starts in the most-significant
        // bit of the bitfield, so we need to 7 - i to map i to
        // the bit for the relevant segment as follows:
        //
        // i = 0 -> 7 - i = 7 - 0 = 7
        // i = 1 -> 7 - i = 7 - 1 = 6
        // ...
        // i = 6 -> 7 - i = 7 - 6 = 1
        // i = 7 -> 7 - i = 7 - 7 =  0
        unsigned int segmentBit = 1 << (7 - i);

        // When the segmentBit is 1 << 7, it produces 0b1000_0000.
        // Where 1 is in the most significant bit and all the other
        // bits are 0.

        // Bitwise-and the segmentBit with the bitfield for the
        // current number. If we get zero, it means that segment
        // should turned off, otherwise the bit is turned on.
        bool illuminateSegment = (segmentBit & values[index]); // != 0;

        // Recall, however, that because the display is common-anode,
        // whenever we want to illuminate a segment, we actually need
        // to pull that pin low (i.e., put false).
        gpio_put(
            ALL_SEGMENTS[i],
            !illuminateSegment);
    }
}