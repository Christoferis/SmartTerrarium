#include "strutils.h"
#include <math.h>
#include <float.h>

// code lifted from: https://github.com/Christoferis/PraktikumMechatronik/blob/main/src/pm_bot/strutil.c

int isnumeric(char c);

int strtoint(String string)
{
    int out = 0;
    int i = 0;
    int negative = 0;
    char current = string.charAt(0);

    // check for minus sign at the beginning
    if (current == '-')
    {
        current = string.charAt(1);
        negative = 1;
    }

    while (isnumeric(current))
    {
        out = out * 10 + (current - 48);
        i++;

        // one bit offset due to negative number
        current = string[i + negative];
    }

    return negative ? out * -1 : out;
}

String inttostr(int num)
{
    String out = "";
    out.reserve(8);

    int negative = 0;

    if (num < 0)
    {
        negative = 1;
        num *= -1;
        out += '-';
    }

    int i;
    int digits = num == 0 ? 1 : (int)(floor(log10((double)num)) + 1) + negative;
    int prev = 0;

    for (i = negative; i < digits; i++)
    {
        // isolates current digit
        int isolated = num / pow(10, digits - 1 - i) - prev;
        out += isolated + 48;
        prev = (prev + isolated) * 10;
    }

    return out;
}


// right now: support for up to 4 digits before and 9 digits after decimal (more research needed)
String floattostr(float num)
{
    String eger = inttostr((int) num);
    num = num - ((int) num);

    String out = "";
    out.reserve(eger.length() + 10);
    out.concat()

    // send rest of the number to inttostr and only process back part

    // cleanup zeroes

}

float strtofloat(String string)
{


}


int isnumeric(char c)
{
  return c >= 48 && c <= 57;
}