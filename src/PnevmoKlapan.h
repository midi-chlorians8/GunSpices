#pragma once
#include <Arduino.h>

class PnevmoKlapan{
private:
    #define Klapan_PIN 6
    unsigned long timing; 
    bool oneTimeKlapanOpen = false; // Разок открыть клапан
    bool oneMeasuring = false;
    
public:
    PnevmoKlapan(){
        pinMode(Klapan_PIN,OUTPUT);
        digitalWrite(Klapan_PIN,LOW);
    }
    bool KlapanOpenSingl(uint16_t millisec){ // 200 mc

        if(oneTimeKlapanOpen == false){ // Один раз
            // Один раз замерять текущее время
            if(oneMeasuring == false){
                    digitalWrite(Klapan_PIN,HIGH);
                    timing = millis();
                    oneMeasuring = true;
            }
            // Как чуть прокрутилось - остановить
            if (millis() - timing > millisec and oneMeasuring == true){  // if (millis() - timing > 200 and oneMeasuring == true){
                    digitalWrite(Klapan_PIN,LOW);
                    oneTimeKlapanOpen = true;
            }

        }                            // Один раз
        if(oneTimeKlapanOpen == true){
            return true;
        }else{
            return false;
        }
        
    }
    void KlapanOpenResetSingl(){
            oneMeasuring = false;
            oneTimeKlapanOpen = false;
            digitalWrite(Klapan_PIN,LOW);
    }

};
PnevmoKlapan* MyKlapanPtr = nullptr; // Cоздали указатель