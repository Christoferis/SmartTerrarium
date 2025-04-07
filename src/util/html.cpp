#include "html.h"

// class implementation
String htmlTemplate::format(String html)
{
    return "";
}

void htmlTemplate::addRule(htmlRule rule)
{
    if (counter < limit) {
        rules[counter] = rule;
    }

    counter++;
}