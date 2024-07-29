#include <stdio.h>
#include "pico/stdlib.h"

#include "includes/morse.h"
#include "includes/seven_segment.h"

#define DASH_THRESHOLD 250
#define ERROR_THRESHOLD 700
#define CHAR_END_THRESHOLD 400

#define BUTTON_PIN 16

void init_button()
{
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, false);
    gpio_pull_down(BUTTON_PIN);
}

void init_program()
{
    printf("Starting morse decoder\n");

    for (int i = 0; i < 5; i++)
    {
        ss_put('-');
        sleep_ms(250);
        ss_put(' ');
        sleep_ms(250);
    }

    for (int i = 0; i < 5; i++)
    {
        ss_put('8');
        sleep_ms(250);
        ss_put(' ');
        sleep_ms(250);
    }

    printf("Seven segment display check complete\n");
}

int main()
{
    stdio_init_all();

    uint millis = 0;
    mchar morse_char = mchar_new();
    bool previous_state = false;
    bool current_state;
    bool too_long = false;

    init_button();
    ss_init();
    init_program();

    while (true)
    {
        current_state = gpio_get(BUTTON_PIN);

        if (previous_state != current_state)
        {
            /*
                Checks for an edge
                for rising edge records the morse character
                else displays hyphen
            */
            if (previous_state)
            {
                bool is_dash = millis > DASH_THRESHOLD;
                if (!too_long)
                {
                    printf("%c", is_dash ? '-' : '.');
                }

                mchar_add_signal(&morse_char, is_dash);
                ss_put(' ');
            }
            else
            {
                ss_put('-');
            }

            millis = 0;
        }
        // if unpressed for a while, display the character
        else if (!current_state && millis > CHAR_END_THRESHOLD && mchar_is_defined(&morse_char))
        {
            char c = mchar_decode(morse_char);
            if (!too_long && c != 0)
            {
                printf("\tdecoded character: %c\n", c);
                ss_put(c);
            }
            else if (too_long)
            {
            }
            else
            {
                printf("\tunrecognised character: 0x%x\n", morse_char.payload);
                ss_put('8');
            }

            too_long = false;
            morse_char = mchar_new();
        }
        // if held down for too long, log some errors
        else if (current_state && millis > ERROR_THRESHOLD && !too_long)
        {
            printf("Button pressed for too long\n");
            too_long = true;
            ss_put('8');
        }

        previous_state = current_state;

        millis += 1;
        sleep_ms(1);
    }
}
