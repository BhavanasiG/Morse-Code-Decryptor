#include "includes/morse.h"

char numerical_values(mchar m_input);
char single_signal(mchar m_input);
char quad_signal(mchar m_input);
char double_signal(mchar m_input);
char triple_signal(mchar m_input);

/*
    This script decodes morse input into characters
    So that they can be output on LEDs
*/

mchar mchar_new()
{
    /*
        intializes a new morse character
    */
    mchar m;
    m.payload = 0;
    m.defined = false;

    return m;
}

bool mchar_is_defined(mchar *m_ch)
{
    /*
        Checks if a signal has been added
    */
    return m_ch->defined;
}

inline char mchar_decode(mchar m_ch)
{
    /*
        Translates morse_character to a alphabet\number
    */
    switch (m_ch.payload >> 5)
    {
    case 1:
        return single_signal(m_ch);

    case 2:
        return double_signal(m_ch);

    case 3:
        return triple_signal(m_ch);

    case 4:
        return quad_signal(m_ch);

    case 5:
        return numerical_values(m_ch);
    default:
        return 0;
    }
}

/*
    updates morse input if needed
*/
void mchar_add_signal(mchar *m, bool is_dash)
{
    /*
        Defines morse character
        by updating the value of dash and dots
    */
    m->payload = ((0b00011111 & m->payload) << 1) | (0b11100000 & m->payload);
    m->payload += is_dash;
    m->payload += 0b00100000;

    m->defined = true;

    /*
        Initial Logic
        m->value >>= 1
        m->value += is_dash
        m->length ++
    */
}

/*
    Following methods are used to simplify decoding of morse code
*/
inline char numerical_values(mchar m_input)
{
    switch (m_input.payload)
    {
    case 0b10111111:
        return '0';

    case 0b10101111:
        return '1';

    case 0b10100111:
        return '2';

    case 0b10100011:
        return '3';

    case 0b10100001:
        return '4';

    case 0b10100000:
        return '5';

    case 0b10110000:
        return '6';

    case 0b10111000:
        return '7';

    case 0b10111100:
        return '8';

    case 0b10111110:
        return '9';
    default:
        return 0;
    }
}

inline char single_signal(mchar m_input)
{
    switch (m_input.payload)
    {
    case 0b00100000:
        return 'E';

    case 0b00100001:
        return 'T';
    default:
        return 0;
    }
}

inline char quad_signal(mchar m_input)
{
    switch (m_input.payload)
    {
    case 0b10000000:
        return 'H';

    case 0b10000001:
        return 'V';

    case 0b10000010:
        return 'F';

    case 0b10000100:
        return 'L';

    case 0b10000110:
        return 'P';

    case 0b10000111:
        return 'J';

    case 0b10001000:
        return 'B';

    case 0b10001001:
        return 'X';

    case 0b10001010:
        return 'C';

    case 0b10001011:
        return 'Y';

    case 0b10001100:
        return 'Z';

    case 0b10001101:
        return 'Q';
    default:
        return 0;
    }
}

inline char double_signal(mchar m_input)
{
    switch (m_input.payload)
    {
    case 0b01000000:
        return 'I';

    case 0b01000001:
        return 'A';

    case 0b01000010:
        return 'N';

    case 0b01000011:
        return 'M';
    default:
        return 0;
    }
}

inline char triple_signal(mchar m_input)
{
    switch (m_input.payload)
    {
    case 0b01100000:
        return 'S';

    case 0b01100001:
        return 'U';

    case 0b01100010:
        return 'R';

    case 0b01100011:
        return 'W';

    case 0b01100100:
        return 'D';

    case 0b01100101:
        return 'K';

    case 0b01100110:
        return 'G';

    case 0b01100111:
        return 'O';
    default:
        return 0;
    }
}
/*  Methods of Decoding end here  */