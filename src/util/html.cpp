#include "html.h"


// class implementation
htmlTemplate::htmlTemplate(String page)
{
    // Constructor
    this->page = page;
}

htmlTemplate::htmlTemplate()
{
    // Constructor
}

// this method directly changes the String, copy must be provided as input
String htmlTemplate::format(String html)
{
    //search handles <ph> search2 handles </ph>

    // first tag
    int search = html.indexOf("<ph>", 0);
    int search2 = html.indexOf("</ph>", 0);
    
    // assumption: there always exists a closing tag
    while (search != -1 && search2 != -1 && counter > 0)
    {        
        // create substring, search rules and rarduino eplace
        String tag = html.substring(search + 4, search2);

        // search rule if none, skip
        for (size_t i = 0; i < counter; i++)
        {
            if (rules[i].identifier.equals(tag))
            {
                html.replace("<ph>" + tag + "</ph>", rules[i].function());
                break;
            }
        }

        // no tags or incomplete tag: skip and end, search from same point (only safe option)
        search = html.indexOf("<ph>", search);
        search2 = html.indexOf("</ph>", search);
    }

    return html;
}

void htmlTemplate::addRule(htmlRule rule)
{
    if (counter < maxRules) {
        rules[counter] = rule;
    }

    counter++;
}

String htmlTemplate::serve()
{
    return this->format(page.substring(0));
}