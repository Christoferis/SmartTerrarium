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
    String page;
    htmlRule rules[maxRules];
    int counter = 0;

    htmlRule searchRules(String identifier);
    String format(String html);

public:
    htmlTemplate(String page);
    htmlTemplate();

    void addRule(htmlRule rule);
    String serve();
};



