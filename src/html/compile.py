# minifies and compiles the html to a header file compatible with the project

FILEindex = "src/html/index.html"
FILEtimeset = "src/html/timeset.html"
DEST = "src/html/webpages.h"


header =  """
#pragma once
#include <Arduino.h>

"""


def compile_index():
    index = ""

    # basic opening
    with open(FILEindex, mode="r") as obj:
        for line in obj:
            if (line.strip().startswith("//")):
                continue
            else:
                index += line

    index = index.replace('"', "'").replace("\n", "")
    return index


def compile_timeset():
    index = ""

    # basic opening
    with open(FILEtimeset, mode="r") as obj:
        for line in obj:
            if (line.strip().startswith("//")):
                continue
            else:
                index += line

    index = index.replace('"', "'").replace("\n", "")
    return index


complete = header + 'const String TIMESET = "' + compile_timeset() + '";\n' + 'const String INDEX = "' + compile_index() + '";'


with open(DEST, "w") as page:
    page.write(complete)

