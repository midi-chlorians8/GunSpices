#pragma once
#include <Arduino.h>

void keyInputFreq(){
    static String inString = "";    // string to hold input
    while (Serial.available() > 0) {
        byte inChar = Serial.read();
        if (isDigit(inChar)) {
          // convert the incoming byte to a char and add it to the string:
          inString += (char)inChar;
        }
        // if you get a newline, print the string, then the string's value:
        if (inChar == '\n') {
          Serial.print(F("Value:"));      Serial.println(inString.toInt());
          //Serial.print(F("String: "));    Serial.println(inString);

          MyServoLf20Ptr->SimpleManagement(inString.toInt());
          //myservo.writeMicroseconds(inString.toInt() );
          // clear the string for new input:
          inString = "";
        }
    }
}