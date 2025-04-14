#include <Arduino.h>

String s = "This is the end";
String copy;


// substring deepocopy test
void setup()
{
    s = "This is the end";
    copy = s.substring(0);
    Serial.begin(115200);
}

void loop()
{
    if (&s[0] == &copy[0])
    {
        Serial.println("Not deepcopy");
    }

    Serial.println("deepcopy");
}