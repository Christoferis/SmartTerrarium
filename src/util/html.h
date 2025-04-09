#pragma once
#include <Arduino.h>

/*
    Basic HTML Templating Engine: replace certain parts in HTML Docs with custom Data!
    To create a placeholder: <ph>placeholder</ph>
*/

#define maxRules 10

typedef String (* htmlReplace)(void);


// htmlRule
struct htmlRule
{
    String identifier;
    htmlReplace function;
};


class htmlTemplate
{
private:
    htmlRule rules[maxRules];
    int counter = 0;

    htmlRule searchRules(String identifier);

public:

    String format(String html);
    void addRule(htmlRule rule);
};

