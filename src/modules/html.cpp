#include "html.h"


// class implementation
String htmlTemplate::format(String html)
{
}

void htmlTemplate::addRule(htmlRule rule)
{
    if (counter < limit) {
        rules[counter] = rule;
    }

    counter++;
}