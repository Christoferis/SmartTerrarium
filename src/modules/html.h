#pragma once
#include <WString.h>

// various stuff for html templates

//replacement statements must be enclosed using this symbol
#define BRACKETS "%%"

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
    static const int limit = 100;

    htmlRule rules[limit];
    int counter = 0;

public:

    String format(String html);
    void addRule(htmlRule rule);
};

