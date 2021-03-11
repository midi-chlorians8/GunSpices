#pragma once
#include <Arduino.h>

volatile boolean actionState = LOW;

void myEventListener() {
  actionState = HIGH; //
  // Выполняем другие действия, например, включаем или выключаем светодиод
}

class StartButton{
private:

  #define PIN_LED 13
  bool buttonPressed = false; // Лог часть кнопки - Если один раз зацепили = нажата пока режим не завершится
public:
  StartButton(){
      pinMode(2, INPUT_PULLUP);
      pinMode(PIN_LED, OUTPUT);
      attachInterrupt(0, myEventListener, LOW);
  }
  bool ButtonRead(){
    if(actionState == HIGH){
        buttonPressed = HIGH;
        digitalWrite(PIN_LED, buttonPressed);
    }
    if(buttonPressed == HIGH){
        return HIGH;
    }else{
        return LOW;
    }   
  }


void RebootButtonRead(){ //Вернуть чуствительность кнопке
    actionState = LOW;
    buttonPressed = LOW;digitalWrite(PIN_LED, buttonPressed);   
}


};
StartButton* MyStartButtonPtr = nullptr; // Cоздали указатель