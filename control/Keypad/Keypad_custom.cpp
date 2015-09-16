#include <Keypad.h>

char Keypad::getKey_custom_pressed()
{
    single_key = true;

    if (getKeys() && key[0].stateChanged && (key[0].kstate==PRESSED))
        return key[0].kchar;

    single_key = false;

    return NO_KEY;
}


char Keypad::getKey_custom_released()
{
    single_key = true;

    if (getKeys() && key[0].stateChanged && (key[0].kstate==RELEASED))
        return key[0].kchar;

    single_key = false;

    return NO_KEY;
}
