#pragma once
#include <Arduino.h>



class TumblerModes{
private:
      #define TUMBLER_PIN A0
      int mode = 1;
      bool lastModeIsEnded = true;
public:
    TumblerModes(){
        //lcd.clear();
    }
    void ReadTumblerModes(){ //! Новый мод не должен начатся пока не закончился старый
        //Если прошлый режим завершился
 
        if(lastModeIsEnded == true){

              //Читаем аналоговый порт
              if(analogRead(A0) > 900){
                mode = SINGL;
              }
              if(analogRead(A0) < 100){
                mode = REFILL;
              }
               if(analogRead(A0) > 100 and analogRead(A0) < 900 ){
                mode = AUTOO;
              }
       
        }
        
    }
    void SetModeEnded(bool state){
        if(state == true){
            lastModeIsEnded = true;
        }else{
            lastModeIsEnded = false;
        }
    }
    bool GetModeEnded(){
        if(lastModeIsEnded == true){
            return true;
        }
        else{
            return false;
        }
    }
    EModes GetCurrentMode(){
        return static_cast<EModes>(mode); //return (ModesList) mode;     
    }
};
TumblerModes* MyTumblerModesPtr = nullptr; // Cоздали указатель