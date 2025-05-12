#include "minimath.h"


// just some small things

int isNumber(char c);
int chartoint(char c);

unsigned long stringtoul(String s)
{
    unsigned long num = 0;
    unsigned long ten = 1;

    // doesnt support negative numbers
    if (s.startsWith("-"))
    {
        return num;
    }

    int i;
    for (i = s.length() - 1; i >= 0 ; i--)
    {
        if (isNumber(s.charAt(i)))
        {
            num += chartoint(s.charAt(i)) * ten;
            ten += 9 * ten;
            continue;

        } else {
            break;
        }
    }
    
    return num;
}

int isNumber(char c)
{
    return c >= 48 && c <= 57;
}

int chartoint(char c)
{
    return isNumber(c) ? c - 48 : 0;
}